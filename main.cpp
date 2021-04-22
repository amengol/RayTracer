#include "rtweekend.h"

#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

#include <chrono>
#include <iostream>

color ray_color(const ray& r, const hittable& world, int depth)
{
    hit_record rec;

    // If bounce limit exceeded, no more light is gathered
    if (depth <= 0)
        return color(0,0,0);

    if (world.hit(r, 0.001, infinity, rec)) {
        ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth-1);
        return color(0,0,0);
    }

    vec3 unit_direction = unit_vector(r.direction());
    double t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0,1.0,1.0) + t*(color(0.5,0.7,1.0));
}

int main()
{
    // Start timer
    auto begin = std::chrono::steady_clock::now();

    // Image
    constexpr double aspect_ratio = 16.0/9.0;
    constexpr int image_width = 400;
    constexpr int image_height = int(image_width/aspect_ratio);
    constexpr int samples_per_pixel = 100;
    constexpr int max_depth = 50;

    // World
    hittable_list world;
    
    auto material_ground = std::make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<lambertian>(color(0.7, 0.3, 0.3));
    auto material_left = std::make_shared<metal>(color(0.8, 0.8, 0.8));
    auto material_right = std::make_shared<metal>(color(0.8, 0.6, 0.2));

    world.add(std::make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(std::make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5, material_center));
    world.add(std::make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
    world.add(std::make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));


    // Camara
    camera cam;

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    
    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            color pixel_color(0,0,0);
            for (int s = 0; s < samples_per_pixel; ++s)
            {
                double u = (i + random_double()) / (image_width-1);
                double v = (j + random_double()) / (image_height-1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }

    //Elapsed time
    auto end = std::chrono::steady_clock::now();
    std::cerr << "\nElapsed time = " 
    << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()
    << " ms" << std::endl;

    std::cerr << "Done.\n";
}