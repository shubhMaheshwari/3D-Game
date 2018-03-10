#include "main.h"
#include "objects.h"

#ifndef BOSS
#define BOSS


class Boss {
public:
    Boss() {}
    Boss(float x, float z, color_t color);
    glm::vec3 position;
    float rotation;
    float roll;
    void draw(glm::mat4 VP);
    void set_position(float x, float z);
    bool tick(float x, float y, float z);
    double speed;
    double yspeed;
    int health; 
    bool alive;
    bounding_box_t bounding_box();


    CubeTextured plank[12];
    Circle circle[6];
};


#endif // BOSS
