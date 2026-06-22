#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <cstddef>
#include <iostream>
#include <ostream>

int main() {
  bool Running = true;
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *Window = glfwCreateWindow(800, 800, "PU Engine", NULL, NULL);
  if (!Window) {
    std::cout << "Failed To Create Window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(Window);

  glClearColor(1, 0, 0, 0); //* Color
  while (Running) {
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(Window);
    glfwPollEvents();

    Running = !glfwWindowShouldClose(Window);

    glViewport(0, 0, 800, 800);
  }

  glfwDestroyWindow(Window);
  glfwTerminate();
  return 0;
}