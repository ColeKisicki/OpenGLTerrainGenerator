#pragma once
#include "glm/glm.hpp"

struct Vertex
{
    glm::vec3 location = glm::vec3(0.f,0.f,0.f);
    glm::vec3 normal = glm::vec3(0.f,0.f,0.f);
};

struct Triangle
{
    Vertex p1, p2, p3;
    Triangle(){;};
    Triangle(const Vertex &vertex1, const Vertex &vertex2, const Vertex &vertex3)
        : p1(vertex1), p2(vertex2), p3(vertex3){;};
};
