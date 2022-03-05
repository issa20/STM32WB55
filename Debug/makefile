################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Utilities/sequencer/subdir.mk
-include Utilities/lpm/tiny_lpm/subdir.mk
-include STM32_WPAN/Target/subdir.mk
-include STM32_WPAN/App/subdir.mk
-include Middlewares/ST/STM32_WPAN/utilities/subdir.mk
-include Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/tl/subdir.mk
-include Middlewares/ST/STM32_WPAN/interface/patterns/ble_thread/shci/subdir.mk
-include Middlewares/ST/STM32_WPAN/ble/svc/Src/subdir.mk
-include Middlewares/ST/STM32_WPAN/ble/core/template/subdir.mk
-include Middlewares/ST/STM32_WPAN/ble/core/auto/subdir.mk
-include Drivers/STM32WBxx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := BLE_Profil
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
BLE_Profil.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
BLE_Profil.list \

OBJCOPY_BIN += \
BLE_Profil.bin \


# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: BLE_Profil.elf secondary-outputs

# Tool invocations
BLE_Profil.elf: $(OBJS) $(USER_OBJS) C:\Users\issa\Downloads\BLE_Profil\STM32WB55RGVX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "BLE_Profil.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\issa\Downloads\BLE_Profil\STM32WB55RGVX_FLASH.ld" --specs=nosys.specs -Wl,-Map="BLE_Profil.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

BLE_Profil.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "BLE_Profil.list"
	@echo 'Finished building: $@'
	@echo ' '

BLE_Profil.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "BLE_Profil.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) BLE_Profil.bin BLE_Profil.elf BLE_Profil.list default.size.stdout
	-@echo ' '

post-build:
	arm-none-eabi-objcopy -O ihex BLE_Profil.elf BLE_Profil.hex
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified post-build

-include ../makefile.targets
