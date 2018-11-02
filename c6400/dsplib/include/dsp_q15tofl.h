/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  DSPLIB  DSP Signal Processing Library                                   */
/*                                                                          */
/*      Release:        Revision 1.00a                                      */
/*      CVS Revision:   1.6     Sun Sep 29 03:32:28 2002 (UTC)              */
/*      Snapshot date:  03-Mar-2006                                         */
/*                                                                          */
/*  This library contains proprietary intellectual property of Texas        */
/*  Instruments, Inc.  The library and its source code are protected by     */
/*  various copyrights, and portions may also be protected by patents or    */
/*  other legal protections.                                                */
/*                                                                          */
/*  This software is licensed for use with Texas Instruments TMS320         */
/*  family DSPs.  This license was provided to you prior to installing      */
/*  the software.  You may review this license by consulting the file       */
/*  TI_license.PDF which accompanies the files in this library.             */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2006 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
/* ======================================================================== */
/*  Assembler compatibility shim for assembling 4.30 and later code on      */
/*  tools prior to 4.30.                                                    */
/* ======================================================================== */
/* ======================================================================== */
/*  End of assembler compatibility shim.                                    */
/* ======================================================================== */
/* ======================================================================== */
/*                                                                          */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      DSP_q15tofl -- Q.15 to IEEE float conversion                        */
/*                                                                          */
/*  REVISION DATE                                                           */
/*      17-Jul-2001                                                         */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine is C-callable and can be called as:                    */
/*                                                                          */
/*          void DSP_q15tofl (short *x, float *r, int nx);                  */
/*                                                                          */
/*          x[nx]  ---  Pointer to Q15 input vector of size nx              */
/*          r[nx]  ---  Pointer to floating-point output data vector        */
/*                      of size nx containing the floating-point equivalent */
/*                      of vector input                                     */
/*          nx     ---  length of input and output data vectors             */
/*                                                                          */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      Converts the Q15 stored in vector input to IEEE floating point      */
/*      numbers stored in vector output.                                    */
/*                                                                          */
/*      void DSP_q15tofl (short *x, float *r, int nx)                       */
/*      {                                                                   */
/*       int i;                                                             */
/*                                                                          */
/*       for (i=0;i<nx;i++)                                                 */
/*            r[i]=(float)x[i]/0x8000;                                      */
/*      }                                                                   */
/*                                                                          */
/*      The above C code is a general implementation without                */
/*      restrictions.  The assembly code may have some restrictions, as     */
/*      noted below.                                                        */
/*                                                                          */
/*  TECHNIQUES                                                              */
/*      unrolled loop 2x                                                    */
/*      split live-too-longs B_input_1 and B_input_2                        */
/*      collapsed 2 prolog and epilog stages                                */
/*                                                                          */
/*  ASSUMPTIONS                                                             */
/*      nx >=2 and multiple of 2                                            */
/*                                                                          */
/*  MEMORY NOTE                                                             */
/*      no bank conflicts occur ever                                        */
/*                                                                          */
/*  NOTES                                                                   */
/*      this routine is interrupt-tolerant but not interruptible            */
/*      this routine is ENDIAN NEUTRAL                                      */
/*                                                                          */
/*  CYCLES                                                                  */
/*      14 + 2 * nx                                                         */
/*                                                                          */
/*  CODESIZE                                                                */
/*      184 bytes                                                           */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2006 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
#ifndef DSP_Q15TOFL_H_
#define DSP_Q15TOFL_H_ 1

void DSP_q15tofl (short *x, float *r, int nx);

#endif
/* ======================================================================== */
/*  End of file:  dsp_q15tofl.h                                             */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2006 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
