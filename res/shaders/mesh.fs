#version 330 core

out vec4 Color;

in vec2 TexCoords;

uniform sampler2D diffuse0;

void main()
{
	vec4 color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    Color = color * vec4(texture(diffuse0, TexCoords));
}
