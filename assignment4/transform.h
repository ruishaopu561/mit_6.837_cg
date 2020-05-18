#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "object3d.h"
#include "vectors.h"
#include "matrix.h"

class Transform : public Object3D
{
public:
    Transform(Matrix &m, Object3D *o);
    virtual bool intersect(const Ray &r, Hit &h, float tmin);
    virtual void paint(void);

private:
    Object3D *object;
    Matrix matrix;
    Matrix matrix_inv;
	Matrix matrix_inv_tr;
};

#endif // !_TRANSFORM_H_