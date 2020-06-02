#include "raytracer.h"
#include "group.h"
#include "light.h"
#include "rayTree.h"

const float epsilon = 0.001;
const float down = 0.33;

Vec3f mirrorDirection(const Vec3f &normal, const Vec3f &incoming)
{
    Vec3f V = incoming;
    V.Normalize();

    float cos = V.Dot3(normal);

    Vec3f L = V - 2 * cos * normal;
    L.Normalize();

    return L;
}

bool transmittedDirection(const Vec3f &normal, const Vec3f &incoming, 
        float index_i, float index_t, Vec3f &transmitted) 
{
    Vec3f V = incoming;
    V.Normalize();

    float cos_i = V.Dot3(normal);

    Vec3f V_h = cos_i * normal;
    Vec3f V_v = V - V_h;
    V_v.Normalize();
    V_h.Normalize();

    float sint = sqrt(1-cos_i*cos_i) * index_i / index_t;

    transmitted = sint * V_v + sqrt(1-sint*sint) * V_h;

    return true;
}

RayTracer::RayTracer(SceneParser *s, int max_bounces, float cutoff_weight, bool shadows, ...)
{
    sp = s;
    maxBounces = max_bounces;
    cutoffWeight = cutoff_weight;
    shadow = shadows;
}

Vec3f RayTracer::traceRay(Ray &ray, float tmin, int bounces, 
        float weight, float indexOfRefraction, Hit &hit) const
{
    if(bounces > maxBounces || weight <= cutoffWeight)
    {
        return Vec3f(0, 0, 0);
    }

    Vec3f color;
	Group* group = sp->getGroup();
    bool hited = group->intersect(ray, hit, tmin);
    if (hited) {
        // hit.set(hit.getT(), hit.getMaterial(), hit.getNormal(), ray);

        Vec3f light_dir, light_col;
        float light_distance;

        color = sp->getAmbientLight() * (hit.getMaterial()->getDiffuseColor());
        for (int i = 0; i < sp->getNumLights(); i++) {
            Light* light = sp->getLight(i);
            light->getIllumination(hit.getIntersectionPoint(), light_dir, light_col, light_distance);

            if(shadow) {
                Ray ray2(ray.getOrigin() + ray.getDirection() * hit.getT(), light_dir);
                Hit hit2(light_distance, NULL, {0, 0, 0});
                group->intersect(ray2, hit2, epsilon);
                if(hit2.getT() == light_distance)
                {
                    color += hit.getMaterial()->Shade(ray, hit, light_dir, light_col);
                }
            } else {
                color += hit.getMaterial()->Shade(ray, hit, light_dir, light_col);
            }
        }

    	Vec3f reflective_color = hit.getMaterial()->getReflectiveColor();
    	if(reflective_color.Length() > 0)
    	{
            Ray mirror_ray(hit.getIntersectionPoint(), mirrorDirection(hit.getNormal(), ray.getDirection()));
            Hit mirror_hit(INFINITY, NULL, {0, 0, 1});
    		color += reflective_color * traceRay(mirror_ray, epsilon, bounces+1, weight, indexOfRefraction, mirror_hit);
        }

    	Vec3f transparent_color = hit.getMaterial()->getTransparentColor();
    	if(transparent_color.Length() > 0)
    	{
            Vec3f transmitted(0, 0, 0);
            Hit transparent_hit(INFINITY, NULL, {0, 0, 1});

            bool inside = (hit.getNormal()).Dot3(ray.getDirection()) > 0;
            bool check = false;
            if(inside){
                check = transmittedDirection(hit.getNormal(), ray.getDirection(), indexOfRefraction, 1, transmitted);
            }else{
                check = transmittedDirection(hit.getNormal(), ray.getDirection(), 1, hit.getMaterial()->getIndexOfRefraction(), transmitted);
            }

            Ray transparent_ray(hit.getIntersectionPoint(), transmitted);
            if(check){
                if(inside)
                {
                	transparent_color = transparent_color * traceRay(transparent_ray, epsilon, bounces+1, weight, 1.0, transparent_hit);
                }else{
            		transparent_color = transparent_color * traceRay(transparent_ray, epsilon, bounces+1, weight, hit.getMaterial()->getIndexOfRefraction(), transparent_hit);
                }
                color += transparent_color;
            }

    	}

        return color;
    }

    return sp->getBackgroundColor();
}