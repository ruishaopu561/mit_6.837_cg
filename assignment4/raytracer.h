#ifndef _RAYTRACER_H_
#define _RAYTRACER_H_

#include "scene_parser.h"
#include "vectors.h"
#include "ray.h"
#include "hit.h"

class RayTracer
{
public:
    RayTracer(SceneParser *, int, float, bool, ...);
    Vec3f traceRay(Ray &, float, int, float, float, Hit &) const;
    Vec3f mirrorDirection(const Vec3f &, const Vec3f &);
    bool transmittedDirection(const Vec3f &, const Vec3f &, float, float, Vec3f &);

private:
    SceneParser *sp;
    int maxBounces;
    float cutoffWeight;
    bool shadow;
};

#endif // !_RAYTRACER_H_