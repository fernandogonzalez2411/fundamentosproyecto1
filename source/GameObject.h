// Evita que este archivo se incluya varias veces
#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

// Incluir utilidades estándar: std::pair y contenedor vector
#include <utility>
#include <vector>

// Declaración de la clase base GameObject
// Esta clase representa un objeto genérico en un espacio 2D
class GameObject {
protected:
    std::pair<float, float> position; // Posición (x, y) del objeto

    float width; // Ancho del objeto
    float height; // Alto del objeto

    std::vector<float> flatVertices; // Lista de vértices en formato plano (x0, y0, x1, y1, ...)
    std::vector<int> indices; // Índices que indican cómo conectar los vértices para formar triángulos

    // Métodos virtuales puros que deben ser implementados por las clases derivadas
    // Sirven para actualizar la geometría del objeto
    virtual void updateVertices() = 0;
    virtual void updateIndices(int num) = 0;

public:
    // Constructor que inicializa la posición, ancho y alto del objeto
    GameObject(std::pair<float, float> pos, float w, float h);

    // Destructor virtual (vacío)
    virtual ~GameObject() {}

    // Método para verificar si hay colisión con otro GameObject
    virtual bool isColliding(const GameObject& other);

    // Getters y setters para posición, ancho, alto, vértices e índices

    const std::pair<float, float>& getPos() const; // Obtener posición
    virtual void setPos(std::pair<float, float> pos); // Establecer nueva posición

    const float& getWidth() const; // Obtener ancho
    virtual void setWidth(float w); // Establecer nuevo ancho

    const float& getHeight() const; // Obtener alto
    virtual void setHeight(float h); // Establecer nuevo alto

    const std::vector<float>& getFlatVertices() const; // Obtener vértices planos
    const std::vector<std::pair<float, float>> getVertices() const; // Obtener vértices como pares (x, y)
    const std::vector<int>& getIndices() const; // Obtener índices de dibujo
};

// Fin de la protección contra inclusiones múltiples
#endif /* GAMEOBJECT_H_ */