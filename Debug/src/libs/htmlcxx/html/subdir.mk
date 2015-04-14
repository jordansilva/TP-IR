################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/libs/htmlcxx/html/CharsetConverter.cc \
../src/libs/htmlcxx/html/Extensions.cc \
../src/libs/htmlcxx/html/Node.cc \
../src/libs/htmlcxx/html/ParserDom.cc \
../src/libs/htmlcxx/html/ParserSax.cc \
../src/libs/htmlcxx/html/Uri.cc \
../src/libs/htmlcxx/html/utils.cc 

CC_DEPS += \
./src/libs/htmlcxx/html/CharsetConverter.d \
./src/libs/htmlcxx/html/Extensions.d \
./src/libs/htmlcxx/html/Node.d \
./src/libs/htmlcxx/html/ParserDom.d \
./src/libs/htmlcxx/html/ParserSax.d \
./src/libs/htmlcxx/html/Uri.d \
./src/libs/htmlcxx/html/utils.d 

OBJS += \
./src/libs/htmlcxx/html/CharsetConverter.o \
./src/libs/htmlcxx/html/Extensions.o \
./src/libs/htmlcxx/html/Node.o \
./src/libs/htmlcxx/html/ParserDom.o \
./src/libs/htmlcxx/html/ParserSax.o \
./src/libs/htmlcxx/html/Uri.o \
./src/libs/htmlcxx/html/utils.o 


# Each subdirectory must supply rules for building sources it contributes
src/libs/htmlcxx/html/%.o: ../src/libs/htmlcxx/html/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/jordan/documents/ir/ir/src/libs/zlib" -I"/home/jordan/documents/ir/ir/src/libs/htmlcxx" -O3 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


