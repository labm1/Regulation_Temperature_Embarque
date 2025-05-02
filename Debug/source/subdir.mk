################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/MKL28Z7_Project.c \
../source/ModuleDEL.c \
../source/ModuleLCD.c \
../source/ModuleTemperature.c \
../source/ModuleVentilateur.c \
../source/bmp280.c \
../source/mtb.c \
../source/semihost_hardfault.c 

C_DEPS += \
./source/MKL28Z7_Project.d \
./source/ModuleDEL.d \
./source/ModuleLCD.d \
./source/ModuleTemperature.d \
./source/ModuleVentilateur.d \
./source/bmp280.d \
./source/mtb.d \
./source/semihost_hardfault.d 

OBJS += \
./source/MKL28Z7_Project.o \
./source/ModuleDEL.o \
./source/ModuleLCD.o \
./source/ModuleTemperature.o \
./source/ModuleVentilateur.o \
./source/bmp280.o \
./source/mtb.o \
./source/semihost_hardfault.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL28Z512VLL7 -DCPU_MKL28Z512VLL7_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\mlabe\Documents\MCUXpressoIDE_24.9.25\workspace\MKL28Z7_Project\board" -I"C:\Users\mlabe\Documents\MCUXpressoIDE_24.9.25\workspace\MKL28Z7_Project\source" -I"C:\Users\mlabe\Documents\MCUXpressoIDE_24.9.25\workspace\MKL28Z7_Project" -I"C:\Users\mlabe\Documents\MCUXpressoIDE_24.9.25\workspace\MKL28Z7_Project\drivers" -I"C:\Users\mlabe\Documents\MCUXpressoIDE_24.9.25\workspace\MKL28Z7_Project\component\serial_manager" -I"C:\Users\mlabe\Documents\MCUXpressoIDE_24.9.25\workspace\MKL28Z7_Project\CMSIS" -I"C:\Users\mlabe\Documents\MCUXpressoIDE_24.9.25\workspace\MKL28Z7_Project\utilities" -I"C:\Users\mlabe\Documents\MCUXpressoIDE_24.9.25\workspace\MKL28Z7_Project\component\uart" -I"C:\Users\mlabe\Documents\MCUXpressoIDE_24.9.25\workspace\MKL28Z7_Project\device" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/MKL28Z7_Project.d ./source/MKL28Z7_Project.o ./source/ModuleDEL.d ./source/ModuleDEL.o ./source/ModuleLCD.d ./source/ModuleLCD.o ./source/ModuleTemperature.d ./source/ModuleTemperature.o ./source/ModuleVentilateur.d ./source/ModuleVentilateur.o ./source/bmp280.d ./source/bmp280.o ./source/mtb.d ./source/mtb.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o

.PHONY: clean-source

