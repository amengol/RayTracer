#pragma once

#include "vec3.h"
#include <iostream>
#include <algorithm>

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
    out << int(256 * std::clamp(r, 0.0, 0.999)) << ' '
        << int(256 * std::clamp(g, 0.0, 0.999)) << ' '
        << int(256 * std::clamp(b, 0.0, 0.999)) << '\n';
}