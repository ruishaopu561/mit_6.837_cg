#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "object3d.h"

class Triangle : public Object3D
{
public:
    Triangle(Vec3f &, Vec3f &, Vec3f &, Material *);
    virtual bool intersect(const Ray &r, Hit &h, float tmin);
    virtual void paint(void);

private:
    Vec3f a, b, c, normal;
};

#endif // !_TRIANGLE_H_