#version 330 core
in vec3 Normal;
in vec3 Color;

out vec4 FragColor;

void main()
{
    // Simple lighting calculation
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(vec3(-0.2f, -1.0f, -0.3f));
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(1.0); // Assuming white light

    vec3 result = (diffuse + vec3(0.1)) * Color; // Simple ambient light
    FragColor = vec4(result, 1.0);
}