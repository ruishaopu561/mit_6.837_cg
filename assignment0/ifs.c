#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <assert.h>
#include "ifs.h"
#include "vectors.h"

float randf()
{
    return (float)rand() / RAND_MAX;
}

Ifs::Ifs(int n)
{
    count = n;
};

Ifs::~Ifs()
{
}

void Ifs::add_matrix(Matrix m, int index)
{
    if(index < 0 || index >= count)
    {
        return;
    }
    transformations.push_back(m);
}

void Ifs::add_prob(float p, int index)
{
    if(index < 0 || index >= count)
    {
        return;
    }
    else if(index == 0)
    {
        prob.push_back(p);
    }
    else{
        prob.push_back(p + prob[index-1]);
    }
    // printf("probability %f\n", prob[index]);
}

void Ifs::read_matrix()
{
    for(int i=0; i<count; i++)
    {
        Matrix m = transformations[i];
        m.Write3x3();
    }
}

void Ifs::read(const char* file)
{
    FILE *input = fopen(file,"r");
    assert(input != NULL);

    int num_transforms;
    fscanf(input,"%d",&num_transforms);

    count = num_transforms;

    for (int i = 0; i < num_transforms; i++) {
        float probability;
        fscanf (input,"%f",&probability);

        Matrix m; 
        m.Read3x3(input);

        add_prob(probability, i);
        add_matrix(m, i);
    }

    fclose(input);
}

void Ifs::render(Image &image, int num_points, int num_iters)
{
    Vec3f white(1.0f, 1.0f, 1.0f), black(0.0f, 0.0f, 0.0f);
    image.SetAllPixels(white);
    int width = image.Width();
    int height = image.Height();

    while(num_points--)
    {
        Vec4f point(randf(), randf(), 0, 1);
        for(int i=0; i < num_iters; i++)
        {
            float r = randf();
            Matrix m = transformations[count - 1];
            for(int j=0; j<count; j++)
            {
                if(r < prob[j])
                {
                    m = transformations[j];
                    break;
                }
            }
            m.Transform(point);
        }

        int tx = max(0, min((int)(point.x()*width), width-1));
        int ty = max(0, min((int)(point.y()*height), height-1));

        image.SetPixel(tx, ty, black);
    }
}
