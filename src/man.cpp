#include "man.h"
#include "main.h"
// #include "cube.h"
Man::Man(float x, float z, color_t color) {
    this->position = glm::vec3(x, 0, z);
    this->rotation = 0;
    this->roll = 0;

    // Body
    GLuint textureID = createTexture("../images/hawaii.jpg");
    this->body = CubeTextured(0,9,0,2,2.5,2,textureID);  
    // Neck
    this->plank[0] = Cube(0,10.4,0,0.5,0.5,0.5,COLOR_BROWN);
    // Face
    this->plank[1] = Cube(0,11.25,0,2,1,2,COLOR_BROWN);
    // Leg1 
    this->plank[2] = Cube(0.5,6,0,0.75,2.5,1,COLOR_BROWN);
    // Leg2
    this->plank[3] = Cube(-0.5,6,0,0.75,2.5,1,COLOR_BROWN);
    // Hand1
    this->plank[4] = Cube(1.35,9.3,0,0.75,2,1,COLOR_BROWN);
    this->plank[4].roll = 45;
    // Hand2
    this->plank[5] = Cube(-1.35,9.3,0,0.75,2,1,COLOR_BROWN);
    this->plank[5].roll = 45;


}

void Man::draw(glm::mat4 VP) {
    glUseProgram (ProgramID);

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 roll      = glm::rotate((float) (this->roll * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of Man arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate *roll);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    // draw3DObject(this->object);
    
    for(int i=0;i<6;i++)
        plank[i].draw(MVP);
    body.draw(MVP);

}

void Man::set_position(float x, float z) {
    this->position = glm::vec3(x, 0, z);
}

void Man::tick(float wind){


    // Use Man's direction to update sail

}

bounding_box_t Man::bounding_box() {
    float x = this->position.x, y = this->position.y, z = this->position.z;
    // The error in  z is due to the forward planks
    // Width and depth will also depend on the rotation 
    bounding_box_t bbox = { x, y ,z, 8.0f, 4.0f,17.0f };
    return bbox;
}