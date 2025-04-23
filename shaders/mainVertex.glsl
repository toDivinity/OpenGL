#version 450 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texcoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 frag_normal;
out vec2 frag_texcoord;

void main() {
    gl_Position = projection * view * model * vec4(position, 1.0);
    frag_normal = mat3(transpose(inverse(model))) * normal;
    frag_texcoord = texcoord;
}