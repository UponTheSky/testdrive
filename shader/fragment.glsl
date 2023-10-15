#version 330 core

in vec3 Normal;
in vec2 ourTexCoord;

uniform sampler2D ourTexture;
uniform vec3 objectColor;
uniform vec3 lightColor;

out vec4 FragColor;

void main() {
  float ambientStrength = 0.1;
  vec3 ambient = ambientStrength * lightColor;
  vec3 result = ambient * objectColor;
  FragColor = vec4(result, 1.0);
}
