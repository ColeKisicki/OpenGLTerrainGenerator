#include "Terrain.hpp"
#include <ctime>
#include <random>
#include <vector>
#include "MarchingCubeTable.cpp"
#include "FastNoiseLite.hpp"
#include <iostream>
#include "glm/glm.hpp"
#include "CSCIx229.hpp"

#define SIZE 16

Terrain::Terrain()
{
    // Seed the random number generator so generation remains constant for all terrain generation
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    FastNoiseLite noise;
    std::vector<std::vector<std::vector<float>>> densityPoints(SIZE, std::vector<std::vector<float>>(SIZE, std::vector<float>(SIZE)));
    noise.SetSeed(100);
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    noise.SetFrequency(0.02);
    //generate chunk
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 16; ++j) {
            for (int k = 0; k < 16; ++k) {
                float val = noise.GetNoise((float)i, (float)j, (float)k);
                densityPoints[i][j][k] = val;
            }
        }
    }
    
    //need to go through and identify which cube is being accessed

}