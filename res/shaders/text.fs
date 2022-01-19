#version 330 core

in vec2 TexCoords;

out vec4 Color;

uniform sampler2D texture;
uniform vec4 color;

void main()
{
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture2D(texture, TexCoords).r);
    Color = color * sampled;
}