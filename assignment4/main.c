#include <cstring>
#include "GL/freeglut.h"
#include "image.h"
#include "scene_parser.h"
#include "hit.h"
#include "material.h"
#include "light.h"
#include "camera.h"
#include "group.h"
#include "glCanvas.h"
#include "raytracer.h"

using namespace std;

char *input_file = NULL;
char *output_file = NULL;
int width = 100;
int height = 100;
bool gui = false;
bool gouraud = false;
bool tessellation = false;
float t_phi = 0;
float t_theta = 0;
bool shadows = false;
bool bounce = false;
bool weight = false;
bool shade_back = false;
int max_bounces = 0;
float weights = float(0);
float epsilon = 0.1;

SceneParser *sp = NULL;

void render();
void traceRay(float i, float j);

int main(int argc, char* argv[]) {
	// sample command line:
    // ./main -input scene3_01_cube_orthographic.txt -size 200 200 -output output3_01.tga -gui
	
    for (int i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "-input")) {
			i++; assert(i < argc);
			input_file = argv[i];
		}
		else if (!strcmp(argv[i], "-size")) {
			i++; assert(i < argc);
			width = atoi(argv[i]);
			i++; assert(i < argc);
			height = atoi(argv[i]);
		}
		else if (!strcmp(argv[i], "-output")) {
			i++; assert(i < argc);
			output_file = argv[i];
		}
		else if (!strcmp(argv[i], "-shadows")) {
			shadows = true;
		}
		else if (!strcmp(argv[i], "-shade_back")) {
			shade_back = true;
		}
		else if (!strcmp(argv[i], "-bounces")) {
			bounce = true;
			i++; assert(i < argc);
			max_bounces = atoi(argv[i]);
		}
		else if (!strcmp(argv[i], "-weight")) {
			weight = true;
			i++; assert(i < argc);
			weights = atof(argv[i]);
		}
        else if (!strcmp(argv[i], "-gui")) {
            gui = true;
        }
		else if (!strcmp(argv[i], "-tessellation")) {
			tessellation = true;
			i++; assert(i < argc);
			t_theta = atof(argv[i]);
			i++; assert(i < argc);
			t_phi = atof(argv[i]);
		}
		else if (!strcmp(argv[i], "-gouraud")) {
            gouraud = true;
		}
		else {
			printf("whoops error with command line argument %d: '%s'\n", i, argv[i]);
			assert(0);
		}
	}
    
	cout << "parse ok!" << endl;

	sp = new SceneParser(input_file);
	RayTracer *rt = new RayTracer(sp, max_bounces, weights, shadows);

	if(gui)
	{
		glutInit(&argc, argv);
		GLCanvas gc;
		gc.initialize(sp, render, traceRay);
	}
	else{
		render();
		// traceRay();
	}
    return 0;
}

void render()
{
	Image *color_img=NULL;
	if (output_file) {
		color_img = new Image(width, height);
		color_img->SetAllPixels(sp->getBackgroundColor());
	}
	Group* group = sp->getGroup();
	Camera* camera = sp->getCamera();
	Vec3f color;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			Hit h(INFINITY, NULL, {0, 0, 1});
			Ray r = camera->generateRay({i * 1.0f / width, j * 1.0f / width});
			bool hited = group->intersect(r, h, camera->getTMin());
			if (hited) {
				Vec3f hit_normal = h.getNormal();
				h.set(h.getT(), h.getMaterial(), hit_normal, r);

				color = sp->getAmbientLight() * (h.getMaterial()->getDiffuseColor());
				for (int i = 0; i < sp->getNumLights(); i++) {
					Light* light = sp->getLight(i);
					Vec3f light_dir, light_col;
					float light_distance;
					light->getIllumination(h.getIntersectionPoint(), light_dir, light_col, light_distance);

					Ray ray2(r.getOrigin() + r.getDirection() * h.getT(), light_dir);
					Hit hit2(light_distance, NULL, {0,0,0});
					group->intersect(ray2, hit2, epsilon);
					if(hit2.getT() == light_distance)
					{
						color += h.getMaterial()->Shade(r, h, light_dir, light_col);
					}
				}

				color_img->SetPixel(i, j, color);
			}
		}
	}
	if (color_img)
    {
        color_img->SaveTGA(output_file);
    }

	delete color_img;
}

void traceRay(float i, float j)
{

}
