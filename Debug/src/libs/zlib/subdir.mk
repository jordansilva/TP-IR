################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/libs/zlib/adler32.c \
../src/libs/zlib/compress.c \
../src/libs/zlib/crc32.c \
../src/libs/zlib/deflate.c \
../src/libs/zlib/gzclose.c \
../src/libs/zlib/gzlib.c \
../src/libs/zlib/gzread.c \
../src/libs/zlib/gzwrite.c \
../src/libs/zlib/infback.c \
../src/libs/zlib/inffast.c \
../src/libs/zlib/inflate.c \
../src/libs/zlib/inftrees.c \
../src/libs/zlib/trees.c \
../src/libs/zlib/uncompr.c \
../src/libs/zlib/zutil.c 

OBJS += \
./src/libs/zlib/adler32.o \
./src/libs/zlib/compress.o \
./src/libs/zlib/crc32.o \
./src/libs/zlib/deflate.o \
./src/libs/zlib/gzclose.o \
./src/libs/zlib/gzlib.o \
./src/libs/zlib/gzread.o \
./src/libs/zlib/gzwrite.o \
./src/libs/zlib/infback.o \
./src/libs/zlib/inffast.o \
./src/libs/zlib/inflate.o \
./src/libs/zlib/inftrees.o \
./src/libs/zlib/trees.o \
./src/libs/zlib/uncompr.o \
./src/libs/zlib/zutil.o 

C_DEPS += \
./src/libs/zlib/adler32.d \
./src/libs/zlib/compress.d \
./src/libs/zlib/crc32.d \
./src/libs/zlib/deflate.d \
./src/libs/zlib/gzclose.d \
./src/libs/zlib/gzlib.d \
./src/libs/zlib/gzread.d \
./src/libs/zlib/gzwrite.d \
./src/libs/zlib/infback.d \
./src/libs/zlib/inffast.d \
./src/libs/zlib/inflate.d \
./src/libs/zlib/inftrees.d \
./src/libs/zlib/trees.d \
./src/libs/zlib/uncompr.d \
./src/libs/zlib/zutil.d 


# Each subdirectory must supply rules for building sources it contributes
src/libs/zlib/%.o: ../src/libs/zlib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


