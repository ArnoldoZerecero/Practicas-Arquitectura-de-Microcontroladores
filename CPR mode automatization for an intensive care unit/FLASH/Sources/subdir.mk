################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/ADC.c" \
"../Sources/MISCELANEO.c" \
"../Sources/PIT.c" \
"../Sources/PWM.c" \
"../Sources/main.c" \
"../Sources/sa_mtb.c" \

C_SRCS += \
../Sources/ADC.c \
../Sources/MISCELANEO.c \
../Sources/PIT.c \
../Sources/PWM.c \
../Sources/main.c \
../Sources/sa_mtb.c \

OBJS += \
./Sources/ADC.o \
./Sources/MISCELANEO.o \
./Sources/PIT.o \
./Sources/PWM.o \
./Sources/main.o \
./Sources/sa_mtb.o \

C_DEPS += \
./Sources/ADC.d \
./Sources/MISCELANEO.d \
./Sources/PIT.d \
./Sources/PWM.d \
./Sources/main.d \
./Sources/sa_mtb.d \

OBJS_QUOTED += \
"./Sources/ADC.o" \
"./Sources/MISCELANEO.o" \
"./Sources/PIT.o" \
"./Sources/PWM.o" \
"./Sources/main.o" \
"./Sources/sa_mtb.o" \

C_DEPS_QUOTED += \
"./Sources/ADC.d" \
"./Sources/MISCELANEO.d" \
"./Sources/PIT.d" \
"./Sources/PWM.d" \
"./Sources/main.d" \
"./Sources/sa_mtb.d" \

OBJS_OS_FORMAT += \
./Sources/ADC.o \
./Sources/MISCELANEO.o \
./Sources/PIT.o \
./Sources/PWM.o \
./Sources/main.o \
./Sources/sa_mtb.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/ADC.o: ../Sources/ADC.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/ADC.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/ADC.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/MISCELANEO.o: ../Sources/MISCELANEO.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/MISCELANEO.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/MISCELANEO.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/PIT.o: ../Sources/PIT.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/PIT.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/PIT.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/PWM.o: ../Sources/PWM.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/PWM.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/PWM.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main.o: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/main.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/sa_mtb.o: ../Sources/sa_mtb.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/sa_mtb.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/sa_mtb.o"
	@echo 'Finished building: $<'
	@echo ' '


