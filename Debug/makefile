################################################################################
# Automatically-generated file. Do not edit!
################################################################################

CG_TOOL_ROOT := /Applications/ti/ccs920/ccs/tools/compiler/msp430-gcc-8.3.0.16_macos

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./fifo.o" \
"./kernel.o" \
"./main.o" \
-T"../msp430f5529.ld" \
$(GEN_CMDS__FLAG) \
-Wl,--start-group \
-lgcc \
-lc \
-Wl,--end-group \

-include ../makefile.init

RM := rm -rf
RMDIR := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
RTOS_LAB2_EX1.out \

EXE_OUTPUTS__QUOTED += \
"RTOS_LAB2_EX1.out" \

BIN_OUTPUTS += \
RTOS_LAB2_EX1.hex \

BIN_OUTPUTS__QUOTED += \
"RTOS_LAB2_EX1.hex" \


# All Target
all: $(OBJS) $(LD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "RTOS_LAB2_EX1.out"

# Tool invocations
RTOS_LAB2_EX1.out: $(OBJS) $(LD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: GNU Linker'
	"/Applications/ti/ccs920/ccs/tools/compiler/msp430-gcc-8.3.0.16_macos/bin/msp430-elf-gcc-8.3.0" -mhwmult=f5series -Og -g -gdwarf-3 -gstrict-dwarf -Wall -mcode-region=none -mlarge -mdata-region=none -Wl,-Map,"RTOS_LAB2_EX1.map" -Wl,--gc-sections -L"/Applications/ti/ccs920/ccs/ccs_base/msp430/include_gcc" -o"RTOS_LAB2_EX1.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

RTOS_LAB2_EX1.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: GNU Objcopy Utility'
	"/Applications/ti/ccs920/ccs/tools/compiler/msp430-gcc-8.3.0.16_macos/bin/msp430-elf-objcopy"  $(EXE_OUTPUTS__QUOTED) "RTOS_LAB2_EX1.hex"
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "fifo.o" "kernel.o" "main.o" 
	-$(RM) "fifo.d" "kernel.d" "main.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

