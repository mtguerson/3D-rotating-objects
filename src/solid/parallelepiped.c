#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "parallelepiped.h"
#include <cglm/cglm.h>
#include <stdio.h>
#include <string.h>

#include "../world/window.h"
#include "../world/shader.h"

vec3 cameraPosParallelepiped = {0.0f, 0.0f, 6.0f};
vec3 cameraTargetParallelepiped = {0.0f, 0.0f, 0.0f};
vec3 cameraUpParallelepiped = {0.0f, 1.0f, 0.0f};
vec3 lightPosParallelepiped = {0.0f, -0.5f, 3.0f};

// Paralelepípedo
float parallelepipedVertices[] = {
    // Face traseira
    -0.5f, -1.0f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, // Face traseira
    0.5f, -1.0f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,  // Face traseira
    0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,   // Face traseira
    -0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,  // Face traseira

    // Face frontal
    -0.5f, -1.0f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // Face frontal
    0.5f, -1.0f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,  // Face frontal
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,   // Face frontal
    -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,  // Face frontal

    // Face esquerda
    -0.5f, -1.0f, -0.5f, 1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, // Face esquerda
    -0.5f, -1.0f, 0.5f, 1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,  // Face esquerda
    -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,   // Face esquerda
    -0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,  // Face esquerda

    // Face direita
    0.5f, -1.0f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, // Face direita
    0.5f, -1.0f, 0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,  // Face direita
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,   // Face direita
    0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,  // Face direita

    // Face inferior
    -0.5f, -1.0f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, // Face inferior
    0.5f, -1.0f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,  // Face inferior
    0.5f, -1.0f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,   // Face inferior
    -0.5f, -1.0f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,  // Face inferior

    // Face superior
    -0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Face superior
    0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // Face superior
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // Face superior
    -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // Face superior
};

unsigned int parallelepipedIndices[] = {
    // Face traseira
    0, 1, 2, // Primeiro triângulo
    2, 3, 0, // Segundo triângulo

    // Face frontal
    4, 5, 6,
    6, 7, 4,

    // Face esquerda
    8, 9, 10,
    10, 11, 8,

    // Face direita
    12, 13, 14,
    14, 15, 12,

    // Face inferior
    16, 17, 18,
    18, 19, 16,

    // Face superior
    20, 21, 22,
    22, 23, 20};

unsigned int ParallelepipedEBO;
unsigned int ParallelepipedVBO, ParallelepipedVAO;
struct Shader shaderParallelepiped;
mat4 projectionParallelepiped, viewParallelepiped, modelParallelepiped;

void createParallelepiped(float x, float y, float z, char *lightType)
{
    // Inicializa o shader
    shaderParallelepiped = createShader("res/shaders/main.vs", "res/shaders/main.fs");
    useShader(shaderParallelepiped);

    glGenVertexArrays(1, &ParallelepipedVAO);
    glGenBuffers(1, &ParallelepipedVBO);
    glGenBuffers(1, &ParallelepipedEBO);

    glBindVertexArray(ParallelepipedVAO);
    glBindBuffer(GL_ARRAY_BUFFER, ParallelepipedVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(parallelepipedVertices), parallelepipedVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ParallelepipedEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(parallelepipedIndices), parallelepipedIndices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Normal attribute
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    // Matriz de projeção
    glm_perspective(glm_rad(45.0f), 1600.0f / 800.0f, 0.1f, 100.0f, projectionParallelepiped);
    setShaderMat4(shaderParallelepiped, "projection", projectionParallelepiped);

    // Matriz de visualização (posicionamento da câmera)
    glm_lookat(cameraPosParallelepiped, cameraTargetParallelepiped, cameraUpParallelepiped, viewParallelepiped);
    setShaderMat4(shaderParallelepiped, "view", viewParallelepiped);
    // Matriz do modelParallelepipedo (transformações do objeto)
    glm_mat4_identity(modelParallelepiped);
    glm_translate(modelParallelepiped, (vec3){x, y, z});
    setShaderMat4(shaderParallelepiped, "model", modelParallelepiped);

    // Configurações da luz

    glUniform3f(glGetUniformLocation(shaderParallelepiped.ID, "light.position"), cameraPosParallelepiped[0], cameraPosParallelepiped[1], cameraPosParallelepiped[2]);

    if (strcmp(lightType, "phong") == 0)
    {
        glUniform3f(glGetUniformLocation(shaderParallelepiped.ID, "light.ambient"), 0.2f, 0.2f, 0.2f);
        glUniform3f(glGetUniformLocation(shaderParallelepiped.ID, "light.diffuse"), 0.5f, 0.5f, 0.5f);
        glUniform3f(glGetUniformLocation(shaderParallelepiped.ID, "light.specular"), 1.0f, 1.0f, 1.0f);
    }
    else if (strcmp(lightType, "ambient") == 0)
    {
        glUniform3f(glGetUniformLocation(shaderParallelepiped.ID, "light.ambient"), 0.2f, 0.2f, 0.2f);
    }
    else if (strcmp(lightType, "diffuse") == 0)
    {
        glUniform3f(glGetUniformLocation(shaderParallelepiped.ID, "light.diffuse"), 0.5f, 0.5f, 0.5f);
    }
    else if (strcmp(lightType, "specular") == 0)
    {
        glUniform3f(glGetUniformLocation(shaderParallelepiped.ID, "light.specular"), 1.0f, 1.0f, 1.0f);
    }

    // Posição da câmera
    glUniform3f(glGetUniformLocation(shaderParallelepiped.ID, "viewPos"), lightPosParallelepiped[0], lightPosParallelepiped[1], lightPosParallelepiped[2]);
}

void drawParallelepiped(double deltaTime)
{
    useShader(shaderParallelepiped);

    float rotationSpeed = 1.0f;
    glm_rotate(modelParallelepiped, rotationSpeed * deltaTime, (vec3){0.0f, 1.0f, 0.0f});
    setShaderMat4(shaderParallelepiped, "model", modelParallelepiped);

    glBindVertexArray(ParallelepipedVAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0); // 36 vértices para o cubo
}