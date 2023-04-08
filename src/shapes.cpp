#include "shapes.hpp"
#include "mathstuff.hpp"
#include "types.hpp"

// sphere
Sphere::Sphere(const Vector& position, float radius): position(position), radius(radius) {}
HitInfo Sphere::ray_test(const Vector& origin, const Vector& direction) const {
    float a = dot(direction, direction);
    Vector tmp{
        origin.x-position.x,
        origin.y-position.y,
        origin.z-position.z,
    };
    float b = 2*dot(direction, tmp);
    float c = dot(tmp, tmp)-std::pow(radius, 2);
    float delta = std::pow(b, 2)-4*a*c; // quadratic equation stuff
    bool one_point = delta == 0;
    bool two_points = delta > 0;
    bool hit = one_point || two_points;
    float distance;
    if (one_point) {
        distance = -b/(2*a);
    }
    if (two_points) {
        float expensive_tmp = std::sqrt(delta);
        float distance1 = (-b-expensive_tmp)/(2*a);
        float distance2 = (-b+expensive_tmp)/(2*a);
        distance = std::fmin(distance1, distance2);
    }
    Vector point {
        origin.x+direction.x*distance,
        origin.y+direction.y*distance,
        origin.z+direction.z*distance,
    };
    Vector to_surface{
        point.x-position.x,
        point.y-position.y,
        point.z-position.z,
    };
    float to_surface_magnitude = magnitude(to_surface);
    Vector normal{
        to_surface.x / to_surface_magnitude,
        to_surface.y / to_surface_magnitude,
        to_surface.z / to_surface_magnitude,
    };
    return HitInfo{hit, point, normal};
}

// tri
Tri::Tri(const Vector& a, const Vector& b, const Vector& c): a(a), b(b), c(c) {}
HitInfo Tri::ray_test(const Vector& origin, const Vector& direction) const {
    // wikipedia is the bomb
    // this implementation is heavily based on Moller-Trumbore wikipedia article
    bool intersects;
    const float epsilon = 0.0001; // small value - I imagine it is for floats being inaccurate at comparisons
    Vector edge1{
        b.x-a.x,
        b.y-a.y,
        b.z-a.z,
    };
    Vector edge2{
        c.x-a.x,
        c.y-a.y,
        c.z-a.z,
    };
    Vector h = cross(direction, edge2);
    float a2 = dot(edge1, h);
    if (a2 > -epsilon && a2 < epsilon) {
        // the ray is parallel to the triangle
        return HitInfo{false};
    }
    float f = 1/a2;
    Vector s{
        origin.x-a.x,
        origin.y-a.y,
        origin.z-a.z,
    };
    float u = f * dot(s, h);
    if (u < 0 || u > 1) {
        return HitInfo{false}; // no intersection
    }
    Vector q = cross(s, edge1);
    float v = f * dot(direction, q);
    if (v < 0 || u + v > 1) {
        return HitInfo{false};
    }
    // here we can compute the distance to the triangle where it is being intersected
    float t = f * dot(edge2, q);
    if (t > epsilon) {
        Vector location{
            origin.x+direction.x*t,
            origin.y+direction.y*t,
            origin.z+direction.z*t,
        };
        return HitInfo{true, location, cross(edge1, edge2)};
    }
    else {
        return HitInfo{false}; // this means that the line intersects, but not in the direction of the ray
    }
}