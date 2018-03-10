#include "boss.h"
#include "main.h"
// #include "cube.h"
Boss::Boss(float x, float z, color_t color) {
    this->position = glm::vec3(x, 0, z);
    this->rotation = 0;
    this->roll = 0;
    this->speed = 0.05;
    this->yspeed = 0;
    this->alive = false;
    this->health = -1;


    GLuint BossTextureID = createTexture("../images/snake.jpg");    
    // left plank
    this->plank[0] =  CubeTextured(0, 0,0, 2,2,2   ,BossTextureID);
    this->plank[1] =  CubeTextured(0, 3	,0, 4,4,4   ,BossTextureID);

    this->plank[2] =  CubeTextured(0,6,0, 2,2,2   ,BossTextureID);
    this->plank[3] =  CubeTextured(0, 9	,0, 4,4,4   ,BossTextureID);

    this->plank[4] =  CubeTextured(0, 12,0, 2,2,2   ,BossTextureID);

    this->plank[5] = CubeTextured(0,15,0,10,5,10,BossTextureID);

    this->circle[0] = Circle(2.7,16,5.1,1,COLOR_BLACK);
    this->circle[1] = Circle(-2.7,16,5.1,1,COLOR_BLACK);
    this->circle[2] = Circle(0,14,5.1,1.8,COLOR_BLACK);

    this->circle[3] = Circle(2.7,16,-5.1,1,COLOR_BLACK);
    this->circle[4] = Circle(-2.7,16,-5.1,1,COLOR_BLACK);
    this->circle[5] = Circle(0,14,-5.1,1.8,COLOR_BLACK);
}

void Boss::draw(glm::mat4 VP) {

	if(!this->alive)
		return;

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation), glm::vec3(0, 1, 0));
    glm::mat4 roll      = glm::rotate((float) (this->roll * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of Boss arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate *roll);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    
    for(int i=0;i<6;i++){
        plank[i].draw(MVP);
    }


    for (int i = 0; i < 6; ++i)
    	this->circle[i].draw(MVP);


}

void Boss::set_position(float x, float z) {
    this->position = glm::vec3(x, 0, z);
}

bool Boss::tick(float x,float y, float z){
	if(!this->alive)
		return false;	

	if(this->health < 0){
		this->alive = false;
		return true;
	}

	this->rotation = -80 - atan((z - this->position.z)/(x - this->position.x));

	if(this->position.z > z)
        this->position.z  -= speed ;
    else
        this->position.z  += speed;


    if(this->position.x > x)
        this->position.x  -= speed + 0.02*(rand()%4);
    else
        this->position.x  += speed - 0.02*(rand()%4);

    return false;


}

bounding_box_t Boss::bounding_box() {
    float x = this->position.x, y = this->position.y, z = this->position.z;
    // The error in  z is due to the forward planks
    // Width and depth will also depend on the rotation 
    bounding_box_t bbox = { x, y ,z, 2.0f, 20.0f,2.0f };
    return bbox;
}