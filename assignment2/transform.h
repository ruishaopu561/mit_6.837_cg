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
    Vec3f origin = r.getOrigin();
    matrix.Transform(origin);

    return object->intersect(Ray(origin, r.getDirection()), h, tmin);
}

#endif // !_TRANSFORM_H_