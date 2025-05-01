#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <utility>
#include <vector>
 
class GameObject {
protected:
    std::pair<float, float> position;

    float width;
    float height;

    std::vector<float> flatVertices;
    std::vector<int> indices;

    virtual void updateVertices() = 0;

public:
    GameObject(std::pair<float, float> pos, float w, float h);
    virtual ~GameObject() {}

    virtual void update() = 0;

    const std::pair<float, float>& getPos() const;
    virtual void setPos(std::pair<float, float> pos);
    const float& getWidth() const;
    virtual void setWidth(float w);
    const float& getHeight() const;
    virtual void setHeight(float h);
    const std::vector<float>& getFlatVertices() const;
    const std::vector<std::pair<float, float>> getVertices() const;
    const std::vector<int>& getIndices() const;
};
 
#endif /* GAMEOBJECT_H_ */