#include "Rectangle.h"

Rectangle::Rectangle(std::pair<float, float> pos, float w, float h) : GameObject(pos, w, h) {
    flatVertices.resize(8);
    updateVertices();
    indices = {0, 1, 2, 2, 3, 0};
}
Rectangle::~Rectangle() {}

void Rectangle::updateVertices() {
    float halfW = width / 2;
    float halfH = height / 2;

    flatVertices[0] = position.first - halfW;
    flatVertices[1] = position.second + halfH;
    flatVertices[2] = position.first - halfW;
    flatVertices[3] = position.second - halfH;
    flatVertices[4] = position.first + halfW;
    flatVertices[5] = position.second - halfH;
    flatVertices[6] = position.first + halfW;
    flatVertices[7] = position.second + halfH;
}

void Rectangle::update() {

}

void Rectangle::setPos(std::pair<float, float> pos) {
    position = pos;
    updateVertices();
}
void Rectangle::setWidth(float w) {
    width = w;
    updateVertices();
}
void Rectangle::setHeight(float h) {
    height = h;
    updateVertices();
}