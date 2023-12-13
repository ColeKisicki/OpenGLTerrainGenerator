#pragma once
#include "glm/glm.hpp"
#include <memory>

struct Vertex {
    glm::vec3 location = glm::vec3(0.f, 0.f, 0.f);
    glm::vec3 normal = glm::vec3(0.f, 0.f, 0.f);
    glm::vec3 color = glm::vec3(1.f,1.f,1.f);
};

struct Triangle {
    std::shared_ptr<Vertex> p1, p2, p3;

    Triangle() = default;

    Triangle(const std::shared_ptr<Vertex>& vertex1, const std::shared_ptr<Vertex>& vertex2, const std::shared_ptr<Vertex>& vertex3)
        : p1(vertex1), p2(vertex2), p3(vertex3) { };
};