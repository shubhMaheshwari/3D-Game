#include "main.h"
#include "sea.h"

Sea::Sea(float x, float y, GLuint textureID) {
    this->position = glm::vec3(x, y+0.25, 0);
    this->rotation = 0;
    this->yspeed = 0.0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A Sea has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -10000.0,0.0, 10000.0,
        10000.0, 0.0, 10000.0,
        10000.0, 0.0, -10000.0,

        10000.0, 0.0, -10000.0,
        -10000.0,0.0, -10000.0,
        -10000.0,0.0, 10000.0
    };

    if(y > 100)
    {
        // For sky 
        GLfloat texture_buffer_data[] = {
        0,1, // TexCoord 1 - bot left
        1,1, // TexCoord 2 - bot right
        1,0, // TexCoord 3 - top right

        1,0, // TexCoord 3 - top right
        0,0, // TexCoord 4 - top left
        0,1,  // TexCoord 1 - bot left
        };
        
    this->object = create3DTexturedObject(GL_TRIANGLES, 6, vertex_buffer_data, texture_buffer_data, textureID, GL_FILL);


    }
    
    else{
                // For sky
    GLfloat texture_buffer_data [] = {
            0,1000, // TexCoord 10000 - bot left
            1000,1000, // TexCoord 1000 - bot right
            1000,0, // TexCoord 3 - top right

            1000,0, // TexCoord 3 - top right
            0,0, // TexCoord 4 - top left
            0,1000  // TexCoord 1 - bot left
        };    
    

    this->object = create3DTexturedObject(GL_TRIANGLES, 6, vertex_buffer_data, texture_buffer_data, textureID, GL_FILL);    
    }

}

void Sea::draw(glm::mat4 VP) {

    glUseProgram (textureProgramID);

    
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of Sea arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.TexMatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DTexturedObject(this->object);
}

void Sea::set_position(float x, float z) {
    this->position = glm::vec3(x, this->position.y , z);
}

void Sea::tick() {

    this->position.y += yspeed;

    if (this->position.y <= 0.0)
        this->yspeed +=0.001;
    else if (this->position.y > 0.0)
        this->yspeed -= 0.001;

    else if (this->position.y > 0.25)
        this->position.y = 0.25;

    else if (this->position.y < -0.25)
        this->position.y = -0.25;

    else
        printf("Error Moving Sea:%lf\n",this->position.y);
   

}

