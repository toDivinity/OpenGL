#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 textureCoord;

out vec3 fragmentColor;    
out vec2 texCoord;         

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(position, 1.0);
    
    fragmentColor = color + position;
    texCoord = textureCoord;
}