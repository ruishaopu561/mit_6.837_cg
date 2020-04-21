#!/bin/bash
make clean
make
rm -r ./image
mkdir image
./raytracer -input scene/scene1_01.txt -size 200 200 -output ./image/output1_01.tga -depth 8 12 ./image/depth1_01.tga
./raytracer -input scene/scene1_02.txt -size 200 200 -output ./image/output1_02.tga -depth 8 12 ./image/depth1_02.tga
./raytracer -input scene/scene1_03.txt -size 200 200 -output ./image/output1_03.tga -depth 8 12 ./image/depth1_03.tga
./raytracer -input scene/scene1_04.txt -size 200 200 -output ./image/output1_04.tga -depth 8 12 ./image/depth1_04.tga
./raytracer -input scene/scene1_05.txt -size 200 200 -output ./image/output1_05.tga -depth 8 12 ./image/depth1_05.tga
./raytracer -input scene/scene1_06.txt -size 200 200 -output ./image/output1_06.tga -depth 8 12 ./image/depth1_06.tga
./raytracer -input scene/scene1_07.txt -size 200 200 -output ./image/output1_07.tga -depth 8 12 ./image/depth1_07.tga
make clean
echo "done!"