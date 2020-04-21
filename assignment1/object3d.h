#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

#include "ray.h"
#include "hit.h"
#include "material.h"

class Object3D
{
public:
    Material *material;

    Object3D() {};
    ~Object3D() {};
    virtual bool intersect(const Ray &r, Hit &h, float tmin) = 0;
private:
};

#endif // !_OBJECT3D_H_