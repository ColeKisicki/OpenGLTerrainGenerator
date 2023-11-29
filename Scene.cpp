#include "Scene.hpp"
#include "DisplayObject.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "glm/glm.hpp"
#include "CSCIx229.hpp"
#include <iostream>

void Scene::RenderScene()
{
    
    //  OpenGL should normalize normal vectors
    glEnable(GL_NORMALIZE);
    //  Enable lighting
    glEnable(GL_LIGHTING);
    //  Location of viewer for specular calculations
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 0);
    //  glColor sets ambient and diffuse color materials
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    for (long long unsigned int i = 0; i < SceneLights.size(); i++)
    {
        if (i > 7)
        {
            Fatal("Too many lights in scene. Max of 8");
        }
        glEnable(GL_LIGHT0 + i);
        glLightfv(GL_LIGHT0 + i, GL_AMBIENT, SceneLights[i]->Ambient);
        glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, SceneLights[i]->Diffuse);
        glLightfv(GL_LIGHT0 + i, GL_SPECULAR, SceneLights[i]->Specular);
        float Location[3] = {SceneLights[i]->GetLocation().x, SceneLights[i]->GetLocation().y, SceneLights[i]->GetLocation().z};
        glLightfv(GL_LIGHT0 + i, GL_POSITION, Location);
    }
    for (auto Object : ObjectsInScene)
    {
        Object->Display();
    }
    glDisable(GL_LIGHTING);
}

Camera *Scene::GetCamera()
{
    if (!SceneCamera)
    {
        SceneCamera = new Camera();
    }
    return SceneCamera;
}
