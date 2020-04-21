#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <cstring>
#include "camera.h"
#include "scene_parser.h"
#include "hit.h"
#include "ray.h"
#include "group.h"
#include "image.h"

Vec3f setcolor(int depth_min, int depth_max, float depth)
{
	float t = ((float)depth_max - depth) / (depth_max - depth_min);
	return Vec3f(t, t, t);
}

int main(int argc, char* argv[])
{
    char *input_file = NULL;
    int width = 100;
    int height = 100;
    char *output_file = NULL;
    float depth_min = 0;
    float depth_max = 1;
    char *depth_file = NULL;

    // sample command line:
    // raytracer -input scene1_1.txt -size 200 200 -output output1_1.tga -depth 9 10 depth1_1.tga

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i],"-input")) {
            i++; assert (i < argc); 
            input_file = argv[i];
        } else if (!strcmp(argv[i],"-size")) {
            i++; assert (i < argc); 
            width = atoi(argv[i]);
            i++; assert (i < argc); 
            height = atoi(argv[i]);
        } else if (!strcmp(argv[i],"-output")) {
            i++; assert (i < argc); 
            output_file = argv[i];
        } else if (!strcmp(argv[i],"-depth")) {
            i++; assert (i < argc); 
            depth_min = atof(argv[i]);
            i++; assert (i < argc); 
            depth_max = atof(argv[i]);
            i++; assert (i < argc); 
            depth_file = argv[i];
        } else {
            printf ("whoops error with command line argument %d: '%s'\n",i,argv[i]);
            assert(0);
        }
    }

    // ========================================================
	// ========================================================

    SceneParser *sp = new SceneParser(input_file);
    Image *image = new Image(width, height);
    Image *backImg = new Image(width, height);

    Camera *camera = sp->getCamera();
    Group *group = sp->getGroup();

    image->SetAllPixels(sp->getBackgroundColor());
    backImg->SetAllPixels(Vec3f(0, 0, 0));

    for(int i=0; i<width; i++)
    {
        for(int j=0; j<height; j++)
        {
            Hit h = Hit();
            Vec2f point((float)i/width, (float)j/height);
            Ray r = camera->generateRay(point);
            if(group->intersect(r, h, camera->getTMin()))
            {
                assert(h.getMaterial() != NULL);
                image->SetPixel(height-j-1, width-i-1, (h.getMaterial())->getDiffuseColor());
                backImg->SetPixel(height-j-1, width-i-1, setcolor(depth_min, depth_max, h.getT()));
            }
        }
    }

    image->SaveTGA(output_file);
    backImg->SaveTGA(depth_file);

    return 0;
}