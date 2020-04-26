#include "sphere.h"

Sphere::Sphere(Vec3f &point, float &r, Material *&m)
{
    center = point;
    radius = r;
    material = m;
}

Sphere::~Sphere()
{
}

bool Sphere::intersect(const Ray &r, Hit &h, float tmin)
{
    Vec3f dir = r.getDirection();
    Vec3f c2c = center - r.getOrigin();

    float tp = c2c.Dot3(dir);
    float d2 = c2c.Dot3(c2c) - tp * tp;
    if(d2 > radius * radius || tp <= 0)
    {
        return false;
    }
    
    float t = sqrt(radius * radius - d2);

    if(radius == 1 && center.z() == 15)
    {
            std::cout 
        << c2c.Dot3(c2c) << "  " 
        << r.getDirection() << "  "
        << tp << "  " 
        << d2 << "  " 
        << t << std::endl;

    }

    if(tp > t)
    {
        if(tp - t >= tmin)
        {
            // std::cout << std::endl;
            if(tp - t < h.getT())
            {
                Vec3f normal = r.pointAtParameter(tp - t) - center;
                normal.Normalize();
                h.set(tp - t, material, normal, r);
            }
            return true;
        }
    }else
    {
        if(tp + t >= tmin)
        {
            if(tp + t < h.getT())
            {
                Vec3f normal = center - r.pointAtParameter(tp + t);
                normal.Normalize();
                h.set(tp + t, material, normal, r);
            }
            return true;
        }        
    }
    return false;
}
