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
    if(normal == v)
    {
        v = Vec3f(0, 1, 0);
    }

    Vec3f::Cross3(b1, v, normal);
    Vec3f::Cross3(b2, normal, b1);

    glBegin(GL_QUADS);
        glNormal3f(normal.x(), normal.y(), normal.z());
        glVertex3f(big * -b1.x(), big * -b1.y(), big * -b1.z());
        glVertex3f(big * -b2.x(), big * -b2.y(), big * -b2.z());
        glVertex3f(big * b1.x(), big * b1.y(), big * b1.z());
        glVertex3f(big * b2.x(), big * b2.y(), big * b2.z());
    glEnd();
}
