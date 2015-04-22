################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/libs/gumbo/attribute.c \
../src/libs/gumbo/char_ref.c \
../src/libs/gumbo/error.c \
../src/libs/gumbo/parser.c \
../src/libs/gumbo/string_buffer.c \
../src/libs/gumbo/string_piece.c \
../src/libs/gumbo/tag.c \
../src/libs/gumbo/tokenizer.c \
../src/libs/gumbo/utf8.c \
../src/libs/gumbo/util.c \
../src/libs/gumbo/vector.c 

O_SRCS += \
../src/libs/gumbo/libgumbo_la-attribute.o \
../src/libs/gumbo/libgumbo_la-char_ref.o \
../src/libs/gumbo/libgumbo_la-error.o \
../src/libs/gumbo/libgumbo_la-parser.o \
../src/libs/gumbo/libgumbo_la-string_buffer.o \
../src/libs/gumbo/libgumbo_la-string_piece.o \
../src/libs/gumbo/libgumbo_la-tag.o \
../src/libs/gumbo/libgumbo_la-tokenizer.o \
../src/libs/gumbo/libgumbo_la-utf8.o \
../src/libs/gumbo/libgumbo_la-util.o \
../src/libs/gumbo/libgumbo_la-vector.o 

OBJS += \
./src/libs/gumbo/attribute.o \
./src/libs/gumbo/char_ref.o \
./src/libs/gumbo/error.o \
./src/libs/gumbo/parser.o \
./src/libs/gumbo/string_buffer.o \
./src/libs/gumbo/string_piece.o \
./src/libs/gumbo/tag.o \
./src/libs/gumbo/tokenizer.o \
./src/libs/gumbo/utf8.o \
./src/libs/gumbo/util.o \
./src/libs/gumbo/vector.o 

C_DEPS += \
./src/libs/gumbo/attribute.d \
./src/libs/gumbo/char_ref.d \
./src/libs/gumbo/error.d \
./src/libs/gumbo/parser.d \
./src/libs/gumbo/string_buffer.d \
./src/libs/gumbo/string_piece.d \
./src/libs/gumbo/tag.d \
./src/libs/gumbo/tokenizer.d \
./src/libs/gumbo/utf8.d \
./src/libs/gumbo/util.d \
./src/libs/gumbo/vector.d 


# Each subdirectory must supply rules for building sources it contributes
src/libs/gumbo/%.o: ../src/libs/gumbo/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


