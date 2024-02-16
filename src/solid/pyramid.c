#include "pyramid.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include "../world/window.h"
#include "../world/shader.h"
#include <stdio.h>
#include <string.h>
vec3 cameraPosPyramid = {0.0f, 0.0f, 6.0f};
vec3 cameraTargetPyramid = {0.0f, 0.0f, 0.0f};
vec3 cameraUpPyramid = {0.0f, 1.0f, 0.0f};
vec3 lightPosPyramid = {0.0f, -0.5f, 3.0f};
float pyramidVertices[] = {
    // Posições         // Cores           // Normais
    -0.5f, 0.0f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, // V0 (Base 1)
    0.5f, 0.0f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,  // V1 (Base 1)
    0.5f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,   // V2 (Base 1)
    -0.5f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,  // V3 (Base 1)

    -0.5f, 0.0f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, // V4 (Face 1)
    0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,   // V5 (Face 1)
    0.5f, 0.0f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,  // V6 (Face 1)

    0.5f, 0.0f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // V7 (Face 2)
    0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // V8 (Face 2)
    0.5f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // V9 (Face 2)

    0.5f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // V10 (Face 3)
    0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // V11 (Face 3)
    -0.5f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, // V12 (Face 3)

    -0.5f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // V13 (Face 4)
    0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,  // V14 (Face 4)
    -0.5f, 0.0f, -0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f // V15 (Face 4)
};

unsigned int pyramidIndices[] = {
    // Base 1
    0, 1, 2,
    0, 2, 3,

    // Face 1
    4, 5, 6,

    // Face 2
    7, 8, 9,

    // Face 3
    10, 11, 12,

    // Face 4
    13, 14, 15};

unsigned int pyramidVAO, pyramidVBO, pyramidEBO;
struct Shader pyramidShader;
mat4 pyramidProjection, pyramidView, pyramidModel;

void createPyramid(float x, float y, float z, char *lightType)
{
    // Inicializa o shader
    pyramidShader = createShader("res/shaders/main.vs", "res/shaders/main.fs");
    useShader(pyramidShader);

    glGenVertexArrays(1, &pyramidVAO);
    glGenBuffers(1, &pyramidVBO);
    glGenBuffers(1, &pyramidEBO);

    glBindVertexArray(pyramidVAO);
    glBindBuffer(GL_ARRAY_BUFFER, pyramidVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidVertices), pyramidVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pyramidEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(pyramidIndices), pyramidIndices, GL_STATIC_DRAW);

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
    glm_perspective(glm_rad(45.0f), 1600.0f / 800.0f, 0.1f, 100.0f, pyramidProjection);
    setShaderMat4(pyramidShader, "projection", pyramidProjection);

    // Matriz de visualização (posicionamento da câmera)
    glm_lookat(cameraPosPyramid, cameraTargetPyramid, cameraUpPyramid, pyramidView);
    setShaderMat4(pyramidShader, "view", pyramidView);
    // Matriz do Modelo (transformações do objeto)
    glm_mat4_identity(pyramidModel);
    glm_translate(pyramidModel, (vec3){x, y, z});
    setShaderMat4(pyramidShader, "model", pyramidModel);

    // Configurações da luz

    glUniform3f(glGetUniformLocation(pyramidShader.ID, "light.position"), cameraPosPyramid[0], cameraPosPyramid[1], cameraPosPyramid[2]);

    if (strcmp(lightType, "phong") == 0)
    {
        glUniform3f(glGetUniformLocation(pyramidShader.ID, "light.ambient"), 0.2f, 0.2f, 0.2f);
        glUniform3f(glGetUniformLocation(pyramidShader.ID, "light.diffuse"), 0.5f, 0.5f, 0.5f);
        glUniform3f(glGetUniformLocation(pyramidShader.ID, "light.specular"), 1.0f, 1.0f, 1.0f);
    }
    else if (strcmp(lightType, "ambient") == 0)
    {
        glUniform3f(glGetUniformLocation(pyramidShader.ID, "light.ambient"), 0.2f, 0.2f, 0.2f);
    }
    else if (strcmp(lightType, "diffuse") == 0)
    {
        glUniform3f(glGetUniformLocation(pyramidShader.ID, "light.diffuse"), 0.5f, 0.5f, 0.5f);
    }
    else if (strcmp(lightType, "specular") == 0)
    {
        glUniform3f(glGetUniformLocation(pyramidShader.ID, "light.specular"), 1.0f, 1.0f, 1.0f);
    }

    // Posição da câmera
    glUniform3f(glGetUniformLocation(pyramidShader.ID, "viewPos"), lightPosPyramid[0], lightPosPyramid[1], lightPosPyramid[2]);
}

void drawPyramid(double deltaTime)
{
    useShader(pyramidShader);

    // Rotação da pirâmide com velocidade constante
    float rotationSpeed = 1.0f;
    glm_rotate(pyramidModel, rotationSpeed * deltaTime, (vec3){0.0f, 1.0f, 0.0f});
    // Atualiza a matriz do modelo no shader
    setShaderMat4(pyramidShader, "model", pyramidModel);

    glBindVertexArray(pyramidVAO);
    glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0); // 18 vértices para a pirâmide
}
