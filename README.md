# PIC18F4520 Peripheral Control Project

## Overview
This project implements various peripheral controls for the PIC18F4520 microcontroller, including LED control, ADC conversion, UART communication, and servo motor control via PWM.

## Features
- LED control with 4 output pins
- Button interrupt handling
- ADC conversion with interrupt support
- UART communication (1200 baud rate)
- Servo motor control using PWM
- Configurable interrupt priorities

## Hardware Requirements
- PIC18F4520 microcontroller
- LEDs connected to PORTA (RA1-RA4)
- Push button connected to RB0
- Analog input on RA0
- UART communication on RC6 (TX) and RC7 (RX)
- Servo motor on RC2 (PWM output)


## Pin Configuration
- RA1-RA4: LED outputs
- RB0: Push button input (interrupt-enabled)
- RA0: Analog input
- RC6: UART TX
- RC7: UART RX
- RC2: Servo motor control (PWM)


## Configuration
Can be modified at `utils/config.h`
- Operating frequency: 4MHz internal oscillator
- UART baud rate: 1200
- ADC configuration: Left-justified result
- PWM period: 20ms (suitable for standard servo motors)

## Project Structure
```
├── main.c              # Main program file
├── utils/
│   ├── adc.c/h        # ADC configuration and control
│   ├── ccp.c/h        # PWM configuration and control
│   ├── config.h       # Global configuration defines
│   ├── interrupt_manager.c/h # Interrupt handling
│   ├── led.c/h        # LED control functions
│   ├── settings.c/h   # Device configuration and initialization
│   ├── timer.c/h      # Timer configuration
│   └── uart.c/h       # UART communication
```

## Setup and Installation
1. Clone this repository
2. Configure your PIC programmer
3. Build and flash the program to your PIC18F4520

## Usage
- The system initializes all configured peripherals on startup
- Button press toggles LED state and servo position between -90° and +90°
- ADC continuously monitors analog input on RA0
- UART communication is available at 1200 baud rate

## Contributing
Feel free to submit issues and pull requests.
