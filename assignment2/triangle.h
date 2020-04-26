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
    Vec3f a, b, c;
    Material *material;
};

Triangle::Triangle(Vec3f &ta, Vec3f &tb, Vec3f &tc, Material *tm)
{
    a = ta;
    b = tb;
    c = tc;
    material = tm;
}

Triangle::~Triangle()
{
}

bool Triangle::intersect(const Ray &r, Hit &h, float tmin)
{
    Vec3f E1 = b-a, E2 = c-a, T = r.getOrigin() - a, D = r.getDirection(), P, Q;
    P.Cross3(P, D, E2);
    Q.Cross3(Q, T, E1);

    float t = Q.Dot3(E2) / P.Dot3(E1);
    float u = P.Dot3(T) / P.Dot3(E1);
    float v = Q.Dot3(D) / P.Dot3(E1);

    if(u < 0 || v < 0 || u + v > 1) {
        return false;
    }

    if(t >= tmin) {
        if(t < h.getT()) {
            Vec3f normal;
            normal.Cross3(normal, b-a, c-a);
            if(normal.Dot3(r.getDirection()) > 0) {
                normal.Cross3(normal, b-a, a-c);
            }
            normal.Normalize();

            h.set(t, material, normal, r);
            return true;
        }
    }
    return false;
}

#endif // !_TRIANGLE_H_