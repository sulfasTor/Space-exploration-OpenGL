#version 330

uniform sampler2D tex;
uniform float ambientStrength;
uniform vec3 lightPos;
uniform vec3 viewPos;

in vec2 vsoTexCoord;
in vec3 vsoNormal;
in vec3 vsoFragPos;

out vec4 fragColor;

void main()
{
  float specularStrength = 2.0;
  const vec3 lightColorDiffuse = vec3(1, 0.5, 0.5);
  const vec3 lightColorAmbient = vec3(0.5, 0.5, 0.4);
  const vec3 lightColorSpecular = vec3(1);
  
  vec3 ambient = ambientStrength * lightColorAmbient;
  vec3 norm = normalize (vsoNormal);
  vec3 lightDir = normalize (lightPos - vsoFragPos);
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = diff * lightColorDiffuse;

  vec3 viewDir = normalize(viewPos - vsoFragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
  vec3 specular = specularStrength * spec * lightColorSpecular;
  
  vec4 result = vec4((ambient + diffuse + specular), 1.0) * texture (tex, vsoTexCoord);
  fragColor = result;
}
