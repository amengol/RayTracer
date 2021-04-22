#pragma once

#include "vec3.h"
#include <iostream>

inline double clamp(double x, double min, double max)
{
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

void write_color(std::ostream& out, color pixel_color, int samples_per_pixel)
{
    double r = pixel_color.r();
    double g = pixel_color.g();
    double b = pixel_color.b();
    
    // Divide the color by the number of samples and gama-correct for gama=2.0
    double scale = 1.0 / samples_per_pixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    // Write the translated [0,255] value of each color component
    out << int(256 * clamp(r, 0.0, 0.999)) << ' '
        << int(256 * clamp(g, 0.0, 0.999)) << ' '
        << int(256 * clamp(b, 0.0, 0.999)) << '\n';
}