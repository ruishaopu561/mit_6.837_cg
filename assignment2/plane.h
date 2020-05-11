#ifndef _PLANE_H_
#define _PLANE_H_

#include "object3d.h"

class Plane : public Object3D
{
public:
    Plane(Vec3f &, float, Material *);
    virtual bool intersect(const Ray &r, Hit &h, float tmin);

private:
    Vec3f normal;
    float distance;
};

Plane::Plane(Vec3f &tnormal, float d, Material *m):normal(tnormal), distance(d), Object3D(m) {}

bool Plane::intersect(const Ray &r, Hit &h, float tmin)
{
    Vec3f dir = r.getDirection(), origin = r.getOrigin();
    float tp = normal.Dot3(dir);
    
    if(tp == 0) {
        return false;
    }

    float t = (distance - origin.Dot3(normal)) / tp;
    if(t > tmin) {
        if(t < h.getT()) {
            h.set(t, material, normal, r);
            return true;
        }
    }
    return false;
}

#endif // !_PLANE_H_