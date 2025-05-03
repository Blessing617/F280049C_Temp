################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
ASM_SRCS += \
../8.dsp/fft/source/fft/CFFT_f32.asm \
../8.dsp/fft/source/fft/CFFT_f32_mag.asm \
../8.dsp/fft/source/fft/CFFT_f32_phase.asm \
../8.dsp/fft/source/fft/CFFT_f32_twiddleFactors.asm \
../8.dsp/fft/source/fft/CFFT_f32_win.asm \
../8.dsp/fft/source/fft/CFFT_f32i.asm \
../8.dsp/fft/source/fft/CFFT_f32it.asm \
../8.dsp/fft/source/fft/CFFT_f32s_mag.asm \
../8.dsp/fft/source/fft/CFFT_f32t.asm \
../8.dsp/fft/source/fft/CFFT_f32u.asm \
../8.dsp/fft/source/fft/CFFT_f32ut.asm \
../8.dsp/fft/source/fft/ICFFT_f32.asm \
../8.dsp/fft/source/fft/ICFFT_f32t.asm \
../8.dsp/fft/source/fft/RFFT_adc_f32.asm \
../8.dsp/fft/source/fft/RFFT_adc_f32u.asm \
../8.dsp/fft/source/fft/RFFT_f32.asm \
../8.dsp/fft/source/fft/RFFT_f32_adc_win.asm \
../8.dsp/fft/source/fft/RFFT_f32_mag.asm \
../8.dsp/fft/source/fft/RFFT_f32_phase.asm \
../8.dsp/fft/source/fft/RFFT_f32_twiddleFactors.asm \
../8.dsp/fft/source/fft/RFFT_f32_win.asm \
../8.dsp/fft/source/fft/RFFT_f32s_mag.asm \
../8.dsp/fft/source/fft/RFFT_f32u.asm \
../8.dsp/fft/source/fft/cfft_f32_brev.asm \
../8.dsp/fft/source/fft/cfft_f32_pack.asm \
../8.dsp/fft/source/fft/cfft_f32_unpack.asm 

C_SRCS += \
../8.dsp/fft/source/fft/CFFT_f32_sincostable.c \
../8.dsp/fft/source/fft/RFFT_f32_sincostable.c 

C_DEPS += \
./8.dsp/fft/source/fft/CFFT_f32_sincostable.d \
./8.dsp/fft/source/fft/RFFT_f32_sincostable.d 

OBJS += \
./8.dsp/fft/source/fft/CFFT_f32.obj \
./8.dsp/fft/source/fft/CFFT_f32_mag.obj \
./8.dsp/fft/source/fft/CFFT_f32_phase.obj \
./8.dsp/fft/source/fft/CFFT_f32_sincostable.obj \
./8.dsp/fft/source/fft/CFFT_f32_twiddleFactors.obj \
./8.dsp/fft/source/fft/CFFT_f32_win.obj \
./8.dsp/fft/source/fft/CFFT_f32i.obj \
./8.dsp/fft/source/fft/CFFT_f32it.obj \
./8.dsp/fft/source/fft/CFFT_f32s_mag.obj \
./8.dsp/fft/source/fft/CFFT_f32t.obj \
./8.dsp/fft/source/fft/CFFT_f32u.obj \
./8.dsp/fft/source/fft/CFFT_f32ut.obj \
./8.dsp/fft/source/fft/ICFFT_f32.obj \
./8.dsp/fft/source/fft/ICFFT_f32t.obj \
./8.dsp/fft/source/fft/RFFT_adc_f32.obj \
./8.dsp/fft/source/fft/RFFT_adc_f32u.obj \
./8.dsp/fft/source/fft/RFFT_f32.obj \
./8.dsp/fft/source/fft/RFFT_f32_adc_win.obj \
./8.dsp/fft/source/fft/RFFT_f32_mag.obj \
./8.dsp/fft/source/fft/RFFT_f32_phase.obj \
./8.dsp/fft/source/fft/RFFT_f32_sincostable.obj \
./8.dsp/fft/source/fft/RFFT_f32_twiddleFactors.obj \
./8.dsp/fft/source/fft/RFFT_f32_win.obj \
./8.dsp/fft/source/fft/RFFT_f32s_mag.obj \
./8.dsp/fft/source/fft/RFFT_f32u.obj \
./8.dsp/fft/source/fft/cfft_f32_brev.obj \
./8.dsp/fft/source/fft/cfft_f32_pack.obj \
./8.dsp/fft/source/fft/cfft_f32_unpack.obj 

