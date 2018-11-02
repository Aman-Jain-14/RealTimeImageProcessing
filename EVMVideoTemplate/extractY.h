/*
 * File     : extractY.h
 * Author   : Pierre BRESSY
 * Company  : HEIG-VD
 * Created  : Tue Jan  8 14:34:50 2013
 * Purpose  :

 |   Date   | By  | Description of changes in extractY.h
 +----------+-----+-----------------------------------------------------------+
 |          |     |

*/

#ifndef _EXTRACTY_H_
#define _EXTRACTY_H_

#include "dsp_types.h"

void extractY(uint32* ycbcrBuffer,uint8 *yBuffer,int width, int height);


#endif /* _EXTRACTY_H_ */
