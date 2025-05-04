// Barra tipo Pong en OpenGL 3.3 - Movimiento horizontal con teclas
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

#include "GameObject.h"
#include "Rectangle.h"

// Vertex Shader con desplazamiento
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec2 aPos;
uniform float uOffsetX1, uOffsetY1;
uniform float uOffsetX2, uOffsetY2;
uniform float uOffsetX3, uOffsetY3;
uniform float uOffsetX4, uOffsetY4;
uniform float uOffsetX5, uOffsetY5;

void main() {
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


// Fragment Shader simple blanco
const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;
void main() {
    FragColor = vec4(1.0);
})";

template <typename T>
T clamp(T value, T min, T max) {
    return (value < min) ? min : (value > max) ? max : value;
}

// Barra: rectángulo horizontal estrecho
float paddleWidth = 0.05f;
float paddleHeight = 0.4f;
float ballRadius = 0.1f;
Rectangle paddleLeftTop({-0.9f, 0.5f}, paddleWidth, paddleHeight, 0);
Rectangle paddleLeftBottom({-0.9f, -0.5f}, paddleWidth, paddleHeight, 1);
Rectangle paddleRightTop({0.9f, 0.5f}, paddleWidth, paddleHeight, 2);
Rectangle paddleRightBottom({0.9f, -0.5f}, paddleWidth, paddleHeight, 3);
Rectangle ball({0, 0}, ballRadius, ballRadius, 4);

float speedPaddleY = 0.002f;       // Velocidad de movimiento
std::pair<float, float> speedBall = {0.004f, 0.003f};

