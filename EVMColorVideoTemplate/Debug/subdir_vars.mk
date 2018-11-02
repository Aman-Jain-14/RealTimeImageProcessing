################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
TCF_SRCS += \
../tsk.tcf 

SA_SRCS += \
../extractY.sa \
../extractYCbCr.sa \
../y_cb_cr_to_ycbcr.sa 

S??_SRCS += \
./tskcfg.s?? 

C_SRCS += \
../audio_params.c \
../i2c_params.c \
../imageProcessing.c \
./tskcfg_c.c \
../video_loopback.c \
../ycbcr_to_y_cb_cr.c 

OBJS += \
./audio_params.obj \
./extractY.obj \
./extractYCbCr.obj \
./i2c_params.obj \
./imageProcessing.obj \
./tskcfg.obj \
./tskcfg_c.obj \
./video_loopback.obj \
./y_cb_cr_to_ycbcr.obj \
./ycbcr_to_y_cb_cr.obj 

GEN_MISC_FILES += \
./tsk.cdb 

GEN_HDRS += \
./tskcfg.h \
./tskcfg.h?? 

S??_DEPS += \
./tskcfg.pp 

C_DEPS += \
./audio_params.pp \
./i2c_params.pp \
./imageProcessing.pp \
./tskcfg_c.pp \
./video_loopback.pp \
./ycbcr_to_y_cb_cr.pp 

GEN_CMDS += \
./tskcfg.cmd 

SA_DEPS += \
./extractY.pp \
./extractYCbCr.pp \
./y_cb_cr_to_ycbcr.pp 

GEN_FILES += \
./tskcfg.cmd \
./tskcfg.s?? \
./tskcfg_c.c 

GEN_HDRS__QUOTED += \
"tskcfg.h" \
"tskcfg.h??" 

GEN_MISC_FILES__QUOTED += \
"tsk.cdb" 

GEN_FILES__QUOTED += \
"tskcfg.cmd" \
"tskcfg.s??" \
"tskcfg_c.c" 

C_DEPS__QUOTED += \
"audio_params.pp" \
"i2c_params.pp" \
"imageProcessing.pp" \
"tskcfg_c.pp" \
"video_loopback.pp" \
"ycbcr_to_y_cb_cr.pp" 

S??_DEPS__QUOTED += \
"tskcfg.pp" 

OBJS__QUOTED += \
"audio_params.obj" \
"extractY.obj" \
"extractYCbCr.obj" \
"i2c_params.obj" \
"imageProcessing.obj" \
"tskcfg.obj" \
"tskcfg_c.obj" \
"video_loopback.obj" \
"y_cb_cr_to_ycbcr.obj" \
"ycbcr_to_y_cb_cr.obj" 

SA_DEPS__QUOTED += \
"extractY.pp" \
"extractYCbCr.pp" \
"y_cb_cr_to_ycbcr.pp" 

C_SRCS__QUOTED += \
"../audio_params.c" \
"../i2c_params.c" \
"../imageProcessing.c" \
"./tskcfg_c.c" \
"../video_loopback.c" \
"../ycbcr_to_y_cb_cr.c" 

SA_SRCS__QUOTED += \
"../extractY.sa" \
"../extractYCbCr.sa" \
"../y_cb_cr_to_ycbcr.sa" 

GEN_CMDS__FLAG += \
-l"./tskcfg.cmd" 

S??_SRCS__QUOTED += \
"./tskcfg.s??" 

S??_OBJS__QUOTED += \
"tskcfg.obj" 


