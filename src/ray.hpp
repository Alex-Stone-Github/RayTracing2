#pragma once

#include <vector>
#include "types.hpp"

#define MARCH_STEPS 30
#define MARCH_STEP_DISTANCE 8

struct HitInfo {
    bool hit;
};
HitInfo ray_march(Vector origin, Vector direction, std::vector<Object>& objects);

