#include "Rectangle.h"

Rectangle::Rectangle(std::pair<float, float> pos, float w, float h, int num) : GameObject(pos, w, h) {
    flatVertices.resize(12);
    updateVertices();
    updateIndices(num);
}
Rectangle::~Rectangle() {}

void Rectangle::updateVertices() {
    float halfWidth = width / 2;
    float halfHeight = height / 2;

    flatVertices[0] = -halfWidth;
    flatVertices[1] = halfHeight;
    flatVertices[2] = -halfWidth;
    flatVertices[3] = -halfHeight;
    flatVertices[4] = halfWidth;
    flatVertices[5] = -halfHeight;

    flatVertices[6] = -halfWidth;
    flatVertices[7] = halfHeight;
    flatVertices[8] = halfWidth;
    flatVertices[9] = -halfHeight;
    flatVertices[10] = halfWidth;
    flatVertices[11] = halfHeight;
}

void Rectangle::updateIndices(int num) {
    indices = {0 + (num * 4), 1 + (num * 4), 2 + (num * 4), 2 + (num * 4), 3 + (num * 4), 0 + (num * 4)};
}