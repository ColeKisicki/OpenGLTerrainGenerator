#include "MarchingCubeObject.hpp"
#include "MarchingCubeTable.cpp"
#include "CSCIx229.hpp"

#include <ctime>
#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Scene.hpp"
#include "FastNoiseLite.hpp"

glm::mat4 GetProjectionMatrix(double fov, double asp, double dim)
{
    return glm::perspective(glm::radians(fov), asp, dim / 16, 16 * dim);
}

MarchingCubeObject::MarchingCubeObject(float isolevel) : DisplayObject(0, 0, 0, 0, 0, 0, 0, 0, 0)
{
    this->isolevel = isolevel;
}


void MarchingCubeObject::GenerateMesh()
{

    // Clear existing triangles and vertices
    objectTris.clear();
    uniqueVertices.clear();

    for (size_t i = 0; i < densityGrid.size() - 1; i++)
    {
        for (size_t j = 0; j < densityGrid[i].size() - 1; j++)
        {
            for (size_t k = 0; k < densityGrid[i][j].size() - 1; k++)
            {
                glm::vec3 cubeVertices[8] = {
                    glm::vec3(i, j, k),
                    glm::vec3(i, j, k + 1),
                    glm::vec3(i + 1, j, k + 1),
                    glm::vec3(i + 1, j, k),
                    glm::vec3(i, j + 1, k),
                    glm::vec3(i, j + 1, k + 1),
                    glm::vec3(i + 1, j + 1, k + 1),
                    glm::vec3(i + 1, j + 1, k)};
                float cubeValues[8] = {0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f};

                // Populate cubeVertices and cubeValues based on i, j, and k
                for (int v = 0; v < 8; v++)
                {
                    // Assign density values from the densityGrid to cubeValues[v]
                    cubeValues[v] = densityGrid[cubeVertices[v].x][cubeVertices[v].y][cubeVertices[v].z]; // Replace with actual index calculation
                }

                int cubeIndex = 0;
                for (int n = 0; n < 8; n++)
                {
                    if (cubeValues[n] < isolevel)
                        cubeIndex |= 1 << n;
                }

                // Process each triangle
                for (int p = 0; triangulation[cubeIndex][p] != -1; p += 3)
                {
                    std::shared_ptr<Vertex> vertices[3];

                    // Interpolation and getting/creating vertices
                    for (int v = 0; v < 3; ++v)
                    {
                        int a = cornerIndexAFromEdge[triangulation[cubeIndex][p + v]];
                        int b = cornerIndexBFromEdge[triangulation[cubeIndex][p + v]];
                        glm::vec3 position = VertexInterp(cubeVertices[a], cubeVertices[b], cubeValues[a], cubeValues[b]);
                        vertices[v] = GetOrCreateVertex(position);
                    }

                    // Calculate face normal for the triangle
                    glm::vec3 faceNormal = glm::normalize(glm::cross(vertices[1]->location - vertices[0]->location, vertices[2]->location - vertices[0]->location));

                    // Accumulate normals
                    for (int v = 0; v < 3; ++v)
                    {
                        vertices[v]->normal += faceNormal;
                    }

                    Triangle tri(vertices[0], vertices[1], vertices[2]);
                    objectTris.push_back(tri);
                }
            }
        }
    }

    // Normalize the accumulated normals for each vertex
    for (auto &[key, vertex] : uniqueVertices)
    {
        vertex->normal = glm::normalize(vertex->normal);
    }
}

void MarchingCubeObject::Render(unsigned int shaderProgramID)
{
    // Update matrices
    glm::mat4 modelMatrix = glm::mat4(1.0f); // Identity matrix for model matrix
    glm::mat4 viewMatrix = Scene::GetScene()->GetCamera()->GetViewMatrix();
    glm::mat4 projectionMatrix = GetProjectionMatrix(55, 2, 20);


    // Assuming you have GLuint shaderProgram and the uniform locations
    GLuint modelLoc = glGetUniformLocation(shaderProgramID, "model");
    GLuint viewLoc = glGetUniformLocation(shaderProgramID, "view");
    GLuint projectionLoc = glGetUniformLocation(shaderProgramID, "projection");

    // Pass matrices to the shader
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    

    // Bind the VAO
    glBindVertexArray(VAO);

    // Draw the mesh
    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(objectTris.size() * 3)); // 3 vertices per triangle

    // Unbind the VAO
    glBindVertexArray(0);
}

glm::vec3 MarchingCubeObject::VertexInterp(const glm::vec3 &p1, const glm::vec3 &p2, float valp1, float valp2)
{
    float t = (isolevel - valp1) / (valp2 - valp1);
    glm::vec3 location = p1 + (t * (p2 - p1));
    return location;
}

std::shared_ptr<Vertex> MarchingCubeObject::GetOrCreateVertex(const glm::vec3 &position)
{
    auto it = uniqueVertices.find(position);
    if (it != uniqueVertices.end())
    {
        return it->second;
    }
    else
    {
        auto newVertex = std::make_shared<Vertex>();
        newVertex->location = position;
        // Set other properties...
        uniqueVertices[position] = newVertex;
        return newVertex;
    }
}

const std::vector<Triangle> &MarchingCubeObject::GetTriangles() const
{
    return objectTris;
}

void MarchingCubeObject::PrepareVertexData()
{

    std::vector<float> vertexData;
    for (const auto &tri : objectTris)
    {
        for (const auto &vertexPtr : {tri.p1, tri.p2, tri.p3})
        {
            const Vertex &vertex = *vertexPtr;
            // Position
            vertexData.push_back(vertex.location.x);
            vertexData.push_back(vertex.location.y);
            vertexData.push_back(vertex.location.z);
            // Normal
            vertexData.push_back(vertex.normal.x);
            vertexData.push_back(vertex.normal.y);
            vertexData.push_back(vertex.normal.z);
            // Color (assuming Vertex struct has color)
            vertexData.push_back(vertex.color.r);
            vertexData.push_back(vertex.color.g);
            vertexData.push_back(vertex.color.b);
        }
    }

    // Create and bind VBO and VAO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Color attribute
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void MarchingCubeObject::PopulateDensityGrid()
{
    densityGrid.clear();
    static int SIZE = 100;
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

    // generate chunk
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            for (int k = 0; k < SIZE; ++k)
            {
                float val = 0.f;
                if (i == 0)
                    val = 1.f;
                if (j == 0)
                    val = 1.f;
                if (k == 0)
                    val = 1.f;
                // Adjust the densityPoints array based on the height value
                densityGrid[i][j][k] = val;
            }
        }
    }
}
