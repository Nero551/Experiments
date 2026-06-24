#include "OpenGL.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout(location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\n";

const char *fragShaderSource = "#version 330 core\n"
                               "out vec4 FragColor;\n"
                               "void main()\n"
                               "{\n"
                               "FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
                               "}\n";

GLFWwindow *CreateWindow(int width, int height, const char *name) {
  GLFWwindow *window = glfwCreateWindow(width, height, name, NULL, NULL);
  if (!window) {
    std::cout << "Failed To Create Window";
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed To Initialize GLAD";
  }

  glViewport(0, 0, width, height);
  glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int width, int height) { glViewport(0, 0, width, height); });

  return window;
}

void ProcessInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

void InitOpenGL() {

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

float Vertices[] = {
  -0.5f,
  -0.5f,
  0.0f,
  0.5f,
  -0.5f,
  0.0f,
  0.0f,
  0.5f,
  0.0f,
};

void CreateShader(unsigned int &ShaderProgram, const char *&vertexSource, const char *&fragSource) {
  //* Vertex Shader
  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  //* Fragment Shader
  unsigned int FragShader;
  FragShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(FragShader, 1, &fragShaderSource, NULL);
  glCompileShader(FragShader);

  //* Shader Program
  ShaderProgram = glCreateProgram();
  glAttachShader(ShaderProgram, vertexShader);
  glAttachShader(ShaderProgram, FragShader);
  glLinkProgram(ShaderProgram);

  //* Cleanup
  glDeleteShader(vertexShader);
  glDeleteShader(FragShader);
}

void CreateVBOVAO(unsigned int &VAO, const int vertexCount, const float vertices[]) {
  //* Vertex Buffer Object (VBO)
  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

  //* Vertex Array Object (VAO)
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  glVertexAttribPointer(0, vertexCount, GL_FLOAT, GL_FALSE, vertexCount * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
}

void DrawTriangle(unsigned int &ShaderProgram, unsigned int &VAO, int vertexCount) {
  glUseProgram(ShaderProgram);
  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}

int main() {
  int WindowWidth = 800;
  int WindowHeight = 800;

  InitOpenGL();
  GLFWwindow *Window = CreateWindow(WindowWidth, WindowHeight, "Plus Ultra");

  unsigned int VAO;
  unsigned int ShaderProgram;
  CreateVBOVAO(VAO, 3, Vertices);
  CreateShader(ShaderProgram, vertexShaderSource, fragShaderSource);

  while (!glfwWindowShouldClose(Window)) {
    glClearColor(0.1, 0.15, 0.2, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    DrawTriangle(ShaderProgram, VAO, 3);

    ProcessInput(Window);
    glfwSwapBuffers(Window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}