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

E4412_DRIVER=./driver/arm.bin
MKBL2=./tool/mkbl2
INIT=./init/bl2.bin

if [ ! -f ${E4412_DRIVER} ]; then
	echo "Error: u-boot.bin NOT found, please build it & try again."
	exit -1
fi

if [ ! -f ${MKBL2} ]; then
	echo "Error: can not find host tool - mkbl2, stop."
	exit -1
fi

#<make bl2>
${MKBL2} ${INIT} bl2.bin 14336

####################################
# fusing images

signed_bl1_position=1
bl2_position=17
driver_position=49

#<BL1 fusing>
echo "---------------------------------------"
echo "BL1 fusing"
dd iflag=dsync oflag=dsync if=./E4412_N.bl1.bin of=$1 seek=$signed_bl1_position

#<BL2 fusing>
echo "---------------------------------------"
echo "BL2 fusing"
dd iflag=dsync oflag=dsync if=./bl2.bin of=$1 seek=$bl2_position

echo "---------------------------------------"
echo "driver fusing"
dd iflag=dsync oflag=dsync if=${E4412_DRIVER} of=$1 seek=$driver_position

sync

####################################
#<Message Display>
echo "---------------------------------------"
echo "driver image is fused successfully."
echo "Eject SD card and insert it again."

