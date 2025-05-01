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
const std::vector<float>& GameObject::getFlatVertices() const {
    return flatVertices;
}
const std::vector<std::pair<float, float>> GameObject::getVertices() const {
    std::vector<std::pair<float, float>> vertices;
    vertices.reserve(flatVertices.size() / 2);

    for (int i = 0; i < flatVertices.size(); i+=2) {
        vertices.emplace_back(flatVertices[i], flatVertices[i + 1]);
    }

    return vertices;
}
const std::vector<int>& GameObject::getIndices() const {
    return indices;
}