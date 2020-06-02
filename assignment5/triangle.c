#include "triangle.h"

Triangle::Triangle(Vec3f &ta, Vec3f &tb, Vec3f &tc, Material *tm):Object3D(tm), a(ta), b(tb), c(tc) 
{
    Vec3f::Cross3(normal, b-a, c-a);
    normal.Normalize();
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
            h.set(t, material, normal, r);
        }
        return true;
    }
    return false;
}

void Triangle::paint(void)
{
    material->glSetMaterial();

    glBegin(GL_TRIANGLES);
        glNormal3f(normal.x(), normal.y(), normal.z());
        glVertex3f(a.x(), a.y(), a.z());
        glVertex3f(b.x(), b.y(), b.z());
        glVertex3f(c.x(), c.y(), c.z());
    glEnd();
}

void Triangle::insertIntoGrid(Grid *g, Matrix *m)
{

}
