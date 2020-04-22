#include "camera.h"
#include <float.h>
#include <math.h>

Camera::Camera()
{
}

Camera::~Camera()
{
}

OrthographicCamera::OrthographicCamera(Vec3f tcenter, Vec3f tdirection, Vec3f tup, float tsize)
{
    size = tsize;
    center = tcenter;
    direction = tdirection;
    horizontal.Cross3(horizontal, tup, direction);
    up.Cross3(up, horizontal, direction);

    direction.Normalize();
    horizontal.Normalize();
    up.Normalize();
}

OrthographicCamera::~OrthographicCamera()
{
}

Ray OrthographicCamera::generateRay(Vec2f point)
{
    Vec3f origin = center + size * horizontal * (point.y() - 0.5) + size * up * (point.x() - 0.5);
    return Ray(origin, direction);
}

float OrthographicCamera::getTMin() const
{
    // 返回最大的负值
    return -FLT_MAX;
}

PerspectiveCamera::PerspectiveCamera(Vec3f &cer, Vec3f &tdirection, Vec3f &tup, float tangle)
{
    center = cer;
    angle = tangle;
    direction = tdirection;
    horizontal.Cross3(horizontal, tup, direction);
    up.Cross3(up, horizontal, direction);

    direction.Normalize();
    horizontal.Normalize();
    up.Normalize();

}

PerspectiveCamera::~PerspectiveCamera()
{
}

Ray PerspectiveCamera::generateRay(Vec2f point)
{
    Vec3f dir = cos(angle/2) / (2*sin(angle/2)) * direction + (point.x() - 0.5) * up + (point.y() - 0.5) * horizontal;
    dir.Normalize();
    return Ray(center, dir);
}

float PerspectiveCamera::getTMin() const
{
    return -FLT_MAX;
}

