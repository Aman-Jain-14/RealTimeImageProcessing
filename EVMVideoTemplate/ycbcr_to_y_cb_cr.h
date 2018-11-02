/*
 * File     : ycbcr_to_y_cb_cr.h
 * Author   : Pierre BRESSY
 * Company  : HEIG-VD
 * Created  : Tue Jan  8 14:34:50 2013
 * Purpose  :

 |   Date   | By  | Description of changes in ycbcr_to_y_cb_cr.h
 +----------+-----+-----------------------------------------------------------+
 |          |     |

*/

#ifndef _YCBCR_TO_Y_CB_CR_H_
#define _YCBCR_TO_Y_CB_CR_H_

#include "dsp_types.h"


void ExtractYCbCr(uint8* src, uint8* YBuffer, uint8 *CbBuffer, uint8* CrBuffer, uint32 width, uint32 height);
void ExtractYCbCr2(uint8* src, uint8* YBuffer, uint8 *CbBuffer, uint8* CrBuffer, uint32 width, uint32 height);
void y_cb_cr_to_ycbcr2(uint8* YBuffer,uint8* CbBuffer,uint8* CrBuffer,uint8* dst, uint32 width, uint32 height);

#endif /* _YCBCR_TO_Y_CB_CR_H_ */
