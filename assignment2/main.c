#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <cstring>
#include <float.h>
#include "camera.h"
#include "scene_parser.h"
#include "hit.h"
#include "ray.h"
#include "group.h"
#include "image.h"
#include "light.h"

Vec3f setcolor(int depth_min, int depth_max, float depth)
{
	float t = ((float)depth_max - depth) / (depth_max - depth_min);
	return Vec3f(t, t, t);
}

void saveImage(const char *output_file, SceneParser *sp, int width, int height)
{
    if(output_file == NULL)
    {
        return;
    }

    Image *image = new Image(width, height);

    Camera *camera = sp->getCamera();
    Group *group = sp->getGroup();
    Vec3f ambient = sp->getAmbientLight();

    image->SetAllPixels(sp->getBackgroundColor());

    for(int i=0; i<width; i++)
    {
        for(int j=0; j<height; j++)
        {
            Hit h = Hit(FLT_MAX, NULL, Vec3f(0, 0, 1));
            Vec2f point((float)i/width, (float)j/height);
            Ray r = camera->generateRay(point);
            if(group->intersect(r, h, camera->getTMin()))
            {
                assert(h.getMaterial() != NULL);

                Vec3f color(ambient * (h.getMaterial())->getDiffuseColor());
                std::cout << color << std::endl;
                for(int k=0; k<sp->getNumLights(); k++)
                {
                    Vec3f dir(0, 0, 0), col(0, 0, 0);
                    Light *light = sp->getLight(k);
                    light->getIllumination (r.pointAtParameter(h.getT()), dir, col);
                    color += max(0.0f, dir.Dot3(h.getNormal())) * col * (h.getMaterial())->getDiffuseColor();
                }
                image->SetPixel(height - j - 1, width - i - 1, color);
            }
        }
    }

    image->SaveTGA(output_file);
}

void normalVisualization(const char* normal_file, SceneParser *sp, int width, int height)
{
    if(normal_file == NULL)
    {
        return;
    }
    
    Image *normalImg = new Image(width, height);
    normalImg->SetAllPixels(Vec3f(0, 0, 0));

    Camera *camera = sp->getCamera();
    Group *group = sp->getGroup();

    for(int i=0; i<width; i++)
    {
        for(int j=0; j<height; j++)
        {
            Hit h = Hit(FLT_MAX, NULL, Vec3f(0, 0, 1));
            Vec2f point((float)i/width, (float)j/height);
            Ray r = camera->generateRay(point);
            if(group->intersect(r, h, camera->getTMin()))
            {
                assert(h.getMaterial() != NULL);

                // 显示时取法向量各部分的绝对值
                float d0, d1, d2;
                h.getNormal().Get(d0, d1, d2);
                d0 = d0 >= 0 ? d0: -d0;
                d1 = d1 >= 0 ? d1: -d1;
                d2 = d2 >= 0 ? d2: -d2;
                normalImg->SetPixel(height - j - 1, width - i - 1, Vec3f(d0, d1, d2));
            }
        }
    }

    normalImg->SaveTGA(normal_file);
}

void saveDepthImg(const char* depth_file, SceneParser *sp, int width, int height, int depth_min, int depth_max)
{
    if(depth_file == NULL)
    {
        return;
    }
    
    Camera *camera = sp->getCamera();
    Group *group = sp->getGroup();

    Image *depthImg = new Image(width, height);
    depthImg->SetAllPixels(Vec3f(0, 0, 0));

    for(int i=0; i<width; i++)
    {
        for(int j=0; j<height; j++)
        {
            Hit h = Hit(FLT_MAX, NULL, Vec3f(0, 0, 1));
            Vec2f point((float)i/width, (float)j/height);
            Ray r = camera->generateRay(point);
            if(group->intersect(r, h, camera->getTMin()))
            {
                assert(h.getMaterial() != NULL);
                depthImg->SetPixel(height - j - 1, width - i - 1, setcolor(depth_min, depth_max, h.getT()));
            }
        }
    }

    depthImg->SaveTGA(depth_file);
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
    char *normal_file = NULL;
    bool shade_back = false;

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
        } else if (!strcmp(argv[i], "-normals")) {
            i++; assert (i < argc);
            normal_file = argv[i];
        } else if (!strcmp(argv[i], "-shade_back")) {
            shade_back = true;
        } else {
            printf ("whoops error with command line argument %d: '%s'\n",i,argv[i]);
            assert(0);
        }
    }

    // ========================================================
	// ========================================================

    SceneParser *sp = new SceneParser(input_file);
    saveImage(output_file, sp, width, height);
    saveDepthImg(depth_file, sp, width, height, depth_min, depth_max);
    normalVisualization(normal_file, sp, width, height);

    return 0;
}