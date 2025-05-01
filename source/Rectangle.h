#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "GameObject.h"
 
class Rectangle : public GameObject {
private:
    void updateVertices() override;

public:
    Rectangle(std::pair<float, float> pos, float w, float h);
    virtual ~Rectangle();

    void update() override;

    void setPos(std::pair<float, float> pos) override;
    void setWidth(float w) override;
    void setHeight(float h) override;
};
 
#endif /* RECTANGLE_H_ */