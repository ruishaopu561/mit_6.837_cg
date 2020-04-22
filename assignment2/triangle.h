#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "object3d.h"

class Triangle : public Object3D
{
public:
       Triangle(Vec3f &, Vec3f &, Vec3f &, Material *);
    ~Triangle();
    virtual bool intersect(const Ray &r, Hit &h, float tmin);

private:
    Vec3f a;
    Vec3f b;
    Vec3f c;
    Material *m;
};

Triangle::Triangle(Vec3f &ta, Vec3f &tb, Vec3f &tc, Material *tm)
{
    a = ta;
    b = tb;
    c = tc;
    m = tm;
}

Triangle::~Triangle()
{
}

bool Triangle::intersect(const Ray &r, Hit &h, float tmin)
{
    return true;
}

#endif // !_TRIANGLE_H_