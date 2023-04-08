#pragma once

#include <cmath>

#include "types.hpp"

class Sphere: public Shape{
private:
    Vector position;
    float radius;
public:
    Sphere(Vector position, float radius);
    virtual bool contains_point(const Vector& point) const;
};