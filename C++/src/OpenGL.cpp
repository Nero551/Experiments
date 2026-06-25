#include "OpenGL.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <array>
#include <iostream>
#include <iterator>
#include <vector>
#include "Math/Vector.h"
#include "Renderer/Renderer.h"

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

void CreateShader(unsigned int &ShaderProgram, const char *&vertexSource, const char *&fragSource) {
  //* Vertex Shader
  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexSource, NULL);
  glCompileShader(vertexShader);

  //* Fragment Shader
  unsigned int FragShader;
  FragShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(FragShader, 1, &fragSource, NULL);
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

void CreateVAOVBOEBO(unsigned int &VAO, std::vector<Vertex> &vertices,std::vector<unsigned int> &indices) {
  //* Vertex Array Object (VAO)
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  //* Vertex Buffer Object (VBO)
  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

  unsigned int EBO;
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(float), indices.data(), GL_STATIC_DRAW);
  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
  glEnableVertexAttribArray(0);
}

void Draw(unsigned int &ShaderProgram, unsigned int &VAO, int indicesCount) {
  glUseProgram(ShaderProgram);
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
}

int main() {
  int WindowWidth = 800;
  int WindowHeight = 800;

  InitOpenGL();
  GLFWwindow *Window = CreateWindow(WindowWidth, WindowHeight, "Plus Ultra");

  std::vector<Vertex> Vertices = {
    Vertex(Vector3(-0.5,-0.5,0.0)),
    Vertex(Vector3(0.5,-0.5,0.0)),
    Vertex(Vector3(0.5,0.5,0.0)),
    Vertex(Vector3(-0.5,0.5,0.0)),
  };

  std::vector<unsigned int> Indices = {
    0,1,2,
    0,2,3
  };

  unsigned int VAO;
  unsigned int ShaderProgram;
  CreateShader(ShaderProgram, vertexShaderSource, fragShaderSource);
  CreateVAOVBOEBO(VAO, Vertices, Indices);

  while (!glfwWindowShouldClose(Window)) {
    glClearColor(0.1, 0.15, 0.2, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    Draw(ShaderProgram, VAO, 6);
    
    glfwSwapBuffers(Window);
    
    ProcessInput(Window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}