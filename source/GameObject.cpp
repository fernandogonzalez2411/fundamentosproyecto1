#include "GameObject.h"

GameObject::GameObject(std::pair<float, float> pos, float w, float h) : position(pos), width(w), height(h) { }

const std::pair<float, float>& GameObject::getPos() const {
    return position;
}
void GameObject::setPos(std::pair<float, float> pos) {
    position = pos;
}

const float& GameObject::getWidth() const {
    return width;
}
void GameObject::setWidth(float w) {
    width = w;
}
const float& GameObject::getHeight() const {
    return height;
}
void GameObject::setHeight(float h) {
    height = h;
}

const std::vector<std::pair<float, float>>& GameObject::getVertices() const {
    return vertices;
}