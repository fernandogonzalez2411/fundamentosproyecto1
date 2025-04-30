#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <utility>
#include <vector>
 
class GameObject {
protected:
    std::pair<float, float> position;

    float width;
    float height;

    std::vector<std::pair<float, float>> vertices;

public:
    GameObject(std::pair<float, float> pos, float w, float h);
    virtual ~GameObject() {}

    virtual void update() = 0;

    const std::pair<float, float>& getPos() const;
    virtual void setPos(std::pair<float, float> pos);

    const float& getWidth() const;
    void setWidth(float w);
    const float& getHeight() const;
    void setHeight(float h);

    const std::vector<std::pair<float, float>>& getVertices() const;
};
 
#endif /* GAMEOBJECT_H_ */