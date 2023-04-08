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
    float smoothness;
};
struct HitInfo {
    bool hit;
    Vector location;
    Vector normal;
};
class Shape {
public:
    virtual HitInfo ray_test(const Vector& origin, const Vector& direction) const = 0;
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