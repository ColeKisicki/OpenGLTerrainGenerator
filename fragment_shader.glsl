#version 330 core
in vec3 Normal;
in vec3 Color;
in vec3 FragPos;
uniform vec3 u_LightPos;    // Light position
uniform vec4 u_Ambient;     // Ambient color and intensity
uniform vec4 u_Diffuse;     // Diffuse color and intensity
uniform vec4 u_Specular;    // Specular color and intensity
uniform vec3 viewPos;       // Camera position
out vec4 FragColor;

void main()
{
    // Ambient
    vec3 ambient = u_Ambient.rgb * u_Ambient.a;
    
    // Diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(u_LightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = u_Diffuse.rgb * diff * u_Diffuse.a;
    
    // Specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = u_Specular.rgb * specularStrength * spec * u_Specular.a;  
    
    vec3 result = (ambient + diffuse + specular) * Color;
    FragColor = vec4(result, 1.0);
}