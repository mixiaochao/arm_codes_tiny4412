#! /bin/bash

./mkimage pro/1.jpg 1image
./mkimage pro/2.jpg 2image
./mkimage pro/3.jpg 3image
./mkimage pro/4.jpg 4image
./mkimage pro/5.jpg 5image
./mkimage pro/6.jpg 6image
./mkimage pro/7.jpg 7image
./mkimage pro/8.jpg 8image
./mkimage pro/9.jpg 9image
./mkimage pro/10.jpg 10image
./mkimage pro/11.jpg 11image
./mkimage pro/12.jpg 12image
./mkimage pro/13.jpg 13image


cat 2image >> 1image
cat 3image >> 1image
cat 4image >> 1image
cat 5image >> 1image
cat 6image >> 1image
cat 7image >> 1image
cat 8image >> 1image
cat 9image >> 1image
cat 10image >> 1image
cat 11image >> 1image
cat 12image >> 1image
cat 13image >> 1image

mv 1image images

rm -f *image





