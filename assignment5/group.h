#ifndef _GROUP_H_
#define _GROUP_H_

#include "object3d.h"
#include "grid.h"

class Group : public Object3D
{
public:
    Group(int &);
    ~Group();
    void addObject(int index, Object3D *obj);
    virtual bool intersect(const Ray &r, Hit &h, float tmin);
    virtual void paint(void);
    virtual void insertIntoGrid(Grid *g, Matrix *m);
    int getSize();
private:
    Object3D **objects;
    int size;
};

#endif // !_GROUP_H_