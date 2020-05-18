#include "camera.h"

OrthographicCamera::OrthographicCamera(Vec3f tcenter, Vec3f tdirection, Vec3f tup, float tsize)
{
    center = tcenter;
    direction = tdirection;
    up = tup;
    size = tsize;
    Vec3f::Cross3(horizontal, direction, tup);
    Vec3f::Cross3(screen_up, horizontal, direction);

    direction.Normalize();
    horizontal.Normalize();
    screen_up.Normalize();
}

Ray OrthographicCamera::generateRay(Vec2f point)
{
    Vec3f origin = center + size * screen_up * (point.y() - 0.5) + size * horizontal * (point.x() - 0.5);
    return Ray(origin, direction);
}

float OrthographicCamera::getTMin() const
{
    // 返回最大的负值
    return -INFINITY;
}

void OrthographicCamera::glInit(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w > h)
        glOrtho(-size/2.0, size/2.0, -size*(float)h/(float)w/2.0, size*(float)h/(float)w/2.0, 0.5, 40.0);
    else
        glOrtho(-size*(float)w/(float)h/2.0, size*(float)w/(float)h/2.0, -size/2.0, size/2.0, 0.5, 40.0);
}

void OrthographicCamera::glPlaceCamera(void)
{
    gluLookAt(center.x(), center.y(), center.z(),
        center.x()+direction.x(), center.y()+direction.y(), center.z()+direction.z(),
        screen_up.x(), screen_up.y(), screen_up.z());
}

// dollyCamera: Move camera along the direction vector
void OrthographicCamera::dollyCamera(float dist)
{
    center += direction*dist;

    // ===========================================
    // ASSIGNMENT 3: Fix any other affected values
    // ===========================================


}

// truckCamera: Translate camera perpendicular to the direction vector
void OrthographicCamera::truckCamera(float dx, float dy)
{
    // Vec3f horizontal;
    // Vec3f::Cross3(horizontal, direction, up);
    // horizontal.Normalize();

    // Vec3f screen_up;
    // Vec3f::Cross3(screen_up, horizontal, direction);

    center += horizontal*dx + screen_up*dy;

    // ===========================================
    // ASSIGNMENT 3: Fix any other affected values
    // ===========================================


}

// rotateCamera: Rotate around the screen_up and horizontal vectors
void OrthographicCamera::rotateCamera(float rx, float ry)
{
    // Vec3f horizontal;
    // Vec3f::Cross3(horizontal, direction, screen_up);
    // horizontal.Normalize();

    // Don't let the model flip upside-down (There is a singularity
    // at the poles when 'screen_up' and 'direction' are aligned)
    float tiltAngle = acos(screen_up.Dot3(direction));
    if (tiltAngle-ry > 3.13)
        ry = tiltAngle - 3.13;
    else if (tiltAngle-ry < 0.01)
        ry = tiltAngle - 0.01;

    Matrix rotMat = Matrix::MakeAxisRotation(screen_up, rx);
    rotMat *= Matrix::MakeAxisRotation(horizontal, ry);

    rotMat.Transform(center);
    rotMat.TransformDirection(direction);
  
    // ===========================================
    // ASSIGNMENT 3: Fix any other affected values
    // ===========================================

    Vec3f::Cross3(horizontal, direction, up);
    Vec3f::Cross3(screen_up, horizontal, direction);
}

PerspectiveCamera::PerspectiveCamera(Vec3f &cer, Vec3f &tdirection, Vec3f &tup, float tangle)
{
    center = cer;
    direction = tdirection;
    up = tup;
    angle = tangle;
    Vec3f::Cross3(horizontal, direction, tup);
    Vec3f::Cross3(screen_up, horizontal, direction);

    direction.Normalize();
    horizontal.Normalize();
    screen_up.Normalize();
}

Ray PerspectiveCamera::generateRay(Vec2f point)
{
    Vec3f dir = 0.5 / tan(angle / 2) * direction + (point.y() - 0.5) * screen_up + (point.x() - 0.5) * horizontal;
    dir.Normalize();
    return Ray(center, dir);
}

float PerspectiveCamera::getTMin() const
{
    return 0;
}

void PerspectiveCamera::glInit(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(angle*180.0/3.14159, (float)w/float(h), 0.5, 40.0);
}

void PerspectiveCamera::glPlaceCamera(void)
{
    gluLookAt(center.x(), center.y(), center.z(),
        center.x()+direction.x(), center.y()+direction.y(), center.z()+direction.z(),
        screen_up.x(), screen_up.y(), screen_up.z());
}

// dollyCamera: Move camera along the direction vector
void PerspectiveCamera::dollyCamera(float dist)
{
    center += direction*dist;

    // ===========================================
    // ASSIGNMENT 3: Fix any other affected values
    // ===========================================


}

// truckCamera: Translate camera perpendicular to the direction vector
void PerspectiveCamera::truckCamera(float dx, float dy)
{
    // Vec3f horizontal;
    // Vec3f::Cross3(horizontal, direction, screen_up);
    // horizontal.Normalize();

    // Vec3f screen_up;
    // Vec3f::Cross3(screen_up, horizontal, direction);

    center += horizontal*dx + screen_up*dy;

    // ===========================================
    // ASSIGNMENT 3: Fix any other affected values
    // ===========================================


}

// rotateCamera: Rotate around the screen_up and horizontal vectors
void PerspectiveCamera::rotateCamera(float rx, float ry)
{
    // Vec3f horizontal;
    // Vec3f::Cross3(horizontal, direction, screen_up);
    // horizontal.Normalize();

    // Don't let the model flip upside-down (There is a singularity
    // at the poles when 'screen_up' and 'direction' are aligned)
    float tiltAngle = acos(screen_up.Dot3(direction));
    if (tiltAngle-ry > 3.13)
        ry = tiltAngle - 3.13;
    else if (tiltAngle-ry < 0.01)
        ry = tiltAngle - 0.01;

    Matrix rotMat = Matrix::MakeAxisRotation(screen_up, rx);
    rotMat *= Matrix::MakeAxisRotation(horizontal, ry);

    rotMat.Transform(center);
    rotMat.TransformDirection(direction);
    direction.Normalize();

    // ===========================================
    // ASSIGNMENT 3: Fix any other affected values
    // ===========================================

    Vec3f::Cross3(horizontal, direction, up);
    Vec3f::Cross3(screen_up, horizontal, direction);
}