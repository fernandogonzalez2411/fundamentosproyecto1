// Barra tipo Pong en OpenGL 3.3 - Movimiento horizontal con teclas
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

#include "GameObject.h"
#include "Rectangle.h"

// Vertex Shader con desplazamiento para múltiples objetos (barras y pelota)
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec2 aPos;
uniform float uOffsetX1, uOffsetY1;
uniform float uOffsetX2, uOffsetY2;
uniform float uOffsetX3, uOffsetY3;
uniform float uOffsetX4, uOffsetY4;
uniform float uOffsetX5, uOffsetY5;

void main() {
    // Selecciona el desplazamiento correspondiente dependiendo del ID del vértice
    if (gl_VertexID < 6) {
        gl_Position = vec4(aPos.x + uOffsetX1, aPos.y + uOffsetY1, 0.0, 1.0);
    } else if (gl_VertexID < 12) {
        gl_Position = vec4(aPos.x + uOffsetX2, aPos.y + uOffsetY2, 0.0, 1.0);
    } else if (gl_VertexID < 18) {
        gl_Position = vec4(aPos.x + uOffsetX3, aPos.y + uOffsetY3, 0.0, 1.0);
    } else if (gl_VertexID < 24) {
        gl_Position = vec4(aPos.x + uOffsetX4, aPos.y + uOffsetY4, 0.0, 1.0);
    } else if (gl_VertexID < 30) {
        gl_Position = vec4(aPos.x + uOffsetX5, aPos.y + uOffsetY5, 0.0, 1.0);
    }
})";

// Fragment Shader que pinta todo de blanco
const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;
void main() {
    FragColor = vec4(1.0); // Color blanco
})";

// Función genérica para limitar un valor entre un mínimo y máximo
template <typename T>
T clamp(T value, T min, T max) {
    return (value < min) ? min : (value > max) ? max : value;
}

// Definición de tamaños y creación de objetos del juego
float paddleWidth = 0.05f;
float paddleHeight = 0.4f;
float ballRadius = 0.1f;

// Inicialización de las barras y la pelota
Rectangle paddleLeftTop({-0.9f, 0.5f}, paddleWidth, paddleHeight, 0);
Rectangle paddleLeftBottom({-0.9f, -0.5f}, paddleWidth, paddleHeight, 1);
Rectangle paddleRightTop({0.9f, 0.5f}, paddleWidth, paddleHeight, 2);
Rectangle paddleRightBottom({0.9f, -0.5f}, paddleWidth, paddleHeight, 3);
Rectangle ball({0, 0}, ballRadius, ballRadius, 4);

float speedPaddleY = 0.002f; // Velocidad de las barras
std::pair<float, float> speedBall = {0.004f, 0.003f}; // Velocidad de la pelota (X, Y)
float speedMultiplier = 1.0f; // Multiplicador de Velocidad (para adaptarlo a diferentes computadoras debido a la ausencia de deltaTime)

// Procesa la entrada del teclado para mover las barras
void processInput(GLFWwindow* window) {
    auto posLeftTop = paddleLeftTop.getPos();
    auto posLeftBottom = paddleLeftBottom.getPos();

    // Movimiento hacia arriba de la barra izquierda
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && posLeftTop.second + (paddleLeftTop.getHeight() / 2) + speedPaddleY*speedMultiplier <= 1) {
        posLeftTop.second += speedPaddleY*speedMultiplier;
        posLeftBottom.second -= speedPaddleY*speedMultiplier;
    }
    // Movimiento hacia abajo de la barra izquierda
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && posLeftTop.second - (paddleLeftTop.getHeight() / 2) - speedPaddleY*speedMultiplier >= 0) {
        posLeftTop.second -= speedPaddleY*speedMultiplier;
        posLeftBottom.second += speedPaddleY*speedMultiplier;
    }

    // Aplicar nueva posición
    paddleLeftTop.setPos(posLeftTop);
    paddleLeftBottom.setPos(posLeftBottom);

    auto posRightTop = paddleRightTop.getPos();
    auto posRightBottom = paddleRightBottom.getPos();

    // Movimiento hacia arriba de la barra derecha
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && posRightTop.second + (paddleRightTop.getHeight() / 2) + speedPaddleY*speedMultiplier <= 1) {
        posRightTop.second += speedPaddleY*speedMultiplier;
        posRightBottom.second -= speedPaddleY*speedMultiplier;
    }
    // Movimiento hacia abajo de la barra derecha
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && posRightTop.second - (paddleRightTop.getHeight() / 2) - speedPaddleY*speedMultiplier >= 0) {
        posRightTop.second -= speedPaddleY*speedMultiplier;
        posRightBottom.second += speedPaddleY*speedMultiplier;
    }

    // Aplicar nueva posición
    paddleRightTop.setPos(posRightTop);
    paddleRightBottom.setPos(posRightBottom);
}

