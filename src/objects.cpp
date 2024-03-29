#include "objects.h"
#include "main.h"

// Define Cube

Cube::Cube(float x, float y,float z, float width , float height , float depth,  color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->speed = glm::vec3(0, 0, 0);
    this->dimensions  = glm::vec3(width,height,depth);
    this->roll = 0;

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

    glUseProgram (ProgramID);


    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 roll      = glm::rotate((float) (this->roll * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate*roll);
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

bounding_box_t Cube::bounding_box() {
    float x = this->position.x, y = this->position.y, z = this->position.z;
    float width = this->dimensions.x, height = this->dimensions.y, depth = this->dimensions.z;
    bounding_box_t bbox = { x, y,z, width, height, depth };
    return bbox;
}


CubeTextured::CubeTextured(float x, float y,float z, float width , float height , float depth,  GLuint textureID) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->speed = glm::vec3(0, 0, 0);
    this->dimensions  = glm::vec3(width,height,depth);
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cubeTextured has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
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

    GLfloat texture_buffer_data [] = {
        0,1, // TexCoord 1 - bot left
        1,1, // TexCoord 2 - bot right
        1,0, // TexCoord 3 - top right

        1,0, // TexCoord 3 - top right
        0,0, // TexCoord 4 - top left
        0,1,  // TexCoord 1 - bot left

        0,1, // TexCoord 1 - bot left
        1,1, // TexCoord 2 - bot right
        1,0, // TexCoord 3 - top right

        1,0, // TexCoord 3 - top right
        0,0, // TexCoord 4 - top left
        0,1,  // TexCoord 1 - bot left

        0,1, // TexCoord 1 - bot left
        1,1, // TexCoord 2 - bot right
        1,0, // TexCoord 3 - top right

        1,0, // TexCoord 3 - top right
        0,0, // TexCoord 4 - top left
        0,1,  // TexCoord 1 - bot left


        0,1, // TexCoord 1 - bot left
        1,1, // TexCoord 2 - bot right
        1,0, // TexCoord 3 - top right

        1,0, // TexCoord 3 - top right
        0,0, // TexCoord 4 - top left
        0,1,  // TexCoord 1 - bot left


        0,1, // TexCoord 1 - bot left
        1,1, // TexCoord 2 - bot right
        1,0, // TexCoord 3 - top right

        1,0, // TexCoord 3 - top right
        0,0, // TexCoord 4 - top left
        0,1,  // TexCoord 1 - bot left


        0,1, // TexCoord 1 - bot left
        1,1, // TexCoord 2 - bot right
        1,0, // TexCoord 3 - top right

        1,0, // TexCoord 3 - top right
        0,0, // TexCoord 4 - top left
        0,1  // TexCoord 1 - bot left

    };

    this->object = create3DTexturedObject(GL_TRIANGLES, 12*3, vertex_buffer_data, texture_buffer_data, textureID, GL_FILL);
}

void CubeTextured::draw(glm::mat4 VP) {

    glUseProgram (textureProgramID);


    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cubeTextured arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.TexMatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DTexturedObject(this->object);
}

void CubeTextured::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void CubeTextured::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

bounding_box_t CubeTextured::bounding_box() {
    float x = this->position.x, y = this->position.y, z = this->position.z;
    float width = this->dimensions.x, height = this->dimensions.y, depth = this->dimensions.z;
    bounding_box_t bbox = { x, y,z, width, height, depth };
    return bbox;
}


Prism::Prism(float x,float z,  color_t color) {
    this->position = glm::vec3(x, 0, z);
    this->rotation = 0;
    this->speed = 0.03;
    // depth = 6;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A Prism has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[] = {
       0.0f, 6.0f,0.0f,
       -2.0f,0.0f,2.0f,
       -2.0f,0.0f,-2.0f,

       0.0f, 6.0f,0.0f,
       -2.0f,0.0f,2.0f,
        2.0f,0.0f,2.0f,

        0.0f, 6.0f,0.0f,
        2.0f,0.0f,-2.0f,
       -2.0f,0.0f,-2.0f,

       0.0f, 6.0f,0.0f,
       2.0f,0.0f,-2.0f,
       2.0f,0.0f,2.0f,
    };

    this->object = create3DObject(GL_TRIANGLES, 4*3, vertex_buffer_data, color, GL_FILL);
}


