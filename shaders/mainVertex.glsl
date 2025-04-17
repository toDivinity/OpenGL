#version 450 core

layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec3 vertexColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 fragmentColor;
out vec2 TexCoord;

uniform vec4 transformation;

void main()
{
    gl_Position = vec4 (vertexPos.x*transformation.x, vertexPos.y*transformation.y, vertexPos.z*transformation.z , 1.0);
    fragmentColor = vertexPos;
    TexCoord = aTexCoord;
}