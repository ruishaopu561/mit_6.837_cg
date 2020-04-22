#!/bin/bash
make clean
make
rm -r ./result
mkdir result
./raytracer -input scene/scene1_01.txt -size 200 200 -output ./result/output1_01.tga -depth 9 10 ./result/depth1_01.tga
./raytracer -input scene/scene1_02.txt -size 200 200 -output ./result/output1_02.tga -depth 8 12 ./result/depth1_02.tga
./raytracer -input scene/scene1_03.txt -size 200 200 -output ./result/output1_03.tga -depth 8 12 ./result/depth1_03.tga
./raytracer -input scene/scene1_04.txt -size 200 200 -output ./result/output1_04.tga -depth 12 17 ./result/depth1_04.tga
./raytracer -input scene/scene1_05.txt -size 200 200 -output ./result/output1_05.tga -depth 14.5 19.5 ./result/depth1_05.tga
./raytracer -input scene/scene1_06.txt -size 200 200 -output ./result/output1_06.tga -depth 3 7 ./result/depth1_06.tga
./raytracer -input scene/scene1_07.txt -size 200 200 -output ./result/output1_07.tga -depth -2 2 ./result/depth1_07.tga
make clean
echo "done!"