#pragma once
#include <string>
#include "glm/glm.hpp"
#include "Material.hpp"

class DisplayObject{
    private:
    
    public:
    glm::vec3 Location;
    glm::vec3 Rotation;
    glm::vec3 Scale;
    Material ObjectMaterial;
    
    DisplayObject();
    DisplayObject(glm::vec3 loc, glm::vec3 rot, glm::vec3 sca);
    DisplayObject(float locx, float locy, float locz, float rotx, float roty, float rotz, float scax, float scay, float scaz);
    virtual void Render(unsigned int shaderProgramID);
    inline bool GetIsVisible() {return IsVisible;};
    inline void SetIsVisible(bool NewVisibility) {IsVisible = NewVisibility;};
    
    protected:
    bool IsVisible = true;
    bool SmoothShading = false;
};