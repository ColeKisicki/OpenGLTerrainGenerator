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


Terrain::Terrain(float isolevel) : MarchingCubeObject(isolevel)
{
    GenerateTerrain();
}

void Terrain::GenerateTerrain()
{
    densityGrid.clear();
    FastNoiseLite noise;
    densityGrid.resize(SIZE);

    // Resize each 2D vector inside the outer vector
    for (auto &grid2D : densityGrid)
    {
        grid2D.resize(SIZE);

        // Resize each 1D vector inside the 2D vector
        for (auto &grid1D : grid2D)
        {
            grid1D.resize(SIZE);
        }
    }
    std::vector<std::vector<float>> HeightMap(SIZE, std::vector<float>(SIZE, 0.0f));
    
    noise.SetSeed(35);
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    noise.SetFrequency(0.02);
    
    // Add octaves, lacunarity, persistence, noise scale, and noise weight here
    noise.SetFractalOctaves(4); // Number of octaves
    noise.SetFractalLacunarity(2.0f); // Lacunarity
    noise.SetFractalGain(0.5f); // Persistence

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
                if (j < (HeightMap[i][k] * MAX_HEIGHT))
                    val = glm::clamp((HeightMap[i][k] * MAX_HEIGHT) - j, 0.0f, 1.0f);
                // Adjust the densityPoints array based on the height value
                densityGrid[i][j][k] = val;
            }
        }
    }
}

void Terrain::AddVertexColors()
{
    for (auto &[key, vertex] : uniqueVertices)
    {
        // Get the vertex's position
        glm::vec3 position = vertex->location;
        float steepness = glm::dot(vertex->normal, glm::vec3(0.0f, 1.0f, 0.0f)); // Assuming up is the reference direction

        // Calculate color based on height (you can adjust these values)
        glm::vec3 color;
        if (position.y > MAX_HEIGHT * 0.5)
        {
            color = glm::vec3(1.0f, 1.0f, 1.0f); // White

        }
        else if (steepness < 0.5f)
        {
            // Stone color
            color = glm::vec3(0.5f, 0.5f, 0.5f); // Grey
        }
        else
        {
            // Grass color
            color = glm::vec3(0.0f, 1.0f, 0.0f); // Green
        }

        vertex->color = color; // Set the color for the vertex
    }
}

void Terrain::GenerateMesh()
{
    MarchingCubeObject::GenerateMesh();
    AddVertexColors();
}
