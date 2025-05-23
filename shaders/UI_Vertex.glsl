#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 textureCoord;
  
out vec2 texCoord;     
out vec3 fragmentColor;       

uniform mat4 modelMatrix;

void main()
{
    gl_Position = modelMatrix * vec4(position, 1.0);
    fragmentColor = color;
    texCoord = textureCoord;
}