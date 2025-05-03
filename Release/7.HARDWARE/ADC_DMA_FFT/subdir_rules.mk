################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
7.HARDWARE/ADC_DMA_FFT/%.obj: ../7.HARDWARE/ADC_DMA_FFT/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccs1250/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --tmu_support=tmu0 -O2 --opt_for_speed=2 --fp_mode=relaxed --include_path="D:/ti/Project/F280049C_Temp" --include_path="D:/ti/ccs1250/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --include_path="D:/ti/Project/F280049C_Temp/3.device/include" --include_path="D:/ti/Project/F280049C_Temp/4.common/include" --include_path="D:/ti/Project/F280049C_Temp/5.headers/include" --include_path="D:/ti/Project/F280049C_Temp/6.user" --include_path="D:/ti/Project/F280049C_Temp/8.dsp/fft/include" --include_path="D:/ti/Project/F280049C_Temp/8.dsp/FPUfastRTS/include" --include_path="D:/ti/Project/F280049C_Temp/7.HARDWARE/LED" --include_path="D:/ti/Project/F280049C_Temp/7.HARDWARE/KEY_EXTI" --include_path="D:/ti/Project/F280049C_Temp/7.HARDWARE/USART" --include_path="D:/ti/Project/F280049C_Temp/7.HARDWARE/OLED" --include_path="D:/ti/Project/F280049C_Temp/7.HARDWARE/ADC" --include_path="D:/ti/Project/F280049C_Temp/7.HARDWARE/DAC" --include_path="D:/ti/Project/F280049C_Temp/7.HARDWARE/ADC_DMA_FFT" --advice:performance=all --define=_INLINE --define=_LAUNCHXL_F280049C --define=_FLASH --define=_STANDALONE --float_operations_allowed=all --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="7.HARDWARE/ADC_DMA_FFT/$(basename $(<F)).d_raw" --obj_directory="7.HARDWARE/ADC_DMA_FFT" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


