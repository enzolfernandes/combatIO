# CombatIO: Embedded Control Firmware ⚔️

![C++](https://img.shields.io/badge/language-C++-00599C?style=for-the-badge&logo=c%2B%2B)
![ESP32](https://img.shields.io/badge/microcontroller-ESP32-2D7F5D?style=for-the-badge&logo=espressif)
![PlatformIO](https://img.shields.io/badge/build-PlatformIO-3A5FCD?style=for-the-badge&logo=platformio)
![Bluetooth](https://img.shields.io/badge/comms-Bluetooth-0082FC?style=for-the-badge&logo=bluetooth)
![EasyEDA](https://img.shields.io/badge/Hardware-EasyEDA-00B2A9?style=for-the-badge)

## 📌 Project Overview
**CombatIO** is a modular, high-performance C++ firmware and hardware project built for competitive combat and sumo robotics. Engineered around the **ESP32 DevKit V1** and structured via **PlatformIO**, this project provides a robust embedded control stack designed for ultra-fast actuation, dynamic mode selection, and wireless remote operation in high-impact environments.

The system abstracts motor actuation, wireless telemetry, and autonomous state machines into decoupled modules, supporting rapid prototyping for both belt-driven combat rigs and autonomous sumo push robots.

---

## ⚙️ Hardware Architecture & Peripheral Control

The hardware abstraction layer is heavily optimized for precise motor drive and seamless wireless communication. The custom PCB design files are included in the repository.

* **Hardware Timer Allocation:** Dynamically allocates all four ESP32 PWM hardware timers (`ESP32PWM::allocateTimer(0..3)`), ensuring zero-jitter, independent PWM generation for dual H-bridge or 4-channel motor driver topologies.
* **Wireless Telemetry (Bluetooth):** Integrates seamless communication with PS4 controllers for teleoperation, featuring real-time HID status signaling (e.g., LED color feedback based on robot state).
* **I/O Matrix Routing:** Leverages the ESP32 GPIO matrix for scalable sensor inputs (sumo edge/opponent detection) and robust actuator outputs.
* **Compile-Time Directives:** * `_DEBUG_`: Enables high-speed (`115200` baud) serial diagnostics.
  * `_AUTONOMOUS_`: Toggles the core behavior pipeline between human-operated and self-directed modes.

---

## 🧠 Firmware Modularity & Features

The codebase relies on a decoupled architecture, separating the signal acquisition layer from the physical actuation layer.

| Module | Core Responsibility |
| :--- | :--- |
| **`joystick.cpp`** | Handles Bluetooth packet parsing from the PS4 controller, filtering inputs, and translating joystick deadzones into normalized vector data. |
| **`motors.cpp`** | Configures PWM frequencies, abstracts motor driver logic, and translates vector data into physical wheel velocities. |
| **`controlled.cpp`** | The main teleoperated state machine, managing real-time human input and translating it into instantaneous motor commands. |
| **`autonomous.cpp`** | Alternate state machine for self-directed behavior, integrating sensor logic and search-and-destroy routines. |

---

## 📁 Repository Structure

```text
├── easyEDA/            # Custom PCB and hardware design source files
│   ├── PCBV3.json      # Physical PCB layout and routing data
│   └── SchematicV3.json# Electronic circuit schematic capture
├── include/            # Shared hardware macros, pinouts, and global board definitions
├── lib/                # External dependencies and reusable utility abstractions
├── src/
│   ├── autonomous.cpp  # Sensor-based control routines
│   ├── controlled.cpp  # Remote teleoperation logic
│   ├── joystick.cpp    # Wireless input parsing
│   ├── motors.cpp      # PWM and motor driver layer
│   └── main.cpp        # Firmware entry point and mode multiplexing
└── platformio.ini      # ESP32 environment, build flags, and dependency management
```

---

## 🚀 Getting Started

To build and flash this firmware, ensure you have **PlatformIO** installed in your VS Code environment. To view or edit the hardware design, import the JSON files into **EasyEDA**.

**1. Clone the repository:**
```bash
git clone [https://github.com/enzolfernandes/combatIO.git](https://github.com/enzolfernandes/combatIO.git)
```

**2. Build the firmware:**
```bash
pio run -e esp32doit-devkit-v1
```

**3. Flash to the ESP32 DevKit V1:**
Ensure the board is connected via USB and in bootloader mode.
```bash
pio run -e esp32doit-devkit-v1 -t upload
```

*(Alternatively, use the PlatformIO GUI inside VS Code to trigger Build and Upload tasks).*
