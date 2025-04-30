#include "Paddle.h"

Paddle::Paddle(std::pair<float, float> pos, float w, float h) : GameObject(pos, w, h) {
    makeNewVertices();
}

void Paddle::update() {

}

void Paddle::makeNewVertices() {
    vertices.clear();
    vertices.reserve(4);

    float halfW = width / 2;
    float halfH = height / 2;

    vertices.emplace_back(position.first - halfW, position.second + halfH);
    vertices.emplace_back(position.first - halfW, position.second - halfH);
    vertices.emplace_back(position.first + halfW, position.second - halfH);
    vertices.emplace_back(position.first + halfW, position.second + halfH);
}

void Paddle::setPos(std::pair<float, float> pos) {
    position = pos;
    makeNewVertices();
}