#include "boat.h"
#include "main.h"
// #include "cube.h"
Boat::Boat(float x, float z, color_t color) {
    this->position = glm::vec3(x, 0, z);
    this->rotation = 0;
    this->roll = 0;
    this->jumping = false;
    this->speed = 0;
    this->yspeed = 0;


    GLuint boatTextureID = createTexture("../images/boat.jpg");    
    // left plank
    this->plank[0] =  CubeTextured(-4, 0,0, 0.4,8,12   ,boatTextureID);
    // right plank
    this->plank[1] =  CubeTextured( 4, 0,0, 0.4,8,12   ,boatTextureID);
    // bottom plank 
    this->plank[2] =  CubeTextured( 0, 1,0, 7.6,0.4,12 ,boatTextureID);
    // back plank
    this->plank[3] =   CubeTextured( 0, 0,6, 7.6,8,0.4 ,boatTextureID);
    // front head 1
    this->plank[4] =   CubeTextured(2,0, -8 ,0.4,8,8, boatTextureID);
    this->plank[4].rotation = 30;
    // front head 2
    this->plank[5] =   CubeTextured(-2,0, -8 ,0.4,8,8, boatTextureID);;
    this->plank[5].rotation = -30;

    GLuint sailTextureID = createTexture("../images/barrel.jpg");
    this->sail =  Rectangle(0,7,-0.5,6,17, sailTextureID);
    // this->sail.rotation = 90;
}

void Boat::draw(glm::mat4 VP) {
    glUseProgram (ProgramID);

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 roll      = glm::rotate((float) (this->roll * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of Boat arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate *roll);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    // draw3DObject(this->object);
    
    for(int i=0;i<6;i++)
        plank[i].draw(MVP);

    // sail.draw(MVP);

}

void Boat::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Boat::tick(){

    this->position.y += yspeed;

    this->position.z += speed*cos(rotation*M_PI/180.0f);   
    this->position.x += speed*sin(rotation*M_PI/180.0f);   

    if(this->position.y > 0)
        yspeed -= 0.006;
    else{
        this->position.y = 0;
        yspeed = 0;
        this->jumping = false;
    }

    // Use boat's direction to update sail
    sail.rotation = (int)(this->rotation/5)%60;
    
    if (sail.rotation < -15.0f)
        sail.rotation = -15.0f;

    else if (sail.rotation > 15.0f)
        sail.rotation = 15.0f;




}

bounding_box_t Boat::bounding_box() {
    float x = this->position.x, y = this->position.y, z = this->position.z;
    // The error in  z is due to the forward planks
    // Width and depth will also depend on the rotation 
    bounding_box_t bbox = { x, y + 2,z - 3.5, 8.0f, 4.0f,17.0f };
    return bbox;
}