################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
8.dsp/source/fpu32/utility/%.obj: ../8.dsp/source/fpu32/utility/%.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccs1250/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu0 -O2 --fp_mode=relaxed --include_path="D:/ti/Project/F280049C_Temp" --include_path="D:/ti/ccs1250/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --include_path="D:/ti/Project/F280049C_Temp/3.device/include" --include_path="D:/ti/Project/F280049C_Temp/4.common/include" --include_path="D:/ti/Project/F280049C_Temp/5.headers/include" --include_path="D:/ti/Project/F280049C_Temp/7.HARDWARE/LED" --include_path="D:/ti/Project/F280049C_Temp/7.HARDWARE/KEY_EXTI" --include_path="D:/ti/Project/F280049C_Temp/7.HARDWARE/USART" --include_path="D:/ti/Project/F280049C_Temp/7.HARDWARE/OLED" --include_path="D:/ti/Project/F280049C_Temp/7.HARDWARE/ADC" --include_path="D:/ti/Project/F280049C_Temp/8.dsp/include" --advice:performance=all --define=_INLINE --define=_LAUNCHXL_F280049C --define=_FLASH --define=_STANDALONE --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="8.dsp/source/fpu32/utility/$(basename $(<F)).d_raw" --obj_directory="8.dsp/source/fpu32/utility" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


