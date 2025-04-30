#ifndef PADDLE_H_
#define PADDLE_H_

#include "GameObject.h"
 
class Paddle : public GameObject {
public:
    Paddle(std::pair<float, float> pos, float w, float h);
    virtual ~Paddle();

    void update() override;
    void makeNewVertices();

    void setPos(std::pair<float, float> pos) override;
};
 
#endif /* PADDLE_H_ */