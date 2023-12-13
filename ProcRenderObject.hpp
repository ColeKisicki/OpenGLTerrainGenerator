#pragma once
#include "glm/glm.hpp"
#include <vector>
#include "basic_structures.hpp"
#include "DisplayObject.hpp"

class ProcRenderObject : public DisplayObject
{
public:
    std::vector<Triangle> objectTris;
    //parameterized constructors that pass info back to the default
    ProcRenderObject(glm::vec3 loc, glm::vec3 rot, glm::vec3 sca) : DisplayObject {loc,rot,sca} {;};
    ProcRenderObject(float locx, float locy, float locz, float rotx, float roty, float rotz, float scax, float scay, float scaz) : DisplayObject {locx, locy, locz, rotx, roty, rotz, scax, scay, scaz}{;};
    virtual void Render() override;
    void drawNormalLine(glm::vec3 &location, glm::vec3 &normal);
};
