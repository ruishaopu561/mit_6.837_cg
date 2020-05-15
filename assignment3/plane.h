#ifndef _PLANE_H_
#define _PLANE_H_

#include "object3d.h"

class Plane : public Object3D
{
public:
    Plane(Vec3f &, float, Material *);
    virtual bool intersect(const Ray &r, Hit &h, float tmin);
    virtual void paint(void);

private:
    Vec3f normal;
    float distance;
};

#endif // !_PLANE_H_