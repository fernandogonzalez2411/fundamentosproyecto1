#include "Rectangle.h"

Rectangle::Rectangle(std::pair<float, float> pos, float w, float h, int num) : GameObject(pos, w, h) {
    flatVertices.resize(12);
    updateVertices();
    updateIndices(num);
}
Rectangle::~Rectangle() {}

void Rectangle::updateVertices() {
    float halfW = width / 2;
    float halfH = height / 2;

    float left = position.first - halfW;
    float right = position.first + halfW;
    float top = position.second + halfH;
    float bottom = position.second - halfH;

    flatVertices[0] = left;
    flatVertices[1] = top;
    flatVertices[2] = left;
    flatVertices[3] = bottom;
    flatVertices[4] = right;
    flatVertices[5] = bottom;

    flatVertices[6] = left;
    flatVertices[7] = top;
    flatVertices[8] = right;
    flatVertices[9] = bottom;
    flatVertices[10] = right;
    flatVertices[11] = top;
}

void Rectangle::updateIndices(int num) {
    indices = {0 + (num * 4), 1 + (num * 4), 2 + (num * 4), 2 + (num * 4), 3 + (num * 4), 0 + (num * 4)};
}