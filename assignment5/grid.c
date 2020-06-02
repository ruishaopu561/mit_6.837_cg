#include "grid.h"

Grid::Grid(BoundingBox *bb, int nx, int ny, int nz);
{
    bounding_box = bb;
    x = nx;
    y = ny;
    z = nz;
    isOpaque = new bool[x * y * z];

    for(int i = 0; i<x * y * z; i++){
        isOpaque = false;
    }
}

BoundingBox *Grid::getBoundingBox()
{
    return bounding_box;
}

void Grid::paint()
{
    
}

bool *Grid::getIsOpaque()
{
    return isOpaque;
}

void Grid::setIsOpaque(int nx, int ny, int nz, bool value)
{
    int index = nx * y * z + ny * z + nz;
    isOpaque[index] = value;
}