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

#define SIZE 400
#define ISOLEVEL 0.5f
#define MAX_HEIGHT 30.f
#define CUBE_SIZE 0.6

glm::vec3 interpolateVerts(glm::vec4 v1, glm::vec4 v2)
{
    float t = (ISOLEVEL - v1.w) / (v2.w - v1.w);
    return glm::vec3(v1) + t * (glm::vec3(v2) - glm::vec3(v1));
}

int indexFromCoord(int x, int y, int z)
{
    return z * SIZE * SIZE + y * SIZE + x;
}

void Terrain::Generate()
{
    // Seed the random number generator so generation remains constant for all terrain generation
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    FastNoiseLite noise;
    std::vector<std::vector<std::vector<glm::vec4>>> densityPoints(SIZE, std::vector<std::vector<glm::vec4>>(SIZE, std::vector<glm::vec4>(SIZE)));
    std::vector<std::vector<float>> HeightMap(SIZE, std::vector<float>(SIZE, 0.0f));
    noise.SetSeed(100);
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    noise.SetFrequency(0.02);

    // Generate HeightMap using noise.GetNoise(x,y)
    for (int y = 0; y < SIZE; y++)
    {
        for (int x = 0; x < SIZE; x++)
        {
            float noiseVal = (noise.GetNoise((float)x, (float)y) + 1.f) / 2.f;
            HeightMap[y][x] = noiseVal;
        }
    }

    // generate chunk
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            for (int k = 0; k < SIZE; ++k)
            {
                float val = 0.f;
                if (j == 0)
                    val = 1.f;
                else if (j < (HeightMap[i][k] * MAX_HEIGHT))
                    val = glm::clamp((HeightMap[i][k] * MAX_HEIGHT) - j, 0.0f, 1.0f);
                // std::cout<<val<<std::endl;
                // Adjust the densityPoints array based on the height value
                densityPoints[i][j][k] = glm::vec4(i * CUBE_SIZE, j * CUBE_SIZE, k * CUBE_SIZE, val);
            }
        }
    }

    // march cubes
    // numcubes = (size - 1) ^3
    for (long long unsigned int i = 0; i < (densityPoints.size() - 1); i++)
    {
        for (long long unsigned int j = 0; (j < densityPoints[i].size() - 1); j++)
        {
            for (long long unsigned int k = 0; k < (densityPoints[i][j].size() - 1); k++)
            {
                glm::vec4 curPoint = densityPoints[i][j][k];
                // Array of current verices of cube

                // Might need to change order of z, y, x
                glm::vec4 cubeVertices[8] = {
                    densityPoints[curPoint.z][curPoint.y][curPoint.x],
                    densityPoints[curPoint.z][curPoint.y][curPoint.x + 1],
                    densityPoints[curPoint.z + 1][curPoint.y][curPoint.x + 1],
                    densityPoints[curPoint.z + 1][curPoint.y][curPoint.x],
                    densityPoints[curPoint.z][curPoint.y + 1][curPoint.x],
                    densityPoints[curPoint.z][curPoint.y + 1][curPoint.x + 1],
                    densityPoints[curPoint.z + 1][curPoint.y + 1][curPoint.x + 1],
                    densityPoints[curPoint.z + 1][curPoint.y + 1][curPoint.x]};
                // Might need to change order of z, y, x

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

                // Goes through points in 3s until runs out of points
                for (int p = 0; triangulation[cubeIndex][p] != -1; p += 3)
                {
                    // interpolates each edge based on weighted noises
                    int a0 = cornerIndexAFromEdge[triangulation[cubeIndex][p]];
                    int b0 = cornerIndexBFromEdge[triangulation[cubeIndex][p]];

                    int a1 = cornerIndexAFromEdge[triangulation[cubeIndex][p + 1]];
                    int b1 = cornerIndexBFromEdge[triangulation[cubeIndex][p + 1]];

                    int a2 = cornerIndexAFromEdge[triangulation[cubeIndex][p + 2]];
                    int b2 = cornerIndexBFromEdge[triangulation[cubeIndex][p + 2]];

                    Vertex v1, v2, v3;
                    v1.location = interpolateVerts(cubeVertices[a0], cubeVertices[b0]);
                    v2.location = interpolateVerts(cubeVertices[a1], cubeVertices[b1]);
                    v3.location = interpolateVerts(cubeVertices[a2], cubeVertices[b2]);
                    // Calculate face normal for the triangle
                    glm::vec3 faceNormal = glm::normalize(glm::cross(v2.location - v1.location, v3.location - v1.location));

                    // Accumulate face normals to vertex normals using corner indices
                    v1.normal += faceNormal;
                    v2.normal += faceNormal;
                    v3.normal += faceNormal;
                    Triangle tri(v1, v2, v3);
                    objectTris.push_back(tri);
                }
            }
        }
    }
}