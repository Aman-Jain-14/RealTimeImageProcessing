/*
 * File     : ycbcr_to_y_cb_cr.c
 * Author   : Pierre BRESSY
 * Company  : HEIG-VD
 * Created  : Tue Jan  8 14:34:50 2013
 * Purpose  :

 |   Date   | By  | Description of changes in ycbcr_to_y_cb_cr.c
 +----------+-----+-----------------------------------------------------------+
 |          |     |

*/

#include "dsp_types.h"

/** extract Y, Cb, Cr buffers from the video acq driver YCbCr mixed buffer */
void ExtractYCbCr(uint8* src, uint8* YBuffer, uint8 *CbBuffer, uint8* CrBuffer, uint32 width, uint32 height) {
	uint32 m, m1, m2;
	// separate Y U V, set U and V to 0x80 (gray scale image)
	for(m = 0; m < _mpy(width,height)>>1; m++)
	{
		m1 = m<<1;
		m2 = m<<2;
		*(CbBuffer + m)    = (*(src + m2 + 0));//0x80;
		*(YBuffer  + m1)   = (*(src + m2 + 1));
		*(YBuffer  + m1+1) = (*(src + m2 + 3));
		*(CrBuffer + m)    = (*(src + m2 + 2));//0x80;
	}
	return;
}
 
/** extract Y buffer from the video acq driver YCbCr mixed buffer */
// Cb and Cr are not used
void ExtractYCbCr2(uint8* src, uint8* YBuffer, uint8 *CbBuffer, uint8* CrBuffer, uint32 width, uint32 height) {
	uint32 *s=(uint32*)src;
	uint32 d,m;
	uint32 size=_mpy(width,height)>>1;
	for(m = 0; m < size; m++)
	{
		d=*s;
		s++;
		*(YBuffer)  = (d & 0x0000FF00)>>8;
		YBuffer++;
		*(YBuffer)  = (d & 0xFF000000)>>24;
		YBuffer++;
	}
	return;
}

// merge YBuffer, CbBuffer, CrBuffer to dst as YCbCr 422 format
// use 32bit data format to increase speed
void y_cb_cr_to_ycbcr2(uint8* YBuffer,uint8* CbBuffer,uint8* CrBuffer,uint8* dst, uint32 width, uint32 height) {

	uint32 limit=_mpy(width,height)>>3;
	uint32 m;
	uint32 *y0=(uint32*)YBuffer;
	uint32 y;
	uint32 *cb=(uint32*)CbBuffer;
	uint32 b,r;
	uint32 *cr=(uint32*)CrBuffer;
	uint32 *out=(uint32*)dst;

	for(m=0;m<limit;m++) {

		y=*y0;
		b=*cb;
		r=*cr;
		*out=((y&0x0000FF00)<< 16) | ((r&0x000000FF)<<16) | ((y&0x000000FF)<<8) | ((b&0x000000FF)   );
		out++;
		*out=((y&0xFF000000)     ) | ((r&0x0000FF00)<< 8) | ((y&0x00FF0000)>>8) | ((b&0x0000FF00)>>8);
		out++;
		y0++;
		y=*y0;
		*out=((y&0x0000FF00)<< 16) | ((r&0x00FF0000)    ) | ((y&0x000000FF)<<8) | ((b&0x00FF0000)>>16);
		out++;
		*out=((y&0xFF000000)     ) | ((r&0xFF000000)>> 8) | ((y&0x00FF0000)>>8) | ((b&0xFF000000)>>24);
		out++;
		y0++;
		cb++;
		cr++;
	}
}

