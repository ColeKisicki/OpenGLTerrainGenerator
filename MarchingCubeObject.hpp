#pragma once

#include "basic_structures.hpp"
#include "CSCIx229.hpp"
#include "DisplayObject.hpp"
#include <vector>
#include <unordered_map>


struct Vec3Hash {
    std::size_t operator()(const glm::vec3& v) const {
        std::size_t h1 = std::hash<float>{}(v.x);
        std::size_t h2 = std::hash<float>{}(v.y);
        std::size_t h3 = std::hash<float>{}(v.z);
        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};

class MarchingCubeObject : public DisplayObject
{
public:
    MarchingCubeObject(float isolevel);
    std::string LoadShaderSource(const char *filepath);
    unsigned int CompileShader(unsigned int type, const std::string &source);
    void CreateShaderProgram();
    void InitializeShaders();
    virtual void GenerateMesh();
    virtual void Render() override;
    glm::vec3 VertexInterp(const glm::vec3 &p1, const glm::vec3 &p2, float valp1, float valp2);
    std::shared_ptr<Vertex> GetOrCreateVertex(const glm::vec3 &position);
    const std::vector<Triangle> &GetTriangles() const;
    void PrepareVertexData();
    void PopulateDensityGrid();

protected:
    unsigned int shaderProgram;
    float isolevel;
    std::vector<Triangle> objectTris;
    std::vector<std::vector<std::vector<float>>> densityGrid;
    std::unordered_map<glm::vec3, std::shared_ptr<Vertex>, Vec3Hash> uniqueVertices;
    unsigned int VAO, VBO = 0; // Add these member variables
};