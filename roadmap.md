# Fall Semester 2026 (Late August – December)
Focus: Environment Setup, Real-Time Kernel, and Initial Hardware Interfacing

## Phase 1: Environment Setup & Real-Time Kernel (Weeks 1–6)
* **Week 1 (Aug 26 – Sept 1):** Cross-compilation toolchain setup (Classes begin Aug 26).
* **Week 2 (Sept 2 – Sept 8):** Applying the PREEMPT-RT patch.
* **Week 3 (Sept 9 – Sept 15):** Kernel compilation & flashing to the Pi.
* 👉 **Week 4 (Sept 16 – Sept 22):** Boot verification & cyclictest latency benchmarking. [ 📍 CHRONOLOGICALLY HERE ]
* **Week 5 (Sept 23 – Sept 29):** Base C daemon & UDP skeleton.
* **Week 6 (Sept 30 – Oct 6):** Unity ground station UDP ingestion setup.

## Phase 2: Hardware Interfacing & Custom Ring 0 Driver — Part 1 (Weeks 7–13)
* **Week 7 (Oct 7 – Oct 13):** Physical I²C sensor wiring & bus verification (i2cdetect).
* **Week 8 (Oct 14 – Oct 20):** LKM skeleton & module lifecycle (Includes Mid-Semester Break Oct 15–16).
* **Week 9 (Oct 21 – Oct 27):** Manual memory mapping (ioremap) for I²C registers.
* **Week 10 (Oct 28 – Nov 3):** Building the custom character device (/dev/drone_sensor).
* 🚀 **Week 11 (Nov 4 – Nov 10):** Implementing user-to-kernel data copying (copy_to_user). [ 🚀 ACTUAL CODING PROGRESS ]
* **Week 12 (Nov 11 – Nov 17):** Configuring sensor hardware interrupts (IRQs).
* **Week 13 (Nov 18 – Dec 2):** Bottom-half tasklets/workqueues (Spans the Thanksgiving Break Nov 20–29; light or paused week).

## Fall Wrap-Up & Finals (Week 14)
* **Week 14 (Dec 3 – Dec 9):** High-resolution timers (hrtimers) in Ring 0 (Last day of classes Dec 10).

🛑 **Winter Break Pause (Dec 10, 2026 – Jan 19, 2027):** Residence halls close for winter break. Project paused so you can focus entirely on your finals and enjoy the break.

# Spring Semester 2027 (January – May)
Focus: Kernel Watchdogs, Fault Injection, Netlink Sockets, and Unity Visualization

## Phase 2: Hardware Interfacing — Part 2 (Weeks 15–16)
* **Week 15 (Jan 20 – Jan 26):** Kernel-space deadline enforcement watchdog (Spring classes begin Jan 20).
* **Week 16 (Jan 27 – Feb 2):** System Integration Test #1 (Character driver + IRQ + Watchdog).

## Phase 3: Kernel-Space Fault Injection & Netlink Sockets (Weeks 17–24)
* **Week 17 (Feb 3 – Feb 9):** Netlink socket architecture design (Ring 0 to Ring 3 bridge).
* **Week 18 (Feb 10 – Feb 16):** Netlink data serialization routines.
* **Week 19 (Feb 17 – Feb 23):** Netfilter packet hook initialization (Includes Mid-Winter Break Feb 18–19).
* **Week 20 (Feb 24 – Mar 2):** Kernel-space UDP fault mutation engine.
* **Week 21 (Mar 3 – Mar 9):** Linking watchdog violations directly to the fault injector.
* **Week 22 (Mar 10 – Mar 16):** User-space sysfs/config control interface for faults.
* **Week 23 (Mar 17 – Mar 30):** End-to-end stress validation (Spans Spring Break Mar 19–28; built-in buffer week).
* **Week 24 (Mar 31 – Apr 6):** System Integration Test #2 (dmesg & Netlink verification).

## Phase 4: Ground Station Visualization & Final Polish (Weeks 25–31)
* **Week 25 (Apr 7 – Apr 13):** Finalizing the C daemon telemetry packaging loop.
* **Week 26 (Apr 14 – Apr 20):** Expanding Unity C# scripts to parse advanced telemetry.
* **Week 27 (Apr 21 – Apr 27):** Real-time 3D visual mapping of jitter and fault states in Unity.
* **Week 28 (Apr 28 – May 4):** End-to-end latency profiling using ftrace.
* **Week 29 (May 5 – May 11):** Documentation & architecture diagrams (Spring classes end May 7).
* **Week 30 (May 12 – May 18):** Code cleanup & repository polish (Final exams week).
* **Week 31 (May 19 – May 25):** Final system demonstration and review (Completed just ahead of Commencement on May 23).
