#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <GL/gl.h>
#include <GL/glu.h>
#include "ray.h"
#include "vectors.h"
#include "matrix.h"

class Camera
{
public:
    virtual Ray generateRay(Vec2f point) = 0;
    virtual float getTMin() const = 0;
    virtual void glInit(int w, int h) = 0;
    virtual void glPlaceCamera(void) = 0;
    virtual void dollyCamera(float dist) = 0;
    virtual void truckCamera(float dx, float dy) = 0;
    virtual void rotateCamera(float rx, float ry) = 0;
protected:
    Vec3f center, direction, up, screen_up, horizontal;
};

class OrthographicCamera : public Camera
{
public:
    OrthographicCamera(Vec3f, Vec3f, Vec3f, float);
    virtual Ray generateRay(Vec2f point);
    virtual float getTMin() const;
    virtual void glInit(int w, int h);
    virtual void glPlaceCamera(void);
    virtual void dollyCamera(float dist);
    virtual void truckCamera(float dx, float dy);
    virtual void rotateCamera(float rx, float ry);
private:
    float size;
};

class PerspectiveCamera : public Camera
{
public:
    PerspectiveCamera(Vec3f &, Vec3f &, Vec3f &, float);
    virtual Ray generateRay(Vec2f point);
    virtual float getTMin() const;
    virtual void glInit(int w, int h);
    virtual void glPlaceCamera(void);
    virtual void dollyCamera(float dist);
    virtual void truckCamera(float dx, float dy);
    virtual void rotateCamera(float rx, float ry);
private:
    float angle;
};

#endif // !_CAMERA_H_