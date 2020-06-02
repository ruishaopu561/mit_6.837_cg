#ifndef _GRID_H_
#define _GRID_H_

#include "boundingbox.h"

class Grid
{
public:
    int x, y, z;

    Grid(BoundingBox *bb, int nx, int ny, int nz);
    ~Grid() {};
    BoundingBox *getBoundingBox();
    void paint();
    bool *getIsOpaque();
    void setIsOpaque(int, int, int, bool);
private:
    BoundingBox *bouding_box;
    bool *isOpaque;
};

#endif // !_GRID_H_