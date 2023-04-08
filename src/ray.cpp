#include "ray.hpp"

HitInfo ray_march(Vector origin, Vector direction, std::vector<Object>& objects) {
    for (float step = 0; step < MARCH_STEPS; step++) {
        Vector test_position{
            origin.x+direction.x*MARCH_STEP_DISTANCE*step,
            origin.y+direction.y*MARCH_STEP_DISTANCE*step,
            origin.z+direction.z*MARCH_STEP_DISTANCE*step,
        };
        for (const auto object : objects) {
            if (object.shape.contains_point(test_position)) {
                return HitInfo{true};
            }
        }
    }
    return HitInfo{false};
}