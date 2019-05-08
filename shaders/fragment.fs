#version 330

uniform sampler2D tex;
uniform float ambientStrength;

in  vec2 vsoTexCoord;

out vec4 fragColor;

void main()
{
  vec4 ambient = ambientStrength * vec4 (0.5, 0.5, 0.5, 1.0);
  vec4 result = ambient * texture (tex, vsoTexCoord);
  fragColor = result;
}
