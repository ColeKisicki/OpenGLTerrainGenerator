#include "Scene.hpp"
#include "DisplayObject.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "CSCIx229.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

Scene::Scene()
{
    SceneCamera = new Camera();
    InitializeShaders();
}

Scene::~Scene()
{
    delete SceneCamera;
    for(auto Light : SceneLights)
    {
        delete Light;
    }
}

void Scene::RenderScene()
{
        // Activate the shader program
    glUseProgram(shaderProgram);

    // Set the camera properties
    GetCamera()->RenderCamera();

    // Iterate over lights and set light properties
    for (auto& light : SceneLights)
    {
        // Set light properties as uniform variables
        // Assuming uniform names: u_LightPos, u_Ambient, u_Diffuse, u_Specular
        glUniform3fv(glGetUniformLocation(shaderProgram, "u_LightPos"), 1, glm::value_ptr(light->GetLocation()));
        glUniform4fv(glGetUniformLocation(shaderProgram, "u_Ambient"), 1, light->Ambient);
        glUniform4fv(glGetUniformLocation(shaderProgram, "u_Diffuse"), 1, light->Diffuse);
        glUniform4fv(glGetUniformLocation(shaderProgram, "u_Specular"), 1, light->Specular);
        glUniform4fv(glGetUniformLocation(shaderProgram, "u_Specular"), 1, light->Specular);
        // ... Additional properties as needed
    }

    for (auto Object : ObjectsInScene)
    {
        Object->Render(shaderProgram);
    }
    glUseProgram(0);
}

Camera *Scene::GetCamera()
{
    return SceneCamera;
}



std::string Scene::LoadShaderSource(const char *filepath)
{
    std::ifstream shaderFile;
    std::stringstream shaderStream;

    shaderFile.open(filepath);
    shaderStream << shaderFile.rdbuf();
    shaderFile.close();

    return shaderStream.str();
}

unsigned int Scene::CompileShader(unsigned int type, const std::string &source)
{
    unsigned int id = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile "
                  << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
                  << " shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

void Scene::CreateShaderProgram()
{
    shaderProgram = glCreateProgram();
    unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, LoadShaderSource("vertex_shader.glsl"));
    unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, LoadShaderSource("fragment_shader.glsl"));

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glValidateProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Scene::InitializeShaders()
{
    CreateShaderProgram();
}
