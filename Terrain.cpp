#include "Terrain.hpp"
#include <ctime>
#include <random>
#include <vector>
#include "MarchingCubeTable.cpp"
#include "FastNoiseLite.hpp"
#include <iostream>
#include "glm/glm.hpp"
#include "basic_structures.hpp"
#include "CSCIx229.hpp"

#define SIZE 4
#define ISOLEVEL 0.04

glm::vec3 interpolateVerts(glm::vec4 v1, glm::vec4 v2)
{
    float t = (ISOLEVEL - v1.w) / (v2.w - v1.w);
    return glm::vec3(v1) + t * (glm::vec3(v2) - glm::vec3(v1));
}

int indexFromCoord(int x, int y, int z)
{
    return z * SIZE * SIZE + y * SIZE + x;
}

Terrain::Terrain()
{
    // Seed the random number generator so generation remains constant for all terrain generation
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    FastNoiseLite noise;
    std::vector<std::vector<std::vector<glm::vec4>>> densityPoints(SIZE, std::vector<std::vector<glm::vec4>>(SIZE, std::vector<glm::vec4>(SIZE)));
    noise.SetSeed(100);
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    noise.SetFrequency(0.02);
    // generate chunk
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            for (int k = 0; k < SIZE; ++k)
            {
                float val = noise.GetNoise((float)i, (float)j, (float)k);
                densityPoints[i][j][k] = glm::vec4(i, j, k, val);
            }
        }
    }

    // march cubes

    // numcubes = (size - 1) ^3
    for (int i = 0; i < (densityPoints.size() - 1); i++)
    {
        for (int j = 0; (j < densityPoints[i].size() - 1); j++)
        {
            for (int k = 0; k < (densityPoints[i][j].size() - 1); k++)
            {
                glm::vec4 curPoint = densityPoints[k][j][i];
                // Array of current verices of cube

                // WRONG
                glm::vec4 cubeVertices[8] = {
                    densityPoints[curPoint.z][curPoint.y][curPoint.x],
                    densityPoints[curPoint.z][curPoint.y][curPoint.x + 1],
                    densityPoints[curPoint.z + 1][curPoint.y][curPoint.x + 1],
                    densityPoints[curPoint.z + 1][curPoint.y][curPoint.x],
                    densityPoints[curPoint.z][curPoint.y + 1][curPoint.x],
                    densityPoints[curPoint.z][curPoint.y + 1][curPoint.x + 1],
                    densityPoints[curPoint.z + 1][curPoint.y + 1][curPoint.x + 1],
                    densityPoints[curPoint.z + 1][curPoint.y + 1][curPoint.x]};
                //WRONG

                int cubeIndex = 0;
                if (cubeVertices[0].w < ISOLEVEL)
                    cubeIndex |= (int)1;
                if (cubeVertices[1].w < ISOLEVEL)
                    cubeIndex |= (int)2;
                if (cubeVertices[2].w < ISOLEVEL)
                    cubeIndex |= (int)4;
                if (cubeVertices[3].w < ISOLEVEL)
                    cubeIndex |= (int)8;
                if (cubeVertices[4].w < ISOLEVEL)
                    cubeIndex |= (int)16;
                if (cubeVertices[5].w < ISOLEVEL)
                    cubeIndex |= (int)32;
                if (cubeVertices[6].w < ISOLEVEL)
                    cubeIndex |= (int)64;
                if (cubeVertices[7].w < ISOLEVEL)
                    cubeIndex |= (int)128;

                // Create triangles for current cube configuration
                for (int i = 0; triangulation[cubeIndex][i] != -1; i += 3)
                {
                    // Get indices of corner points A and B for each of the three edges
                    // of the cube that need to be joined to form the triangle.
                    int a0 = cornerIndexAFromEdge[triangulation[cubeIndex][i]];
                    int b0 = cornerIndexBFromEdge[triangulation[cubeIndex][i]];

                    int a1 = cornerIndexAFromEdge[triangulation[cubeIndex][i + 1]];
                    int b1 = cornerIndexBFromEdge[triangulation[cubeIndex][i + 1]];

                    int a2 = cornerIndexAFromEdge[triangulation[cubeIndex][i + 2]];
                    int b2 = cornerIndexBFromEdge[triangulation[cubeIndex][i + 2]];

                    Triangle tri;
                    tri.p1 = interpolateVerts(cubeVertices[a0], cubeVertices[b0]);
                    tri.p2 = interpolateVerts(cubeVertices[a1], cubeVertices[b1]);
                    tri.p3 = interpolateVerts(cubeVertices[a2], cubeVertices[b2]);
                    terrainTris.push_back(tri);
                }
            }
        }
    }
}