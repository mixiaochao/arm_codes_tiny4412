#! /bin/bash

./mkimage mm1/1.jpg 1image
./mkimage mm1/2.jpg 2image
./mkimage mm1/3.jpg 3image
./mkimage mm1/4.jpg 4image
./mkimage mm1/5.jpg 5image
./mkimage mm1/6.jpg 6image
./mkimage mm1/7.jpg 7image
./mkimage mm1/8.jpg 8image
./mkimage mm1/9.jpg 9image
./mkimage mm1/10.jpg 10image
./mkimage mm1/11.jpg 11image
./mkimage mm1/12.jpg 12image
./mkimage mm1/13.jpg 13image
./mkimage mm1/14.jpg 14image
./mkimage mm1/15.jpg 15image
./mkimage mm1/16.jpg 16image
./mkimage mm1/17.jpg 17image
./mkimage mm1/18.jpg 18image
./mkimage mm1/19.jpg 19image
./mkimage mm1/20.jpg 20image

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
cat 14image >> 1image
cat 15image >> 1image
cat 16image >> 1image
cat 17image >> 1image
cat 18image >> 1image
cat 19image >> 1image
cat 20image >> 1image

mv 1image pics

rm -f *image





