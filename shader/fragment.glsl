#version 330 core

in vec2 ourTexCoord;

uniform sampler2D ourTexture;
uniform vec3 objectColor;
uniform vec3 lightColor;

out vec4 FragColor;

void main() {
  FragColor = texture(ourTexture, ourTexCoord) * vec4(objectColor * lightColor, 1.0);
}
