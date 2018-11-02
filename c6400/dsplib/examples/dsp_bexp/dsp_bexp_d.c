/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      DSP_bexp_d.c -- Example file for DSP_bexp                           */
/*                                                                          */
/*  USAGE                                                                   */
/*      This file contains code for demonstrating the C64x DSPLIB           */
/*      DSP_bexp function. All inputs to the function contain random        */
/*      data. The assembly version of DSP_bexp is called and the output     */
/*      is compared with the reference C code using mem_compare() in        */
/*      support.c.                                                          */
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
#include "DSP_bexp.h"    

/* Header file for the C function */
short DSP_bexp_c(const int * x, unsigned short nx);

/* ======================================================================== */
/*  DSPLIB function-specific alignments. Refer to the                       */
/*  TMS320C64x DSP Library Programmer's Reference for details.              */
/* ======================================================================== */
#pragma DATA_ALIGN(x, 8);

/* ======================================================================== */
/*  Constant dataset.                                                       */
/* ======================================================================== */
#define NX   (800)


/* ======================================================================== */
/*  Initialize arrays with random test data.                                */
/* ======================================================================== */
int     test = 0;
const int  x[NX] = 
{
    -0x370A40FD,  0x1E455D3A, -0x26E6080F,  0x268E4DCD,
    -0x2BF110AA,  0x033670EB,  0x4C9FF887, -0x109687FA,
    -0x62C0C0B1,  0x2BF4F347,  0x5AB71E1D, -0x448143D7,
    -0x5F972DCC,  0x23969302,  0x3FBA6511,  0x38C88708,
    -0x7A44013C,  0x06352184,  0x7A646352, -0x178C4888,
    -0x276EAB70,  0x036C3972, -0x7F09C615,  0x473D18CF,
     0x04B8AABF, -0x0D38EC78,  0x062DEAE1, -0x44401D94,
     0x56D6365D,  0x033A771D, -0x31C8F5ED, -0x3AA2ACFE,
    -0x311B7B6B, -0x61ADADB6, -0x224F1D79, -0x06828173,
     0x11008577, -0x73D9DF6D, -0x39057B71,  0x6BFC5071,
     0x16DA3E0E,  0x2E1DB8A9,  0x4DEE3BDF, -0x46FC9DD0,
    -0x119F2073,  0x421A3CE3, -0x3FEA119C, -0x5E6D2C54,
    -0x69AB503D,  0x0537777E,  0x01C7094D, -0x5801133D,
    -0x0D012853, -0x5A2E2344, -0x307FDC1D, -0x3CEFB3AD,
     0x156113DD,  0x4D06F60B,  0x43BC7238,  0x0371FAAB,
     0x189DDF16,  0x344E6237, -0x7CEF2B3F, -0x246503DC,
     0x614A2F83, -0x7A5E1F9C, -0x4E5148BC,  0x0DF0DA44,
    -0x4D03122D, -0x051028A6,  0x21A5E7C7, -0x5F00851C,
     0x4E4BCDFD,  0x6C87681D,  0x2FB95D38,  0x38B23297,
    -0x6B9274C4,  0x06561F8F, -0x66CD3965,  0x4DF0141A,
    -0x799BBF42, -0x5299456F, -0x151C96EB, -0x69AB72B2,
     0x0C796591,  0x1CAFA1F4,  0x0FF18245,  0x31AAB437,
    -0x7112AF97, -0x50B76846,  0x6ED50B7C, -0x3EB5DFF3,
     0x20CB85DF,  0x334895D7,  0x0944C2AD, -0x0C2F14D9,
    -0x31A05277, -0x5EC5BB5C,  0x5DF0FE46,  0x0E8BD2B9,
     0x41F035B5,  0x0475273A,  0x5B059A3A,  0x1FFAE691,
    -0x04E7AB33, -0x3748B1A1,  0x2EBF8D9A, -0x18F5AB73,
     0x2DEE5297,  0x00BD98CD, -0x317F88F6, -0x07443D12,
    -0x389E5C6D, -0x669EBEC2,  0x59390A57, -0x09CABB4C,
    -0x523ED25E,  0x78B1DC72, -0x00226CDF, -0x7C805C8A,
     0x553895FB, -0x3C9811A9, -0x24ADC812,  0x58E10811,
     0x2B1769A1, -0x436EAB22,  0x73A293F7,  0x5D20875A,
    -0x78554901, -0x244626FF,  0x7B111A0F, -0x086C09BE,
     0x5E8E35A9,  0x21CE31CD, -0x1247E794,  0x48B3782F,
    -0x128B7B2A, -0x7259B8AD,  0x48B680B3,  0x2392E56B,
    -0x694EE6A9, -0x494EC857,  0x28907637,  0x557E3D6A,
    -0x4906679C, -0x4950705E, -0x167391DC, -0x447702B0,
     0x67D92919,  0x7010F181, -0x53D411D5,  0x1AE8FED0,
    -0x2DDA4154, -0x317262F5, -0x14466671,  0x7825F455,
     0x0DAFA816,  0x229FF5BA,  0x0C373F8E, -0x456337B1,
     0x160358FB,  0x3809095E, -0x1170E866,  0x7AAF7872,
    -0x1C1587F7, -0x6551A135,  0x37F89BF3,  0x7D02ED33,
     0x0E429F01,  0x070FB8D7, -0x4EE5AFCF, -0x42FD7311,
     0x194380C5,  0x56709121,  0x6E619492,  0x29B471E9,
    -0x123FBBD6, -0x4C5740BE,  0x44118284,  0x07202E97,
    -0x12CA20CA,  0x4E7E3A1B,  0x7CA7E734, -0x4C6D3D84,
    -0x1C7147BF,  0x08C13F72,  0x55C6E0AF, -0x41E0A572,
     0x6B606968,  0x265EAFE8,  0x44929A26, -0x515F2A34,
    -0x087C5008,  0x4B9ADA36,  0x6CA1D40F,  0x2EDCD344,
    -0x05291389, -0x110BFCE0,  0x52FD447C,  0x71EFAE0D,
     0x6F9F13DC,  0x3C62C639,  0x2439B5BE,  0x13B1CC18,
    -0x3B65F595,  0x4833ACA0,  0x2141F333,  0x20681570,
    -0x34FEC7E8,  0x1B24D1A7, -0x38745815, -0x58047CD6,
     0x58DD1D98,  0x68661378, -0x1B2C61AA, -0x4F9B2BEF,
     0x220F72C6,  0x525D2CA6, -0x566D9B08, -0x0BCA78A4,
    -0x3B9FCA6D, -0x0ED8C688,  0x5CEBC168,  0x76CE7E22,
    -0x1B25A26A, -0x575968B8,  0x66420B91, -0x04F0E2D3,
    -0x428F3352, -0x004388DF, -0x3A1DD148, -0x0077D415,
    -0x1A8509A4,  0x41D555E3, -0x4FF8CD45,  0x1AD7A310,
     0x529BC0C3,  0x340274A7,  0x40DC0529, -0x2F56021A,
    -0x5AC692AA, -0x478FA5BB, -0x3F1E2706,  0x1263711A,
     0x330E3B2B, -0x61FC67F6,  0x41823841,  0x27647843,
    -0x0BF70DE0, -0x3D1BB75A, -0x7940F190,  0x7382DB71,
     0x612EED03, -0x456E44F7,  0x62AFD1F2, -0x0DD5F19D,
     0x13932BEA, -0x3907D627, -0x4514495C,  0x4DFD80B5,
    -0x37909EC6, -0x7B68E1A6, -0x60771253,  0x14F3267F,
    -0x514F3B26, -0x60DABD4F,  0x7B4BCB2A, -0x46E50954,
     0x38F3A26C, -0x16433FC0, -0x6E1FDC35,  0x6B680B71,
     0x25BBB281, -0x60FBECCF, -0x406094D9,  0x678937E1,
    -0x3E3096BD,  0x62CB9944,  0x55A6C539,  0x451A11D5,
    -0x148B0AF7, -0x743EB249,  0x033EF5F6,  0x2BB90389,
    -0x67F31506, -0x6C2F733D, -0x19188F60, -0x583506FC,
    -0x2B4A9625, -0x1A4B8103, -0x3B81B15C,  0x7D9C62F4,
     0x50A3F38C,  0x434CE181,  0x790004F8,  0x333E754B,
    -0x5BC9FA4B,  0x59755D73, -0x096453A9,  0x13E34102,
     0x49D08F5B, -0x4B298961, -0x1137DA6C, -0x58DBC48B,
     0x55011A8C, -0x797C33DC,  0x7FE8F4B7, -0x1004366E,
    -0x03FF84AB, -0x3657C633, -0x1915A6CB, -0x78116DA6,
    -0x13FD5AFD, -0x4293E8D2, -0x2CDEC94D, -0x3EED4143,
    -0x06713FCC, -0x1809B42F, -0x01FC5B64,  0x25AADC62,
     0x255D7F13,  0x66AA9E73,  0x39E070E4,  0x08C1AD91,
     0x353591F5, -0x624F6403, -0x26124A8E, -0x0491390B,
    -0x7A37C5D1,  0x05D0AA1B,  0x07A558BC,  0x28081295,
     0x7DEE098E, -0x68B1D771,  0x194C9108,  0x4F013BBD,
    -0x29DF2D9E, -0x3C82C6B8, -0x1EA13D75, -0x6564E43F,
    -0x289B4536,  0x2696C586,  0x0B8CCAA9,  0x3E03273C,
    -0x56021446,  0x5A6F7624, -0x6AFE6EF2,  0x57C9B1A7,
    -0x353AD9B8,  0x10B6B9D5,  0x09896DB8,  0x6D1C5EA7,
    -0x4949CEFE,  0x1AA9DF85,  0x66C84FDA, -0x05833954,
    -0x76E7E903, -0x27E71170,  0x7F71D5C3,  0x494AD419,
    -0x46605A09, -0x7A26A1E1, -0x57AF3067,  0x5D3ACE94,
     0x4E7E60C7, -0x0DAB22ED, -0x731830DA,  0x11B02F44,
    -0x32190E1D, -0x708AD4AD,  0x7A717556,  0x06736293,
     0x3921407B, -0x4FFBCE10, -0x6A0E5C7E, -0x19EE657F,
    -0x158736AF,  0x4BD5FA97, -0x1C8BC474,  0x73A7BBE0,
     0x6B888751, -0x52F00927, -0x49E44470, -0x45AA9865,
    -0x3024E28D,  0x165BB67F,  0x343A97E9,  0x2791AE45,
     0x253AF09C, -0x4621E864,  0x1012F756,  0x67609728,
     0x36BA68DF, -0x2DE9E383, -0x7FD8D236,  0x61CC3DAF,
     0x3E67C0B9,  0x0F2453C7, -0x1FF61026, -0x104005D6,
    -0x13D93B52, -0x034E618A,  0x3EAE3C9A,  0x7EFEAF96,
     0x393E534E, -0x5869298C,  0x2181B9BD, -0x32440D27,
     0x1845582D, -0x5583BC7F, -0x70EF8FCB, -0x7AE8A9B9,
     0x0E4CAD51,  0x087F7F3E, -0x2690DF07,  0x47932CD6,
    -0x53D51AD8,  0x7025AB2F, -0x75C3E5BD, -0x63513B6D,
    -0x5612CD2A, -0x1C8BD77D, -0x54D96AC0, -0x3136113C,
    -0x1FD98BB1,  0x6566FCF4, -0x1965ACB2, -0x0AC5A1FF,
    -0x16A056BA,  0x1C9C647D,  0x25607A02, -0x14414BBC,
     0x39AAFF41,  0x2B4A328B, -0x4A91DDF5, -0x7DA17A44,
     0x1193486B, -0x6C462E01,  0x4E42FB2D, -0x701D368E,
    -0x5FCB2D5C, -0x1C36ADB0, -0x6B76B716, -0x6DB47A51,
     0x581B20DC,  0x3D138A2C,  0x7991E330,  0x7A649AD7,
    -0x3A8D61E9,  0x7E86F0ED, -0x79D1169D, -0x3040432D,
    -0x7BFE95C7, -0x7B67CA54, -0x19C06277, -0x09CFBAD4,
     0x06D0D0DB, -0x4CE33A17, -0x1B7201F0,  0x18060B8F,
     0x435F4634,  0x0500EF95, -0x31302C8D,  0x61C1A7D8,
    -0x09B78921,  0x30027E1D,  0x4F8405C7,  0x47FBC61A,
     0x52B767A0, -0x0575647F, -0x654F1C0F, -0x1F8C29F0,
    -0x60E0CFDC,  0x34495F51,  0x46513B36,  0x78EDC752,
     0x50239F80,  0x770228F3, -0x53DE35A1,  0x0E8D9783,
     0x7E9AE0AA,  0x128716B8,  0x03613FA0,  0x1DF93509,
     0x7425B7B5, -0x3AEB0969, -0x5AEC13A1, -0x467852E2,
     0x5F65B398,  0x4D39F575, -0x55451B9A,  0x0A5DDADA,
     0x6AEA30E7, -0x39872365, -0x6889616F, -0x6C378F00,
     0x41ABBCD6,  0x3760C9B7,  0x4956A1E3, -0x3EEE6C31,
    -0x2797A0AA,  0x2D9254CB,  0x635F1B06,  0x25373FE8,
     0x5C38E24B, -0x00545A79,  0x285DF21B,  0x5ED98FA2,
     0x3760416C, -0x20CF3D07, -0x4E29BC21, -0x60FC627B,
    -0x37DCE365,  0x23A564DC, -0x06A82FA0, -0x04F282CA,
     0x0AF1AD5C, -0x786AAA62,  0x646F3BB7, -0x37F20D35,
     0x1FBBF793,  0x0B570427, -0x0A9CB139, -0x3FF02CF7,
    -0x6345F364, -0x6B40536D, -0x0494431C, -0x1F8746D7,
    -0x2EBFC378,  0x6592A002, -0x5B1BC527, -0x56526956,
    -0x0D195149, -0x6C23C7C0, -0x782B3473,  0x5F1B10C4,
     0x09261A6B,  0x7CAEBB73,  0x0763C856, -0x44913216,
    -0x49254223, -0x49D7A26A, -0x2805AD38,  0x34912D18,
     0x321E9DD4,  0x7AC653A7,  0x3334F455,  0x6D0CFA89,
    -0x61C58B7D, -0x18E78D3C,  0x58A0F1CD, -0x5203D7B3,
    -0x72C5A3F7, -0x25569B17, -0x112956C8,  0x264B6A2A,
    -0x3CCB6360,  0x7F8C1992, -0x5A7AB0BE,  0x39B90341,
     0x75C74DD0, -0x1A6E30D4, -0x4ABA96BC,  0x06962FFE,
     0x50CE9D67,  0x0ADACDF0,  0x36271A33, -0x1088831B,
     0x5B682C07,  0x3E67EA40, -0x43BE6E67, -0x7A2002B7,
    -0x0FFEAB37,  0x11103A79, -0x5BC834B5,  0x318999AD,
    -0x22FD3F10, -0x2D505F5D, -0x261AD59D,  0x4274C3FE,
     0x4E0FB1BE,  0x0D71942F,  0x03E4681A, -0x1B77CDE7,
    -0x4D27DA40, -0x5E523362, -0x02C26206, -0x2B50C400,
     0x1F45A312, -0x0DD4B8FA,  0x6DD64EF6,  0x38AE1203,
    -0x53EA51D2, -0x40F2C1DE, -0x36E8837D, -0x4D61F0CC,
     0x29E83969, -0x3F60C479,  0x5CDF5045, -0x652FB1CB,
     0x6A8381B6,  0x1370FDE4,  0x2BE11743, -0x01E5C581,
    -0x175F1CB5, -0x3CF3C3FC, -0x42AFA4AA,  0x4022AE03,
    -0x170E1942, -0x0B7B7212,  0x4B727D96, -0x7412260C,
     0x72FAB744, -0x3BA7734F, -0x5FA5E2DA,  0x7E89C405,
    -0x74E37CE0, -0x4501C31F,  0x0E4A16ED, -0x68DBDB15,
    -0x6AF2BD64, -0x5D32F0BB,  0x5339227F,  0x6F8C70EC,
    -0x0984F8B0, -0x2863D9EF,  0x6055FAA9,  0x69EAB982,
     0x2073D59E,  0x28F6569A,  0x399535EE,  0x729D1735,
     0x5B77A205, -0x3F7FDE54, -0x08C125F4, -0x60441AF3,
    -0x351768B1, -0x116658DE,  0x1F2FE2FB, -0x58174FE8,
    -0x3C1A6C9F,  0x49C8BB0B, -0x29F7B84F, -0x28CF6EC6,
     0x0FF5782E,  0x559E0AFC, -0x010CAF33, -0x218EA6B9,
     0x52A45C72, -0x7032BA85, -0x2FD72BDB,  0x60060569,
     0x11ED27B0,  0x630DC9D7,  0x098DD447,  0x6FCA884F,
     0x5156CE5C, -0x4B51CF44,  0x752FC34A, -0x2D649293,
     0x66658D66,  0x65C3E2D6, -0x682AF1E4,  0x00838D30,
     0x5CFDDABC,  0x11E433B1,  0x65EB8C31, -0x5277B7D2,
    -0x6FEC37F9, -0x40A053DD,  0x0FE09026, -0x712DCC7A,
    -0x11BBB588,  0x686622CD, -0x41D43426, -0x52615DF2,
    -0x386644E4,  0x36EA64E8,  0x39E68968, -0x060B5A01,
     0x49BEE7D4, -0x3E86EF01,  0x6644F342,  0x1718F4A5,
    -0x759DCD34,  0x692D3DF6,  0x770648EF, -0x0FCA29E6,
     0x5D49309F,  0x74C9F515,  0x683F4CA6,  0x0A71FD6A,
    -0x69D3AE18, -0x2FBE877B,  0x2BC0D58E,  0x478FB239,
     0x6810E11F, -0x38A0DE3D, -0x01453D6E, -0x1B0034DC,
    -0x7AD6866F, -0x2F0EB6F3,  0x5AE75A18, -0x4196B83E,
    -0x52A36A26,  0x1B3BB5CE,  0x18A033DD, -0x34FCA16C,
    -0x3CF8E448, -0x0871B6A6, -0x21E26AA0, -0x450CFF40,
    -0x65816CA1,  0x76D5AA18,  0x0E64F000, -0x363BEC62,
     0x2444F135,  0x6E8010D4, -0x33D4FE5E, -0x45AA454D,
    -0x4E5E9809, -0x7B7BAA57, -0x0F3D895F,  0x34CF0A44,
    -0x2CA50A8F, -0x086D5108, -0x670EF075,  0x17ED266B,
     0x623F2F97, -0x25153ECC,  0x5AE86F4B, -0x3494CEA8,
     0x214DFC6F, -0x4BF40B14,  0x55743531,  0x479887C2,
     0x1D4FCD69,  0x5EA919EE, -0x00779A79, -0x5FF96CBF,
     0x230A489B,  0x00F2EA4B, -0x11CE9B56, -0x1ADBB356,
    -0x3C182B03,  0x358A0E01,  0x3B92AD79, -0x45CE369F,
    -0x16267645,  0x4393511C, -0x6E190914, -0x4D3EA680,
    -0x1FA3FB5D, -0x7B2FC5A5, -0x54CB79DD, -0x7D4CD752,
    -0x61213A85, -0x4EDA20BB, -0x69E0243B,  0x2DA237EA,
    -0x10BAAAAA, -0x681E55E3, -0x579F6EB7,  0x270F59D0,
    -0x39C8C4CB,  0x31BEA2A4,  0x20039E79, -0x62698579,
     0x3EDF0C6A, -0x2752F4A0, -0x64D7C765, -0x713C6747,
     0x5FEF0C10, -0x6CE8EB9A,  0x4A5860AB,  0x16F0CE7A,
     0x0B9A316E, -0x18D78F58, -0x59AA105D, -0x266A4620,
    -0x58BF7C07,  0x4D82902A,  0x3F43EFA0, -0x5B43E16C,
    -0x599B4B2D, -0x0E03C71B, -0x3F1944B9,  0x4A1A7190,
    -0x10E1E42B, -0x4B91CF15, -0x3DFA5421, -0x5249D2CE,
    -0x5A94129E,  0x18109487,  0x6C8CA454,  0x0CD20E7C,
    -0x24CBD801, -0x66EA7048, -0x4B300983, -0x5C9C34F5
};



/* ======================================================================== */
/*  Variables to catch return values from function.                         */
/* ======================================================================== */
short ret_val_asm = 0;
short ret_val_c = 0;

int main()
{   

/* ======================================================================== */
/*  Call hand-coded assembly version (located in DSP64x.lib library         */ 
/*  archive - see Project -> Build Options -> Linker -> Include Libraries)  */
/* ======================================================================== */   
    ret_val_asm = DSP_bexp(x, NX);
    
/* ======================================================================== */
/*  Call natural-C version                                                  */
/* ======================================================================== */
    ret_val_c = DSP_bexp_c(x, NX);

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
/*  End of file:  dsp_bexp_d.c                                              */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2003 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
