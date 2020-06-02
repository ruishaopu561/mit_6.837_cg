#ifndef _RAYTRACER_H_
#define _RAYTRACER_H_

#include "scene_parser.h"
#include "vectors.h"
#include "ray.h"
#include "hit.h"
#include "grid.h"

class RayTracer
{
public:
    RayTracer(SceneParser *, int, float, bool, ...);
    Vec3f traceRay(Ray &, float, int, float, float, Hit &) const;

private:
    SceneParser *sp;
    int maxBounces;
    float cutoffWeight;
    bool shadow;
    Grid *g;
};

#endif // !_RAYTRACER_H_