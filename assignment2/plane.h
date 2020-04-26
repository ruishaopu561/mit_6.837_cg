#ifndef _PLANE_H_
#define _PLANE_H_

#include "object3d.h"

class Plane : public Object3D
{
public:
    Plane(Vec3f &, float, Material *);
    ~Plane();
    virtual bool intersect(const Ray &r, Hit &h, float tmin);

private:
    Vec3f normal;
    float distance;
    Material *material;
    Vec3f z_point;
};

Plane::Plane(Vec3f &tnormal, float d, Material *m)
{
    normal = tnormal;
    distance = d;
    material = m;

    if(normal.x() != 0) {
        z_point = Vec3f((float)d/tnormal.x(), 0, 0);
    }else if (normal.y() != 0) {
        z_point = Vec3f(0, (float)d/tnormal.y(), 0);
    }else{
        z_point = Vec3f(0, 0, (float)d/tnormal.z());
    }
}

Plane::~Plane()
{
}

bool Plane::intersect(const Ray &r, Hit &h, float tmin)
{
    Vec3f dir = r.getDirection();
    float tp = normal.Dot3(dir);
    
    if(tp >= 0) {
        return false;
    }

    Vec3f c2c = r.getOrigin() - z_point;
    float d = c2c.Dot3(normal);
    float t = d / -tp;

    if(t >= tmin) {
        if(t < h.getT()) {
            h.set(t, material, normal, r);
            return true;
        }
    }
    return false;
}

#endif // !_PLANE_H_