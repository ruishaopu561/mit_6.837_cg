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
    Vec3f V = incoming;
    V.Normalize();

    float cos = V.Dot3(normal);

    Vec3f L = V - 2 * cos * normal;
    L.Normalize();

    return L;
}

bool RayTracer::transmittedDirection(const Vec3f &normal, const Vec3f &incoming, 
        float index_i, float index_t, Vec3f &transmitted)
{
    Vec3f V = incoming;
    V.Normalize();

    float cos_i = V.Dot3(normal);

    if(cos_i >= 0)
    {
        return false;
    }

    Vec3f V_h = cos_i * normal;
    Vec3f V_v = V - V_h;
    V_v.Normalize();
    V_h.Normalize();

    float sint = sqrt(1-cos_i*cos_i) * index_i / index_t;

    transmitted = sint * V_v + sqrt(1-sint*sint) * V_h;

    return true;
}