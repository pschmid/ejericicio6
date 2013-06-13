################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Cliente.cpp \
../Consumidor.cpp \
../Productor.cpp \
../Servidor.cpp 

CC_SRCS += \
../main1.cc \
../main2.cc 

OBJS += \
./Cliente.o \
./Consumidor.o \
./Productor.o \
./Servidor.o \
./main1.o \
./main2.o 

CC_DEPS += \
./main1.d \
./main2.d 

CPP_DEPS += \
./Cliente.d \
./Consumidor.d \
./Productor.d \
./Servidor.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DEJEMPLO_2 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

%.o: ../%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DEJEMPLO_2 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


