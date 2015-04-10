################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/parser/TextParser.cpp 

OBJS += \
./src/parser/TextParser.o 

CPP_DEPS += \
./src/parser/TextParser.d 


# Each subdirectory must supply rules for building sources it contributes
src/parser/%.o: ../src/parser/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/jordan/documents/ir/ir/src/libs/zlib" -I"/home/jordan/documents/ir/ir/src/libs/htmlcxx" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


