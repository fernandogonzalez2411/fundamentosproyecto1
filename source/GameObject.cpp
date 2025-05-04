// Incluir la definición de la clase GameObject
#include "GameObject.h"

// Constructor que inicializa la posición, ancho y alto del objeto usando lista de inicialización
GameObject::GameObject(std::pair<float, float> pos, float w, float h) : position(pos), width(w), height(h) { }

// Método para verificar si este objeto colisiona con otro GameObject
bool GameObject::isColliding(const GameObject& other) {
    // Calcular los bordes del rectángulo A (este objeto)
    float leftA = getPos().first - (getWidth() / 2);
    float rightA = getPos().first + (getWidth() / 2);
    float topA = getPos().second + (getHeight() / 2);
    float bottomA = getPos().second - (getHeight() / 2);

    // Calcular los bordes del rectángulo B (el otro objeto)
    float leftB = other.getPos().first - (other.getWidth() / 2);
    float rightB = other.getPos().first + (other.getWidth() / 2);
    float topB = other.getPos().second + (other.getHeight() / 2);
    float bottomB = other.getPos().second - (other.getHeight() / 2);

    // Verificar si no hay superposición entre los dos rectángulos (no hay colisión)
    if (rightA < leftB || rightB < leftA || topA < bottomB || topB < bottomA) {
        return false; // No colisionan
    }

    return true; // Hay colisión
}

// Getter para obtener la posición del objeto
const std::pair<float, float>& GameObject::getPos() const {
    return position;
}

// Setter para actualizar la posición del objeto
void GameObject::setPos(std::pair<float, float> pos) {
    position = pos;
}

// Getter para obtener el ancho del objeto
const float& GameObject::getWidth() const {
    return width;
}

// Setter para establecer el nuevo ancho del objeto
void GameObject::setWidth(float w) {
    width = w;
}

// Getter para obtener el alto del objeto
const float& GameObject::getHeight() const {
    return height;
}

// Setter para establecer el nuevo alto del objeto
void GameObject::setHeight(float h) {
    height = h;
}

// Getter para obtener los vértices en formato plano (x0, y0, x1, y1, ...)
const std::vector<float>& GameObject::getFlatVertices() const {
    return flatVertices;
}

// Getter para obtener los vértices como una lista de pares (x, y)
const std::vector<std::pair<float, float>> GameObject::getVertices() const {
    std::vector<std::pair<float, float>> vertices; // Vector donde se almacenarán los pares
    int vectorSize = getFlatVertices().size(); // Obtener cantidad de coordenadas

    vertices.reserve(vectorSize / 2); // Reservar espacio para optimizar rendimiento

    // Convertir cada par de coordenadas consecutivas (x, y) en un std::pair y agregarlo al vector
    for (int i = 0; i < vectorSize; i+=2) {
        vertices.emplace_back(flatVertices[i], flatVertices[i + 1]);
    }

    return vertices; // Devolver la lista de vértices como pares
}

// Getter para obtener los índices que indican cómo se deben conectar los vértices para formar triángulos
const std::vector<int>& GameObject::getIndices() const {
    return indices;
}