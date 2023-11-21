#include "DisplayObject.hpp"
#ifdef USEGLEW
#include <GL/glew.h>
#endif
//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
// Tell Xcode IDE to not gripe about OpenGL deprecation
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#else
#include <GL/glut.h>
#endif

DisplayObject::DisplayObject()
{
    // default constructor
    Location = Vector3(0.f, 0.f, 0.f);
    Rotation = Vector3(0.f, 0.f, 0.f);
    Scale = Vector3(1.f, 1.f, 1.f);
}

DisplayObject::DisplayObject(Vector3 loc, Vector3 rot, Vector3 sca)
{
    Location = loc;
    Rotation = rot;
    Scale = sca;
}

DisplayObject::DisplayObject(float locx, float locy, float locz, float rotx, float roty, float rotz, float scax, float scay, float scaz)
{
    Location = Vector3(locx,locy,locz);
    Rotation = Vector3(rotx,roty,rotz);
    Scale = Vector3(scax,scay,scaz);
}

void DisplayObject::Display()
{
}