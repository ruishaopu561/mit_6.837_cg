#include "camera.h"

OrthographicCamera::OrthographicCamera(Vec3f tcenter, Vec3f tdirection, Vec3f tup, float tsize)
{
    size = tsize;
    center = tcenter;
    direction = tdirection;
    Vec3f::Cross3(horizontal, direction, tup);
    Vec3f::Cross3(up, horizontal, direction);

    direction.Normalize();
    horizontal.Normalize();
    up.Normalize();
}

Ray OrthographicCamera::generateRay(Vec2f point)
{
    Vec3f origin = center + size * up * (point.y() - 0.5) + size * horizontal * (point.x() - 0.5);
    return Ray(origin, direction);
}

float OrthographicCamera::getTMin() const
{
    // 返回最大的负值
    return -INFINITY;
}

PerspectiveCamera::PerspectiveCamera(Vec3f &cer, Vec3f &tdirection, Vec3f &tup, float tangle)
{
    center = cer;
    angle = tangle;
    direction = tdirection;
    Vec3f::Cross3(horizontal, direction, tup);
    Vec3f::Cross3(up, horizontal, direction);

    direction.Normalize();
    horizontal.Normalize();
    up.Normalize();

}

Ray PerspectiveCamera::generateRay(Vec2f point)
{
    Vec3f dir = 0.5 / tan(angle / 2) * direction + (point.y() - 0.5) * up + (point.x() - 0.5) * horizontal;
    dir.Normalize();
    return Ray(center, dir);
}

float PerspectiveCamera::getTMin() const
{
    return 0;
}