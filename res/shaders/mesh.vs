#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 projview;

void main()
{
    gl_Position = projview * model * vec4(position, 1.0f);
    TexCoords = uv;
}
