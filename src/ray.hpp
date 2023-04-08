#pragma once

#include <vector>
#include <tuple>
#include <cmath>
#include "types.hpp"
#include "mathstuff.hpp"

//#define AMBIENT_LIGHT Vector{1, 1, 1}
#define AMBIENT_LIGHT Vector{1, 1, 1}
#define MAX_LIGHT_BOUNCES 3

Color ray_trace(const Vector& origin, const Vector& direction, const std::vector<Object>& objects);
static std::tuple<HitInfo, Material> ray_jump(const Vector& origin,
    const Vector& direction, const std::vector<Object>& objects);
static Vector diffuse_vec(const Vector& normal);
static Vector specular_vec(const Vector& direction, const Vector& normal);
// this function takes a step back by a very small value in order to prevent
// a new ray bounce from hitting the same object
static Vector epsilon_stepback(const Vector& origin, const Vector& point);
