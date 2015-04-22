################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/index/Dictionary.cpp \
../src/index/IndexDocument.cpp \
../src/index/Indexer.cpp 

OBJS += \
./src/index/Dictionary.o \
./src/index/IndexDocument.o \
./src/index/Indexer.o 

CPP_DEPS += \
./src/index/Dictionary.d \
./src/index/IndexDocument.d \
./src/index/Indexer.d 


# Each subdirectory must supply rules for building sources it contributes
src/index/%.o: ../src/index/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/jordan/documents/ir/ir/src/libs/zlib" -I"/home/jordan/documents/ir/ir/src/libs/htmlcxx" -O3 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


