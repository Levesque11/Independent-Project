# Hardware, Software & Toolchain Dependencies

## Hardware Components
* **Core Processing Unit:** Raspberry Pi 5 (Quad-core ARM Cortex-A76 @ 2.4GHz)
* **Power Supply:** Official USB-C Power Supply (5V/5A)
* **Connectivity:** j5create USB-C Dual 4K Adapter / Hub, Ethernet (currently disabled), and `wlan0` Wi-Fi interface (`sly-devices`)
* **Sensors & Peripherals:** I²C IMU/Sensor wired to physical pins (SDA on GPIO 2, SCL on GPIO 3)

## Software & Environment Stack
* **Operating System:** Raspberry Pi OS (Debian-based) with custom PREEMPT-RT Real-Time patch
* **Kernel Interaction:** Netlink sockets, Netfilter hooks, hrtimers, tasklets/workqueues
* **Compilers & Build Tools:** GCC cross-compilation toolchain, Make, Kbuild
* **Networking:** NetworkManager (`nmcli`), `iproute2`, SSH (`sshd`), Custom C UDP daemon

## Visualization & User Space
* **Telemetry:** C daemon for packaging sensor and fault data
* **Ground Station:** Unity Engine (C#) for real-time 3D visual mapping of jitter, fault states, and drone telemetry
* **Debugging & Validation:** `i2cdetect`, `cyclictest` (latency benchmarking), `dmesg`, `ftrace`, and custom system integration test scripts