// Define Prism

void Prism::draw(glm::mat4 VP) {

    glUseProgram (ProgramID);
    
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

    // Adding Randomization for fun

    if(this->position.z > z)
        this->position.z  -= speed ;
    else
        this->position.z  += speed;


    if(this->position.x > x)
        this->position.x  -= speed + 0.02*(rand()%4);
    else
        this->position.x  += speed - 0.02*(rand()%4);  

}

bounding_box_t Prism::bounding_box() {
    float x = this->position.x, y = this->position.y, z = this->position.z;
    bounding_box_t bbox = { x, y + 3.0,z, 2, 3, 2 };
    return bbox;
}

// Define Arrow
Arrow::Arrow(float x,float z,  color_t color) {
    this->position = glm::vec3(x, 2, z);
    this->rotation = 0;
    // depth = 6;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A Prism has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[] = {
        0.0,0.0,-2.0,
        1.0,0.0,0.0,
        -1.0,0.0,0.0,

        0.5,0.0,0.0,
        0.5,0.0,4.0,
        -0.5,0.0,0.0,

        -0.5,0.0,0.0,
        0.5,0.0,4.0,
        -0.5,0.0,4.0,
    };

    this->object = create3DObject(GL_TRIANGLES, 3*3, vertex_buffer_data, color, GL_FILL);
}


// Define Prism

void Arrow::draw(glm::mat4 VP) {

    glUseProgram (ProgramID);
    
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of Arrow arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}


Sphere::Sphere(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->speed = 0.0;
    this->yspeed = 0.0;
    this->radius = 3.0f;
    
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A Sphere has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[90000];
    int sides = 100;
    float angle = (2*M_PI)/float(sides);

    for(int j=0;j<sides;j++)
        for(int i=0;i<sides;i++)
        {
            int k = sides*i + j;
            vertex_buffer_data[9*k] = 0.0f;
            vertex_buffer_data[9*k + 1] = 0.0f;  
            vertex_buffer_data[9*k + 2] = radius*sin(j*angle);
            vertex_buffer_data[9*k + 3] = radius*cos(i*angle)*cos(j*angle); 
            vertex_buffer_data[9*k + 4] = radius*sin(i*angle)*cos(j*angle);
            vertex_buffer_data[9*k + 5] = radius*sin(j*angle); 
            vertex_buffer_data[9*k + 6] = radius*cos((i+1)*angle)*cos(j*angle); 
            vertex_buffer_data[9*k + 7] = radius*sin((i+1)*angle)*cos(j*angle); 
            vertex_buffer_data[9*k + 8] = radius*sin(j*angle); 
        }

    this->object = create3DObject(GL_TRIANGLES, sides*sides*3, vertex_buffer_data, color, GL_FILL);
}

void Sphere::draw(glm::mat4 VP) {

    glUseProgram (ProgramID);
    
    Matrices.model = glm::mat4(1.0f);
    // Rotate about y axis and not center of object
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of Sphere arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Sphere::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

bool Sphere::tick() {


    this->position.y += yspeed;
    this->yspeed -= 0.001;

    this->position.z -= speed*cos(rotation*M_PI/180.0f);   
    this->position.x += speed*sin(rotation*M_PI/180.0f); 

    return this->position.y < -5.0f;

}

bounding_box_t Sphere::bounding_box() {
    float x = this->position.x, y = this->position.y, z = this->position.z;
    bounding_box_t bbox = { x, y,z, this->radius, this->radius, this->radius };
    return bbox;
}


// Rectangle for sail


Sail::Sail(float x, float y, float z,float length, float height, GLuint textureID) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->dimensions = glm::vec2(length,height);  
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A Sail has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    GLfloat vertex_buffer_data[] = {
        0.0,10.0,0.0,
        6,0.0,0.0,
        -6,0.0,0.0
    };

    GLfloat texture_buffer_data[]={
        1,0,
        0,1,
        1,1
    }; 


 
    this->object = create3DTexturedObject(GL_TRIANGLES, 3, vertex_buffer_data, texture_buffer_data, textureID, GL_FILL);
    
}

