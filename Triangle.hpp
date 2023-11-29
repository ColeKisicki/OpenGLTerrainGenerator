#pragma once
#include "glm/glm.hpp"
struct Triangle {
    glm::vec3 p1, p2, p3;
    Triangle(glm::vec3 _p1 = glm::vec3(0,0,0), glm::vec3 _p2 = glm::vec3(0,0,0), glm::vec3 _p3 = glm::vec3(0,0,0))
        : p1(_p1), p2(_p2), p3(_p3) {}
};