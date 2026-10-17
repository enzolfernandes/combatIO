# CombatIO — my contributions to ESP32 robotics control

I contributed to **CombatIO with the TERA robotics team**, working on ESP32/C++ firmware for combat and sumo robotics. This repository is my fork of [roboticatera/CombatIO](https://github.com/roboticatera/CombatIO), preserving the team's history and contributions.

## My contributions

| What I worked on | Commit |
| --- | --- |
| Changes to locomotion output correction | [1252732 — correction factor](https://github.com/enzolfernandes/combatIO/commit/12527322fff6e27bc620f852db3d01cad864fc83) |
| Motor-stop commands when the controller disconnects | [440a736 — disconnection handling](https://github.com/enzolfernandes/combatIO/commit/440a736070e4b5e61b1fc55070fb83deb96480b1) |
| Adaptation of the weapon command to a unidirectional ESC | [a3fbd44 — ESC adaptation](https://github.com/enzolfernandes/combatIO/commit/a3fbd44a5bf5782af3b5fd2ee67f7c70121aa490) |

These links identify my changes within a team project. The correction factor is zero in the current source; the first commit records its historical introduction.

## How the project is organized

| File | Role |
| --- | --- |
| [src/main.cpp](src/main.cpp) | Arduino startup/loop, PWM timer allocation and compile-time mode selection |
| [include/joystick.cpp](include/joystick.cpp) | PS4 Bluetooth setup and controller connection |
| [include/controlled.cpp](include/controlled.cpp) | Joystick mapping, dead zone, locomotion/weapon commands and stop on disconnection |
| [include/motors.cpp](include/motors.cpp) | Three servo-style PWM outputs through ESP32Servo |
| [include/autonomous.cpp](include/autonomous.cpp) | IR ready/start/stop handling and sensor setup |
| [easyEDA/](easyEDA/) | Team PCB and schematic JSON files |
| [test/test_main.cpp](test/test_main.cpp) | Unity routines using the robot's peripherals |

The teleoperated path is selected by default: `_AUTONOMOUS_` and `_DEBUG_` are commented in `src/main.cpp`. The motor module configures GPIO 25/26/27 with servo-style pulses at 50 Hz. The controller connects over Bluetooth, and the firmware maps joystick input to ESC commands.

## Current state and testing

My contribution evidence is the code and commit history linked above. The autonomous module includes IR and sensor routines; strategy selection and execution remain TODOs.

The test file uses physical peripherals and includes commands that move all motor outputs. Some setup assertions only check `true`. I did not compile, upload or physically test the firmware during this presentation review, and the repository does not include a passing test report.

## Local build procedure

Use Git and PlatformIO Core, or VS Code with PlatformIO:

```sh
git clone https://github.com/enzolfernandes/combatIO.git
cd combatIO
pio run -e esp32doit-devkit-v1
```

The [configuration](platformio.ini) selects `esp32doit-devkit-v1`, `espressif32` and the Arduino framework. The platform version is not pinned. These instructions describe the configured build procedure; record resolved toolchain/dependency versions and a build log when reproducing it.

Before commissioning, review the controller pairing in `include/joystick.cpp`, motor pins, pulse ranges and neutral commands against your hardware. Read `test/test_main.cpp` before running its hardware-dependent routines.

## Team and dependency attribution

I keep the team's history in this fork and link my individual changes rather than attributing the whole project to myself.

The repository vendors **PS4-esp32**, **ESP32Servo**, **Arduino-IRremote** and **vl53l1x-arduino** under [lib/](lib/). Their authorship, licenses and notices remain with their maintainers. The repository has no root LICENSE file; this documentation assigns no new license.

[Source baseline before the presentation revisions](https://github.com/enzolfernandes/combatIO/tree/a00594d7261e4af5991677c7685855f846543ac7).

*Presentation updated on 17 October 2026. Documentation changes only.*
