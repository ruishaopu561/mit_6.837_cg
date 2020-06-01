#ifndef _GROUP_H_
#define _GROUP_H_

#include "object3d.h"

class Group : public Object3D
{
public:
    Group(int &);
    ~Group();
    virtual bool intersect(const Ray &r, Hit &h, float tmin);
    void addObject(int index, Object3D *obj);
    virtual void paint(void);
    int getSize();
private:
    Object3D **objects;
    int size;
};

#endif // !_GROUP_H_