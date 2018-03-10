#ifndef MAIN_H
#define MAIN_H


#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <pthread.h>
#include <ao/ao.h>
#include <mpg123.h>


struct color_t {
    int r;
    int g;
    int b;
};

// nonedit.cpp
GLFWwindow *initGLFW(int width, int height);
GLuint     LoadShaders(const char *vertex_file_path, const char *fragment_file_path);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const GLfloat *color_buffer_data, GLenum fill_mode = GL_FILL);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const GLfloat red, const GLfloat green, const GLfloat blue, GLenum fill_mode = GL_FILL);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const color_t color, GLenum fill_mode = GL_FILL);
struct VAO* create3DTexturedObject(GLenum primitive_mode, int numVertices, const GLfloat* vertex_buffer_data, const GLfloat* texture_buffer_data, GLuint textureID, GLenum fill_mode=GL_FILL);
void       draw3DObject(struct VAO *vao);
void draw3DTexturedObject (struct VAO* vao);
GLuint createTexture (const char* filename);
GLuint loadDDS(const char * imagepath);
 
// input.cpp
void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods);
void keyboardChar(GLFWwindow *window, unsigned int key);
void mouseButton(GLFWwindow *window, int button, int action, int mods);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void mouseuse(GLFWwindow *window,int fbwidth, int fbheight,float* eye_x, float* eye_z);

// other_handlers.cpp
void error_callback(int error, const char *description);
void quit(GLFWwindow *window);
void reshapeWindow(GLFWwindow *window, int width, int height);
void* play_audio(void *ptr);

// Types
struct VAO {
    GLuint VertexArrayID;
    GLuint VertexBuffer;
    GLuint ColorBuffer;
    GLuint TextureBuffer;
    GLuint TextureID;

    GLenum PrimitiveMode; // GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES, GL_LINE_STRIP_ADJACENCY, GL_LINES_ADJACENCY, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES, GL_TRIANGLE_STRIP_ADJACENCY and GL_TRIANGLES_ADJACENCY
    GLenum FillMode; // GL_FILL, GL_LINE
    int NumVertices;
};
typedef struct VAO VAO;

struct GLMatrices {
    glm::mat4 projection;
    glm::mat4 model;
    glm::mat4 view;
    GLuint    MatrixID;
    GLuint    TexMatrixID;
};

extern GLMatrices Matrices;
extern GLuint ProgramID,textureProgramID;

// ---- Logic ----

enum direction_t { DIR_UP, DIR_RIGHT, DIR_DOWN, DIR_LEFT };

struct bounding_box_t {
    float x;
    float y;
    float z;
    float width;
    float height;
    float depth;
};

// main.cpp
bool detect_collision(bounding_box_t a, bounding_box_t b);
void get_gift();
void display_score(int time);

extern float screen_zoom, screen_center_x, screen_center_y;
extern int boat_health,score;
extern bool clk,pause;
// ---- Colors ----
extern const color_t COLOR_RED;
extern const color_t COLOR_ORANGE;
extern const color_t COLOR_GREEN;
extern const color_t COLOR_BLUE;
extern const color_t COLOR_BROWN;
extern const color_t COLOR_GREY;
extern const color_t COLOR_BLACK;
extern const color_t COLOR_SHARK_FIN;
extern const color_t COLOR_WHITE;
extern const color_t COLOR_BACKGROUND;

#endif
