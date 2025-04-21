#version 450 core

layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec3 vertexColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 fragmentColor;
out vec2 TexCoord;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(vertexPos.x, vertexPos.y, vertexPos.z , 1.0);
    fragmentColor = vertexColor + vertexPos;
    TexCoord = aTexCoord;
}