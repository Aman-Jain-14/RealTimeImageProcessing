/*
 * ======== audio_params.c ========
 *
 */

#include <psp_audio.h>

#define LABO_SPECTROGRAPHE  0
#define LABO_GOERTZELL 0
#define LABO_CONV1D 0
#define AUDIO_LOOPBACK  1  // input is MIC, ouput is HP



#if LABO_CONV1D // input from dvd
PSP_audio_cfg   audio_cfg = {
        PSP_AUDIO_AIC_MASTER,   /* AIC Mode */
        99000000,               /* Input Frequency to McBSP or McASP module */
        44100,                   /* Sampling Rate */
        60,                     /* Input Gain */
        80,                     /* Output Gain */
        PSP_AUDIO_LINE_IN, //PSP_AUDIO_MIC_IN_2_0_V,      /* Input Select */
        PSP_AUDIO_SPK_OUT//PSP_AUDIO_LINE_OUT      /* Output Select */
};
#elif LABO_GOERTZELL
PSP_audio_cfg   audio_cfg = {
        PSP_AUDIO_AIC_MASTER,   /* AIC Mode */
        99000000,               /* Input Frequency to McBSP or McASP module */
        8000,                   /* Sampling Rate */
        1,                     /* Input Gain */
        80,                     /* Output Gain */
        PSP_AUDIO_LINE_IN, //PSP_AUDIO_MIC_IN_2_0_V,      /* Input Select */
        PSP_AUDIO_SPK_OUT//PSP_AUDIO_LINE_OUT      /* Output Select */
};
#elif LABO_SPECTROGRAPHE
PSP_audio_cfg   audio_cfg = {
        PSP_AUDIO_AIC_MASTER,   /* AIC Mode */
        99000000,               /* Input Frequency to McBSP or McASP module */
        16000,                   /* Sampling Rate */
        50,                     /* Input Gain */
        80,                     /* Output Gain */
        PSP_AUDIO_MIC_IN_2_0_V, //PSP_AUDIO_MIC_IN_2_0_V,      /* Input Select */
        PSP_AUDIO_SPK_OUT//PSP_AUDIO_LINE_OUT      /* Output Select */
};
#elif AUDIO_LOOPBACK
PSP_audio_cfg   audio_cfg = {
        PSP_AUDIO_AIC_MASTER,   /* AIC Mode */
        99000000,               /* Input Frequency to McBSP or McASP module */
        16000,                   /* Sampling Rate */
        50,                     /* Input Gain */
        80,                     /* Output Gain */
        PSP_AUDIO_MIC_IN_2_0_V, //PSP_AUDIO_MIC_IN_2_0_V,      /* Input Select */
        PSP_AUDIO_SPK_OUT//PSP_AUDIO_LINE_OUT      /* Output Select */
};
#elif LABO_SPECTROGRAPHE_LINE
PSP_audio_cfg   audio_cfg = {
        PSP_AUDIO_AIC_MASTER,   /* AIC Mode */
        99000000,               /* Input Frequency to McBSP or McASP module */
        16000,                   /* Sampling Rate */
        1,                     /* Input Gain */
        80,                     /* Output Gain */
        PSP_AUDIO_LINE_IN, //PSP_AUDIO_MIC_IN_2_0_V,      /* Input Select */
        PSP_AUDIO_SPK_OUT//PSP_AUDIO_LINE_OUT      /* Output Select */
};
#elif ACQ_STETHO
PSP_audio_cfg   audio_cfg = {
        PSP_AUDIO_AIC_MASTER,   /* AIC Mode */
        99000000,               /* Input Frequency to McBSP or McASP module */
        8000,                   /* Sampling Rate */
        10000,                     /* Input Gain */
        90,                     /* Output Gain */
        PSP_AUDIO_MIC_IN_2_0_V, //PSP_AUDIO_MIC_IN_2_0_V,      /* Input Select */
        PSP_AUDIO_SPK_OUT//PSP_AUDIO_LINE_OUT      /* Output Select */
};
#else
PSP_audio_cfg   audio_cfg = {
        PSP_AUDIO_AIC_MASTER,   /* AIC Mode */
        99000000,               /* Input Frequency to McBSP or McASP module */
        44100,                   /* Sampling Rate */
        10,                     /* Input Gain */
        80,                     /* Output Gain */
        PSP_AUDIO_LINE_IN, //PSP_AUDIO_MIC_IN_2_0_V,      /* Input Select */
        PSP_AUDIO_SPK_OUT//PSP_AUDIO_LINE_OUT      /* Output Select */
};
#endif


