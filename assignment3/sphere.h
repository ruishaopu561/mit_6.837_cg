#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "vectors.h"
#include "object3d.h"

class Sphere : public Object3D
{
public:
    Sphere(Vec3f &, float &, Material *&);
    virtual bool intersect(const Ray &r, Hit &h, float tmin);
    virtual void paint(void);

private:
    Vec3f center;
    float radius;
};

#endif // !_SPHERE_H_