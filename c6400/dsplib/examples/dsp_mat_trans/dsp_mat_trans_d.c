/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      DSP_mat_trans_d.c -- Example file for DSP_mat_trans                 */
/*                                                                          */
/*  USAGE                                                                   */
/*      This file contains code for demonstrating the C64x DSPLIB           */
/*      DSP_mat_trans function. All inputs to the function contain random   */
/*      data. The assembly version of DSP_mat_trans is called and the       */
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
#include "DSP_mat_trans.h"    

/* Header file for the C function */
void DSP_mat_trans_c(const short * x, short row, short col, short * r);


/* ======================================================================== */
/*  Constant dataset.                                                       */
/* ======================================================================== */
#define C    (64)
#define R    (16)
#define RC   (1024)


/* ======================================================================== */
/*  Initialize arrays with random test data.                                */
/* ======================================================================== */
int     test = 0;
const short  x[RC] = 
{
     0x79F0,  0x3B5B, -0x5EDA, -0x3EBB, -0x2FB7,  0x6F4D,  0x1EEF,  0x3E8C,
    -0x36EB, -0x6EE4, -0x02A5,  0x15E5, -0x6B68, -0x7098, -0x71E5, -0x5271,
    -0x21E2, -0x1361, -0x4FC8, -0x597D, -0x51D0, -0x4331,  0x2D70, -0x0E2A,
    -0x0145,  0x2F77, -0x1412, -0x56C5,  0x309F,  0x6658, -0x3055,  0x55BC,
    -0x6BC7,  0x5B03,  0x2FCF,  0x45CF, -0x221D, -0x62FF,  0x7374, -0x13E5,
     0x6669,  0x56A1,  0x0318, -0x6E75,  0x44A8, -0x270C, -0x15FA,  0x6F79,
     0x55E1,  0x2110,  0x0444, -0x0176,  0x046D, -0x0BCD,  0x4BA1, -0x738F,
     0x4412, -0x5FFB,  0x0543,  0x3DA6,  0x6B41,  0x6264, -0x0856,  0x64B8,
     0x4EB9,  0x163A,  0x5E8B,  0x4D5F,  0x6678, -0x6CF7, -0x2E05,  0x13A0,
    -0x570B, -0x3252,  0x40F4,  0x1B5F, -0x0288,  0x014A, -0x122B, -0x36DB,
     0x252A,  0x339C, -0x29D2,  0x0C63,  0x5955,  0x36CF, -0x6346,  0x631D,
    -0x5894, -0x204B,  0x3401, -0x2B59, -0x3692,  0x65BF, -0x2D4E,  0x7361,
     0x53E1, -0x6789, -0x4B5B,  0x4730,  0x0BA9, -0x3741,  0x19C2,  0x5474,
    -0x102B,  0x5624,  0x0C3D,  0x1FC0,  0x7C38,  0x31FA, -0x1334,  0x4446,
     0x39DD, -0x2C56, -0x6424,  0x4B7E, -0x22EC, -0x7864,  0x1BA0,  0x70AF,
    -0x318E, -0x35EB, -0x325D,  0x08CD, -0x4296, -0x0632,  0x1AE0, -0x6BB5,
    -0x5C21, -0x678A, -0x07ED, -0x1FB4, -0x4FB1, -0x22A4,  0x5632,  0x0E55,
    -0x1CBF,  0x2507,  0x3D3F, -0x56B7, -0x1307, -0x07C6, -0x52BD,  0x4D6D,
    -0x6E75,  0x7737, -0x089C, -0x2763,  0x008C,  0x01CF, -0x3F85,  0x0A16,
     0x1340,  0x49B1, -0x1EC3, -0x51CC,  0x045B, -0x4C53,  0x707F,  0x1D25,
    -0x7B5C,  0x59EF, -0x1762,  0x6950, -0x5DEA, -0x4794,  0x2B3D, -0x6BB7,
     0x7A8F, -0x1E32, -0x6F01,  0x25F3,  0x18FA, -0x0439, -0x5814,  0x554F,
    -0x60E9, -0x3E3D,  0x453D, -0x125D,  0x7F7E, -0x3B39, -0x74B7, -0x283E,
     0x7561, -0x5A5C, -0x77F3,  0x773C,  0x5A79,  0x05A4,  0x4A4B,  0x541B,
     0x60D1,  0x1DD1, -0x3649,  0x0C5F, -0x502B, -0x1AB2, -0x5A3C,  0x75B3,
    -0x013E,  0x5A51, -0x07BF, -0x7E79, -0x42AD, -0x73F5, -0x4743, -0x5CA4,
    -0x3973, -0x5905,  0x495E,  0x63CA, -0x4E4D,  0x6B4D,  0x3DAF,  0x0F8F,
    -0x1D75,  0x430A,  0x6498,  0x33D7, -0x772B,  0x3610, -0x5E67,  0x0AD1,
     0x1211, -0x687A,  0x4788,  0x33C4, -0x3BDF, -0x3DA8, -0x1383,  0x5D2D,
    -0x52E4, -0x1F1C,  0x6E62,  0x2CE0,  0x777C, -0x5510, -0x0F0B,  0x583E,
    -0x6C67, -0x3C4B,  0x65D2, -0x5734, -0x736B, -0x7758,  0x2E8F, -0x6F5B,
     0x3FAA,  0x2AD9, -0x2B20,  0x32D9,  0x4B38,  0x0F46, -0x161C, -0x5D88,
     0x1B53, -0x3448,  0x2FA2, -0x4645, -0x7C69, -0x0D03,  0x64D1, -0x0468,
     0x5F3F, -0x5AF2, -0x4E81,  0x7E74, -0x35DC, -0x121B, -0x2C39,  0x23AC,
     0x1330,  0x769E, -0x10C8, -0x3A8B, -0x1137, -0x4DF6, -0x3624,  0x3FE2,
    -0x2E4A, -0x0E61,  0x6028,  0x47DE, -0x5A62, -0x5C1F, -0x34CF,  0x1588,
     0x4879, -0x07E8,  0x77F4,  0x5BED,  0x535E, -0x6767, -0x58B5,  0x7DF0,
    -0x45AC, -0x3995,  0x7A76, -0x0951, -0x3614, -0x245F, -0x54D9,  0x241E,
    -0x1824,  0x2940,  0x16B6, -0x22DB, -0x61C2, -0x6B33,  0x3235,  0x3F30,
     0x5DCB,  0x78A7, -0x2441, -0x12C7, -0x043A, -0x34F5,  0x22DF,  0x568D,
     0x48E9, -0x124A,  0x255E, -0x19E8,  0x7864, -0x1DBA, -0x1008,  0x2455,
     0x73BB,  0x6633, -0x56D3, -0x1E68, -0x248E,  0x1D12,  0x5630, -0x7D23,
     0x7931,  0x5BC2, -0x1F1F, -0x5648, -0x75CC, -0x7BFA, -0x7748,  0x7A67,
    -0x54F1,  0x05FE, -0x4892,  0x0D70, -0x62A4, -0x3BC1, -0x3CB0, -0x4668,
    -0x587C,  0x5C51,  0x7F81, -0x57A1, -0x652D,  0x5050,  0x5E52,  0x5BD9,
     0x1EC2,  0x60E3, -0x1F4F, -0x1EBD,  0x1D3A,  0x2C08,  0x20B1,  0x36F6,
    -0x2010, -0x2610, -0x48F2, -0x7F98, -0x393E,  0x2DF3,  0x589B, -0x0FDE,
    -0x3F1D,  0x34E1,  0x0EEA, -0x1E3C,  0x2040,  0x7BF9, -0x790A, -0x4233,
    -0x4570, -0x5BCF,  0x1C40, -0x5931,  0x5341,  0x56B2, -0x53D7, -0x137A,
     0x0AED,  0x178C,  0x1FA5, -0x2C6C, -0x2214, -0x24EE,  0x1F61,  0x7D7D,
    -0x0BB5, -0x42FB,  0x139B,  0x570D, -0x3BB6, -0x4A4B, -0x56F9,  0x6B19,
     0x7AD3,  0x3F12, -0x1E27,  0x7F4C,  0x2261, -0x0125,  0x1541, -0x2F75,
    -0x01FF, -0x63F8,  0x4268,  0x0E8A,  0x3814, -0x4DCA, -0x43F4, -0x3FDD,
    -0x5AC4, -0x21B7, -0x3980, -0x6A36, -0x468F,  0x4F0D, -0x6CDC, -0x7B48,
     0x12DB, -0x613F, -0x4C59,  0x4758,  0x4A75, -0x081B,  0x37B4, -0x1390,
    -0x1821,  0x2789,  0x0FED, -0x7FED, -0x234B, -0x6A32, -0x0013,  0x7CB0,
     0x55B0, -0x36A9,  0x1918,  0x6921, -0x235C,  0x1E9E, -0x6949, -0x51CD,
    -0x07FF,  0x7655, -0x67E1,  0x3457, -0x2A9C, -0x2012, -0x33FF, -0x3A59,
     0x03B8,  0x753D, -0x1548,  0x0E6D, -0x5AE8,  0x3E7D,  0x49C0,  0x7E88,
    -0x0986,  0x2B13,  0x7A8B,  0x49CD,  0x1FC4,  0x0E92, -0x71CB, -0x7180,
    -0x3B05, -0x662C,  0x3A4A,  0x13A1,  0x5295, -0x3E98,  0x41F9, -0x2048,
    -0x5B41,  0x2950,  0x2D21, -0x1274, -0x51A4,  0x5C3E,  0x182F, -0x75A2,
    -0x66C2, -0x39F9, -0x742B,  0x1B77, -0x6361,  0x0E94, -0x47B0, -0x3131,
    -0x111D,  0x2056, -0x177E,  0x7691,  0x2353, -0x5DBF, -0x15A1, -0x585E,
     0x094E,  0x135C,  0x0A1C,  0x74BF, -0x5219, -0x195A,  0x0BA9,  0x442A,
    -0x0973, -0x05E6,  0x5CA2, -0x5D77,  0x1394,  0x46CB,  0x2EC7,  0x30CC,
     0x72F8,  0x7C04, -0x256E, -0x705F, -0x6398,  0x7570, -0x7196,  0x1504,
     0x363F,  0x20B2,  0x165C, -0x1DDB, -0x4559,  0x1252, -0x06CE, -0x3F42,
    -0x50F1,  0x7EE2,  0x713E,  0x70C3, -0x06BC, -0x7794, -0x51F4, -0x69D0,
    -0x7F77,  0x70E5,  0x17B4,  0x1EFF, -0x549D,  0x630A, -0x5568, -0x6DB0,
     0x7338, -0x076D,  0x238C, -0x3600, -0x6161,  0x6371, -0x2A68, -0x267D,
    -0x1B08,  0x0F8E,  0x7DB4, -0x25A7,  0x5ED8,  0x6482, -0x7839,  0x2238,
     0x087F, -0x7A14,  0x6318, -0x566F,  0x3A02,  0x1D50, -0x22B6,  0x709A,
    -0x3B31,  0x7BD7,  0x3E3B, -0x3BC0, -0x55E7,  0x49B9,  0x0097,  0x25B5,
     0x5FD4, -0x1684,  0x58D2, -0x0F1D,  0x5809, -0x72B9,  0x04C1, -0x06FA,
    -0x5E10, -0x7F78,  0x5425, -0x1A1D, -0x6634, -0x35C2,  0x313B,  0x4986,
    -0x7107,  0x4C0B, -0x41E2, -0x0E9A, -0x259F,  0x2881, -0x49A3, -0x0CF5,
     0x6A78, -0x0C17, -0x1970,  0x1F15,  0x12A9,  0x432A, -0x7C8A,  0x4809,
     0x2E8C,  0x491B,  0x4BC4, -0x08E3,  0x1755,  0x570A, -0x692F, -0x7197,
     0x54F2,  0x680A,  0x3D47, -0x4EA7,  0x4F3E,  0x38FE, -0x6638,  0x3EA5,
     0x411F,  0x0DE3, -0x042A, -0x773E,  0x2281,  0x22F4, -0x6302, -0x7F0E,
    -0x7BD8,  0x2A54, -0x688B, -0x3014,  0x20B5,  0x2FC9, -0x1F27,  0x46CA,
    -0x7C62,  0x2558, -0x001D, -0x5151, -0x17A8,  0x4B9A,  0x4094,  0x17E2,
     0x1CF5,  0x38C4,  0x2F3E, -0x5754,  0x6464,  0x1A10,  0x5DB6, -0x22D7,
     0x5F6D, -0x63D4,  0x3B12, -0x6805,  0x2893,  0x1C25, -0x11E4, -0x01D2,
     0x60A0,  0x1B33, -0x0122,  0x59CA,  0x4C6D, -0x46A8, -0x5057, -0x7B05,
    -0x2B03, -0x6D22, -0x78F2,  0x4D64,  0x72CB, -0x6B20,  0x515E,  0x7F44,
     0x18A1, -0x3E76,  0x135C, -0x624E,  0x3AAE, -0x449F,  0x50B6, -0x6B93,
     0x17BD,  0x7242,  0x21D1,  0x6C03, -0x4643, -0x4C16,  0x2A4D,  0x35FC,
     0x61D9, -0x483C, -0x6FF7,  0x558D,  0x66CC, -0x7DA3,  0x7F12,  0x6290,
    -0x414A,  0x631D,  0x00B5, -0x0022,  0x1403,  0x075A, -0x4717,  0x6EAE,
     0x7C9F,  0x7E1A, -0x6DB5,  0x1C43, -0x6FE4, -0x3049,  0x7D19,  0x045D,
    -0x59D8, -0x5548,  0x0461, -0x0729, -0x36BF, -0x341E, -0x0A3F, -0x4562,
     0x6E2B, -0x3E35, -0x5698, -0x7807,  0x5CAA, -0x49BD, -0x186C,  0x54B4,
     0x0AF9,  0x0E8C,  0x1D78, -0x0F77, -0x43E8,  0x2D84,  0x2700,  0x6849,
     0x6E38, -0x50BE, -0x62A9, -0x22A8,  0x41AE, -0x5426,  0x6C63,  0x255D,
     0x5BD8,  0x7868, -0x06E0,  0x0F19, -0x2BAF, -0x6D10, -0x7CC6, -0x18C6,
     0x69FB, -0x375E, -0x6228,  0x4A1B,  0x0A27, -0x7E46,  0x20C2, -0x5F8C,
    -0x26B0,  0x58AF, -0x3645,  0x5F00, -0x03EC, -0x1B72, -0x19A2,  0x4871,
     0x37B1, -0x2F0F,  0x273B, -0x233C,  0x596D, -0x5DC2,  0x2DD0,  0x4ED0,
     0x0C42, -0x646C,  0x2C7D, -0x1BA3, -0x3AD7,  0x4F56, -0x1682,  0x6B7F,
     0x2F71, -0x3F98,  0x3AB0, -0x1797, -0x480C, -0x0C43, -0x5DE9,  0x5240,
    -0x7E86,  0x2A6B,  0x5DA8,  0x2C5B, -0x2275, -0x090F, -0x3CA8,  0x7FEB,
     0x3EFC, -0x1658, -0x67FB, -0x7A11,  0x0E8E,  0x0E99, -0x59DD, -0x4A47,
     0x7E49,  0x4683,  0x16A1,  0x4CA0, -0x2A2D,  0x74D8, -0x302F, -0x1881,
    -0x4E45, -0x5A2D,  0x451C,  0x4E3E, -0x5613, -0x2E24,  0x4776, -0x1534,
    -0x6B8D,  0x3012, -0x12DB,  0x68F0, -0x10C8,  0x4C4D, -0x593A, -0x5073,
     0x512A,  0x36D1,  0x6E8F, -0x6ED9,  0x102C,  0x7CEE, -0x5496, -0x2404,
     0x2EC5,  0x0329, -0x02B2,  0x4067, -0x12CB, -0x7C81,  0x10ED,  0x1C4D,
    -0x73AB, -0x38CF,  0x6B48, -0x5EE4,  0x5597, -0x3DD1,  0x6EC5,  0x28CF,
    -0x67DC, -0x5E40,  0x2938,  0x69F9,  0x160F,  0x1D27,  0x56A7,  0x0EE9,
    -0x49D4, -0x5980, -0x6601, -0x090E, -0x47E5, -0x716C,  0x5517,  0x6BB6,
     0x12FB,  0x104C,  0x556B,  0x1F17, -0x0537,  0x2D6E, -0x4E06,  0x2CD1,
    -0x4927,  0x2501,  0x22E2,  0x373A, -0x5416,  0x7487, -0x4FD9, -0x61E4,
    -0x15C3, -0x368D,  0x535F, -0x2251, -0x6FBB, -0x540B, -0x2DEF,  0x226F,
    -0x6EAB, -0x43EE,  0x0AE1, -0x7C02, -0x67A9, -0x0955,  0x20FF,  0x0E3C,
    -0x4186, -0x4E45,  0x6DC2,  0x2EEB, -0x3469,  0x4D45, -0x33F9,  0x665C,
    -0x4621,  0x65BB,  0x0564,  0x6CE4,  0x05FB,  0x204D, -0x789F,  0x639A,
     0x4BB2, -0x3190, -0x39AC,  0x5B4D, -0x402A,  0x0B02, -0x242E,  0x4697,
     0x112D,  0x3B31, -0x07B0, -0x69F4, -0x1D76,  0x258B,  0x54B9, -0x55D4,
     0x7DDE, -0x0105, -0x098B, -0x1ADA, -0x1B1C,  0x18A6, -0x2D78,  0x307E,
    -0x07A2, -0x1DC7,  0x22BA, -0x22DF,  0x2D05, -0x0466, -0x742E,  0x7C99,
    -0x6197,  0x266B, -0x6234, -0x0181,  0x2A00,  0x6DA8,  0x2068, -0x7787,
    -0x12F3,  0x38C7,  0x56A9,  0x7677,  0x3029,  0x209F,  0x25DC, -0x6BDE,
    -0x2BFD, -0x51FD, -0x2366,  0x6AE5, -0x30E4,  0x2944, -0x3DAF,  0x7190,
     0x7F1A,  0x5845, -0x4151,  0x7E2F,  0x033D,  0x0D04, -0x5569,  0x7D05,
     0x5390,  0x4BED, -0x1E67,  0x73C3,  0x3F3C,  0x7A59, -0x7160,  0x536F,
    -0x5408, -0x04B6,  0x075B, -0x3243,  0x25AD, -0x04BA,  0x29A2,  0x3388
};



short  r_asm[RC];
short  r_c[RC];

int main()
{   

/* ======================================================================== */
/*  Call hand-coded assembly version (located in DSP64x.lib library         */ 
/*  archive - see Project -> Build Options -> Linker -> Include Libraries)  */
/* ======================================================================== */   
    DSP_mat_trans(x, R, C, r_asm);
    
/* ======================================================================== */
/*  Call natural-C version                                                  */
/* ======================================================================== */
    DSP_mat_trans_c(x, R, C, r_c);

/* ======================================================================== */
/*  Compare outputs using mem_compare() in support.c.  If different,        */
/*  mem_compare() displays location of failures.                            */
/* ======================================================================== */
    test = mem_compare(r_asm, "r_asm", r_c, "r_c", sizeof(r_c));
    if (test == 0) 
    {
      printf("r_asm vs. r_c");
      printf("\nVerification successful.\n");
    }

}

/* ======================================================================== */
/*  End of file:  dsp_mat_trans_d.c                                         */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2003 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
