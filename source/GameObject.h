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

    virtual const std::pair<float, float>& getPos() const;
    virtual void setPos(std::pair<float, float> p);

    virtual const float& getWidth() const;
    virtual void setWidth(float w);
    virtual const float& getHeight() const;
    virtual void setHeight(float h);

    virtual const std::vector<std::pair<float, float>>& getVertices() const;
};
 
#endif /* GAMEOBJECT_H_ */