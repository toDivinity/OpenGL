#version 450 core

in vec2 texCoord;

uniform sampler2D loadedTexture;

void main()
{
   gl_FragColor = texture(loadedTexture, texCoord);
}