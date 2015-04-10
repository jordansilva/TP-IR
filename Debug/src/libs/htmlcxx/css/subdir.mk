################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/libs/htmlcxx/css/parser_pp.cc 

C_SRCS += \
../src/libs/htmlcxx/css/css_lex.c \
../src/libs/htmlcxx/css/css_syntax.c \
../src/libs/htmlcxx/css/parser.c 

CC_DEPS += \
./src/libs/htmlcxx/css/parser_pp.d 

OBJS += \
./src/libs/htmlcxx/css/css_lex.o \
./src/libs/htmlcxx/css/css_syntax.o \
./src/libs/htmlcxx/css/parser.o \
./src/libs/htmlcxx/css/parser_pp.o 

C_DEPS += \
./src/libs/htmlcxx/css/css_lex.d \
./src/libs/htmlcxx/css/css_syntax.d \
./src/libs/htmlcxx/css/parser.d 


# Each subdirectory must supply rules for building sources it contributes
src/libs/htmlcxx/css/%.o: ../src/libs/htmlcxx/css/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/libs/htmlcxx/css/%.o: ../src/libs/htmlcxx/css/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/jordan/documents/ir/ir/src/libs/zlib" -I"/home/jordan/documents/ir/ir/src/libs/htmlcxx" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


