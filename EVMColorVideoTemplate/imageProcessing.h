/*
 * imageProcessing.h
 *
 *  Created on: 31 janv. 2013
 *      Author: pierre
 */

#ifndef IMAGEPROCESSING_H_
#define IMAGEPROCESSING_H_

#include "dsp_types.h"


// Preprocessor symbols
#define IMG_HEIGHT 		576
#define IMG_WIDTH 		720
#define IMG_HEIGHT_NTSC 480

// new types

// enumerations

// structures

// function's prototypes
void dataProcessing(uint8 *YInputBuffer, uint8 *YOutputBuffer, uint8 *CbOutputBuffer, uint8 *CrOutputBuffer, uint32 imgHeight, uint32 imgWidth);

// exported variables

#endif /* IMAGEPROCESSING_H_ */
