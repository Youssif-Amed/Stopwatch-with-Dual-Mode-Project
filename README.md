# Stopwatch with Dual Mode (Increment and Countdown) Using ATmega32 and Seven-Segment Display

## Project Overview

This project implements a versatile digital stopwatch with two operational modes: counting up (Increment Mode) and counting down (Countdown Mode). The system is built using an ATmega32 microcontroller, six multiplexed seven-segment displays, and push buttons for user interaction. The stopwatch can be reset, paused, and resumed, making it highly functional for time-tracking purposes.

## Features

- **Increment Mode**: The stopwatch counts upwards from zero, displaying hours, minutes, and seconds.
- **Countdown Mode**: A user-defined countdown timer that triggers an alarm when the time reaches zero.
- **Reset**: Resets the stopwatch to zero.
- **Pause and Resume**: Pauses and resumes the stopwatch at the current time.
- **Mode Toggle**: Easily switch between Increment and Countdown modes.

## Components Used

- **Microcontroller**: ATmega32
- **Display**: Six multiplexed seven-segment displays (common anode)
- **Push Buttons**:
  - Reset, Pause, Resume, Mode Toggle
  - Time Adjustment (Increment/Decrement Hours, Minutes, Seconds)
- **Alarm/Buzzer**: Activated when the countdown reaches zero
- **LED Indicators**: Shows whether the stopwatch is in Increment (Red LED) or Countdown (Yellow LED) mode

## Hardware Setup

1. **Microcontroller**: ATmega32 operating at 16 MHz.
2. **Display**: Six multiplexed seven-segment displays driven by 7447 BCD to seven-segment decoder.
3. **Input**: 10 push buttons for control (reset, pause, resume, mode toggle, and time adjustments).
4. **External Interrupts**: Configured to handle key stopwatch functions:
   - **INT0**: Resets the stopwatch.
   - **INT1**: Pauses the stopwatch.
   - **INT2**: Resumes the stopwatch.
5. **Buzzer**: Alerts the user when the countdown reaches zero.

## Operation

- **Increment Mode**: Default mode. The time counts upwards from zero and is displayed in hours, minutes, and seconds. The red LED indicates Increment Mode.
- **Countdown Mode**: Triggered by the mode toggle button. The user can set the countdown start time, and an alarm will sound when the timer hits zero. The yellow LED indicates Countdown Mode.

## System Requirements

- ATmega32 microcontroller (16 MHz)
- Six multiplexed seven-segment displays
- 7447 BCD to seven-segment decoder
- Push buttons for control and time adjustment
- External Interrupts (INT0, INT1, INT2)
- Buzzer for alarm functionality

## Acknowledgments

This project is part of the Standard Embedded Systems Diploma under the supervision of **Eng. Mohamed Tarek**.
