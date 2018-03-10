#include "main.h"
#include "objects.h"

#ifndef MAN_H
#define MAN_H

class Man {
public:
    Man() {}
    Man(float x, float z, color_t color);
    glm::vec3 position;
    float rotation;
    float roll;
    void draw(glm::mat4 VP);
    void set_position(float x, float z);
    void tick(float wind);
    bounding_box_t bounding_box();

    CubeTextured body;
    Cube plank[6];
};


#endif // MAN_H