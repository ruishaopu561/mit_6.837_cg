#include "group.h"

Group::Group(int &num_obejcts)
{
    size = num_obejcts;
    objects = new Object3D *[num_obejcts];
    for(int i=0; i<num_obejcts; i++)
    {
        objects[i] = NULL;
    }
}

Group::~Group()
{
    delete []objects;
}

bool Group::intersect(const Ray &r, Hit &h, float tmin)
{
    for(int i=0; i<size; i++)
    {
        Object3D *object = objects[i];
        if(object->intersect(r, h, tmin))
        {
            return true;
        }
    }
    return false;
}

void Group::addObject(int index, Object3D *obj)
{
    objects[index] = obj;
}