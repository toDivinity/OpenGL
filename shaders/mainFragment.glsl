#version 450 core
in vec3 frag_normal;
in vec2 frag_texcoord;

out vec4 color;

uniform vec3 light_dir = normalize(vec3(0.5, 1.0, 0.7));
uniform vec3 light_color = vec3(1.0, 1.0, 1.0);
uniform vec3 object_color = vec3(0.7, 0.0, 0.0);

void main() {
    float diff = max(dot(frag_normal, light_dir), 0.0);
    vec3 diffuse = diff * light_color;
    
    color = vec4((diffuse * 0.7 + 0.3) * object_color, 1.0);
}