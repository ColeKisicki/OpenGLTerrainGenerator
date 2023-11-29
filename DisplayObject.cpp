#include "DisplayObject.hpp"
#include "CSCIx229.hpp"

DisplayObject::DisplayObject()
{
    // default constructor
    Location = glm::vec3(0.f, 0.f, 0.f);
    Rotation = glm::vec3(0.f, 0.f, 0.f);
    Scale = glm::vec3(1.f, 1.f, 1.f);
}

DisplayObject::DisplayObject(glm::vec3 loc, glm::vec3 rot, glm::vec3 sca)
{
    Location = loc;
    Rotation = rot;
    Scale = sca;
}

DisplayObject::DisplayObject(float locx, float locy, float locz, float rotx, float roty, float rotz, float scax, float scay, float scaz)
{
    Location = glm::vec3(locx,locy,locz);
    Rotation = glm::vec3(rotx,roty,rotz);
    Scale = glm::vec3(scax,scay,scaz);
}

void DisplayObject::Display()
{
}