ASM_DEPS += \
./8.dsp/fft/source/fft/CFFT_f32.d \
./8.dsp/fft/source/fft/CFFT_f32_mag.d \
./8.dsp/fft/source/fft/CFFT_f32_phase.d \
./8.dsp/fft/source/fft/CFFT_f32_twiddleFactors.d \
./8.dsp/fft/source/fft/CFFT_f32_win.d \
./8.dsp/fft/source/fft/CFFT_f32i.d \
./8.dsp/fft/source/fft/CFFT_f32it.d \
./8.dsp/fft/source/fft/CFFT_f32s_mag.d \
./8.dsp/fft/source/fft/CFFT_f32t.d \
./8.dsp/fft/source/fft/CFFT_f32u.d \
./8.dsp/fft/source/fft/CFFT_f32ut.d \
./8.dsp/fft/source/fft/ICFFT_f32.d \
./8.dsp/fft/source/fft/ICFFT_f32t.d \
./8.dsp/fft/source/fft/RFFT_adc_f32.d \
./8.dsp/fft/source/fft/RFFT_adc_f32u.d \
./8.dsp/fft/source/fft/RFFT_f32.d \
./8.dsp/fft/source/fft/RFFT_f32_adc_win.d \
./8.dsp/fft/source/fft/RFFT_f32_mag.d \
./8.dsp/fft/source/fft/RFFT_f32_phase.d \
./8.dsp/fft/source/fft/RFFT_f32_twiddleFactors.d \
./8.dsp/fft/source/fft/RFFT_f32_win.d \
./8.dsp/fft/source/fft/RFFT_f32s_mag.d \
./8.dsp/fft/source/fft/RFFT_f32u.d \
./8.dsp/fft/source/fft/cfft_f32_brev.d \
./8.dsp/fft/source/fft/cfft_f32_pack.d \
./8.dsp/fft/source/fft/cfft_f32_unpack.d 

OBJS__QUOTED += \
"8.dsp\fft\source\fft\CFFT_f32.obj" \
"8.dsp\fft\source\fft\CFFT_f32_mag.obj" \
"8.dsp\fft\source\fft\CFFT_f32_phase.obj" \
"8.dsp\fft\source\fft\CFFT_f32_sincostable.obj" \
"8.dsp\fft\source\fft\CFFT_f32_twiddleFactors.obj" \
"8.dsp\fft\source\fft\CFFT_f32_win.obj" \
"8.dsp\fft\source\fft\CFFT_f32i.obj" \
"8.dsp\fft\source\fft\CFFT_f32it.obj" \
"8.dsp\fft\source\fft\CFFT_f32s_mag.obj" \
"8.dsp\fft\source\fft\CFFT_f32t.obj" \
"8.dsp\fft\source\fft\CFFT_f32u.obj" \
"8.dsp\fft\source\fft\CFFT_f32ut.obj" \
"8.dsp\fft\source\fft\ICFFT_f32.obj" \
"8.dsp\fft\source\fft\ICFFT_f32t.obj" \
"8.dsp\fft\source\fft\RFFT_adc_f32.obj" \
"8.dsp\fft\source\fft\RFFT_adc_f32u.obj" \
"8.dsp\fft\source\fft\RFFT_f32.obj" \
"8.dsp\fft\source\fft\RFFT_f32_adc_win.obj" \
"8.dsp\fft\source\fft\RFFT_f32_mag.obj" \
"8.dsp\fft\source\fft\RFFT_f32_phase.obj" \
"8.dsp\fft\source\fft\RFFT_f32_sincostable.obj" \
"8.dsp\fft\source\fft\RFFT_f32_twiddleFactors.obj" \
"8.dsp\fft\source\fft\RFFT_f32_win.obj" \
"8.dsp\fft\source\fft\RFFT_f32s_mag.obj" \
"8.dsp\fft\source\fft\RFFT_f32u.obj" \
"8.dsp\fft\source\fft\cfft_f32_brev.obj" \
"8.dsp\fft\source\fft\cfft_f32_pack.obj" \
"8.dsp\fft\source\fft\cfft_f32_unpack.obj" 

C_DEPS__QUOTED += \
"8.dsp\fft\source\fft\CFFT_f32_sincostable.d" \
"8.dsp\fft\source\fft\RFFT_f32_sincostable.d" 

