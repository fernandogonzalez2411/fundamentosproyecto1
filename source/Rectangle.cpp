#include "Rectangle.h"

Rectangle::Rectangle(std::pair<float, float> pos, float w, float h, int num) : GameObject(pos, w, h) {
    flatVertices.resize(12);
    updateVertices();
    updateIndices(num);
}
Rectangle::~Rectangle() {}

void Rectangle::updateVertices() {
    float side = width / 2;
    float otherSide = height / 2;

    flatVertices[0] = -side;
    flatVertices[1] = otherSide;
    flatVertices[2] = -side;
    flatVertices[3] = -otherSide;
    flatVertices[4] = side;
    flatVertices[5] = -otherSide;

    flatVertices[6] = -side;
    flatVertices[7] = otherSide;
    flatVertices[8] = side;
    flatVertices[9] = -otherSide;
    flatVertices[10] = side;
    flatVertices[11] = otherSide;
}

void Rectangle::updateIndices(int num) {
    indices = {0 + (num * 4), 1 + (num * 4), 2 + (num * 4), 2 + (num * 4), 3 + (num * 4), 0 + (num * 4)};
}