#pragma once

#include <cmath>

#include "types.hpp"
#include "mathstuff.hpp"

class Sphere: public Shape{
private:
    Vector position;
    float radius;
public:
    Sphere(const Vector& position, float radius);
    HitInfo ray_test(const Vector& origin, const Vector& direction) const override;
};
class Tri: public Shape {
private:
    Vector a, b, c;
public:
    Tri(const Vector& a, const Vector& b, const Vector& c);
    HitInfo ray_test(const Vector& origin, const Vector& direction) const override;
};

/*
class Box: public Shape{
private:
    Vector position;
    Vector size;
public:
    Box(Vector position, Vector size);
    HitInfo ray_test(const Vector& origin, const Vector& direction) const override;
};
*/