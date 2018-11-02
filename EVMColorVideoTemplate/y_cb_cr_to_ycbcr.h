/*
 * y_cb_cr_to_y.h
 *
 *  Created on: 31 janv. 2013
 *      Author: pierre
 */

#ifndef Y_CB_CR_TO_Y_H_
#define Y_CB_CR_TO_Y_H_

#include "dsp_types.h"

void y_cb_cr_to_ycbcr(uint8 *YBufferOut, uint8 *CbBuffer, uint8 *CrBuffer, uint8 *frameBufferPtr, uint32 width, uint32 height);


#endif /* Y_CB_CR_TO_Y_H_ */
