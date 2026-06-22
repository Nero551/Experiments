#include "OpenGL.h"
#include <cmath>
#include <cstddef>
#include <iostream>
#include <ostream>

// Vertex Shader source code
const char *vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
// Fragment Shader source code
const char *fragShaderSource = "#version 330 core\n"
                               "out vec4 FragColor;\n"
                               "void main()\n"
                               "{\n"
                               "   FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
                               "}\n\0";

int main() {
  glfwInit(); //* Initializing GLFW Library
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,
                 3); //* Hinting at the my version of the library
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,
                 3); //* Hinting at the my version of the library
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLfloat vertices[] = {
      -0.5f, -0.5f * float(std::sqrt(3)) / 3,    0.0f,
      0.5f,  -0.5f * float(std::sqrt(3)) / 3,    0.0f,
      0.0f,  0.5f * float(std::sqrt(3)) * 2 / 3, 0.0f,
  };

  GLFWwindow *Window =
      glfwCreateWindow(800, 800, "PU Engine", NULL, NULL); //* Creating Window
  if (!Window) {
    std::cout << "Failed To Create Window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(
      Window); //* Telling GLFW that this is the window it should use

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  glViewport(0, 0, 800, 800);

  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragShader, 1, &fragShaderSource, NULL);
  glCompileShader(fragShader);

  GLuint shaderProgram = glCreateProgram();

  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragShader);
  glLinkProgram(shaderProgram);

  glDeleteShader(vertexShader);
  glDeleteShader(fragShader);

  GLuint VAO, VBO;

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  glClearColor(0.07, 0.13, 0.17, 0.5); //* Color

  //* Main Loop
  while (!glfwWindowShouldClose(Window)) {
    glClearColor(0.07, 0.13, 0.17, 0.5); //* Color
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(Window); //* Swapping back and front buffers
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(shaderProgram);

  glfwDestroyWindow(Window);
  glfwTerminate();
  return 0;
}
