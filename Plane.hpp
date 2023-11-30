#pragma once
#include "glm/glm.hpp"
#include "DisplayObject.hpp"

class Plane : public DisplayObject
{
public:
    unsigned int textureID = 0;
    unsigned int textureScale = 1;
    //parameterized constructors that pass info back to the default
    Plane(glm::vec3 loc, glm::vec3 rot, glm::vec3 sca) : DisplayObject {loc,rot,sca} {;};
    Plane(float locx, float locy, float locz, float rotx, float roty, float rotz, float scax, float scay, float scaz, unsigned int _textureID) : DisplayObject {locx, locy, locz, rotx, roty, rotz, scax, scay, scaz}, textureID(_textureID){;};
    virtual void Display() override;
};