void Sail::draw(glm::mat4 VP) {

    glUseProgram(textureProgramID);

    Matrices.model = glm::mat4(1.0f);

    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));

    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.TexMatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DTexturedObject(this->object);
}

void Sail::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

bounding_box_t Sail::bounding_box() {
    float x = this->position.x, y = this->position.y, z = this->position.z;
    bounding_box_t bbox = { x, y,z, this->dimensions.x, this->dimensions.y, 0};
    return bbox;
}

Circle::Circle(float x, float y, float z, float radius,color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->speed = 0.0;
    this->yspeed = 0.0;
    this->radius = radius;
    
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A Circle has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data[900];
    int sides = 100;
    float angle = (2*M_PI)/float(sides);

    for(int i=0;i<sides;i++)
    {
        vertex_buffer_data[9*i] = 0.0f;
        vertex_buffer_data[9*i + 1] = 0.0f;  
        vertex_buffer_data[9*i + 2] = 0.0f;
        vertex_buffer_data[9*i + 3] = radius*cos(i*angle); 
        vertex_buffer_data[9*i + 4] = radius*sin(i*angle);
        vertex_buffer_data[9*i + 5] = 0.0f; 
        vertex_buffer_data[9*i + 6] = radius*cos((i+1)*angle); 
        vertex_buffer_data[9*i + 7] = radius*sin((i+1)*angle); 
        vertex_buffer_data[9*i + 8] = 0.0f; 
    }

    this->object = create3DObject(GL_TRIANGLES, sides*3, vertex_buffer_data, color, GL_FILL);
}

void Circle::draw(glm::mat4 VP) {

    glUseProgram (ProgramID);
    
    Matrices.model = glm::mat4(1.0f);
    // Rotate about y axis and not center of object
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of Circle arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Circle::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

bool Circle::tick() {


    this->position.y += yspeed;
    this->yspeed -= 0.001;

    this->position.z -= speed*cos(rotation*M_PI/180.0f);   
    this->position.x += speed*sin(rotation*M_PI/180.0f); 

    return this->position.y < -5.0f;

}


VerticalRectangle::VerticalRectangle(float x,float z,  GLuint textureID) {
    this->position = glm::vec3(x, 2, z);
    this->rotation = 0;
    // depth = 6;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A Prism has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    
    static const GLfloat vertex_buffer_data[] = {
        -1000.0,400, 0.0,
        1000.0, 400, 0.0,
        1000.0, -400,0.0,

        1000.0, -400, 0.0,
        -1000.0,-400, 0.0,
        -1000.0,400,  0.0
    };

        // For sky 
        GLfloat texture_buffer_data[] = {
        1,0, // TexCoord 1 - bot left
        0,0, // TexCoord 2 - bot right
        0,1, // TexCoord 3 - top right

        0,1, // TexCoord 3 - top right
        1,1, // TexCoord 4 - top left
        1,0,  // TexCoord 1 - bot left
        };


 
    this->object = create3DTexturedObject(GL_TRIANGLES, 6, vertex_buffer_data, texture_buffer_data, textureID, GL_FILL);

}


// Define Prism

void VerticalRectangle::draw(glm::mat4 VP) {

    glUseProgram(textureProgramID);

    Matrices.model = glm::mat4(1.0f);

    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));

    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.TexMatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DTexturedObject(this->object);
}