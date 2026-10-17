# CombatIO - ESP32 robotics control

C++ firmware and EasyEDA hardware files for combat and sumo robotics, developed in the **TERA robotics team**.

This repository is **Enzo Fernandes's fork** of [roboticatera/CombatIO](https://github.com/roboticatera/CombatIO). Team contributions and vendored libraries remain attributed to their respective authors.

## My documented contributions

| Contribution | Evidence in the team history |
| --- | --- |
| Changes to locomotion output correction | [1252732 - correction factor](https://github.com/enzolfernandes/combatIO/commit/12527322fff6e27bc620f852db3d01cad864fc83) |
| Motor-stop commands when the controller disconnects | [440a736 - disconnection handling](https://github.com/enzolfernandes/combatIO/commit/440a736070e4b5e61b1fc55070fb83deb96480b1) |
| Adaptation of the weapon command to a unidirectional ESC | [a3fbd44 - ESC adaptation](https://github.com/enzolfernandes/combatIO/commit/a3fbd44a5bf5782af3b5fd2ee67f7c70121aa490) |

These commits identify specific contributions by Enzo; they do not establish sole authorship of the project or its dependencies. The correction factor is zero in the current source, so its historical introduction is not presented as an active tuning result.

## Architecture and current state

| File | Role observed in source | Limit |
| --- | --- | --- |
| [src/main.cpp](src/main.cpp) | Arduino startup/loop, PWM timer allocation and compile-time mode selection | Mode selection is compile-time, not a dynamic operating-mode selector |
| [include/joystick.cpp](include/joystick.cpp) | PS4 Bluetooth setup and controller connection | Startup waits for a connection; pairing configuration is hardware-specific |
| [include/controlled.cpp](include/controlled.cpp) | Joystick mapping, dead zone, locomotion/weapon commands and stop on disconnection | Code behavior; no latency or fail-safe certification is claimed |
| [include/motors.cpp](include/motors.cpp) | Three servo-style PWM outputs through ESP32Servo | This is not field-oriented/vector control of motor phase currents |
| [include/autonomous.cpp](include/autonomous.cpp) | IR ready/start/stop handling and sensor setup | Strategy selection/execution remain TODOs |
| [easyEDA/](easyEDA/) | PCB and schematic JSON files | Hardware files do not establish physical validation |
| [test/test_main.cpp](test/test_main.cpp) | Unity test routines using peripherals | Hardware-dependent; no passing test report is supplied |

The teleoperated path is selected by default: `_AUTONOMOUS_` and `_DEBUG_` are commented in `src/main.cpp`. The motor module configures GPIO 25/26/27 with servo-style pulses at 50 Hz. Review the source and actual hardware before any use.

**Validation boundary:** source and historical changes are available. This documentation review did not compile, upload or run the firmware, and did not test physical robots. No measured jitter, response time, competition result or complete autonomous operation is claimed.

## Inspect and attempt a build

Requirements: Git, PlatformIO Core or VS Code with PlatformIO, and the dependencies included in `lib/`.

```sh
git clone https://github.com/enzolfernandes/combatIO.git
cd combatIO
pio run -e esp32doit-devkit-v1
```

The command is a **procedure to attempt**, not a verified build result. The [configuration](platformio.ini) selects `esp32doit-devkit-v1`, `espressif32` and the Arduino framework. The platform version is not pinned; record your resolved toolchain and dependency versions when reproducing it.

Before commissioning:

- Review the controller pairing setting in `include/joystick.cpp` for your own hardware.
- Check motor pins, pulse ranges and neutral commands against the actual ESCs.
- Review the autonomous TODOs before enabling that mode.
- Read `test/test_main.cpp` before running tests: it includes commands that move all motor outputs. Some setup assertions only check `true`, so the file is not evidence of complete functional coverage.

No flashing or motor test command is part of this documentation review.

## Dependencies and authorship

The repository vendors **PS4-esp32**, **ESP32Servo**, **Arduino-IRremote** and **vl53l1x-arduino** under [lib/](lib/). Their code, licenses and notices belong to their respective maintainers.

Workflow files inside vendored libraries are upstream library artifacts. They do not establish a CombatIO firmware CI pipeline or personal GitHub Actions experience.

No repository-level LICENSE file was identified in the inspected tree. This README assigns no license to team code and does not change dependency licenses.

## Technical portfolio value

This project provides reviewable examples of C++ on ESP32, Arduino/PlatformIO configuration, joystick-to-actuator mapping, Bluetooth library integration and collaborative Git history. Read the contribution commits above alongside the current source.

[Source baseline before this documentation revision](https://github.com/enzolfernandes/combatIO/tree/a00594d7261e4af5991677c7685855f846543ac7).

*Presentation revised on 16 October 2026. This revision corrects documentation and file paths; it adds no firmware functionality, autonomous strategy or new test result.*
