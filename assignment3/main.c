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
SceneParser *sp = NULL;

void render();

void diffuse_shader(const SceneParser *sp, Ray &ray, const Hit& hit, Vec3f& color) {
	color = sp->getAmbientLight() * (hit.getMaterial()->getDiffuseColor());
	for (int i = 0; i < sp->getNumLights(); i++) {
		Light* light = sp->getLight(i);
		Vec3f light_dir, light_col;
		float light_distance;
		light->getIllumination(hit.getIntersectionPoint(), light_dir, light_col, light_distance);
		color += hit.getMaterial()->Shade(ray, hit, light_dir, light_col);
	}
}

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
    
	sp = new SceneParser(input_file);
	if(gui)
	{
		glutInit(&argc, argv);
		GLCanvas gc;
		gc.initialize(sp, render);
	}
	else{
		render();
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
	Group* g = sp->getGroup();
	Camera* cam = sp->getCamera();
	for (int i = 0; i <width; i++) {
		for (int j = 0; j < height; j++) {
			Hit h(INFINITY, NULL, {0, 0, 1});
			Ray r = cam->generateRay({i * 1.0f / width, j * 1.0f / width});
			bool hited = g->intersect(r, h, cam->getTMin());
			if (hited) {
				Vec3f hit_normal = h.getNormal();
				h.set(h.getT(), h.getMaterial(), hit_normal, r);
				Vec3f pixel_color;
				if (color_img) {
					diffuse_shader(sp, r, h, pixel_color);
					color_img->SetPixel(i, j, pixel_color);
				}
			}
		}
	}
	if (color_img)
    {
        color_img->SaveTGA(output_file);
    }

	delete color_img;
}