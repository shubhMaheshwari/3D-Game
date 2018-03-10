#include "main.h"
#include "objects.h"

#ifndef TOWER_H
#define TOWER_H
#define num_layers 13
#define layer_height 10

class Tower {
public:
    Tower() {}
    Tower(float x, float z, color_t color);
    glm::vec3 position;
    glm::vec3 dimensions;
    float rotation;
    float roll;
    void draw(glm::mat4 VP);
    void set_position(float x, float z);
    void tick(float wind);
    bounding_box_t bounding_box();


    CubeTextured plank[num_layers];
};


#endif // TOWER_H