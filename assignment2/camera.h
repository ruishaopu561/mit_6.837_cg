#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "ray.h"
#include "vectors.h"

class Camera
{
public:
    Camera();
    ~Camera();
    virtual Ray generateRay(Vec2f point) = 0;
    virtual float getTMin() const = 0;
protected:
    Vec3f center;
    Vec3f direction;
    Vec3f up;
    Vec3f horizontal;
};

class OrthographicCamera : public Camera
{
public:
    OrthographicCamera(Vec3f, Vec3f, Vec3f, float);
    ~OrthographicCamera();
    virtual Ray generateRay(Vec2f point);
    virtual float getTMin() const;
private:
    float size;
};

class PerspectiveCamera : public Camera
{
public:
    PerspectiveCamera(Vec3f &, Vec3f &, Vec3f &, float);
    ~PerspectiveCamera();
    virtual Ray generateRay(Vec2f point);
    virtual float getTMin() const;
private:
    float angle;
};

#endif // !_CAMERA_H_