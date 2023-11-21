#pragma once
#include "DisplayObject.hpp"

class Cube : public DisplayObject
{
public:
    //parameterized constructors that pass info back to the default
    Cube(Vector3 loc, Vector3 rot, Vector3 sca) : DisplayObject {loc,rot,sca} {;};
    Cube(float locx, float locy, float locz, float rotx, float roty, float rotz, float scax, float scay, float scaz) : DisplayObject {locx, locy, locz, rotx, roty, rotz, scax, scay, scaz} {;};
    virtual void Display() override;
};
