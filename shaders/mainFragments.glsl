#version 450 core

in vec3 fragmentColor;
in vec2 TexCoord;

uniform sampler2D Texture;
uniform float mixPercent;

void main()
{
   gl_FragColor = mix(texture(Texture, TexCoord), (vec4(fragmentColor,1.0)/2+(0.5)), mixPercent);
}