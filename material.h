#ifndef MATERIAL_H
#define MATERIAL_H

#include "rtweekend.h"
#include "hittable.h"

class material
{
public:
    virtual bool scatter(
        const ray& r_in, 
        const hit_record& rec, 
        color& attenuation, 
        ray& scattered) const = 0;
};

class lambertian : public material
{
public:
    color albedo;

    lambertian(const color& a) : albedo(a) {}
    
    bool scatter(
        const ray& r_in, 
        const hit_record& rec, 
        color& attenuation, 
        ray& scattered) const override
    {
        vec3 scatter_direction = rec.normal + random_in_unit_vector();

        // Catch defenerate scatter direction
        if (scatter_direction.near_zero())
            scatter_direction = rec.normal;

        scattered = ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }
};

class metal : public material
{
public:
    color albedo;

    metal(const color& a) : albedo(a) {}

    bool scatter(
        const ray& r_in, 
        const hit_record& rec, 
        color& attenuation, 
        ray& scattered) const override
    {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = ray(rec.p, reflected);
        attenuation = albedo;
        return dot(scattered.direction(), rec.normal) > 0;
    }
};

#endif