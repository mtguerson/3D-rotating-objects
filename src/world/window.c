#include "window.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

#include <cglm/cglm.h>

struct Window window;

static void _sizeCallback()
{
    glViewport(0, 0, window.width, window.height);
}

static void _keyboardCallback()
{
    if (glfwGetKey(window.self, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window.self, 1);
}

void createWindow()
{
    window.title = "Trabalho de Computação Gráfica";
    window.width = 1600;
    window.height = 800;

    window.dt = 0.0f;
    window.lastFrame = 0.0f;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

// Apple users :)
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window.self = glfwCreateWindow(window.width, window.height, window.title, NULL, NULL);
    if (window.self == NULL)
    {
        printf("Failed to create GLFW window");
        glfwTerminate();
        exit(1);
    }

    glfwMakeContextCurrent(window.self);

    // Load all OpenGL function pointers with Glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD");
        exit(1);
    }

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glCullFace(GL_BACK);

    glfwSetFramebufferSizeCallback(window.self, _sizeCallback);
    glfwSetKeyCallback(window.self, _keyboardCallback);
}

void terminateWindow()
{
    glfwDestroyWindow(window.self);
    glfwTerminate();
}

void updateWindow()
{

    float currentFrame = glfwGetTime();
    window.dt = currentFrame - window.lastFrame;
    window.lastFrame = currentFrame;

    // Render
    float aspectRatio = (float)window.width / (float)window.height;
    glm_perspective(glm_rad(70.0f), aspectRatio, 0.1f, 100.0f, window.projection);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}