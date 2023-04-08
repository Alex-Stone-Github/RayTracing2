#pragma once

#include <math.h>
#include "types.hpp"

float map(float value, float a, float b, float c, float d);
float magnitude(const Vector& v);
float dot(const Vector& a, const Vector& b);
Vector cross(const Vector& a, const Vector& b);
float lerp(float t, float a, float b);
float distance(const Vector& a, const Vector& b);