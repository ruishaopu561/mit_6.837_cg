#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "object3d.h"
#include "vectors.h"

class Transform : public Object3D
{
public:
    Transform(Matrix &m, Object3D *o);
    ~Transform();
    virtual bool intersect(const Ray &r, Hit &h, float tmin);
private:
    Object3D *object;
    Matrix matrix;
};

Transform::Transform(Matrix &m, Object3D *o)
{
    object = o;
    matrix = m;
}

Transform::~Transform()
{
}

bool Transform::intersect(const Ray &r, Hit &h, float tmin)
{
    Vec3f origin = r.getOrigin(), dir = r.getDirection();
    Matrix temp(matrix);

    temp.Inverse();
    temp.Transform(origin);

    if (object->intersect(Ray(origin, dir), h, tmin)) {
        temp.Transpose();

        Vec3f normal = h.getNormal();
        temp.Transform(normal);
        normal.Normalize();
        h.set(h.getT(), h.getMaterial(), normal, r);
    	return true;
    }
    return false;
}

#endif // !_TRANSFORM_H_