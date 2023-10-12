#version 330 core

in vec2 ourTexCoord;

uniform sampler2D ourTexture;

out vec4 FragColor;

void main() {
  FragColor = texture(ourTexture, ourTexCoord);
}
