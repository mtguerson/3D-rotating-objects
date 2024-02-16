#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "cube.h"
#include <cglm/cglm.h>
#include <stdio.h>
#include <string.h>

#include "../world/window.h"
#include "../world/shader.h"

vec3 cameraPosCube = {0.0f, 0.0f, 6.0f};
vec3 cameraTargetCube = {0.0f, 0.0f, 0.0f};
vec3 cameraUpCube = {0.0f, 1.0f, 0.0f};
vec3 lightPosCube = {0.0f, -0.5f, 3.0f};

float vertices[] = {
    // Face traseira
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, // Face traseira
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,  // Face traseira
    0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,   // Face traseira
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,  // Face traseira

    // Face frontal
    -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // Face frontal
    0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // Face frontal
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,   // Face frontal
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // Face frontal

    // Face esquerda
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, // Face esquerda
    -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,  // Face esquerda
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,   // Face esquerda
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,  // Face esquerda

    // Face direita
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, // Face direita
    0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // Face direita
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,   // Face direita
    0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // Face direita

    // Face inferior
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, // Face inferior
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,  // Face inferior
    0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,   // Face inferior
    -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,  // Face inferior

    // Face superior
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // Face superior
    0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,  // Face superior
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,   // Face superior
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,  // Face superior
};

unsigned int indices[] = {
    // Repetindo os índices já existentes, pois a estrutura do cubo permanece a mesma
    0, 1, 2, 2, 3, 0,       // Face traseira
    4, 5, 6, 6, 7, 4,       // Face frontal
    8, 9, 10, 10, 11, 8,    // Face esquerda
    12, 13, 14, 14, 15, 12, // Face direita
    16, 17, 18, 18, 19, 16, // Face inferior
    20, 21, 22, 22, 23, 20  // Face superior
};
unsigned int EBO;
unsigned int VBO, VAO;
struct Shader shader;
mat4 projection, view, model;

void createCube(float x, float y, float z, char *lightType)
{
    // Inicializa o shader
    shader = createShader("res/shaders/main.vs", "res/shaders/main.fs");
    useShader(shader);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Normal attribute
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Matriz de projeção
    glm_perspective(glm_rad(45.0f), 1600.0f / 800.0f, 0.1f, 100.0f, projection);
    setShaderMat4(shader, "projection", projection);

    // Matriz de visualização (posicionamento da câmera)
    glm_lookat(cameraPosCube, cameraTargetCube, cameraUpCube, view);
    setShaderMat4(shader, "view", view);

    // Matriz do modelo (transformações do objeto)
    glm_mat4_identity(model);
    glm_translate(model, (vec3){x, y, z});
    setShaderMat4(shader, "model", model);

    // Configurações da luz

    glUniform3f(glGetUniformLocation(shader.ID, "light.position"), cameraPosCube[0], cameraPosCube[1], cameraPosCube[2]);

    if (strcmp(lightType, "phong") == 0)
    {
        glUniform3f(glGetUniformLocation(shader.ID, "light.ambient"), 0.2f, 0.2f, 0.2f);
        glUniform3f(glGetUniformLocation(shader.ID, "light.diffuse"), 0.5f, 0.5f, 0.5f);
        glUniform3f(glGetUniformLocation(shader.ID, "light.specular"), 1.0f, 1.0f, 1.0f);
    }
    else if (strcmp(lightType, "ambient") == 0)
    {
        glUniform3f(glGetUniformLocation(shader.ID, "light.ambient"), 0.2f, 0.2f, 0.2f);
    }
    else if (strcmp(lightType, "diffuse") == 0)
    {
        glUniform3f(glGetUniformLocation(shader.ID, "light.diffuse"), 0.5f, 0.5f, 0.5f);
    }
    else if (strcmp(lightType, "specular") == 0)
    {
        glUniform3f(glGetUniformLocation(shader.ID, "light.specular"), 1.0f, 1.0f, 1.0f);
    }

    // Posição da câmera
    glUniform3f(glGetUniformLocation(shader.ID, "viewPos"), lightPosCube[0], lightPosCube[1], lightPosCube[2]);
}

void drawCube(double deltaTime)
{
    useShader(shader);

    float rotationSpeed = 1.0f;
    glm_rotate(model, rotationSpeed * deltaTime, (vec3){0.0f, 1.0f, 0.0f});
    setShaderMat4(shader, "model", model);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0); // 36 vértices para o cubo
}