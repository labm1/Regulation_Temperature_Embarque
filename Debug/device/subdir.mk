################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../device/system_MKL28Z7.c 

C_DEPS += \
./device/system_MKL28Z7.d 

OBJS += \
./device/system_MKL28Z7.o 


# Each subdirectory must supply rules for building sources it contributes
device/%.o: ../device/%.c device/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL28Z512VLL7 -DCPU_MKL28Z512VLL7_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\mlabe\Documents\MCUXpressoIDE_24.9.25\workspace\MKL28Z7_Project\board" -I"C:\Users\mlabe\Documents\MCUXpressoIDE_24.9.25\workspace\MKL28Z7_Project\source" -I"C:\Users\mlabe\Documents\MCUXpressoIDE_24.9.25\workspace\MKL28Z7_Project" -I"C:\Users\mlabe\Documents\MCUXpressoIDE_24.9.25\workspace\MKL28Z7_Project\drivers" -I"C:\Users\mlabe\Documents\MCUXpressoIDE_24.9.25\workspace\MKL28Z7_Project\component\serial_manager" -I"C:\Users\mlabe\Documents\MCUXpressoIDE_24.9.25\workspace\MKL28Z7_Project\CMSIS" -I"C:\Users\mlabe\Documents\MCUXpressoIDE_24.9.25\workspace\MKL28Z7_Project\utilities" -I"C:\Users\mlabe\Documents\MCUXpressoIDE_24.9.25\workspace\MKL28Z7_Project\component\uart" -I"C:\Users\mlabe\Documents\MCUXpressoIDE_24.9.25\workspace\MKL28Z7_Project\device" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-device

clean-device:
	-$(RM) ./device/system_MKL28Z7.d ./device/system_MKL28Z7.o

.PHONY: clean-device

