#!/bin/bash
make clean
make
rm -r ./result
mkdir result

./raytracer -input ./scene/scene2_01_diffuse.txt -size 200 200 -output ./result/output2_01.tga
./raytracer -input ./scene/scene2_02_ambient.txt -size 200 200 -output ./result/output2_02.tga
./raytracer -input ./scene/scene2_03_colored_lights.txt -size 200 200 -output ./result/output2_03.tga -normals ./result/normals2_03.tga
./raytracer -input ./scene/scene2_04_perspective.txt -size 200 200 -output ./result/output2_04.tga -normals ./result/normals2_04.tga
./raytracer -input ./scene/scene2_05_inside_sphere.txt -size 200 200 -output ./result/output2_05.tga -depth 9 11 ./result/depth2_05.tga -normals ./result/normals2_05.tga -shade_back
./raytracer -input ./scene/scene2_05_inside_sphere.txt -size 200 200 -output ./result/output2_05_no_back.tga
./raytracer -input ./scene/scene2_06_plane.txt -size 200 200 -output ./result/output2_06.tga -depth 8 20 ./result/depth2_06.tga -normals ./result/normals2_06.tga
./raytracer -input ./scene/scene2_07_sphere_triangles.txt -size 200 200 -output ./result/output2_07.tga -depth 9 11 ./result/depth2_07.tga -normals ./result/normals2_07.tga -shade_back
./raytracer -input ./scene/scene2_07_sphere_triangles.txt -size 200 200 -output ./result/output2_07_no_back.tga
./raytracer -input ./scene/scene2_08_cube.txt -size 200 200 -output ./result/output2_08.tga
./raytracer -input ./scene/scene2_09_bunny_200.txt -size 200 200 -output ./result/output2_09.tga
./raytracer -input ./scene/scene2_10_bunny_1k.txt -size 200 200 -output ./result/output2_10.tga
./raytracer -input ./scene/scene2_11_squashed_sphere.txt -size 200 200 -output ./result/output2_11.tga -normals ./result/normals2_11.tga
./raytracer -input ./scene/scene2_12_rotated_sphere.txt -size 200 200 -output ./result/output2_12.tga -normals ./result/normals2_12.tga
./raytracer -input ./scene/scene2_13_rotated_squashed_sphere.txt -size 200 200 -output ./result/output2_13.tga -normals ./result/normals2_13.tga
./raytracer -input ./scene/scene2_14_axes_cube.txt -size 200 200 -output ./result/output2_14.tga
./raytracer -input ./scene/scene2_15_crazy_transforms.txt -size 200 200 -output ./result/output2_15.tga
./raytracer -input ./scene/scene2_16_t_scale.txt -size 200 200 -output ./result/output2_16.tga -depth 2 7 ./result/depth2_16.tga

make clean
echo "done!"