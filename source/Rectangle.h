// Evita que este archivo se incluya varias veces
#ifndef RECTANGLE_H_
#define RECTANGLE_H_

// Incluir la clase base GameObject, que se usará para heredar funcionalidades
#include "GameObject.h"

// Definición de la clase Rectangle, que hereda de GameObject
class Rectangle : public GameObject {
private:
    // Método privado que actualiza los vértices del rectángulo
    void updateVertices() override;

    // Método privado que actualiza los índices del rectángulo, pasando un número como parámetro
    void updateIndices(int num) override;

public:
    // Constructor público de la clase Rectangle, que toma posición (pos), ancho (w), alto (h) y un número opcional
    Rectangle(std::pair<float, float> pos, float w, float h, int num = 0);

    // Destructor público de la clase Rectangle
    virtual ~Rectangle();
};

// Fin de la protección contra inclusiones múltiples
#endif /* RECTANGLE_H_ */