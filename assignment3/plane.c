#include "plane.h"

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

void Plane::paint(void)
{
    material->glSetMaterial();

    float big = 10000;

    Vec3f v(1, 0 ,0), b1, b2;
    if(normal.Dot3(v) == 1)
    {
        v = Vec3f(0, 1, 0);
    }

    Vec3f::Cross3(b1, v, normal);
    Vec3f::Cross3(b2, normal, b1);
    b1.Normalize();
    b2.Normalize();

    Vec3f center = distance * normal;
    
    Vec3f p1 = center - big * b1, p2 = center - big * b2, p3 = center + big * b1, p4 = center + big * b2;

    glBegin(GL_QUADS);
        glNormal3f(normal.x(), normal.y(), normal.z());
        glVertex3f(p1.x(), p1.y(), p1.z());
        glVertex3f(p2.x(), p2.y(), p2.z());
        glVertex3f(p3.x(), p3.y(), p3.z());
        glVertex3f(p4.x(), p4.y(), p4.z());
    glEnd();
}
