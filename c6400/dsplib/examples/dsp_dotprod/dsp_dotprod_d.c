/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      DSP_dotprod_d.c -- Example file for DSP_dotprod                     */
/*                                                                          */
/*  USAGE                                                                   */
/*      This file contains code for demonstrating the C64x DSPLIB           */
/*      DSP_dotprod function. All inputs to the function contain random     */
/*      data. The assembly version of DSP_dotprod is called and the         */
/*      output is compared with the reference C code using mem_compare()    */
/*      in support.c.                                                       */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2003 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
    
#include <stdio.h> 
#include <stdlib.h>

/* Header file for the memory compare function */
int mem_compare(const void *ptr1, const char *name1, 
                const void *ptr2, const char *name2, int len);

/* Header file for the DSPLIB function */
#include "DSP_dotprod.h"    

/* Header file for the C function */
int DSP_dotprod_c(const short * x, const short * y, int nx);

/* ======================================================================== */
/*  DSPLIB function-specific alignments. Refer to the                       */
/*  TMS320C64x DSP Library Programmer's Reference for details.              */
/* ======================================================================== */
#pragma DATA_ALIGN(x, 8);
#pragma DATA_ALIGN(y, 8);

/* ======================================================================== */
/*  Constant dataset.                                                       */
/* ======================================================================== */
#define NX   (40)


/* ======================================================================== */
/*  Initialize arrays with random test data.                                */
/* ======================================================================== */
int     test = 0;
const short  x[NX] = 
{
    -0x7AD0, -0x3490, -0x2458, -0x0D7E, -0x4C9C, -0x7452, -0x0011,  0x7837,
    -0x4E91,  0x0DDB,  0x78C9, -0x69B4, -0x36B5,  0x1302, -0x4C3C, -0x16EC,
    -0x51EE,  0x354A, -0x0D18,  0x28C6,  0x6B29, -0x0A54,  0x6509, -0x2116,
     0x4AA2, -0x0CE3, -0x57A0, -0x66A2, -0x612D, -0x6A7A, -0x3E36,  0x53D8,
    -0x7DA9,  0x677A, -0x30F1, -0x2D1E,  0x1DF1, -0x5517,  0x4DB5, -0x0998
};

const short  y[NX] = 
{
     0x41EF, -0x0DCB,  0x789F,  0x5257,  0x11CB, -0x4B93,  0x6BE9,  0x4CD2,
    -0x31DD, -0x3BE6,  0x2C99,  0x797B,  0x2E46, -0x175D, -0x7A3C, -0x7F3D,
    -0x49D3,  0x32A7, -0x325C, -0x6BD0,  0x6BAA, -0x68CD, -0x0E5A, -0x5B04,
     0x34EC,  0x098C, -0x062E,  0x481B,  0x51B2,  0x0693,  0x5727,  0x39AF,
    -0x6916,  0x408E, -0x5F00, -0x27DA,  0x07E4,  0x2F9F, -0x35D9, -0x735E
};



/* ======================================================================== */
/*  Variables to catch return values from function.                         */
/* ======================================================================== */
int ret_val_asm = 0;
int ret_val_c = 0;

int main()
{   

/* ======================================================================== */
/*  Call hand-coded assembly version (located in DSP64x.lib library         */ 
/*  archive - see Project -> Build Options -> Linker -> Include Libraries)  */
/* ======================================================================== */   
    ret_val_asm = DSP_dotprod(x, y, NX);
    
/* ======================================================================== */
/*  Call natural-C version                                                  */
/* ======================================================================== */
    ret_val_c = DSP_dotprod_c(x, y, NX);

/* ======================================================================== */
/*  Compare outputs using mem_compare() in support.c.  If different,        */
/*  mem_compare() displays location of failures.                            */
/* ======================================================================== */

      printf("ret_val_asm vs. ret_val_c");
    if ((ret_val_c == ret_val_asm)) 
    {
      printf("\nVerification successful.\n");
    } else 
    {
      printf("\nVerification failure.\n");
    }

}

/* ======================================================================== */
/*  End of file:  dsp_dotprod_d.c                                           */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2003 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
