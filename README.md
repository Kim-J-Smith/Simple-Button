# Simple-Button
[English](./README.md)
[中文](./docs/README_zh.md)

---

## Contents

- [Contents](#contents)

- [Brief Introduction](#brief-introduction)
    - [Brief instruction of design](#brief-instruction-of-design)
    - [Brief introduction of the feature](#brief-introduction-of-the-feature)

---

## Brief Introduction

### Brief instruction of design

- Buttons are the simplest, most common and most effective input in embedded design. Nowadays, there are already quite a few mature open-source button projects on GitHub. However, I still found many problems that these projects haven't solved, which led me to have the idea of creating my own button project. This project should have the following characteristics:

- 1. **Comprehensive Feature** - "Comprehensive" means: at least supporting *short press, long press, timer long press, double push, counter multiple push, combination buttons, and long press hold*.
- 2. **Simple Deployment** - "Simple" means: providing only ONE interface for creating buttons, and one line of code can register(create) a button statically.
- 3. **Use State Machine** - The purpose is: To achieve non-blocking debouncing while having high scalability and a clear hierarchical structure.
- 4. **Use EXTI** - The purpose is: Using interrupts instead of polling is beneficial for * low power consumption * support.

- So, after comprehensive consideration, I chose to **use C language macros to simulate the generation of functions similar to C++ templates**. Users only need to use the provided template to create a button object (which is actually a structure and three functions) with just one line of code.

- Except for the initialization function which needs to be explicitly called, the calling methods of the other two functions are similar to the "methods" in C++. This is my attempt to implementing OOP using the C language.

### Brief introduction of the feature

- **Under the guidance of the [Design Concept](#brief-instruction-of-design), this project has implemented a pure C language button project based on the C99 standard (or C++11 standard).**

1. ✅ **Comprehensive Features** : This project currently supports *short press, long press, timer long press, double push, counter multiple push, combination buttons, and long press hold*.

2. ✅ **State Machine** : This project uses a state machine for code organization, which has strong scalability. However, users can use it easily without having to understand the details of the state machine.

3. ✅ **External Interrupt(EXTI)** : This project uses an external interrupt(EXTI) trigger button, *naturally supporting low power consumption*. The project also provides a line of code to determine and enter a low-power interface.

4. ✅ **Asynchronous Processing** : The callback function is processed asynchronously to reduce the interrupt dwell time.

4. ✅ **Secondary Confirmation** : This project performs secondary confirmation on the pin trigger signal, thereby supporting pins who have the same number in GPIOX to be used as button pins simultaneously, eliminating concerns about external interrupt conflicts.

5. ✅ **Adjustable Time** : This project supports setting the *minimum time for long press determination, multi-click window time, and cooldown time* for each button separately, making it convenient for button customization.

6. ✅ **Multi-threading Safety** : This project supports enabling (multi-threading mode)[] to ensure multi-threading safety.

7. ✅ **Debugging Support** : This project supports enabling (debugging mode)[] to locate anomalies, facilitating secondary development of the project.

[Back to Contents](#contents)

---

