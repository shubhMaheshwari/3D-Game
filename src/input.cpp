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

#include "main.h"

bool   cannon_keyboard_input = true;
bool   drag_pan = false, old_cki;
double drag_oldx = -1, drag_oldy = -1;

using namespace std;

/* Executed when a regular key is pressed/released/held-down */
/* Preferred for Keyboard events */
void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods) {
    // Function is called first on GLFW_PRESS.

    if (action == GLFW_RELEASE) {
        // switch (key) {
        // case GLFW_KEY_C:
        // rectangle_rot_status = !rectangle_rot_status;
        // break;
        // case GLFW_KEY_P:
        // triangle_rot_status = !triangle_rot_status;
        // break;
        // case GLFW_KEY_X:
        //// do something ..
        // break;
        // default:
        // break;
        // }
    } else if (action == GLFW_PRESS) {
        switch (key) {
        case GLFW_KEY_ESCAPE:
            quit(window);
            break;
        default:
            break;
        }
    }
}

/* Executed for character input (like in text boxes) */
void keyboardChar(GLFWwindow *window, unsigned int key) {
    switch (key) {
    case 'p':
        pause = !pause;
        break;
    case 'q':
        quit(window);
        break;
    default:
        break;
    }
}

/* Executed when a mouse button is pressed/released */
void mouseButton(GLFWwindow *window, int button, int action, int mods) {
    switch (button) {
    case GLFW_MOUSE_BUTTON_LEFT:
        if (action == GLFW_PRESS) {
            // Do something
           clk = true;
            return;
        } else if (action == GLFW_RELEASE) {
            clk = false;
            // Do something
        }
        break;
    // case GLFW_MOUSE_BUTTON_RIGHT:
    // if (action == GLFW_RELEASE) {
    // rectangle_rot_dir *= -1;
    // }
    // break;
    default:
        break;
    }
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    // Do something
    if(yoffset == 1)
        screen_zoom *= 1.1;

    else if(yoffset == -1)
        screen_zoom /= 1.1;


    reshapeWindow(window,1600,1600);

}

float prev_xpos=0.0f,prev_ypos=0.0f;
void mouseuse(GLFWwindow *window,int fbwidth, int fbheight,float* eye_x, float* eye_z)
{
    double xpos,ypos;
    glfwGetCursorPos(window,&xpos,&ypos);
    xpos=(xpos/fbwidth)*8-2;
    ypos=(ypos/fbheight)*8-2;
    float ox=(float)xpos-prev_xpos;
    float oy=(float)ypos-prev_ypos;
    //cout<<clk;
    if(clk)
    {
        *eye_x +=ox;
        *eye_z +=oy;

        // cout<<camx<<" "<<camy<<" "<<fbheight<<" "<<fbwidth<<"\n";
        //clk=0;
    }

    prev_xpos = xpos;
    prev_ypos = ypos;
     
}