################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: GNU Compiler'
	"/Applications/ti/ccs920/ccs/tools/compiler/msp430-gcc-8.3.0.16_macos/bin/msp430-elf-gcc-8.3.0" -c -mmcu=msp430f5529 -mhwmult=f5series -I"/Applications/ti/ccs920/ccs/ccs_base/msp430/include_gcc" -I"/Users/igorsantos/workspace_v9/RTOS_LAB1_EX3" -I"/Applications/ti/ccs920/ccs/tools/compiler/msp430-gcc-8.3.0.16_macos/msp430-elf/include" -Og -g -gdwarf-3 -gstrict-dwarf -Wall -mlarge -mcode-region=none -mdata-region=none -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


