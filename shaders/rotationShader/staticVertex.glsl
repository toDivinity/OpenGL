#version 450 core

layout (location = 0) in vec3 position;
layout (location = 2) in vec2 textureCoord;
  
out vec2 texCoord;         

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
    texCoord = textureCoord;
}