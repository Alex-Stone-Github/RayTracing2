#include "mathstuff.hpp"

float map(float value, float a, float b, float c, float d) {
    float percent = (value-a)/(b-a);
    return percent * (d-c) + c;
}
float magnitude(const Vector& v) {
    return sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
}
float dot(const Vector& a, const Vector& b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}
Vector cross(const Vector& a, const Vector& b) {
    return Vector{
        a.y*b.z-a.z*b.y,
        a.z*b.x-a.x-b.z,
        a.x*b.y-a.y*b.x,
    };
}
float lerp(float t, float a, float b) {
    return a + t*(b-a);
}
float distance(const Vector& a, const Vector& b) {
    return std::sqrt(
        std::pow((a.x-b.x), 2) +
        std::pow((a.y-b.y), 2) +
        std::pow((a.z-b.z), 2));
}

