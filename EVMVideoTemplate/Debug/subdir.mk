################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../audio_params.c \
../i2c_params.c \
../video_loopback.c 

TCF_SRCS += \
../tsk.tcf 

SA_SRCS += \
../extractY.sa \
../extractYCbCr.sa \
../y_cb_cr_to_y.sa 

GEN_SRCS += \
./tskcfg.cmd \
./tskcfg.s?? \
./tskcfg_c.c 

GEN_CMDS += \
./tskcfg.cmd 

OBJS += \
./audio_params.obj \
./extractY.obj \
./extractYCbCr.obj \
./i2c_params.obj \
./tskcfg.obj \
./tskcfg_c.obj \
./video_loopback.obj \
./y_cb_cr_to_y.obj \
./ycbcr_to_y_cb_cr.obj 

GEN_MISC_FILES += \
./tskcfg.h \
./tskcfg.h?? \
./tsk.cdb 

S??_DEPS += \
./tskcfg.pp 

C_DEPS += \
./audio_params.pp \
./i2c_params.pp \
./tskcfg_c.pp \
./video_loopback.pp \
./ycbcr_to_y_cb_cr.pp 

SA_DEPS += \
./extractY.pp \
./extractYCbCr.pp \
./y_cb_cr_to_y.pp 

GEN_MISC_FILES__QUOTED += \
"tskcfg.h" \
"tskcfg.h??" \
"tsk.cdb" 

C_DEPS__QUOTED += \
"audio_params.pp" \
"i2c_params.pp" \
"tskcfg_c.pp" \
"video_loopback.pp" \
"ycbcr_to_y_cb_cr.pp" 

SA_DEPS__QUOTED += \
"extractY.pp" \
"extractYCbCr.pp" \
"y_cb_cr_to_y.pp" 

OBJS__QUOTED += \
"audio_params.obj" \
"extractY.obj" \
"extractYCbCr.obj" \
"i2c_params.obj" \
"tskcfg.obj" \
"tskcfg_c.obj" \
"video_loopback.obj" \
"y_cb_cr_to_y.obj" \
"ycbcr_to_y_cb_cr.obj" 

S??_DEPS__QUOTED += \
"tskcfg.pp" 

GEN_SRCS__QUOTED += \
"tskcfg.cmd" \
"tskcfg.s??" \
"tskcfg_c.c" 

C_SRCS__QUOTED += \
"../audio_params.c" \
"../i2c_params.c" \
"../video_loopback.c" 

SA_SRCS__QUOTED += \
"../extractY.sa" \
"../extractYCbCr.sa" \
"../y_cb_cr_to_y.sa" 

TCF_SRCS__QUOTED += \
"../tsk.tcf" 

GEN_CMDS__FLAG += \
-l"./tskcfg.cmd" 


# Each subdirectory must supply rules for building sources it contributes
audio_params.obj: ../audio_params.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/Program Files/Texas Instruments/ccsv5/tools/compiler/c6000/bin/cl6x" -mv64+ -g -O3 --include_path="C:/Program Files/Texas Instruments/ccsv5/tools/compiler/c6000/include" --include_path="..\..\CommonLib" --include_path="C:\dvsdk_1_01_00_15\examples\common\evmDM6437" --include_path="C:\CCStudio_v3.3\EVMDM6437\boards\evmdm6437_v2\include" --include_path="C:\dvsdk_1_01_00_15\psp_1_00_02_00\pspdrivers\soc\dm6437\dsp\inc" --include_path="C:\dvsdk_1_01_00_15\psp_1_00_02_00\pspdrivers\inc" --include_path="C:/Program Files/Texas Instruments/bios_5_41_10_36/packages/ti/bios/include" --include_path="C:/Program Files/Texas Instruments/bios_5_41_10_36/packages/ti/rtdx/include/c6000" --diag_warning=225 --abi=coffabi --opt_for_speed=5 --preproc_with_compile --preproc_dependency="audio_params.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

extractY.obj: ../extractY.sa $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/Program Files/Texas Instruments/ccsv5/tools/compiler/c6000/bin/cl6x" -mv64+ -g -O3 --include_path="C:/Program Files/Texas Instruments/ccsv5/tools/compiler/c6000/include" --include_path="..\..\CommonLib" --include_path="C:\dvsdk_1_01_00_15\examples\common\evmDM6437" --include_path="C:\CCStudio_v3.3\EVMDM6437\boards\evmdm6437_v2\include" --include_path="C:\dvsdk_1_01_00_15\psp_1_00_02_00\pspdrivers\soc\dm6437\dsp\inc" --include_path="C:\dvsdk_1_01_00_15\psp_1_00_02_00\pspdrivers\inc" --include_path="C:/Program Files/Texas Instruments/bios_5_41_10_36/packages/ti/bios/include" --include_path="C:/Program Files/Texas Instruments/bios_5_41_10_36/packages/ti/rtdx/include/c6000" --diag_warning=225 --abi=coffabi --opt_for_speed=5 --preproc_with_compile --preproc_dependency="extractY.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

