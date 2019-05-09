#version 330

uniform sampler2D tex;
uniform float ambientStrength;
uniform vec3 lightPos;

in vec2 vsoTexCoord;
in vec3 vsoNormal;
in vec3 vsoFragPos;

out vec4 fragColor;

void main()
{
  vec3 ambient = ambientStrength * vec3 (1.0, 1.0, 1.0);
  vec3 norm = normalize (vsoNormal);
  vec3 lightDir = normalize (lightPos - vsoFragPos);
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = diff * vec3 (0.5, 0.5, 0.5);
  vec4 result = vec4((ambient + diffuse), 1.0) * texture (tex, vsoTexCoord);
  fragColor = result;
}
