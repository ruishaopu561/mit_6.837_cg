#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "ray.h"
#include "vectors.h"

class Camera
{
public:
    virtual Ray generateRay(Vec2f point) = 0;
    virtual float getTMin() const = 0;
protected:
    Vec3f center, direction, up, horizontal;
};

class OrthographicCamera : public Camera
{
public:
    OrthographicCamera(Vec3f, Vec3f, Vec3f, float);
    virtual Ray generateRay(Vec2f point);
    virtual float getTMin() const;
private:
    float size;
};

class PerspectiveCamera : public Camera
{
public:
    PerspectiveCamera(Vec3f &, Vec3f &, Vec3f &, float);
    virtual Ray generateRay(Vec2f point);
    virtual float getTMin() const;
private:
    float angle;
};

#endif // !_CAMERA_H_