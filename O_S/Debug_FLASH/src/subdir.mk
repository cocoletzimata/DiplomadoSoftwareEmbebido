################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ADC_Task.c \
../src/helper_functions.c \
../src/main.c \
../src/rtos.c 

OBJS += \
./src/ADC_Task.o \
./src/helper_functions.o \
./src/main.o \
./src/rtos.o 

C_DEPS += \
./src/ADC_Task.d \
./src/helper_functions.d \
./src/main.d \
./src/rtos.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/ADC_Task.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


