#pragma once
#include "Vector3.hpp"
struct Triangle {
    Vector3 p1, p2, p3;
    Triangle(Vector3 _p1 = Vector3(0,0,0), Vector3 _p2 = Vector3(0,0,0), Vector3 _p3 = Vector3(0,0,0))
        : p1(_p1), p2(_p2), p3(_p3) {}
};