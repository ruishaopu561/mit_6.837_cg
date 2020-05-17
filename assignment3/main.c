#include <iostream>
#include <cstring>
#include "image.h"
#include "scene_parser.h"
#include "hit.h"
#include "material.h"
#include "light.h"
#include "camera.h"
#include "group.h"

using namespace std;

int main(int argc, char* argv[]) {
    std::cout << "make success!" << std::endl;

 	char *input_file = NULL;
	char *output_file = NULL;
	int width = 100;
	int height = 100;
	bool gui = false;
    bool gouraud = false;

	// sample command line:
    // raytracer -input scene3_01_cube_orthographic.txt -size 200 200 -output output3_01.tga -gui
	
    for (int i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "-input")) {
			i++; assert(i < argc);
			input_file = argv[i];
            cout << argv[i] << endl;
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
			i++; assert(i < argc);
			width = atoi(argv[i]);
			i++; assert(i < argc);
			height = atoi(argv[i]);
		}
		else if (!strcmp(argv[i], "-gouraud ")) {
			i++; assert(i < argc);
            gouraud = true;
		}
		else {
			printf("whoops error with command line argument %d: '%s'\n", i, argv[i]);
			assert(0);
		}
	}
    
    cout << "parse ok! " << input_file << endl;
    
	SceneParser sp(input_file);
    cout << "parse ok!" << endl;
	Image *color_img=NULL;
	if (output_file) {
		color_img = new Image(width, height);
		color_img->SetAllPixels(sp.getBackgroundColor());
	}
	Group* g = sp.getGroup();
	Camera* cam = sp.getCamera();
	for (int i = 0; i <width; i++) {
		for (int j = 0; j < height; j++) {
			Hit h(INFINITY, NULL, {0, 0, 1});
			Ray r = cam->generateRay({i * 1.0f / width, j * 1.0f / width});
			bool hited = g->intersect(r, h, cam->getTMin());
			if (hited) {
				Vec3f hit_normal = h.getNormal();
				bool back = hit_normal.Dot3(r.getDirection()) > 0;
				if (back) {
					if(color_img) {
    					color_img->SetPixel(i, j, {0, 0, 0});
                    }
					continue;
				}
				if (back) hit_normal.Negate();
				h.set(h.getT(), h.getMaterial(), hit_normal, r);
				Vec3f pixel_color;
				if (color_img) {
					color_img->SetPixel(i, j, pixel_color);
				}
			}
		}
	}
	if (color_img)
    {
        color_img->SaveTGA(output_file);
    }

    return 0;
}