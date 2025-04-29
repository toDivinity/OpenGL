#version 460 core

in vec3 fragmentColor;
in vec2 texCoord;

uniform sampler2D loadedTexture;
uniform float mixPercent;

out vec4 FragColor;

void main()
{
   FragColor = mix(texture(loadedTexture, texCoord), (vec4(fragmentColor,1.0)/2+(0.5)), mixPercent);
}