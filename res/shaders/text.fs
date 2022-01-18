#version 330 core

in vec2 TexCoords;

out vec4 Color;

uniform sampler2D texture;
uniform vec3 color;

void main()
{
    //vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
    //Color = vec4(color, 1.0) * sampled;

    Color = vec4(color.rgb, texture2D(texture, TexCoords).a);
}