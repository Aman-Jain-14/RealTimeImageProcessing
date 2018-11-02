/*
 * File     : video_loopback.c
 * Author   : Pierre BRESSY
 * Company  : HEIG-VD
 * Created  : Tue Jan  8 14:34:50 2013
 * Purpose  :

 |   Date   | By  | Description of changes in video_loopback.c
 +----------+-----+-----------------------------------------------------------+
 |          |     |

*/

/* runtime include files */
#include <stdio.h>
#include <stdlib.h>
#include <log.h>
#include <string.h>
#include <stdarg.h>

/* BIOS include files */
#include <std.h>
#include <gio.h>
#include <tsk.h>
#include <trc.h>

/* PSP include files */
#include <psp_i2c.h>
#include <psp_vpfe.h>
#include <psp_vpbe.h>
#include <fvid.h>
#include <psp_tvp5146_extVidDecoder.h>

/* CSL include files */
#include <soc.h>
#include <cslr_sysctl.h>

/* BSL include files */
#include <evmdm6437.h>
#include <evmdm6437_dip.h>

/* Video Params Defaults */
#include <vid_params_default.h>


#include "imageProcessing.h"

#include "extractY.h"
#include "y_cb_cr_to_ycbcr.h"
#include "ycbcr_to_y_cb_cr.h"

/* This example supports either PAL or NTSC depending on position of JP1 */
#define STANDARD_PAL  0
#define STANDARD_NTSC 1

#define FRAME_BUFF_CNT 6

static int read_JP1(void);

static CSL_SysctlRegsOvly sysModuleRegs = (CSL_SysctlRegsOvly )CSL_SYS_0_REGS;

uint8 YBufferIn[IMG_HEIGHT*IMG_WIDTH];
uint8 YBufferOut[IMG_HEIGHT*IMG_WIDTH];
uint8 CbOutputBuffer[IMG_HEIGHT*IMG_WIDTH>>1];
uint8 CrOutputBuffer[IMG_HEIGHT*IMG_WIDTH>>1];


/*
 * ======== main ========
 */
void main() {

    printf("Image Processing started\n");
    fflush(stdout);

    /* Initialize BSL library to read jumper switches: */
    EVMDM6437_DIP_init();

    /* VPSS PinMuxing */
    /* CI10SEL   - No CI[1:0]                       */
    /* CI32SEL   - No CI[3:2]                       */
    /* CI54SEL   - No CI[5:4]                       */
    /* CI76SEL   - No CI[7:6]                       */
    /* CFLDSEL   - No C_FIELD                       */
    /* CWENSEL   - No C_WEN                         */
    /* HDVSEL    - CCDC HD and VD enabled           */
    /* CCDCSEL   - CCDC PCLK, YI[7:0] enabled       */
    /* AEAW      - EMIFA full address mode          */
    /* VPBECKEN  - VPBECLK enabled                  */
    /* RGBSEL    - No digital outputs               */
    /* CS3SEL    - LCD_OE/EM_CS3 disabled           */
    /* CS4SEL    - CS4/VSYNC enabled                */
    /* CS5SEL    - CS5/HSYNC enabled                */
    /* VENCSEL   - VCLK,YOUT[7:0],COUT[7:0] enabled */
    /* AEM       - 8bEMIF + 8bCCDC + 8 to 16bVENC   */
    sysModuleRegs -> PINMUX0    &= (0x005482A3u);
    sysModuleRegs -> PINMUX0    |= (0x005482A3u);

    /* PCIEN    =   0: PINMUX1 - Bit 0 */
    sysModuleRegs -> PINMUX1 &= (0xFFFFFFFEu);
    sysModuleRegs -> VPSSCLKCTL = (0x18u);

    return;
}


/*
 * ======== processing_task ========
 */
