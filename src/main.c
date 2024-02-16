#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "world/window.h"
#include "world/shader.h"
#include "solid/cube.h"
#include "solid/pyramid.h"
#include "solid/parallelepiped.h"

// get light type from args
int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    printf("Uso do aplcaitivo: %s <tipo da luz>\n", argv[0]);
    return 1;
  }

  printf("tipo da luz: %s\n", argv[1]);
  createWindow();

  createCube(-2.0f, -0.5f, 0.0f, argv[1]);
  createPyramid(2.0f, -1.0f, 0.0f, argv[1]);
  createParallelepiped(0.0f, 0.0f, 0.0f, argv[1]);

  while (!glfwWindowShouldClose(window.self))
  {
    updateWindow();

    drawCube(window.dt);
    drawPyramid(window.dt);
    drawParallelepiped(window.dt);

    glfwSwapBuffers(window.self);
    glfwPollEvents();
  }

  terminateWindow();

  return 0;
}
