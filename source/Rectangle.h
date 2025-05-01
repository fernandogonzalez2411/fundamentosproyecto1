#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "GameObject.h"
 
class Rectangle : public GameObject {
private:
    void updateVertices() override;
    void updateIndices() override;

public:
    Rectangle(std::pair<float, float> pos, float w, float h);
    virtual ~Rectangle();
};
 
#endif /* RECTANGLE_H_ */