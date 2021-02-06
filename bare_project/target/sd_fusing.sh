
if [ -z $1 ]
then
    echo "usage: ./sd_fusing.sh <SD Reader's device file>"
    exit 0
fi

if [ -b $1 ]
then
    echo "$1 reader is identified."
else
    echo "$1 is NOT identified."
    exit 0
fi

####################################
#<verify device>

BDEV_NAME=`basename $1`
BDEV_SIZE=`cat /sys/block/${BDEV_NAME}/size`

if [ ${BDEV_SIZE} -le 0 ]; then
	echo "Error: NO media found in card reader."
	exit 1
fi

if [ ${BDEV_SIZE} -gt 32000000 ]; then
	echo "Error: Block device size (${BDEV_SIZE}) is too large"
	exit 1
fi

####################################
# check files

MYDRV=./arm.bin

if [ ! -f ${MYDRV} ]; then
	echo "Error: u-boot.bin NOT found, please build it & try again."
	exit -1
fi

if [ ! -f ${MKBL2} ]; then
	echo "Error: can not find host tool - mkbl2, stop."
	exit -1
fi

####################################
# fusing images

signed_bl1_position=1
bl2_position=17
my_position=49
image_position=705   #size: 40960
pic_position=42000
#<BL1 fusing>
echo "---------------------------------------"
echo "BL1 fusing"
dd iflag=dsync oflag=dsync if=./bl1.bin of=$1 seek=$signed_bl1_position

#<BL2 fusing>
echo "---------------------------------------"
echo "BL2 fusing"
dd iflag=dsync oflag=dsync if=./bl2.bin of=$1 seek=$bl2_position

#<mydrv fusing>
echo "---------------------------------------"
echo "The driver fusing"
dd iflag=dsync oflag=dsync if=${MYDRV} of=$1 seek=$my_position

echo "---------------------------------------"
#<images fusing>
echo "---------------------------------------"
echo "The Menu fusing"
dd iflag=dsync oflag=dsync if=./images of=$1 seek=$image_position

echo "---------------------------------------"
#<images fusing>
echo "---------------------------------------"
echo "The pic fusing"
dd iflag=dsync oflag=dsync if=./pics of=$1 seek=$pic_position

echo "--------------007System-----------------------"
echo "The development team members are Songze Lee"
echo "Shuchao Wang, Ning Cheng and Rui Ma."
echo "------------------Thank Use!------------------"

sync

####################################
#<Message Display>
echo "---------------------------------------"
echo "The driver  is fused successfully."
echo "Eject SD card and insert it again."

