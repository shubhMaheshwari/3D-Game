#include "main.h"

#ifndef PRISM_H
#define PRISM_H


class Prism {
public:
    Prism() {}
    Prism(float x, float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float z);
    void tick(float x,float z);
    double speed;


private:
	VAO *object;
};


#endif // BOAT_H
