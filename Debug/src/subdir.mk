################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Ball.c \
../src/Display.c \
../src/GPIO.c \
../src/Paddle.c \
../src/RCC.c \
../src/Setup.c \
../src/TIMER.c \
../src/USART.c \
../src/main.c \
../src/stm32f4xx_it.c \
../src/syscalls.c \
../src/system_stm32f4xx.c 

OBJS += \
./src/Ball.o \
./src/Display.o \
./src/GPIO.o \
./src/Paddle.o \
./src/RCC.o \
./src/Setup.o \
./src/TIMER.o \
./src/USART.o \
./src/main.o \
./src/stm32f4xx_it.o \
./src/syscalls.o \
./src/system_stm32f4xx.o 

C_DEPS += \
./src/Ball.d \
./src/Display.d \
./src/GPIO.d \
./src/Paddle.d \
./src/RCC.d \
./src/Setup.d \
./src/TIMER.d \
./src/USART.d \
./src/main.d \
./src/stm32f4xx_it.d \
./src/syscalls.d \
./src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F411RETx -DNUCLEO_F411RE -DDEBUG -DSTM32F411xE -DUSE_HAL_DRIVER -I"C:/Users/juanp/Documents/RTOS/Brcik-Breaker-Game-2/HAL_Driver/Inc/Legacy" -I"C:/Users/juanp/Documents/RTOS/Brcik-Breaker-Game-2/Utilities/STM32F4xx-Nucleo" -I"C:/Users/juanp/Documents/RTOS/Brcik-Breaker-Game-2/inc" -I"C:/Users/juanp/Documents/RTOS/Brcik-Breaker-Game-2/CMSIS/device" -I"C:/Users/juanp/Documents/RTOS/Brcik-Breaker-Game-2/CMSIS/core" -I"C:/Users/juanp/Documents/RTOS/Brcik-Breaker-Game-2/HAL_Driver/Inc" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


