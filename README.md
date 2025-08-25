# AVR Programming Samples

This repository contains a collection of **sample projects in Embedded
C** based on the book *[AVR Programming: Learning to Write Software for
Hardware](https://www.noStarch.com/avrprogramming)*.\
The goal is to provide reference implementations and hands-on examples
for learning how to program AVR microcontrollers at the register level.

## 📂 Repository Structure

Each folder contains a self-contained project that demonstrates a
specific concept:

-   **`328p_Blink`** -- Classic LED blink example (GPIO basics).\
-   **`328p_ADC_Example`** -- Using the Analog-to-Digital Converter
    (ADC).\
-   **`328p_I2C_Driver_Sample`** -- Interfacing via I²C/TWI.\
-   **`328p_PWM`** -- Pulse Width Modulation for LED dimming or motor
    control.\
-   **`328p_Serial`** -- UART/serial communication with a computer.\
-   **`328p_Timer`** -- Using hardware timers and interrupts.\
-   *(and more depending on the repo contents)*

> All code is written for the **ATmega328P** (the same MCU used in the
> Arduino Uno), but can be adapted for other AVR chips with minimal
> changes.

## 🔧 Requirements

-   **Hardware**
    -   ATmega328P (or compatible AVR microcontroller)\
    -   Breadboard, LEDs, resistors, sensors, etc. (depending on the
        example)\
    -   AVR ISP programmer (e.g., USBasp, AVRISP mkII, or Arduino as
        ISP)
-   **Software**
    -   [AVR-GCC
        toolchain](https://www.microchip.com/mplab/avr-support/avr-and-arm-toolchains)\
    -   [AVRDude](https://www.nongnu.org/avrdude/) for flashing
        firmware\
    -   Optional: [AVRDUDE
        GUI](https://sourceforge.net/projects/avrdudegui/) or
        [PlatformIO](https://platformio.org/) for easier project
        management

## ▶️ Building and Uploading

From within a project directory:

``` bash
# Compile the code
avr-gcc -mmcu=atmega328p -Os -o main.elf main.c

# Convert to hex file
avr-objcopy -O ihex -R .eeprom main.elf main.hex

# Upload to chip (example using USBasp)
avrdude -c usbasp -p m328p -U flash:w:main.hex
```

Or, if a `Makefile` is included:

``` bash
make
make flash
```

## 🎯 Learning Goals

These examples cover the fundamentals of bare-metal AVR development:

-   GPIO and bit manipulation\
-   Timers and interrupts\
-   PWM for analog-like control\
-   ADC for sensor input\
-   Serial and I²C communication\
-   Writing reusable drivers for peripherals

## 📚 Reference

-   *AVR Programming: Learning to Write Software for Hardware* -- Elliot
    Williams\
-   [AVR-GCC Documentation](https://gcc.gnu.org/wiki/avr-gcc)\
-   [AVR Libc Manual](https://www.nongnu.org/avr-libc/user-manual/)
