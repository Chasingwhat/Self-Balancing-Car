################################################################################
# Automatically-generated file. Do not edit!
################################################################################

#Progress monitor hint: 18
first : all
-include ../makefile.init

# This file contains definitions of environment variables used in the makefiles and .args files if exist.
-include makefile.local

RM := "$(GNU_Make_Install_DirEnv)/rm" -f

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include User\ Modules/subdir.mk
-include Sources/subdir.mk
-include Project\ Settings/Startup_Code/subdir.mk
-include Generated_Code/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
sdm_pROM_xRAM.elf \

EXECUTABLES_QUOTED += \
"sdm_pROM_xRAM.elf" \

EXECUTABLES_OS_FORMAT += \
sdm_pROM_xRAM.elf \


# All Target
all: warning-messages explicit-dependencies sdm_pROM_xRAM.elf

# Tool invocations
sdm_pROM_xRAM.elf: $(OBJS) $(USER_OBJS) ../Project\ Settings/Linker_Files/smm_pROM_xRAM.cmd
	@echo 'Building target: $@'
	@echo 'Executing target #19 $@'
	@echo 'Invoking: DSC Linker'
	"$(DSC_ToolsDirEnv)/mwld56800e" -o "sdm_pROM_xRAM.elf" @@"sdm_pROM_xRAM.args"  $(USER_OBJS_QUOTED)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(S_DEPS_QUOTED) $(CPP_DEPS_QUOTED) $(CC_DEPS_QUOTED) "./*/*.obj" "./*/*/*.obj"  $(S_UPPER_DEPS_QUOTED) $(CXX_DEPS_QUOTED) "./*/*/*.d"  $(ASM_UPPER_DEPS_QUOTED) $(C_UPPER_DEPS_QUOTED) $(C++_DEPS_QUOTED) $(EXECUTABLES_QUOTED) "./*/*.d"  $(ProjDirPath)/smm pROM-xRAM/sdm_pROM_xRAM.elf
	-@echo ' '

.PHONY: all clean dependents explicit-dependencies warning-messages
.SECONDARY:

-include ../makefile.targets

explicit-dependencies: ../Project\ Settings/Linker_Files/smm_pROM_xRAM.cmd 

warning-messages: 

