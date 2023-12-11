################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Math.c \
../src/Socket_Utils.c \
../src/UDPServer.c 

C_DEPS += \
./src/Math.d \
./src/Socket_Utils.d \
./src/UDPServer.d 

OBJS += \
./src/Math.o \
./src/Socket_Utils.o \
./src/UDPServer.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/Math.d ./src/Math.o ./src/Socket_Utils.d ./src/Socket_Utils.o ./src/UDPServer.d ./src/UDPServer.o

.PHONY: clean-src

