################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/libs/reader/CollectionReader.cpp \
../src/libs/reader/Document.cpp 

OBJS += \
./src/libs/reader/CollectionReader.o \
./src/libs/reader/Document.o 

CPP_DEPS += \
./src/libs/reader/CollectionReader.d \
./src/libs/reader/Document.d 


# Each subdirectory must supply rules for building sources it contributes
src/libs/reader/%.o: ../src/libs/reader/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/jordan/documents/ir/ir/src/libs/zlib" -I"/home/jordan/documents/ir/ir/src/libs/htmlcxx" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


