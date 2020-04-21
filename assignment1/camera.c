#include "camera.h"
#include <float.h>

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
    horizontal.Cross3(horizontal, tup, tdirection);
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
    // Vec3f origin = center + (point.y() - 0.5) * size * horizontal + (point.x() - 0.5) * size * up;
    Vec3f origin = center + size * horizontal * (point.y() - 0.5) + size * up * (point.x() - 0.5);
    return Ray(origin, direction);
}

float OrthographicCamera::getTMin() const
{
    // 返回最大的负值
    return -FLT_MAX;
}