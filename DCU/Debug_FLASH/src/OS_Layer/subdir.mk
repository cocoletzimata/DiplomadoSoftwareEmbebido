################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/OS_Layer/Project_Tasks.c \
../src/OS_Layer/rtos.c 

OBJS += \
./src/OS_Layer/Project_Tasks.o \
./src/OS_Layer/rtos.o 

C_DEPS += \
./src/OS_Layer/Project_Tasks.d \
./src/OS_Layer/rtos.d 


# Each subdirectory must supply rules for building sources it contributes
src/OS_Layer/%.o: ../src/OS_Layer/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/OS_Layer/Project_Tasks.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


