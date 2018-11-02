/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      tw_fft16x32                                                         */
/*                                                                          */
/*  USAGE                                                                   */
/*      This is a stand-alone program intended to generate twiddle-factor   */
/*      arrays for the DSP_fft16x32 and DSP_ifft16x32 FFT library routine.  */
/*      It is called as follows:                                            */
/*                                                                          */
/*          tw_fft16x32 [-s scale] N > outputfile.c                         */
/*                                                                          */
/*      The argument 'N' specifies the size of the FFT.  This value         */
/*      must be a power of 2.  The switch '-s scale' allows selecting       */
/*      a different scale factor for the coefficients.  The default         */
/*      scale factor is 32767.5.                                            */
/*                                                                          */
/*      This program will generate the twiddle factor array 'w' and         */
/*      output the result to the display.  Redirect the output to           */
/*      a file as shown above.                                              */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      This program contains the twiddle-factor generation routine         */
/*      that is described within the source code for the DSPLIB FFT         */
/*      functions DSP_fft16x32 and DSP_ifft16x32.  This code may not        */
/*      produce an appropriate twiddle-factor array for the other DSPLIB    */
/*      FFT functions.                                                      */
/*                                                                          */
/*      Please consult the specific FFT that you are using for details.     */
/*                                                                          */
/*      The final twiddle-factor array generated by the routine will        */
/*      be 2 * N elements long.                                             */
/*                                                                          */
/*  NOTES                                                                   */
/*      The code below may be adapted to run directly on the target,        */
/*      rather than running as a separate program running off-line.         */
/*      Such adaptation is not recommended for time-critical applications.  */
/*      To adapt this program, remove the 'usage' and 'main' functions,     */
/*      and call 'gen_twiddle' directly.                                    */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2001 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef PI
# ifdef M_PI
#  define PI M_PI
# else
#  define PI 3.14159265358979323846
# endif
#endif

/* ======================================================================== */
/*  D2S -- Truncate a 'double' to a 'short', with clamping.                 */
/* ======================================================================== */
static short d2s(double d)
{
    if (d >=  32767.0) return  32767;
    if (d <= -32768.0) return -32768;
    return (short)d;
}

/* ======================================================================== */
/*  GEN_TWIDDLE -- Generate twiddle factors for TI's custom FFTs.           */
/*                                                                          */
/*  USAGE                                                                   */
/*      This routine is called as follows:                                  */
/*                                                                          */
/*          int gen_twiddle(short *w, int n, double scale)                  */
/*                                                                          */
/*          short  *w     Pointer to twiddle-factor array                   */
/*          int    n      Size of FFT                                       */
/*          double scale  Scale factor to apply to values.                  */
/*                                                                          */
/*      The routine will generate the twiddle-factors directly into the     */
/*      array you specify.  The array needs to be approximately 2*N         */
/*      elements long.  (The actual size, which is slightly smaller, is     */
/*      returned by the function.)                                          */
/* ======================================================================== */
int gen_twiddle(short *w, int n, double scale)
{
    int i, j, k;

    for (j = 1, k = 0; j < n >> 2; j = j << 2)
    {
        for (i = 0; i < n >> 2; i += j)
        {
            w[k +  5] = d2s(scale * cos(6.0 * PI * i / n));
            w[k +  4] = d2s(scale * sin(6.0 * PI * i / n));

            w[k +  3] = d2s(scale * cos(4.0 * PI * i / n));
            w[k +  2] = d2s(scale * sin(4.0 * PI * i / n));

            w[k +  1] = d2s(scale * cos(2.0 * PI * i / n));
            w[k +  0] = d2s(scale * sin(2.0 * PI * i / n));

            k += 6;
        }
    }

    return k;
}