void processInput(GLFWwindow* window) {
    auto posLeftTop = paddleLeftTop.getPos();
    auto posLeftBottom = paddleLeftBottom.getPos();

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && posLeftTop.second + (paddleLeftTop.getHeight() / 2) + speedPaddleY <= 1) {
        posLeftTop.second += speedPaddleY;
        posLeftBottom.second -= speedPaddleY;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && posLeftTop.second - (paddleLeftTop.getHeight() / 2) - speedPaddleY >= 0) {
        posLeftTop.second -= speedPaddleY;
        posLeftBottom.second += speedPaddleY;
    }

    paddleLeftTop.setPos(posLeftTop);
    paddleLeftBottom.setPos(posLeftBottom);

    auto posRightTop = paddleRightTop.getPos();
    auto posRightBottom = paddleRightBottom.getPos();

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && posRightTop.second + (paddleRightTop.getHeight() / 2) + speedPaddleY <= 1) {
        posRightTop.second += speedPaddleY;
        posRightBottom.second -= speedPaddleY;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && posRightTop.second - (paddleRightTop.getHeight() / 2) - speedPaddleY >= 0) {
        posRightTop.second -= speedPaddleY;
        posRightBottom.second += speedPaddleY;
    }

    paddleRightTop.setPos(posRightTop);
    paddleRightBottom.setPos(posRightBottom);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Inicialización
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Pong", NULL, NULL);
    if (!window) { std::cerr << "Error al crear ventana\n"; glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Fallo al inicializar GLAD\n"; return -1;
    }

    // Shaders
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

    // Buffers
    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    std::vector<float> barVertices;
    barVertices.insert(barVertices.end(), paddleLeftTop.getFlatVertices().begin(), paddleLeftTop.getFlatVertices().end());
    barVertices.insert(barVertices.end(), paddleLeftBottom.getFlatVertices().begin(), paddleLeftBottom.getFlatVertices().end());
    barVertices.insert(barVertices.end(), paddleRightTop.getFlatVertices().begin(), paddleRightTop.getFlatVertices().end());
    barVertices.insert(barVertices.end(), paddleRightBottom.getFlatVertices().begin(), paddleRightBottom.getFlatVertices().end());
    barVertices.insert(barVertices.end(), ball.getFlatVertices().begin(), ball.getFlatVertices().end());

    glBufferData(GL_ARRAY_BUFFER, barVertices.size() * sizeof(float), barVertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    std::vector<int> indices;
    indices.insert(indices.end(), paddleLeftTop.getIndices().begin(), paddleLeftTop.getIndices().end());
    indices.insert(indices.end(), paddleLeftBottom.getIndices().begin(), paddleLeftBottom.getIndices().end());
    indices.insert(indices.end(), paddleRightTop.getIndices().begin(), paddleRightTop.getIndices().end());
    indices.insert(indices.end(), paddleRightBottom.getIndices().begin(), paddleRightBottom.getIndices().end());
    indices.insert(indices.end(), ball.getIndices().begin(), ball.getIndices().end());
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Loop principal
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        auto ballPos = ball.getPos();

        if (ballPos.second + (ball.getHeight() / 2) >= 1 || ballPos.second - (ball.getHeight() / 2) <= -1) {
            speedBall.second *= -1;
        }

        if (ball.isColliding(paddleLeftTop) || ball.isColliding(paddleLeftBottom)) {
            speedBall.first *= -1;
            ballPos.first = paddleLeftTop.getPos().first + (paddleLeftTop.getWidth() / 2) + (ball.getWidth() / 2);
            int aux = speedBall.second > 0 ? 1 : -1;
            speedBall.second = (((rand() % 6) + 1) / 1000.0f) * aux;
        }
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

        ballPos.first += speedBall.first;
        ballPos.second += speedBall.second;
        ball.setPos(ballPos);

        glfwPollEvents();

        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        int offsetX1Loc = glGetUniformLocation(shaderProgram, "uOffsetX1");
        int offsetY1Loc = glGetUniformLocation(shaderProgram, "uOffsetY1");
        int offsetX2Loc = glGetUniformLocation(shaderProgram, "uOffsetX2");
        int offsetY2Loc = glGetUniformLocation(shaderProgram, "uOffsetY2");
        int offsetX3Loc = glGetUniformLocation(shaderProgram, "uOffsetX3");
        int offsetY3Loc = glGetUniformLocation(shaderProgram, "uOffsetY3");
        int offsetX4Loc = glGetUniformLocation(shaderProgram, "uOffsetX4");
        int offsetY4Loc = glGetUniformLocation(shaderProgram, "uOffsetY4");
        int offsetX5Loc = glGetUniformLocation(shaderProgram, "uOffsetX5");
        int offsetY5Loc = glGetUniformLocation(shaderProgram, "uOffsetY5");

        glUniform1f(offsetX1Loc, paddleLeftTop.getPos().first);
        glUniform1f(offsetY1Loc, paddleLeftTop.getPos().second);

        glUniform1f(offsetX2Loc, paddleLeftBottom.getPos().first);
        glUniform1f(offsetY2Loc, paddleLeftBottom.getPos().second);

        glUniform1f(offsetX3Loc, paddleRightTop.getPos().first);
        glUniform1f(offsetY3Loc, paddleRightTop.getPos().second);

        glUniform1f(offsetX4Loc, paddleRightBottom.getPos().first);
        glUniform1f(offsetY4Loc, paddleRightBottom.getPos().second);

        glUniform1f(offsetX5Loc, ball.getPos().first);
        glUniform1f(offsetY5Loc, ball.getPos().second);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6 * 5);

        glfwSwapBuffers(window);
    }

    // Limpieza
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

