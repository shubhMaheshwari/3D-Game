#include "cube.h"
#include "main.h"

Cube::Cube(float x, float y,float z, float width , float height , float depth,  color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->speed = glm::vec3(0, 0, 0);
    // depth = 6;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[] = {
        -width/2.0f ,-height/2.0f ,-depth/2.0f, // triangle 1 : begin
        -width/2.0f ,-height/2.0f , depth/2.0f,
        -width/2.0f , height/2.0f , depth/2.0f, // triangle 1 : end

        width/2.0f , height/2.0f ,-depth/2.0f, // triangle 2 : begin
        -width/2.0f ,-height/2.0f ,-depth/2.0f,
        -width/2.0f , height/2.0f ,-depth/2.0f, // triangle 2 : end

        width/2.0f ,-height/2.0f , depth/2.0f,
        -width/2.0f ,-height/2.0f ,-depth/2.0f,
        width/2.0f ,-height/2.0f ,-depth/2.0f,

        width/2.0f , height/2.0f ,-depth/2.0f,
        width/2.0f ,-height/2.0f ,-depth/2.0f,
        -width/2.0f ,-height/2.0f ,-depth/2.0f,

        -width/2.0f ,-height/2.0f ,-depth/2.0f,
        -width/2.0f , height/2.0f , depth/2.0f,
        -width/2.0f , height/2.0f ,-depth/2.0f,

        width/2.0f ,-height/2.0f , depth/2.0f,
        -width/2.0f ,-height/2.0f , depth/2.0f,
        -width/2.0f ,-height/2.0f ,-depth/2.0f,

        -width/2.0f , height/2.0f , depth/2.0f,
        -width/2.0f ,-height/2.0f , depth/2.0f,
        width/2.0f ,-height/2.0f , depth/2.0f,

        width/2.0f , height/2.0f , depth/2.0f,
        width/2.0f ,-height/2.0f ,-depth/2.0f,
        width/2.0f , height/2.0f ,-depth/2.0f,

        width/2.0f ,-height/2.0f ,-depth/2.0f,
        width/2.0f , height/2.0f , depth/2.0f,
        width/2.0f ,-height/2.0f , depth/2.0f,

        width/2.0f , height/2.0f , depth/2.0f,
        width/2.0f , height/2.0f ,-depth/2.0f,
        -width/2.0f , height/2.0f ,-depth/2.0f,

        width/2.0f , height/2.0f , depth/2.0f,
        -width/2.0f , height/2.0f ,-depth/2.0f,
        -width/2.0f , height/2.0f , depth/2.0f,

        width/2.0f , height/2.0f , depth/2.0f,
        -width/2.0f , height/2.0f , depth/2.0f,
        width/2.0f ,-height/2.0f , depth/2.0f
    };

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
}

void Cube::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Cube::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Cube::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}
