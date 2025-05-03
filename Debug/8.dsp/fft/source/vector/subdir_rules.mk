################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
8.dsp/fft/source/vector/%.obj: ../8.dsp/fft/source/vector/%.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccs1250/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu0 --fp_mode=relaxed --include_path="D:/ti/Project/F280049C_Temp" --include_path="D:/ti/ccs1250/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --include_path="D:/ti/Project/F280049C_Temp/3.device/include" --include_path="D:/ti/Project/F280049C_Temp/4.common/include" --include_path="D:/ti/Project/F280049C_Temp/5.headers/include" --advice:performance=all --define=_LAUNCHXL_F280049C -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="8.dsp/fft/source/vector/$(basename $(<F)).d_raw" --obj_directory="8.dsp/fft/source/vector" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

8.dsp/fft/source/vector/%.obj: ../8.dsp/fft/source/vector/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"D:/ti/ccs1250/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu0 --fp_mode=relaxed --include_path="D:/ti/Project/F280049C_Temp" --include_path="D:/ti/ccs1250/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --include_path="D:/ti/Project/F280049C_Temp/3.device/include" --include_path="D:/ti/Project/F280049C_Temp/4.common/include" --include_path="D:/ti/Project/F280049C_Temp/5.headers/include" --advice:performance=all --define=_LAUNCHXL_F280049C -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="8.dsp/fft/source/vector/$(basename $(<F)).d_raw" --obj_directory="8.dsp/fft/source/vector" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


