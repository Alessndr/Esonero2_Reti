################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Socket_Utils.c \
../src/UDPClient.c 

C_DEPS += \
./src/Socket_Utils.d \
./src/UDPClient.d 

OBJS += \
./src/Socket_Utils.o \
./src/UDPClient.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/Socket_Utils.d ./src/Socket_Utils.o ./src/UDPClient.d ./src/UDPClient.o

.PHONY: clean-src

