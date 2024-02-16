#ifndef WINDOW_H
#define WINDOW_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

struct Window
{
    GLFWwindow *self;
    const char *title;
    int width;
    int height;

    float dt; // Delta Time
    float lastFrame;
    mat4 projection;
};

extern struct Window window;

void createWindow();
void terminateWindow();
void updateWindow();

#endif