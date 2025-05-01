#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "GameObject.h"
 
class Circle : public GameObject {
private:
    void updateVertices() override;
    void updateIndices() override;

public:
    Circle(std::pair<float, float> pos, float r);
    virtual ~Circle();
};
 
#endif /* CIRCLE_H_ */