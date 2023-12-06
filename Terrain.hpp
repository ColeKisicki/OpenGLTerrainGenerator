#pragma once
#include "ProcRenderObject.hpp"
#include <vector>
#include<iostream>
class Terrain : public ProcRenderObject{
public:
    const float ChunkSize = 256.f;
    const float ChunkSections = 16.f;
    Terrain(float locx, float locy, float locz, float rotx, float roty, float rotz, float scax, float scay, float scaz) : ProcRenderObject {locx, locy, locz, rotx, roty, rotz, scax, scay, scaz} {Generate();};
    void Generate();
    //generate chunk
};