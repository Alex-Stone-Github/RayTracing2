#include "shapes.hpp"

Sphere::Sphere(Vector position, float radius): position(position), radius(radius) {}
bool Sphere::contains_point(const Vector& point) const {
    return std::pow((point.x-position.x),2)
        +std::pow((point.y-position.y),2)
        +std::pow((point.z-position.z),2)
        < std::pow(radius, 2);
}