extractYCbCr.obj: ../extractYCbCr.sa $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/Program Files/Texas Instruments/ccsv5/tools/compiler/c6000/bin/cl6x" -mv64+ -g -O3 --include_path="C:/Program Files/Texas Instruments/ccsv5/tools/compiler/c6000/include" --include_path="..\..\CommonLib" --include_path="C:\dvsdk_1_01_00_15\examples\common\evmDM6437" --include_path="C:\CCStudio_v3.3\EVMDM6437\boards\evmdm6437_v2\include" --include_path="C:\dvsdk_1_01_00_15\psp_1_00_02_00\pspdrivers\soc\dm6437\dsp\inc" --include_path="C:\dvsdk_1_01_00_15\psp_1_00_02_00\pspdrivers\inc" --include_path="C:/Program Files/Texas Instruments/bios_5_41_10_36/packages/ti/bios/include" --include_path="C:/Program Files/Texas Instruments/bios_5_41_10_36/packages/ti/rtdx/include/c6000" --diag_warning=225 --abi=coffabi --opt_for_speed=5 --preproc_with_compile --preproc_dependency="extractYCbCr.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

i2c_params.obj: ../i2c_params.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/Program Files/Texas Instruments/ccsv5/tools/compiler/c6000/bin/cl6x" -mv64+ -g -O3 --include_path="C:/Program Files/Texas Instruments/ccsv5/tools/compiler/c6000/include" --include_path="..\..\CommonLib" --include_path="C:\dvsdk_1_01_00_15\examples\common\evmDM6437" --include_path="C:\CCStudio_v3.3\EVMDM6437\boards\evmdm6437_v2\include" --include_path="C:\dvsdk_1_01_00_15\psp_1_00_02_00\pspdrivers\soc\dm6437\dsp\inc" --include_path="C:\dvsdk_1_01_00_15\psp_1_00_02_00\pspdrivers\inc" --include_path="C:/Program Files/Texas Instruments/bios_5_41_10_36/packages/ti/bios/include" --include_path="C:/Program Files/Texas Instruments/bios_5_41_10_36/packages/ti/rtdx/include/c6000" --diag_warning=225 --abi=coffabi --opt_for_speed=5 --preproc_with_compile --preproc_dependency="i2c_params.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

tskcfg.cmd: ../tsk.tcf
	@echo 'Building file: $<'
	@echo 'Invoking: TConf Script Compiler'
	"C:/Program Files/Texas Instruments/xdctools_3_20_08_88/tconf" -b -Dconfig.importPath="C:/Program Files/Texas Instruments/bios_5_41_10_36/packages;" "$<"
	@echo 'Finished building: $<'
	@echo ' '

tskcfg.s??: tskcfg.cmd
tskcfg_c.c: tskcfg.cmd
tskcfg.h: tskcfg.cmd
tskcfg.h??: tskcfg.cmd
tsk.cdb: tskcfg.cmd

tskcfg.obj: ./tskcfg.s?? $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/Program Files/Texas Instruments/ccsv5/tools/compiler/c6000/bin/cl6x" -mv64+ -g -O3 --include_path="C:/Program Files/Texas Instruments/ccsv5/tools/compiler/c6000/include" --include_path="..\..\CommonLib" --include_path="C:\dvsdk_1_01_00_15\examples\common\evmDM6437" --include_path="C:\CCStudio_v3.3\EVMDM6437\boards\evmdm6437_v2\include" --include_path="C:\dvsdk_1_01_00_15\psp_1_00_02_00\pspdrivers\soc\dm6437\dsp\inc" --include_path="C:\dvsdk_1_01_00_15\psp_1_00_02_00\pspdrivers\inc" --include_path="C:/Program Files/Texas Instruments/bios_5_41_10_36/packages/ti/bios/include" --include_path="C:/Program Files/Texas Instruments/bios_5_41_10_36/packages/ti/rtdx/include/c6000" --diag_warning=225 --abi=coffabi --opt_for_speed=5 --preproc_with_compile --preproc_dependency="tskcfg.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

