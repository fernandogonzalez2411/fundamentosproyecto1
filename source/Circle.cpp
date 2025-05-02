#include "Circle.h"
#include <cmath>

#define segments 40

Circle::Circle(std::pair<float, float> pos, float r, int num) : GameObject(pos, r * 2, r * 2) {
    flatVertices.resize((segments + 1) * 2);
    updateVertices();
    updateIndices(num);
}
Circle::~Circle() {}

void Circle::updateVertices() {
    float centerX = position.first;
    float centerY = position.second;
    float radius = width / 2;

    flatVertices[0] = centerX;
    flatVertices[1] = centerY;

    for (int i = 0; i < segments; i++) {
        float angle = 2 * M_PI * i / segments;
        float x = centerX + std::cos(angle) * radius;
        float y = centerY + std::sin(angle) * radius;

        flatVertices[(i + 1) * 2] = x;
        flatVertices[(i + 1) * 2 + 1] = y;
    }
}

void Circle::updateIndices(int num) {
    indices.clear();
    for (int i = 1; i < segments; i++) {
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(i + 1);
    }

    indices.push_back(0);
    indices.push_back(segments);
    indices.push_back(1);
}