#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec3 Color;

// Parâmetros da luz
struct Light{
   vec3 position;
   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
};

uniform Light light;
uniform vec3 viewPos;// Posição da câmera

void main()
{
   // Componente ambiente
   vec3 ambient=light.ambient*Color;
   
   // Componente difusa
   vec3 norm=normalize(Normal);
   vec3 lightDir=normalize(light.position-FragPos);
   float diff=max(dot(norm,lightDir),0.);
   vec3 diffuse=light.diffuse*(diff*Color);
   
   // Componente especular
   float specularStrength=.5;
   vec3 viewDir=normalize(viewPos-FragPos);
   vec3 reflectDir=reflect(-lightDir,norm);
   float spec=pow(max(dot(viewDir,reflectDir),0.),32);
   vec3 specular=light.specular*(specularStrength*spec);
   
   vec3 result=ambient+diffuse+specular;
   FragColor=vec4(result,1.);
}
