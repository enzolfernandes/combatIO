# Combat I/O ⚔️
## Project Overview

<img src="https://img.shields.io/badge/language-C++-00599C?logo=c++" alt="C/C++">

<img src="https://img.shields.io/badge/microcontroller-ESP32-2D7F5D?logo=Espressif" alt="ESP32">

<img src="https://img.shields.io/badge/build-PlatformIO-3A5FCD?logo=platform.io" alt="PlatformIO">

<img src="https://img.shields.io/badge/framework-Arduino-00979D?logo=arduino" alt="Arduino">

CombatIO is a generic I/O control firmware for competitive combat and sumo robotics built around the ESP32 DevKit V1. The project is structured for PlatformIO and designed to provide a professional embedded control stack for fast actuation, mode selection, and remote operation in high-impact robotics applications.

This firmware abstracts motor actuation, joystick input, and autonomous behavior into separate modules to support rapid prototyping on belt-driven combat rigs and sumo push robots.

## Tech Stack & Tools

- C / C++
- ESP32 DevKit V1
- PlatformIO
- Arduino framework
- ESP32 PWM timer subsystem

## Hardware Architecture & Pinout

The code architecture indicates a motor-centric ESP32 control board with the following inferred hardware design:

- `ESP32PWM::allocateTimer(0..3)` allocates all four ESP32 PWM timers.
  - This strongly suggests support for up to four independent PWM outputs.
  - Typical usage is dual H-bridge motor drivers or a 4-channel motor driver arrangement.
- The board is based on the ESP32 DevKit V1, so sensor and actuator I/O are routed through the DevKit GPIO matrix.
- The firmware modules are decoupled:
  - `joystick.cpp` handles remote control inputs.
  - `motors.cpp` configures PWM and motor driver outputs.
  - `controlled.cpp` runs teleoperated logic.
  - `autonomous.cpp` runs autonomous control sequences.
- Compile-time flags are used for behavior selection:
  - `_DEBUG_` enables serial debug output at `115200`.
  - `_AUTONOMOUS_` enables autonomous operation and PS4 controller feedback.

## Firmware Features

- Modular control topology
  - `setup()` initializes joystick and motor subsystems.
  - `loop()` selects either teleoperation or autonomous mode.
- PWM-driven motor control
  - Uses ESP32 PWM timers 0, 1, 2, and 3 for precise motor actuation.
  - Likely supports independent left/right or multi-motor drive trains.
- Remote control interface
  - `joystickSetup()` and `controlledLoop()` implement human-operated control.
  - The code structure separates I/O acquisition from motor commands.
- Autonomous mode support
  - `autonomousSetup()` and `autonomousLoop()` provide an alternate state machine for self-directed behavior.
  - PS4 controller integration is present via `PS4.setLed(pink)` and `PS4.sendToController()`, indicating Bluetooth/HID status signaling.
- Debug and diagnostics
  - Conditional serial logging when `_DEBUG_` is defined.
  - The firmware is prepared for iterative testing within PlatformIO.

## Getting Started

1. Install PlatformIO and the ESP32 development environment.
2. Open the repository in VS Code.
3. Build the firmware:

```bash
pio run -e esp32doit-devkit-v1
```

4. Flash the firmware to the ESP32 DevKit V1:

```bash
pio run -e esp32doit-devkit-v1 -t upload
```

5. Optionally, use VS Code PlatformIO commands:
   - `PlatformIO: Build`
   - `PlatformIO: Upload`

## Project Structure

- platformio.ini — ESP32 PlatformIO environment definition
- main.cpp — Main runtime, mode selection, and peripheral initialization
- `src/joystick.cpp` — Joystick/remote control input handling
- `src/motors.cpp` — Motor driver PWM setup and output abstraction
- `src/controlled.cpp` — Teleoperated control loop
- `src/autonomous.cpp` — Autonomous control loop and state transitions
- include — Shared headers and board definitions
- lib — External libraries and reusable utility modules