void processing_task(void) {

  FVID_Frame *frameBuffTable[FRAME_BUFF_CNT];
  FVID_Frame *frameBuffPtr;
  GIO_Handle hGioVpfeCcdc;
  GIO_Handle hGioVpbeVid0;
  GIO_Handle hGioVpbeVenc;
  uint32 status = 0;
  uint32 result;
  uint32 i;
  uint32 standard;
  uint32 width;
  uint32 height;
  uint32 frameCounter=0;

  /* Set video display/capture driver params to defaults */
  PSP_VPFE_TVP5146_ConfigParams tvp5146Params = 
       VID_PARAMS_TVP5146_DEFAULT;
  PSP_VPFECcdcConfigParams      vpfeCcdcConfigParams = 
       VID_PARAMS_CCDC_DEFAULT_D1;
  PSP_VPBEOsdConfigParams vpbeOsdConfigParams = 
       VID_PARAMS_OSD_DEFAULT_D1;
  PSP_VPBEVencConfigParams vpbeVencConfigParams;

  standard = read_JP1();
  
  /* Update display/capture params based on video standard (PAL/NTSC) */
  if (standard == STANDARD_PAL)  {
       width  = IMG_WIDTH;
       height = IMG_HEIGHT;
       vpbeVencConfigParams.displayStandard = PSP_VPBE_DISPLAY_PAL_INTERLACED_COMPOSITE;
  }
  else {
       width  = IMG_WIDTH;
       height = IMG_HEIGHT_NTSC;
       vpbeVencConfigParams.displayStandard = PSP_VPBE_DISPLAY_NTSC_INTERLACED_COMPOSITE;
  }
  vpfeCcdcConfigParams.height = vpbeOsdConfigParams.height = height;
  vpfeCcdcConfigParams.width = vpbeOsdConfigParams.width = width;
  vpfeCcdcConfigParams.pitch = vpbeOsdConfigParams.pitch = width * 2;

  /* init the frame buffer table */
  for (i=0; i<FRAME_BUFF_CNT; i++) {
    frameBuffTable[i] = NULL;
  }

  /* create video input channel */
  if (status == 0) {
    PSP_VPFEChannelParams vpfeChannelParams;
    vpfeChannelParams.id     = PSP_VPFE_CCDC;
    vpfeChannelParams.params = (PSP_VPFECcdcConfigParams*)&vpfeCcdcConfigParams;
    hGioVpfeCcdc = FVID_create("/VPFE0",IOM_INOUT,NULL,&vpfeChannelParams,NULL);
    status = (hGioVpfeCcdc == NULL ? -1 : 0);
  }

  /* create video output channel, plane 0 */
  if (status == 0) {
    PSP_VPBEChannelParams vpbeChannelParams;
    vpbeChannelParams.id     = PSP_VPBE_VIDEO_0;
    vpbeChannelParams.params = (PSP_VPBEOsdConfigParams*)&vpbeOsdConfigParams;
    hGioVpbeVid0 = FVID_create("/VPBE0",IOM_INOUT,NULL,&vpbeChannelParams,NULL);
    status = (hGioVpbeVid0 == NULL ? -1 : 0);
  }

  /* create video output channel, venc */
  if (status == 0) {
    PSP_VPBEChannelParams vpbeChannelParams;
    vpbeChannelParams.id     = PSP_VPBE_VENC;
    vpbeChannelParams.params = (PSP_VPBEVencConfigParams *)&vpbeVencConfigParams;
    hGioVpbeVenc = FVID_create("/VPBE0",IOM_INOUT,NULL,&vpbeChannelParams,NULL);
    status = (hGioVpbeVenc == NULL ? -1 : 0);
  }

  /* configure the TVP5146 video decoder */
  if (status == 0) {
    result = FVID_control(hGioVpfeCcdc, VPFE_ExtVD_BASE+PSP_VPSS_EXT_VIDEO_DECODER_CONFIG, &tvp5146Params);
    status = (result == IOM_COMPLETED ? 0 : -1);
  }

  /* allocate some frame buffers */
  if (status == 0) {
    for (i=0; i<FRAME_BUFF_CNT && status == 0; i++) {
      result = FVID_allocBuffer(hGioVpfeCcdc, &frameBuffTable[i]);
      status = (result == IOM_COMPLETED && frameBuffTable[i] != NULL ? 0 : -1);
    }
  }

  /* prime up the video capture channel */
  if (status == 0) {
    FVID_queue(hGioVpfeCcdc, frameBuffTable[0]);
    FVID_queue(hGioVpfeCcdc, frameBuffTable[1]);
    FVID_queue(hGioVpfeCcdc, frameBuffTable[2]);
  }

  /* prime up the video display channel */
  if (status == 0) {
    FVID_queue(hGioVpbeVid0, frameBuffTable[3]);
    FVID_queue(hGioVpbeVid0, frameBuffTable[4]);
    FVID_queue(hGioVpbeVid0, frameBuffTable[5]);
  }

  /* grab first buffer from input queue */
  if (status == 0) {
    FVID_dequeue(hGioVpfeCcdc, &frameBuffPtr);
  }

  memset(CbOutputBuffer,0x80,sizeof(uint8)*IMG_WIDTH*IMG_HEIGHT>>1);
  memset(CrOutputBuffer,0x80,sizeof(uint8)*IMG_WIDTH*IMG_HEIGHT>>1);

  /* loop forever performing video capture and display */
  while ( 1 ) {

    /* grab a fresh video input frame */
    FVID_exchange(hGioVpfeCcdc, &frameBuffPtr);

    if(++frameCounter>25) {
		/* extract Y buffer from frame */
		extractY((uint32*)frameBuffPtr->frame.frameBufferPtr,YBufferIn,IMG_WIDTH, IMG_HEIGHT);

		// process YBufferIn
		dataProcessing(YBufferIn,YBufferOut,CbOutputBuffer,CrOutputBuffer,IMG_HEIGHT,IMG_WIDTH);
	
		/* merge the Y, Cb and Cr buffers to frame buffer */
		y_cb_cr_to_ycbcr(YBufferOut,CbOutputBuffer,CrOutputBuffer,(uint8*)frameBuffPtr->frame.frameBufferPtr,IMG_WIDTH,IMG_HEIGHT);
    }

    /* display the video frame */
    FVID_exchange(hGioVpbeVid0, &frameBuffPtr);

  }

}

/*
 * ======== read_JP1 ========
 * Read the PAL/NTSC jumper.
 *
 * Retry, as I2C sometimes fails:
 */
static int read_JP1(void) {
    int32 jp1 = -1;

    while (jp1 == -1) {
      jp1 = EVMDM6437_DIP_get(JP1_JUMPER); 
      TSK_sleep(1);
    }
    return(jp1);
}       





