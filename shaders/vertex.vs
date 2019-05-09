#version 330

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

layout (location = 0) in vec3 vsiPosition;
layout (location = 1) in vec3 vsiNormal;
layout (location = 2) in vec2 vsiTexCoord;

out vec2 vsoTexCoord;
out vec3 vsoNormal;
out vec3 vsoFragPos;

void main(void) {
  gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vsiPosition.xyz, 1.0);
  vsoFragPos = vec3(modelMatrix * vec4(vsiPosition, 1.0));
  vsoTexCoord = vsiTexCoord;
  vsoNormal = mat3(transpose(inverse(modelMatrix))) * vsiNormal;
}
