#version 330 core
layout(location=0)in vec3 aPos;
layout(location=1)in vec3 aColor;
layout(location=2)in vec3 aNormal;// Adicione a normal como entrada

out vec3 FragPos;
out vec3 Normal;
out vec3 Color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
   FragPos=vec3(model*vec4(aPos,1.));// Posição do fragmento no espaço do mundo
   Normal=mat3(transpose(inverse(model)))*aNormal;// Normal transformada
   
   Color=aColor;
   gl_Position=projection*view*vec4(FragPos,1.);
}