ASM_DEPS__QUOTED += \
"8.dsp\fft\source\fft\CFFT_f32.d" \
"8.dsp\fft\source\fft\CFFT_f32_mag.d" \
"8.dsp\fft\source\fft\CFFT_f32_phase.d" \
"8.dsp\fft\source\fft\CFFT_f32_twiddleFactors.d" \
"8.dsp\fft\source\fft\CFFT_f32_win.d" \
"8.dsp\fft\source\fft\CFFT_f32i.d" \
"8.dsp\fft\source\fft\CFFT_f32it.d" \
"8.dsp\fft\source\fft\CFFT_f32s_mag.d" \
"8.dsp\fft\source\fft\CFFT_f32t.d" \
"8.dsp\fft\source\fft\CFFT_f32u.d" \
"8.dsp\fft\source\fft\CFFT_f32ut.d" \
"8.dsp\fft\source\fft\ICFFT_f32.d" \
"8.dsp\fft\source\fft\ICFFT_f32t.d" \
"8.dsp\fft\source\fft\RFFT_adc_f32.d" \
"8.dsp\fft\source\fft\RFFT_adc_f32u.d" \
"8.dsp\fft\source\fft\RFFT_f32.d" \
"8.dsp\fft\source\fft\RFFT_f32_adc_win.d" \
"8.dsp\fft\source\fft\RFFT_f32_mag.d" \
"8.dsp\fft\source\fft\RFFT_f32_phase.d" \
"8.dsp\fft\source\fft\RFFT_f32_twiddleFactors.d" \
"8.dsp\fft\source\fft\RFFT_f32_win.d" \
"8.dsp\fft\source\fft\RFFT_f32s_mag.d" \
"8.dsp\fft\source\fft\RFFT_f32u.d" \
"8.dsp\fft\source\fft\cfft_f32_brev.d" \
"8.dsp\fft\source\fft\cfft_f32_pack.d" \
"8.dsp\fft\source\fft\cfft_f32_unpack.d" 

ASM_SRCS__QUOTED += \
"../8.dsp/fft/source/fft/CFFT_f32.asm" \
"../8.dsp/fft/source/fft/CFFT_f32_mag.asm" \
"../8.dsp/fft/source/fft/CFFT_f32_phase.asm" \
"../8.dsp/fft/source/fft/CFFT_f32_twiddleFactors.asm" \
"../8.dsp/fft/source/fft/CFFT_f32_win.asm" \
"../8.dsp/fft/source/fft/CFFT_f32i.asm" \
"../8.dsp/fft/source/fft/CFFT_f32it.asm" \
"../8.dsp/fft/source/fft/CFFT_f32s_mag.asm" \
"../8.dsp/fft/source/fft/CFFT_f32t.asm" \
"../8.dsp/fft/source/fft/CFFT_f32u.asm" \
"../8.dsp/fft/source/fft/CFFT_f32ut.asm" \
"../8.dsp/fft/source/fft/ICFFT_f32.asm" \
"../8.dsp/fft/source/fft/ICFFT_f32t.asm" \
"../8.dsp/fft/source/fft/RFFT_adc_f32.asm" \
"../8.dsp/fft/source/fft/RFFT_adc_f32u.asm" \
"../8.dsp/fft/source/fft/RFFT_f32.asm" \
"../8.dsp/fft/source/fft/RFFT_f32_adc_win.asm" \
"../8.dsp/fft/source/fft/RFFT_f32_mag.asm" \
"../8.dsp/fft/source/fft/RFFT_f32_phase.asm" \
"../8.dsp/fft/source/fft/RFFT_f32_twiddleFactors.asm" \
"../8.dsp/fft/source/fft/RFFT_f32_win.asm" \
"../8.dsp/fft/source/fft/RFFT_f32s_mag.asm" \
"../8.dsp/fft/source/fft/RFFT_f32u.asm" \
"../8.dsp/fft/source/fft/cfft_f32_brev.asm" \
"../8.dsp/fft/source/fft/cfft_f32_pack.asm" \
"../8.dsp/fft/source/fft/cfft_f32_unpack.asm" 

C_SRCS__QUOTED += \
"../8.dsp/fft/source/fft/CFFT_f32_sincostable.c" \
"../8.dsp/fft/source/fft/RFFT_f32_sincostable.c" 


