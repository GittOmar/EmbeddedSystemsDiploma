# PIC18F6420 Microcontroller

The **PIC18F6420** is a high-performance 8-bit microcontroller from **Microchip’s PIC18 family**, designed for applications that demand large program memory, multiple peripherals, and robust performance. With a 10 MIPS execution rate, flexible analog/digital peripherals, and advanced power management features, it is a versatile choice for embedded system design.

---

## 🔹 Key Specifications

- **Core Architecture**
  - 8-bit PIC18 RISC architecture
  - Up to **40 MHz** operation (10 MIPS)
  - Instruction set optimized for C compilers
  - 31-level hardware stack with overflow/underflow protection

- **Memory**
  - **64 KB Flash Program Memory** (self-programmable)
  - **3.8 KB SRAM**
  - **1 KB EEPROM** for non-volatile data storage

- **I/O**
  - 53 I/O pins (individually configurable)
  - Multiple alternate pin functions
  - High-current source/sink capability on PORTB

- **Timers**
  - 4 × 16-bit timers
  - 1 × 8-bit timer
  - Real-Time Clock (RTC) support with Timer1

- **Communication Modules**
  - 2 × USART (supports RS-232, RS-485, LIN)
  - MSSP module (supports **SPI** and **I²C** in Master/Slave modes)
  - Enhanced Capture/Compare/PWM (ECCP) module

- **Analog Features**
  - 12-channel, 10-bit Analog-to-Digital Converter (ADC)
  - Programmable voltage reference
  - Comparator module

- **Special Features**
  - Watchdog Timer (WDT) with programmable prescaler
  - Brown-out Reset (BOR)
  - In-Circuit Serial Programming (ICSP™) and In-Circuit Debugging (ICD)
  - Enhanced Power-Save and Sleep modes

---

## 🔹 Applications

- Industrial automation & process control  
- Motor control and robotics  
- Consumer electronics  
- Automotive modules  
- Data acquisition systems  
- Communication interface controllers  

---

## 🔹 Pin Diagram

Below is the pinout diagram for the **PIC18F microcontroller family** (PIC18F4520 / PIC18F6420 compatible layout):

![PIC18F Microcontroller Pin Diagram](https://robosumo.wordpress.com/wp-content/uploads/2012/01/pic18f-pin-numbers-and-labels.jpg)

*Source: robosumo.wordpress.com*

---

## 🔹 Development Tools

To work with the PIC18F6420, you can use the following toolchains:

- **Compiler:** [MPLAB XC8](https://www.microchip.com/en-us/tools-resources/develop/mplab-xc-compilers)  
- **IDE:** [MPLAB X IDE](https://www.microchip.com/en-us/tools-resources/develop/mplab-x-ide)  
- **Programmer/Debugger:** PICkit™ 3 / PICkit™ 4 / ICD 3 / SNAP  

Example workflow:
```bash
# Compile with XC8
xc8 --chip=18F6420 main.c

# Upload using PICkit
pk3cmd -P18F6420 -Fdist/main.hex -M
