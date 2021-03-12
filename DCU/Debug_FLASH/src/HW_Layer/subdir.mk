################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/HW_Layer/CANDriver.c \
../src/HW_Layer/SensorManager.c 

OBJS += \
./src/HW_Layer/CANDriver.o \
./src/HW_Layer/SensorManager.o 

C_DEPS += \
./src/HW_Layer/CANDriver.d \
./src/HW_Layer/SensorManager.d 


# Each subdirectory must supply rules for building sources it contributes
src/HW_Layer/%.o: ../src/HW_Layer/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/HW_Layer/CANDriver.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


