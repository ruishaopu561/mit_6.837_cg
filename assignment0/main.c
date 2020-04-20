#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <cstring>
#include "matrix.h"
#include "ifs.h"
#include "image.h"

int main(int argc, char* argv[])
{
    char *input_file = NULL;
    int num_points = 10000;
    int num_iters = 10;
    int size = 100;
    char *output_file = NULL;

    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i],"-input"))
        {
            i++; assert (i < argc); 
            input_file = argv[i];
        } else if (!strcmp(argv[i],"-points")) {
            i++; assert (i < argc); 
            num_points = atoi(argv[i]);
        } else if (!strcmp(argv[i],"-iters")) {
            i++; assert (i < argc); 
            num_iters = atoi(argv[i]);
        } else if (!strcmp(argv[i],"-size")) {
            i++; assert (i < argc); 
            size = atoi(argv[i]);
        } else if (!strcmp(argv[i],"-output")) {
            i++; assert (i < argc); 
            output_file = argv[i];
        } else {
            printf ("whoops error with command line argument %d: '%s'\n",i,argv[i]);
            assert(0);
        }
    }
    // printf ("parse ok! file name %s, points %d\n", input_file, num_points);

    Ifs *ifs = new Ifs(0);
    ifs->read(input_file);

    Image *image = new Image(size, size);
    ifs->render(*image, num_points, num_iters);
    image->SaveTGA(output_file);

    return 0;
}