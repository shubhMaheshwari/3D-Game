#include "prism.h"
#include "main.h"

Prism::Prism(float x,float z,  color_t color) {
    this->position = glm::vec3(x, 0, z);
    this->rotation = 0;
    this->speed = 0.03;
    // depth = 6;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A Prism has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[] = {
       0.0f, 3.0f,0.0f,
       -1.0f,0.0f,1.0f,
       -1.0f,0.0f,-1.0f,

       0.0f, 3.0f,0.0f,
       -1.0f,0.0f,1.0f,
        1.0f,0.0f,1.0f,

        0.0f, 3.0f,0.0f,
        1.0f,0.0f,-1.0f,
       -1.0f,0.0f,-1.0f,

       0.0f, 3.0f,0.0f,
       1.0f,0.0f,-1.0f,
       1.0f,0.0f,1.0f,
    };

    this->object = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data, color, GL_FILL);
}

void Prism::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of Prism arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Prism::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Prism::tick(float x,float z) {


    if(this->position.z > z)
        this->position.z  -= speed;
    else
        this->position.z  += speed;


    if(this->position.x > x)
        this->position.x  -= speed;
    else
        this->position.x  += speed;  

}
