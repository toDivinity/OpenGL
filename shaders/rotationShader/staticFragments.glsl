#version 450 core

in vec2 texCoord;
in vec3 fragmentColor;

uniform sampler2D loadedTexture;

void main()
{
   gl_FragColor = mix(texture(loadedTexture, texCoord), vec4(fragmentColor, 1.0f), 0.25f);
}