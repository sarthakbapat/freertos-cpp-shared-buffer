# freertos-cpp-shared-buffer

A real-time multitasking system simulated using **FreeRTOS POSIX port** in **C++**, designed to demonstrate shared resource synchronization, and real-world RTOS primitives — including mutexes and task scheduling.

This simulation is platform-independent and runs on macOS or Linux, requiring no embedded hardware.

---

## Features

- C++-based multitasking with FreeRTOS POSIX
- Shared data buffer (`SharedBuffer`) protected by a mutex
- Multiple producer tasks generate simulated sensor data
- Consumer (uploader) task retrieves and prints data
- Designed with embedded software architecture principles

---

## 📐 Architecture Overview

```plaintext
+------------------+         +------------------+
|  Sensor Task A   |         |  Sensor Task B   |
| (Producer Task)  |         | (Producer Task)  |
+--------+---------+         +--------+---------+
         |                            |
         |         push(data)         |
         |---------------------------->
         |     SharedBuffer (mutex)   |
         +----------------------------+
                         |
            +------------v------------+
            |    Uploader Task        |
            | (Consumer/Logger Task)  |
            +-------------------------+
```

## Takeaways

- C++ Integration with RTOS Design
- Singleton Shared Buffer with protected with Mutex
- FreeRTOS task and mutex APIs.