tskcfg_c.obj: ./tskcfg_c.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/Program Files/Texas Instruments/ccsv5/tools/compiler/c6000/bin/cl6x" -mv64+ -g -O3 --include_path="C:/Program Files/Texas Instruments/ccsv5/tools/compiler/c6000/include" --include_path="..\..\CommonLib" --include_path="C:\dvsdk_1_01_00_15\examples\common\evmDM6437" --include_path="C:\CCStudio_v3.3\EVMDM6437\boards\evmdm6437_v2\include" --include_path="C:\dvsdk_1_01_00_15\psp_1_00_02_00\pspdrivers\soc\dm6437\dsp\inc" --include_path="C:\dvsdk_1_01_00_15\psp_1_00_02_00\pspdrivers\inc" --include_path="C:/Program Files/Texas Instruments/bios_5_41_10_36/packages/ti/bios/include" --include_path="C:/Program Files/Texas Instruments/bios_5_41_10_36/packages/ti/rtdx/include/c6000" --diag_warning=225 --abi=coffabi --opt_for_speed=5 --preproc_with_compile --preproc_dependency="tskcfg_c.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

video_loopback.obj: ../video_loopback.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/Program Files/Texas Instruments/ccsv5/tools/compiler/c6000/bin/cl6x" -mv64+ -g -O3 --include_path="C:/Program Files/Texas Instruments/ccsv5/tools/compiler/c6000/include" --include_path="..\..\CommonLib" --include_path="C:\dvsdk_1_01_00_15\examples\common\evmDM6437" --include_path="C:\CCStudio_v3.3\EVMDM6437\boards\evmdm6437_v2\include" --include_path="C:\dvsdk_1_01_00_15\psp_1_00_02_00\pspdrivers\soc\dm6437\dsp\inc" --include_path="C:\dvsdk_1_01_00_15\psp_1_00_02_00\pspdrivers\inc" --include_path="C:/Program Files/Texas Instruments/bios_5_41_10_36/packages/ti/bios/include" --include_path="C:/Program Files/Texas Instruments/bios_5_41_10_36/packages/ti/rtdx/include/c6000" --diag_warning=225 --abi=coffabi --opt_for_speed=5 --preproc_with_compile --preproc_dependency="video_loopback.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

y_cb_cr_to_y.obj: ../y_cb_cr_to_y.sa $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/Program Files/Texas Instruments/ccsv5/tools/compiler/c6000/bin/cl6x" -mv64+ -g -O3 --include_path="C:/Program Files/Texas Instruments/ccsv5/tools/compiler/c6000/include" --include_path="..\..\CommonLib" --include_path="C:\dvsdk_1_01_00_15\examples\common\evmDM6437" --include_path="C:\CCStudio_v3.3\EVMDM6437\boards\evmdm6437_v2\include" --include_path="C:\dvsdk_1_01_00_15\psp_1_00_02_00\pspdrivers\soc\dm6437\dsp\inc" --include_path="C:\dvsdk_1_01_00_15\psp_1_00_02_00\pspdrivers\inc" --include_path="C:/Program Files/Texas Instruments/bios_5_41_10_36/packages/ti/bios/include" --include_path="C:/Program Files/Texas Instruments/bios_5_41_10_36/packages/ti/rtdx/include/c6000" --diag_warning=225 --abi=coffabi --opt_for_speed=5 --preproc_with_compile --preproc_dependency="y_cb_cr_to_y.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

ycbcr_to_y_cb_cr.obj: ../ycbcr_to_y_cb_cr.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/Program Files/Texas Instruments/ccsv5/tools/compiler/c6000/bin/cl6x" -mv64+ -g -O3 --include_path="C:/Program Files/Texas Instruments/ccsv5/tools/compiler/c6000/include" --include_path="..\..\CommonLib" --include_path="C:\dvsdk_1_01_00_15\examples\common\evmDM6437" --include_path="C:\CCStudio_v3.3\EVMDM6437\boards\evmdm6437_v2\include" --include_path="C:\dvsdk_1_01_00_15\psp_1_00_02_00\pspdrivers\soc\dm6437\dsp\inc" --include_path="C:\dvsdk_1_01_00_15\psp_1_00_02_00\pspdrivers\inc" --include_path="C:/Program Files/Texas Instruments/bios_5_41_10_36/packages/ti/bios/include" --include_path="C:/Program Files/Texas Instruments/bios_5_41_10_36/packages/ti/rtdx/include/c6000" --diag_warning=225 --abi=coffabi --opt_for_speed=5 --preproc_with_compile --preproc_dependency="ycbcr_to_y_cb_cr.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


