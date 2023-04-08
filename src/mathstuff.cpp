#include "mathstuff.hpp"

float map(float value, float a, float b, float c, float d) {
    float percent = (value-a)/(b-a);
    return percent * (d-c) + c;
}