#pragma once
#include "Vector3.hpp"
#include <string>
#include "Material.hpp"

class DisplayObject{
    private:
    
    public:
    Vector3 Location;
    Vector3 Rotation;
    Vector3 Scale;
    Material ObjectMaterial;
    
    DisplayObject();
    DisplayObject(Vector3 loc, Vector3 rot, Vector3 sca);
    DisplayObject(float locx, float locy, float locz, float rotx, float roty, float rotz, float scax, float scay, float scaz);
    virtual void Display();
    inline bool GetIsVisible() {return IsVisible;};
    inline void SetIsVisible(bool NewVisibility) {IsVisible = NewVisibility;};
    
    protected:
    bool IsVisible = true;
    bool SmoothShading = false;
};