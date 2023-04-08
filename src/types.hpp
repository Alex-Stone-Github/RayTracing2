#pragma once

struct float3 {
    float x;
    float y;
    float z;
};
typedef struct float3 Vector;
typedef struct float3 Color;
struct Material {
    Color color;
};
class Shape {
public:
    virtual bool contains_point(const Vector& point) const = 0;
};
struct Object {
    Shape& shape;
    Material material;
};
struct Camera {
    Vector position;
    float yaw;
    float pitch;
};