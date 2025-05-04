// Incluir la definición de la clase Rectangle
#include "Rectangle.h"

// Constructor de la clase Rectangle
// Inicializa la clase base GameObject con posición, ancho y alto
// Redimensiona el vector de vértices planos a 12 elementos (6 vértices * 2 coordenadas cada uno)
// Luego llama a los métodos para actualizar los vértices y los índices
Rectangle::Rectangle(std::pair<float, float> pos, float w, float h, int num) : GameObject(pos, w, h) {
    flatVertices.resize(12); // Reservar espacio para 6 vértices (2 coordenadas por vértice)
    updateVertices(); // Generar la geometría del rectángulo
    updateIndices(num); // Generar los índices para dibujar el rectángulo
}

// Destructor de la clase Rectangle (vacío en este caso)
Rectangle::~Rectangle() {}

// Método para calcular las coordenadas de los vértices del rectángulo
void Rectangle::updateVertices() {
    float halfWidth = width / 2; // Calcular la mitad del ancho
    float halfHeight = height / 2; // Calcular la mitad del alto

    // Definir dos triángulos que forman el rectángulo completo, en orden de dibujo
    // Primer triángulo (vértices 0, 1, 2)
    flatVertices[0] = -halfWidth; // x0
    flatVertices[1] = halfHeight; // y0
    flatVertices[2] = -halfWidth; // x1
    flatVertices[3] = -halfHeight; // y1
    flatVertices[4] = halfWidth; // x2
    flatVertices[5] = -halfHeight; // y2

    // Segundo triángulo (vértices 3, 4, 5)
    flatVertices[6] = -halfWidth; // x3
    flatVertices[7] = halfHeight; // y3
    flatVertices[8] = halfWidth; // x4
    flatVertices[9] = -halfHeight; // y4
    flatVertices[10] = halfWidth; // x5
    flatVertices[11] = halfHeight; // y5
}

// Método para actualizar los índices que definen qué vértices forman los triángulos
// 'num' permite desplazar los índices si hay múltiples rectángulos en un solo buffer
void Rectangle::updateIndices(int num) {
    indices = {
        0 + (num * 4), 1 + (num * 4), 2 + (num * 4), // Primer triángulo
        2 + (num * 4), 3 + (num * 4), 0 + (num * 4) // Segundo triángulo
    };
}