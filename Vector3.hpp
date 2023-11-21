#pragma once

struct Vector3
{
    float x, y, z;
    Vector3(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f)
        : x(_x), y(_y), z(_z) {}
};