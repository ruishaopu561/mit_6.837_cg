#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "vectors.h"
#include "object3d.h"
#include "grid.h"

class Sphere : public Object3D
{
public:
    Sphere(Vec3f &, float &, Material *&);
    virtual bool intersect(const Ray &r, Hit &h, float tmin);
    virtual void paint(void);
    virtual void insertIntoGrid(Grid *g, Matrix *m);

private:
    Vec3f center;
    float radius;
    Vec3f pt2localxyz(float phi, float theta);
	Vec3f pt2xyz(float phi, float theta);
	Vec3f pt2Normal(float phi, float theta);
};

#endif // !_SPHERE_H_