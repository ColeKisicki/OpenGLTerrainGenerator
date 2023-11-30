#pragma once
#include <vector>
class Terrain {
public:
    const float ChunkSize = 256.f;
    const float ChunkSections = 16.f;
    Terrain();
    //generate chunk
    std::vector<class Triangle> terrainTris;
    //
};