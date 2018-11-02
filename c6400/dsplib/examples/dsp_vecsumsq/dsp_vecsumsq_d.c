/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      DSP_vecsumsq_d.c -- Example file for DSP_vecsumsq                   */
/*                                                                          */
/*  USAGE                                                                   */
/*      This file contains code for demonstrating the C64x DSPLIB           */
/*      DSP_vecsumsq function. All inputs to the function contain random    */
/*      data. The assembly version of DSP_vecsumsq is called and the        */
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
#include "DSP_vecsumsq.h"    

/* Header file for the C function */
int DSP_vecsumsq_c(const short * x, int nx);


/* ======================================================================== */
/*  Constant dataset.                                                       */
/* ======================================================================== */
#define N    (256)


/* ======================================================================== */
/*  Initialize arrays with random test data.                                */
/* ======================================================================== */
int     test = 0;
const short  x[N] = 
{
     0x4DCE, -0x7BB1,  0x376B,  0x3B05,  0x374D, -0x325F, -0x0467, -0x280D,
    -0x6661,  0x3383,  0x506F,  0x7E5A, -0x38E4,  0x6196,  0x2FD9, -0x3751,
    -0x1854,  0x4DE8, -0x01CF,  0x46B5, -0x27E5, -0x61E2,  0x3F33,  0x073F,
     0x579E, -0x3D37,  0x6C79, -0x7C9A,  0x018F,  0x1DEB, -0x1F0F, -0x545F,
    -0x2D3D, -0x3BC2, -0x6E27,  0x0D75,  0x6A06,  0x3E21,  0x27DA,  0x2262,
     0x7088,  0x781E, -0x754C,  0x4231,  0x790D, -0x4287,  0x2EFA, -0x6B2B,
     0x201A, -0x0F1F, -0x0064, -0x241B,  0x628E,  0x4AC4,  0x4501,  0x7953,
     0x4585,  0x5F70,  0x694F, -0x0B0E, -0x2A80,  0x1163,  0x7600,  0x19C2,
     0x5507, -0x2FC8,  0x3A4D,  0x04AC, -0x3EAF,  0x35CF, -0x08D8, -0x1E8F,
    -0x1650, -0x3EE3, -0x2C09,  0x2185,  0x522A, -0x4C79, -0x2324, -0x05D5,
     0x33A7, -0x0804, -0x03EE, -0x129B,  0x4FC4,  0x01CB, -0x218E,  0x2E39,
     0x16A3, -0x03E8, -0x033A, -0x67B9,  0x2EF6, -0x09CF,  0x4122, -0x0BE4,
    -0x2ED8,  0x5977, -0x3680, -0x6992,  0x22AB,  0x480C,  0x00DF,  0x4976,
    -0x7CD7, -0x746F, -0x3F4E,  0x080A, -0x1EE6, -0x1777,  0x2F5A,  0x52EC,
     0x748C,  0x4CBC,  0x57DF,  0x7349, -0x4D86,  0x1D0A,  0x1402, -0x53A0,
    -0x572E,  0x4ED4, -0x6F85,  0x0162, -0x169D,  0x0CC8, -0x0979,  0x1365,
    -0x3520,  0x072A, -0x3B38,  0x627F, -0x13C9, -0x5635, -0x488D,  0x3C62,
     0x3495, -0x67A4,  0x174C,  0x74E0,  0x56D5, -0x286B,  0x4256, -0x3798,
     0x7E1D,  0x10E8,  0x4870, -0x06DD,  0x0896, -0x7BB7, -0x64A3, -0x3B81,
    -0x4433, -0x7C98, -0x056B, -0x1004,  0x618B,  0x0CFF, -0x1D87, -0x7B5D,
     0x391E, -0x7ED4,  0x5B3C, -0x5E9B,  0x105C,  0x3E00, -0x2A2A, -0x7F68,
     0x6F21, -0x717B,  0x2ED6,  0x33B7, -0x4F12, -0x7DFF, -0x7303,  0x7D3E,
    -0x738D,  0x007B,  0x7884,  0x17D9,  0x514B, -0x74D9, -0x1A09, -0x7703,
    -0x1BD0, -0x652A, -0x37AA, -0x14BB,  0x1CB4, -0x0474, -0x2A59,  0x3585,
     0x68EF, -0x25C1, -0x0A70,  0x515F,  0x381A,  0x0326,  0x2CD6,  0x090E,
     0x2D18, -0x53DE,  0x480F, -0x7BC2,  0x0F46,  0x067B, -0x5D54,  0x57FC,
    -0x03C4, -0x65B1, -0x5FB7, -0x0F2A,  0x5042,  0x765E, -0x2D27, -0x7222,
    -0x2AD0,  0x1ED0, -0x40C8, -0x70D6, -0x2191,  0x25EA, -0x2CB9, -0x719D,
     0x43D9,  0x0750,  0x0D19, -0x5D01,  0x56A2,  0x3857,  0x5E05, -0x29E5,
    -0x768A,  0x1F75,  0x593E,  0x1965, -0x5B77, -0x5E20, -0x0D02,  0x0896,
    -0x7BC4,  0x7611, -0x330E,  0x3238, -0x61C5, -0x0D2A, -0x79C4, -0x045D,
     0x6BAB, -0x516D,  0x141F, -0x1A51, -0x6C8D, -0x37C7,  0x0CA5,  0x7A52
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
    ret_val_asm = DSP_vecsumsq(x, N);
    
/* ======================================================================== */
/*  Call natural-C version                                                  */
/* ======================================================================== */
    ret_val_c = DSP_vecsumsq_c(x, N);

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
/*  End of file:  dsp_vecsumsq_d.c                                          */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2003 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */