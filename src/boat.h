#include "main.h"
#include "objects.h"
#include "man.h"

#ifndef BOAT_H
#define BOAT_H


class Boat {
public:
    Boat() {}
    Boat(float x, float z, color_t color);
    glm::vec3 position;
    float rotation;
    float roll;
    void draw(glm::mat4 VP);
    void set_position(float x, float z);
    void tick(float wind);
    double speed;
    double yspeed;
    bool jumping;
    bool sail_on;
    float on_water;
    bounding_box_t bounding_box();


    CubeTextured plank[8];
    Sail sail;
    Arrow arrow;
    Man man;
};


#endif // BOAT_H
