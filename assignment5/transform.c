#include "transform.h"

Transform::Transform(Matrix &m, Object3D *o)
{
    object = o;
    matrix = m;

    matrix_inv = matrix;
    matrix_inv.Inverse();
    matrix_inv_tr = matrix_inv;
    matrix_inv_tr.Transpose();
}

bool Transform::intersect(const Ray &r, Hit &h, float tmin)
{
    Vec3f origin = r.getOrigin(), dir = r.getDirection();

    matrix_inv.Transform(origin);
    matrix_inv.TransformDirection(dir);
    // float scale = dir.Length();
    // dir.Normalize();

    bool hit = object->intersect(Ray(origin, dir), h, tmin);
    if (hit) {
        Vec3f normal = h.getNormal();
        matrix_inv_tr.TransformDirection(normal);
        normal.Normalize();
        h.set(h.getT(), h.getMaterial(), normal, r);
        // h.set(h.getT() / scale, h.getMaterial(), normal, r);
    }
    return hit;
}

void Transform::paint(void)
{
    glPushMatrix();
        GLfloat *glMatrix = matrix.glGet();
        glMultMatrixf(glMatrix);
        delete[] glMatrix;

        object->paint();

    glPopMatrix();
}

void Transform::insertIntoGrid(Grid *g, Matrix *m)
{

}