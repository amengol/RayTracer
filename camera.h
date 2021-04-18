#pragma once

#include "rtweekend.h"

class camera
{
    point3 origin;
    point3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
public:
    camera()
    {
            const double aspect_ratio = 16.0/9.0;
            double viewport_height = 2.0;
            double viewport_width = aspect_ratio * viewport_height;
            double focal_length = 1.0;

            origin = point3(0, 0, 0);
            horizontal = vec3(viewport_width, 0, 0); // Offset horizontal vector
            vertical = vec3(0, viewport_height, 0); // Offset vertical vector
            lower_left_corner = origin - horizontal/2.0 - vertical/2.0 - vec3(0, 0, focal_length);
    }

    ray get_ray(double u, double v)
    {
        return ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
    }
};