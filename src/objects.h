#include "main.h"

#ifndef OBJECTS
#define OBJECTS


class Cube {
public:
    Cube() {}
    Cube(float x, float y,float z,float width , float height , float depth,  color_t color);
    glm::vec3 position;
    glm::vec3 speed;
    glm::vec3 dimensions;
    float rotation,roll;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bounding_box_t bounding_box();
private:
    VAO *object;
};

class CubeTextured {
public:
    CubeTextured() {}
    CubeTextured(float x, float y,float z,float width , float height , float depth,  GLuint textureID);
    glm::vec3 position;
    glm::vec3 speed;
    glm::vec3 dimensions;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bounding_box_t bounding_box();
private:
    VAO *object;
};


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
    bounding_box_t bounding_box();

private:
	VAO *object;
};

class Arrow {
public:
    Arrow() {}
    Arrow(float x, float z, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);

private:
    VAO *object;
};


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
    float radius;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

class Sail {
public:
    Sail() {}
    Sail(float x, float y,float z,float length, float height, GLuint textureID);
    glm::vec3 position;
    glm::vec2 dimensions;
    float rotation;
    float roll;
    void draw(glm::mat4 VP);
    void set_position(float x, float y ,float z);
    bool tick();
    bounding_box_t bounding_box();
private:
    VAO *object;
};


class Circle {
public:
    Circle() {}
    Circle(float x, float y,float z,float radius, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y ,float z);
    bool tick();
    double speed;
    double yspeed;
    float radius;
private:
    VAO *object;
};

class VerticalRectangle {
public:
    VerticalRectangle() {}
    VerticalRectangle(float x,float z,  GLuint textureID);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
private:
    VAO *object;
};

#endif // OBJECTS