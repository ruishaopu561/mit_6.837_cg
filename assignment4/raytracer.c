#include "raytracer.h"

RayTracer::RayTracer(SceneParser *s, int max_bounces, float cutoff_weight, bool shadows, ...)
{
    sp = s;
    maxBounces = max_bounces;
    cutoffWeight = cutoff_weight;
    shadow = shadows;
}

Vec3f RayTracer::traceRay(Ray &ray, float tmin, int bounces, 
        float weight, float indexOfRefraction, Hit &hit) const
{
    return Vec3f(0, 0, 0);
}

Vec3f RayTracer::mirrorDirection(const Vec3f &normal, const Vec3f &incoming)
{
    return normal;
}

bool RayTracer::transmittedDirection(const Vec3f &normal, const Vec3f &incoming, 
        float index_i, float index_t, Vec3f &transmitted)
{
    return false;
}