/*
// Pelota que rebota en los bordes con rebote por ángulo y bordes en azul
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

// Vertex Shader con desplazamiento
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
uniform vec2 uOffset;
void main() {
    gl_Position = vec4(aPos.xy + uOffset, aPos.z, 1.0);
})";

// Fragment Shader con color uniforme
const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;
uniform vec4 uColor;
void main() {
    FragColor = uColor;
})";

// Geometría de la pelota (cuadrado)
float ballVertices[] = {
    -0.025f, -0.025f, 0.0f,
     0.025f, -0.025f, 0.0f,
     0.025f,  0.025f, 0.0f,
    -0.025f,  0.025f, 0.0f
};

unsigned int ballIndices[] = {
    0, 1, 2,
    2, 3, 0
};

// Bordes como líneas
float borderVertices[] = {
    -1.0f, -1.0f, 0.0f,   1.0f, -1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,   1.0f,  1.0f, 0.0f,
     1.0f,  1.0f, 0.0f,  -1.0f,  1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f,  -1.0f, -1.0f, 0.0f
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    // Inicialización de GLFW y OpenGL
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    GLFWwindow* window = glfwCreateWindow(800, 600, "Pelota rebote azul", NULL, NULL);
    if (!window) { std::cerr << "Fallo al crear ventana GLFW\n"; glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Fallo al inicializar GLAD\n"; return -1;
    }

    // Compilación de shaders
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

    // Buffers para la pelota
    GLuint ballVAO, ballVBO, ballEBO;
    glGenVertexArrays(1, &ballVAO);
    glGenBuffers(1, &ballVBO);
    glGenBuffers(1, &ballEBO);
    glBindVertexArray(ballVAO);
    glBindBuffer(GL_ARRAY_BUFFER, ballVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ballVertices), ballVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ballEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ballIndices), ballIndices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Buffers para los bordes
    GLuint borderVAO, borderVBO;
    glGenVertexArrays(1, &borderVAO);
    glGenBuffers(1, &borderVBO);
    glBindVertexArray(borderVAO);
    glBindBuffer(GL_ARRAY_BUFFER, borderVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(borderVertices), borderVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Posición y velocidad de la pelota
    float ballX = 0.0f, ballY = 0.0f;
    float velocidad = 0.005f;
    float angle = ((std::rand() % 360) * 3.1415926f / 180.0f);
    float velocityX = std::cos(angle) * velocidad;
    float velocityY = std::sin(angle) * velocidad;
    float ballRadius = 0.025f;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Movimiento de la pelota
        ballX += velocityX;
        ballY += velocityY;
        float speed = std::sqrt(velocityX * velocityX + velocityY * velocityY);

        // Rebote horizontal (izquierda/derecha)
        if (ballX + ballRadius >= 1.0f || ballX - ballRadius <= -1.0f) {
            float newAngle = ((std::rand() % 60) + 60) * 3.1415926f / 180.0f;
            float dir = (ballX > 0) ? -1.0f : 1.0f;
            velocityX = std::cos(newAngle) * speed * dir;
            velocityY = std::sin(newAngle) * speed * ((std::rand() % 2 == 0) ? 1 : -1);
            ballX = (ballX > 0) ? 1.0f - ballRadius : -1.0f + ballRadius;
        }

        // Rebote vertical (arriba/abajo)
        if (ballY + ballRadius >= 1.0f || ballY - ballRadius <= -1.0f) {
            float newAngle = ((std::rand() % 60) + 30) * 3.1415926f / 180.0f;
            float dir = (ballY > 0) ? -1.0f : 1.0f;
            velocityY = std::sin(newAngle) * speed * dir;
            velocityX = std::cos(newAngle) * speed * ((std::rand() % 2 == 0) ? 1 : -1);
            ballY = (ballY > 0) ? 1.0f - ballRadius : -1.0f + ballRadius;
        }

        // Dibujar escena
        glClearColor(0.05f, 0.05f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);

        int offsetLoc = glGetUniformLocation(shaderProgram, "uOffset");
        int colorLoc  = glGetUniformLocation(shaderProgram, "uColor");

        // Dibujar bordes en azul
        glLineWidth(3.0f);
        glUniform2f(offsetLoc, 0.0f, 0.0f);
        glUniform4f(colorLoc, 0.2f, 0.4f, 1.0f, 1.0f); // Azul
        glBindVertexArray(borderVAO);
        glDrawArrays(GL_LINES, 0, 8);

        // Dibujar pelota en cian
        glUniform2f(offsetLoc, ballX, ballY);
        glUniform4f(colorLoc, 0.2f, 1.0f, 1.0f, 1.0f);
        glBindVertexArray(ballVAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
    }

    // Limpieza
    glDeleteVertexArrays(1, &ballVAO);
    glDeleteBuffers(1, &ballVBO);
    glDeleteBuffers(1, &ballEBO);
    glDeleteVertexArrays(1, &borderVAO);
    glDeleteBuffers(1, &borderVBO);
    glDeleteProgram(shaderProgram);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
*/