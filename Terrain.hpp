#pragma once
#include <vector>
#include "MarchingCubeObject.hpp"
#include<iostream>
class Terrain : public MarchingCubeObject {
public:
    const int SIZE = 200;
    const int MAX_HEIGHT = 100;

    Terrain(float isolevel);
    void GenerateTerrain();
    void AddVertexColors();
    virtual void GenerateMesh() override;

    // Add any additional methods or properties specific to Terrain here
};