#include "sphere.h"

Sphere::Sphere(Vec3f &point, float &r, Material *&m)
{
    center = point;
    radius = r;
    material = m;
}

bool Sphere::intersect(const Ray &r, Hit &h, float tmin)
{
    Vec3f origin = r.getOrigin() - center;
    Vec3f dir = r.getDirection();
    float a = dir.Length()*dir.Length(), b = dir.Dot3(origin) * 2, c = origin.Dot3(origin) - radius * radius;
    float d = b * b - 4 * a*c;
    float t = 0;
    if (d < 0) return false;
    if (d == 0) {
        t = -b / (2 * a);
    }
    else {
        d = sqrt(d);
        t = (-b - d) / (2 * a);
        if (t < tmin) t = (-b + d) / (2 * a);
    }
    if (t > tmin) {
        if (h.getT() > t) {
            Vec3f hit_point = r.pointAtParameter(t);
            Vec3f normal = hit_point - center;
            normal.Normalize();
            h.set(t, material, normal, r);
            return true;
        }
    }
    return false;
}

void Sphere::paint(void)
{
    material->glSetMaterial();

    glBegin(GL_QUADS);
        for (int iPhi=-90; iPhi<90; iPhi++)
        {
            for (int iTheta=0; iTheta<360; iTheta++)
            {
                // compute appropriate coordinates & normals
                float theta = iTheta / 1800.f * M_PI, phi = iPhi / 180.0f * M_PI;
                Vec3f normal(cos(theta), sin(phi), sin(theta));

                glNormal3f(cos(theta), sin(phi), sin(theta));
                glVertex3f(center.x() + cos(theta), center.y() + sin(phi), center.z() + sin(theta));
                glVertex3f(center.x() + cos(theta), center.y() + sin(phi+1), center.z() + sin(theta));
                glVertex3f(center.x() + cos(theta+1), center.y() + sin(phi+1), center.z() + sin(theta+1));
                glVertex3f(center.x() + cos(theta+1), center.y() + sin(phi), center.z() + sin(theta+1));
            }
        }
   glEnd();
}