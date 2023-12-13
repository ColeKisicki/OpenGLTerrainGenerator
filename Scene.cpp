#include "Scene.hpp"
#include "DisplayObject.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "glm/glm.hpp"
#include "CSCIx229.hpp"
#include <iostream>

Scene::Scene()
{
    SceneCamera = new Camera();
}

Scene::~Scene()
{
    delete SceneCamera;
    for(auto Object: ObjectsInScene)
    {
        delete Object;
    }
    for(auto Light : SceneLights)
    {
        delete Light;
    }
}
void Scene::RenderScene()
{
    GetCamera()->RenderCamera();
    //  OpenGL should normalize normal vectors
    glEnable(GL_NORMALIZE);
    //  Enable lighting
    glEnable(GL_LIGHTING);
    //  Location of viewer for specular calculations
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 0);
    //  glColor sets ambient and diffuse color materials
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    for (long long unsigned int i = 0; i < SceneLights.size(); i++)
    {
        if (i > 7)
        {
            Fatal("Too many lights in scene. Max of 8");
        }
        glEnable(GL_LIGHT0 + i);

        // Apply transformations to the light position
        glm::vec3 lightPos = SceneLights[i]->GetLocation();
        glPushMatrix();
        glTranslatef(lightPos.x, lightPos.y, lightPos.z); // Translate light position
        // Apply any other transformations (e.g., rotation, scaling) to the light if needed
        // ...

        // Set the transformed light position
        float TransformedLocation[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
        glLightfv(GL_LIGHT0 + i, GL_POSITION, TransformedLocation);
        glPopMatrix();

        // Set light properties
        glLightfv(GL_LIGHT0 + i, GL_AMBIENT, SceneLights[i]->Ambient);
        glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, SceneLights[i]->Diffuse);
        glLightfv(GL_LIGHT0 + i, GL_SPECULAR, SceneLights[i]->Specular);

        // Render a sphere at the light's position for debugging
        glPushMatrix();
        glTranslatef(lightPos.x, lightPos.y, lightPos.z);
        glutSolidSphere(0.2, 20, 20); // Adjust the radius as needed
        glPopMatrix();
    }

    for (auto Object : ObjectsInScene)
    {
        Object->Display();
    }

    glDisable(GL_LIGHTING);
    glDisable(GL_COLOR_MATERIAL);
}

Camera *Scene::GetCamera()
{
    return SceneCamera;
}