/* ======================================================================== */
/*  USAGE -- Print usage information and optionally an error message.       */
/* ======================================================================== */
void usage(char *error)
{
    fprintf(stderr,
"                                                                        \n"
"USAGE                                                                   \n"
"    This is a stand-alone program intended to generate twiddle-factor   \n"
"    arrays for the DSP_fft16x32 and DSP_ifft16x32 FFT library routine.  \n"
"    It is called as follows:                                            \n"
"                                                                        \n"
"        tw_fft16x32 [-s scale] N > outputfile.c                         \n"
"                                                                        \n"
"    The argument 'N' specifies the size of the FFT.  This value         \n"
"    must be a power of 2.  The switch '-s scale' allows selecting       \n"
"    a different scale factor for the coefficients.  The default         \n"
"    scale factor is 32767.5.                                            \n"
"                                                                        \n"
"    This program will generate the twiddle factor array 'w' and         \n"
"    output the result to the display.  Redirect the output to           \n"
"    a file as shown above.                                              \n"
"                                                                        \n");

    if (error)
        fprintf(stderr, "ERROR:  %s\n", error);

    exit(1);
}


/* ======================================================================== */
/*  MAIN -- Where the action happens.                                       */
/* ======================================================================== */
int main(int argc, char *argv[])
{
    int i, n = -1, size;
    short *w;
    double scale = 32767.5;
    char *s;
    char buf[80];

    /* -------------------------------------------------------------------- */
    /*  Parse the arguments.                                                */
    /* -------------------------------------------------------------------- */
    if (argc < 2) { usage(NULL); }

    while (argc-->1)
    {
        if (**++argv == '-' || **argv == '/')
        {
            switch (argv[0][1])
            {
                case 's' : case 'S' :
                {
                    if (argv[0][2])
                    {
                        s = &argv[0][2];
                    } else
                    {
                        argc--;
                        s = *++argv;
                    }
                    if (!s || !*s || sscanf(s, "%lf", &scale) != 1)
                        usage("The -s switch requires a numeric argument.\n");

                    if (scale <= 0.0 || scale > 32767.6)
                        usage("Scale factor out of range.\n");

                    break;
                }

                default:
                {
                    sprintf(buf, "Unrecognized switch character: '%c'\n",
                            argv[0][1]);
                    usage(buf);
                    break;
                }
            }
        } else
        {
            if (!isdigit(argv[0][0]) || sscanf(argv[0], "%d", &n) != 1)
            {
                sprintf(buf, "Unrecognized argument:  %-.32s\n",
                        argv[0][0]);
                usage(buf);
            }

            if (n < 16 || n > 32768)
                usage("FFT size must be between 16 and 32768 points.");

            for (i = 2; i < 24; i++)
                if ((1 << i) == n) break;

            if (i >= 24)
            {
                usage("FFT size must be a power of 2\n");
                exit(1);
            }
        }
    }

    if (n == -1)
        usage("Must specify FFT size.");

    /* -------------------------------------------------------------------- */
    /*  Allocate memory for the FFT twiddle factors.                        */
    /* -------------------------------------------------------------------- */
    w = calloc(2 * sizeof(short), n);
    if (!w)
    {
        fprintf(stderr, "ERROR:  Unable to allocate memory for "
                        "twiddle factors\n");
        exit(1);
    }


    /* -------------------------------------------------------------------- */
    /*  Generate the twiddle-factor array.                                  */
    /* -------------------------------------------------------------------- */
    size = gen_twiddle(w, n, scale);


    /* -------------------------------------------------------------------- */
    /*  Print out the resulting twiddle factors.                            */
    /* -------------------------------------------------------------------- */
    printf(
"/* -------------------------------------------------------------------- */\n"
"/*  Automatically generated twiddle-factor array.                       */\n"
"/*      Number of points:    %-5d                                      */\n"
"/*      Scale factor:        %-20.9f                       */\n"
"/*      Appropriate FFTs:    DSP_fft16x32, DSP_ifft16x32                */\n"
"/*      Required alignment:  8 byte (double-word)                       */\n"
"/* -------------------------------------------------------------------- */\n",
        n, scale);

    printf("#pragma DATA_ALIGN(w, 8);\n");

    printf("const short w[2 * %d] =\n{", size / 2);
    for (i = 0; i < size; i++)
    {
        printf("%s%c0x%.4X",
               i == 0 ? "\n    " : (i & 7) == 0 ? ",\n    " : ", ",
               w[i] < 0 ? '-' : ' ', abs(w[i]));
    }
    printf("\n};\n");

    return 0;
}

