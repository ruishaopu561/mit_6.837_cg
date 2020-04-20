#ifndef _IFS_H_
#define _IFS_H_

#include <assert.h>
#include <vector>
#include "matrix.h"
#include "image.h"

class Ifs
{
public:
    Ifs(int n);
    ~Ifs();
    void add_matrix(Matrix m, int index);
    void add_prob(float p, int index);
    void read_matrix();
    void read(const char* file);
    void render(Image &image, int num_points, int num_iters);
private:
    int count;
    std::vector<float> prob;
    std::vector<Matrix> transformations;
};

#endif // _IFS_H_