// Callback para ajustar el viewport cuando cambia el tamaño de la ventana
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr))); // Semilla aleatoria

    // Inicialización de GLFW y configuración de versión de OpenGL
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Crear ventana
    GLFWwindow* window = glfwCreateWindow(800, 800, "Pong", NULL, NULL);
    if (!window) { std::cerr << "Error al crear ventana\n"; glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Inicializar GLAD para manejar punteros de funciones de OpenGL
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Fallo al inicializar GLAD\n"; return -1;
    }

    // Compilación y enlace de shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Crear buffers de vértices y de índices
    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Combinar vértices de las 4 barras y la pelota
    std::vector<float> barVertices;
    barVertices.insert(barVertices.end(), paddleLeftTop.getFlatVertices().begin(), paddleLeftTop.getFlatVertices().end());
    barVertices.insert(barVertices.end(), paddleLeftBottom.getFlatVertices().begin(), paddleLeftBottom.getFlatVertices().end());
    barVertices.insert(barVertices.end(), paddleRightTop.getFlatVertices().begin(), paddleRightTop.getFlatVertices().end());
    barVertices.insert(barVertices.end(), paddleRightBottom.getFlatVertices().begin(), paddleRightBottom.getFlatVertices().end());
    barVertices.insert(barVertices.end(), ball.getFlatVertices().begin(), ball.getFlatVertices().end());

    // Cargar vértices en el buffer
    glBufferData(GL_ARRAY_BUFFER, barVertices.size() * sizeof(float), barVertices.data(), GL_STATIC_DRAW);

    // Cargar índices en el buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    std::vector<int> indices;
    indices.insert(indices.end(), paddleLeftTop.getIndices().begin(), paddleLeftTop.getIndices().end());
    indices.insert(indices.end(), paddleLeftBottom.getIndices().begin(), paddleLeftBottom.getIndices().end());
    indices.insert(indices.end(), paddleRightTop.getIndices().begin(), paddleRightTop.getIndices().end());
    indices.insert(indices.end(), paddleRightBottom.getIndices().begin(), paddleRightBottom.getIndices().end());
    indices.insert(indices.end(), ball.getIndices().begin(), ball.getIndices().end());
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), indices.data(), GL_STATIC_DRAW);

    // Configurar atributo de vértice
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Bucle principal del juego
    while (!glfwWindowShouldClose(window)) {
        processInput(window); // Leer teclas y actualizar barras

        auto ballPos = ball.getPos();

        // Rebote vertical de la pelota
        if (ballPos.second + (ball.getHeight() / 2) >= 1 || ballPos.second - (ball.getHeight() / 2) <= -1) {
            speedBall.second *= -1;
        }

        // Colisión con barra izquierda
        if (ball.isColliding(paddleLeftTop) || ball.isColliding(paddleLeftBottom)) {
            speedBall.first *= -1;
            ballPos.first = paddleLeftTop.getPos().first + (paddleLeftTop.getWidth() / 2) + (ball.getWidth() / 2);
            int aux = speedBall.second > 0 ? 1 : -1;
            speedBall.second = (((rand() % 6) + 1) / 1000.0f) * aux;
        }
        // Colisión con barra derecha
        else if (ball.isColliding(paddleRightTop) || ball.isColliding(paddleRightBottom)) {
            speedBall.first *= -1;
            ballPos.first = paddleRightTop.getPos().first - (paddleRightTop.getWidth() / 2) - (ball.getWidth() / 2);
            int aux = speedBall.second > 0 ? 1 : -1;
            speedBall.second = (((rand() % 6) + 1) / 1000.0f) * aux;
        }
        else if (ballPos.first - (ball.getWidth() / 2) <= -1 || ballPos.first + (ball.getWidth() / 2) >= 1) {
            ballPos = {0, 0};
            speedBall.first *= -1;
        }

        // Actualizar posición de la pelota
        ballPos.first += speedBall.first*speedMultiplier;
        ballPos.second += speedBall.second*speedMultiplier;
        ball.setPos(ballPos);

        // Renderizado
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        // Enviar offsets de posición a los shaders
        glUniform1f(glGetUniformLocation(shaderProgram, "uOffsetX1"), paddleLeftTop.getPos().first);
        glUniform1f(glGetUniformLocation(shaderProgram, "uOffsetY1"), paddleLeftTop.getPos().second);
        glUniform1f(glGetUniformLocation(shaderProgram, "uOffsetX2"), paddleLeftBottom.getPos().first);
        glUniform1f(glGetUniformLocation(shaderProgram, "uOffsetY2"), paddleLeftBottom.getPos().second);
        glUniform1f(glGetUniformLocation(shaderProgram, "uOffsetX3"), paddleRightTop.getPos().first);
        glUniform1f(glGetUniformLocation(shaderProgram, "uOffsetY3"), paddleRightTop.getPos().second);
        glUniform1f(glGetUniformLocation(shaderProgram, "uOffsetX4"), paddleRightBottom.getPos().first);
        glUniform1f(glGetUniformLocation(shaderProgram, "uOffsetY4"), paddleRightBottom.getPos().second);
        glUniform1f(glGetUniformLocation(shaderProgram, "uOffsetX5"), ball.getPos().first);
        glUniform1f(glGetUniformLocation(shaderProgram, "uOffsetY5"), ball.getPos().second);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6 * 5);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Liberar recursos
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}