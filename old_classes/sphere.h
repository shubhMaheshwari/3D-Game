#include "main.h"

#ifndef SPHERE_H
#define SPHERE_H


class Sphere {
public:
    Sphere() {}
    Sphere(float x, float y,float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y ,float z);
    bool tick();
    double speed;
    double yspeed;
private:
    VAO *object;
};

#endif // SPHERE_H
