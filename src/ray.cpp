#include "ray.hpp"
#include "mathstuff.hpp"
#include <tuple>

Color ray_trace(const Vector& origin, const Vector& direction, const std::vector<Object>& objects) {
    Vector light = AMBIENT_LIGHT;
    Vector current_origin = origin;
    Vector current_direction = direction;
    for (int light_bounce = 0; light_bounce < MAX_LIGHT_BOUNCES; light_bounce++) {
        auto package = ray_jump(current_origin, 
            current_direction, objects);
        HitInfo info = std::get<0>(package);
        Material material = std::get<1>(package);
        // if we hit something we need to get the next ray ready
        if (info.hit) {
            light.x*=material.color.x;
            light.y*=material.color.y;
            light.z*=material.color.z;
            // get ready for the new vector
            Vector spec_vec = specular_vec(current_direction, info.normal);
            Vector diff_vec = diffuse_vec(info.normal);
            current_origin = epsilon_stepback(current_origin, info.location);
            /*
            current_direction = Vector {
                lerp(material.smoothness, diff_vec.x, spec_vec.x),
                lerp(material.smoothness, diff_vec.y, spec_vec.y),
                lerp(material.smoothness, diff_vec.z, spec_vec.z),
            };
            */
            current_direction = diff_vec;
        }
        else {
            // no need right?
            // light.x*=AMBIENT_LIGHT.x;
            // light.y*=AMBIENT_LIGHT.y;
            // light.z*=AMBIENT_LIGHT.z;
            break;
        }
    }
    return light;
}
static std::tuple<HitInfo, Material> ray_jump(const Vector& origin,
    const Vector& direction, const std::vector<Object>& objects) {
    float closest_distance = INFINITY;
    bool hit_something = false;
    HitInfo rinfo;
    Material rmat;
    for (const auto object : objects) {
        HitInfo info = object.shape.ray_test(origin, direction);
        if (info.hit) {
            float dist = distance(info.location, origin);
            if (closest_distance > dist) {
                rmat = object.material;
                rinfo = info;
                closest_distance = dist; // this was a confusing bug for about ten minutes
                hit_something = true;
            }
        }
    }
    return hit_something ? std::make_tuple(rinfo, rmat) : std::make_tuple(HitInfo{false}, Material{});
}

static Vector diffuse_vec(const Vector& normal) {
    Vector random_vec {
        (float)rand(),
        (float)rand(),
        (float)rand(),
    };
    float mag = magnitude(random_vec);
    random_vec.x/=mag;
    random_vec.y/=mag;
    random_vec.z/=mag;
    if (dot(normal, random_vec) < 0) {
        random_vec.x*=-1;
        random_vec.y*=-1;
        random_vec.z*=-1;
    }
    return random_vec;
}
static Vector specular_vec(const Vector& direction, const Vector& normal) {
    float tmp = dot(normal, direction);
    return Vector{
        tmp*-2*normal.x*direction.x,
        tmp*-2*normal.y*direction.y,
        tmp*-2*normal.z*direction.z,
    };
}
// this function takes a step back by a very small value in order to prevent
// a new ray bounce from hitting the same object
static Vector epsilon_stepback(const Vector& origin, const Vector& point) {
    const float epsilon = 0.01;
    return Vector{
        point.x+(origin.x-point.x)*epsilon,
        point.y+(origin.y-point.y)*epsilon,
        point.z+(origin.z-point.z)*epsilon,
    };
}


