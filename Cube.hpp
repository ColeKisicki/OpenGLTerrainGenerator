#pragma once
#include "glm/glm.hpp"
#include "DisplayObject.hpp"

class Cube : public DisplayObject
{
public:
    //parameterized constructors that pass info back to the default
    Cube(glm::vec3 loc, glm::vec3 rot, glm::vec3 sca) : DisplayObject {loc,rot,sca} {;};
    Cube(float locx, float locy, float locz, float rotx, float roty, float rotz, float scax, float scay, float scaz) : DisplayObject {locx, locy, locz, rotx, roty, rotz, scax, scay, scaz} {;};
    virtual void Render() override;
};
