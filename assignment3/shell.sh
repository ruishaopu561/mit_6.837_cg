#!/bin/bash
make clean
make
rm -r ./result
mkdir result

./main -input ./scene/scene3_01_cube_orthographic.txt -size 200 200 -output ./result/output3_01.tga -gui
./main -input ./scene/scene3_02_cube_perspective.txt -size 200 200 -output ./result/output3_02.tga -gui
./main -input ./scene/scene3_03_bunny_mesh_200.txt -size 200 200 -output ./result/output3_03.tga -gui
./main -input ./scene/scene3_04_bunny_mesh_1k.txt -size 200 200 -output ./result/output3_04.tga -gui
./main -input ./scene/scene3_05_axes_cube.txt -size 200 200 -output ./result/output3_05.tga -gui
./main -input ./scene/scene3_06_crazy_transforms.txt -size 200 200 -output ./result/output3_06.tga -gui
./main -input ./scene/scene3_07_plane.txt -size 200 200 -output ./result/output3_07.tga -gui -tessellation 10 5
./main -input ./scene/scene3_08_sphere.txt -size 200 200 -output ./result/output3_08.tga -gui -tessellation 10 5
./main -input ./scene/scene3_08_sphere.txt -size 200 200 -output ./result/output3_08.tga -gui -tessellation 20 10
./main -input ./scene/scene3_08_sphere.txt -size 200 200 -output ./result/output3_08.tga -gui -tessellation 10 5 -gouraud
./main -input ./scene/scene3_08_sphere.txt -size 200 200 -output ./result/output3_08.tga -gui -tessellation 20 10 -gouraud
./main -input ./scene/scene3_09_exponent_variations.txt -size 300 300 -output ./result/output3_09.tga -gui -tessellation 100 50 -gouraud
./main -input ./scene/scene3_10_exponent_variations_back.txt -size 300 300 -output ./result/output3_10.tga -gui -tessellation 100 50 -gouraud 
./main -input ./scene/scene3_11_weird_lighting_diffuse.txt -size 200 200 -output ./result/output3_11.tga -gui -tessellation 100 50 -gouraud 
./main -input ./scene/scene3_12_weird_lighting_specular.txt -size 200 200 -output ./result/output3_12.tga -gui -tessellation 100 50 -gouraud

make clean
echo "done!"