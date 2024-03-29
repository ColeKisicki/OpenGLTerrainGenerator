#version 330 core
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;

out vec3 Normal;
out vec3 Color;
out vec3 FragPos;  // Output world position of the fragment

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    Normal = aNormal;
    Color = aColor;
    FragPos = vec3(model * vec4(aPos, 1.0)); // Calculate world position
}