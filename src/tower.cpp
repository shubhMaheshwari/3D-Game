#include "tower.h"
#include "main.h"
// #include "cube.h"
Tower::Tower(float x, float z, color_t color) {
    this->position = glm::vec3(x, 0, z);
    this->rotation = 0;
    this->roll = 0;


    GLuint TowerTextureID = createTexture("../images/grass.png");

    float k = layer_height;
    for(int i=0;i<num_layers;i++)    
    // left plank
    {
        this->plank[i] =  CubeTextured(0, k*i/2,0, k*(num_layers-i),k/2,k*(num_layers-i)   ,TowerTextureID);
    }

    this->dimensions = glm::vec3(k*num_layers,k*num_layers,k*num_layers);
}

void Tower::draw(glm::mat4 VP) {
    glUseProgram (ProgramID);

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 roll      = glm::rotate((float) (this->roll * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of Tower arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate *roll);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    // draw3DObject(this->object);
    
    for(int i=0;i<num_layers;i++)
        plank[i].draw(MVP);

}

void Tower::set_position(float x, float z) {
    this->position = glm::vec3(x, 0, z);
}

void Tower::tick(float wind){


    // Use Tower's direction to update sail

}

bounding_box_t Tower::bounding_box() {
    float x = this->position.x, y = this->position.y, z = this->position.z;
    float width = this->dimensions.x, height = this->dimensions.y, depth = this->dimensions.z;
     // Error in Height to include jumping of player
    bounding_box_t bbox = { x, y ,z, width, height,depth };  
    return bbox;
}