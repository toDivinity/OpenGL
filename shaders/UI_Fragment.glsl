#version 460 core

in vec2 texCoord;
in vec3 fragmentColor;

uniform sampler2D loadedTexture;

out vec4 FragColor;

void main()
{
   FragColor = mix(texture(loadedTexture, texCoord), vec4(fragmentColor, 1.0f), 0.0f);
}