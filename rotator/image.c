
#include <image.h>

/*垂直翻转*/
void flip_ver(void)
{
	CONTROL &= ~(0x3 << 6);
	CONTROL |= 0x2 << 6;
}

/*水平翻转*/
void flip_hor(void)
{
	CONTROL |= 0x3 << 6;
}

void start_rotat(void)
{
	CONTROL |= 0x1;
}


void image_rotat(void)
{
	/**/
	CONTROL = (0x6 << 8);

	SRCBASEADDR0 = SRC_IMAGE; //要翻转的图片所在的地址为  ：0x60000000
	DSTBASEADDR0 = DST_IMAGE; //翻转结束后图片所在的地址为：0x65000000

	/*原图片的大小设置*/
	SRCIMGSIZE = (480 << 16) | 800;
	SRC_XY = 0;
	SRCROTSIZE = (480 << 16) | 800;

	DSTIMGSIZE = (480 << 16) | 800;

	DST_XY = 0;
}
