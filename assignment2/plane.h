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
    float d;
    Material *m;
};

Plane::Plane(Vec3f &tnormal, float td, Material *tm)
{
    normal = tnormal;
    d = td;
    m = tm;
}

Plane::~Plane()
{
}

bool Plane::intersect(const Ray &r, Hit &h, float tmin)
{
    Vec3f dir = r.getDirection();
    float tp = normal.Dot3(dir);
    if(tp == 0)
    {
        return false;
    }
    
    // float d0, d1, d2;
    // normal.Get(d0, d1, d2);
    // Vec3f temp = Vec3f(0, 0, d/d2);
    // if(tp - t >= tmin)
    // { 
    //     if(tp - t < h.getT())
    //     {
    //         Vec3f normal = r.pointAtParameter(tp - t) - center;
    //         normal.Normalize();
    //         h.set(tp - t, material, normal, r);
    //     }
    // }
    return true;
}

#endif // !_PLANE_H_