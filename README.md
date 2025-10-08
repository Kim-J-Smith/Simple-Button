# Simple-Button
[English](./README.md)
[中文](./README_zh.md)

---

## Contents

- [Contents](#contents)

- [Brief Introduction](#brief-introduction)
    - [Brief instruction of design](#brief-instruction-of-design)
    - [Brief introduction of the feature](#brief-introduction-of-the-feature)

- [Usage](#usage)
    - [Overview](#overview)
    - [Detailed Step](#detailed-steps)
        - [Step 1](#step-1)
        - [Step 2](#step-2)

- [Advanced features](#advanced-features)
    - [Timer Long Push]()
    - [Counter Pepeat Push]()
    - [Long Push Hold]()
    - [Button Combination]()
    - [Low Power]()

- [Derivative Projects](#derivative-project)

---

## Brief Introduction

### Brief instruction of design

- Buttons are the simplest, most common, and most effective input in embedded design. There are quite a few mature open source projects with buttons on GitHub today, but I still see a lot of problems that these projects don't address: *Some projects don't support long-hold buttons, some don't support multi-click buttons, some don't support low power, and some have complex API*. (**The lack of low power support is a consequence of the project's use of polling instead of interrupts!**)

- There are a lot of projects that use polling because it has a natural advantage: users only need to implement the `Read_Pin()` functional interface to use polling, which is very portable; But polling comes with a natural drawback: the CPU must be working all the time to keep scanning, **which is the natural contradiction of low power** !

- I got the idea to make my own non-polling button project. The project should have the following characteristics:

- 1. **Comprehensive Feature** - "Comprehensive" means: at least supporting *short press, long press, timer long press, double push, counter multiple push, combination buttons, and long press hold*.
- 2. **Simple Deployment** - "Simple" means: providing only __ONE__ interface for creating buttons, and one line of code can register(create) a button statically.
- 3. **Use State Machine** - The purpose is: To achieve non-blocking debouncing while having high scalability and a clear hierarchical structure.
- 4. **Use EXTI** - The purpose is: Using interrupts instead of polling is beneficial for *low power consumption* support.

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

## Usage

### Overview

- As this project is a cross-platform one, all its interfaces are abstract, or in other words: all interfaces need to be customized by the user according to the chip being used. From this perspective, this project is merely a "half-finished product". If you prefer to use it directly out of the box, you can take a look at the customized version of the chip you need in the [Derivative Project](#derivative-project). If so, you can directly download it, skip step 1 and proceed directly to step 2.

- **Step 1**: You need to customize the transformation for your chip:
    - 1.1 - Add head file in **Head-File** at the beginning of the file.
    - 1.2 - **Simple-Button-Type** adjusts the type definition at the beginning of the file.
    - 1.3 - **Other-Functions** implement the abstract interface at the top of the file.
    - 1.4 - Implement the EXTI Initialization Function in the **Initialization-Function** at the beginning of the file.

- **Step 2**: Use project to create and use button: (**[]** represents optional step)
    - 2.1 - Use the **SIMPLEBTN__CREATE()** macro to create the required buttons.
    - [2.2] - Declare the created button (if used in another file) using the **SIMPLEBTN__DECLARE()** macro.
    - 2.3 - Calling the button initializer before the `while` loop in the `main` function.
    - 2.4 - Calling buttons' asynchronous handler inside a `while` loop.
    - 2.5 - Calling buttons' interrupt handler function from the EXTI interrupt function.

### Detailed Steps

#### Step 1

1. Add head file in **Head-File** at the beginning of the file. The added header files depend on the specific chip. The following takes the HAL library of STM32F103C8T6 as an example:
```c
/** @b ================================================================ **/
/** @b Head-File */

#include "stm32f1xx_hal.h"

```

2. Adjust the type definition at the **Simple-Button-Type** at the beginning of the file. These types are adjusted according to the specific chips. For instance, if the type of GPIO_Pin_x on some chips is not `uint16_t` but `GPIOPin_TypeDef`, the type below needs to be changed. Meanwhile, the definition of `SIMPLEBTN_EXTI_TRIGGER_FALLING` should be refined by adding the `EXTI_TRIGGER_FALLING` value of the chip you are using.
```c
/** @b ================================================================ **/
/** @b Simple-Button-Type */

// The type of GPIOX_BASE. (X can be A / B / C ...)
typedef uint32_t            simpleButton_Type_GPIOBase_t;
// The type of GPIO_PIN_X. (X can be 0 / 1 / 2 / 3 / ...)
// typedef uint16_t            simpleButton_Type_GPIOPin_t;
typedef GPIOPin_TypeDef            simpleButton_Type_GPIOPin_t; // 修改
// The type of Value of Pin. (The value usually be 0 or 1)
typedef uint8_t             simpleButton_Type_GPIOPinVal_t;
// The type of EXTI_TRIGGER_X. (X can be FALLING / RAISING / ...)
typedef uint32_t            simpleButton_Type_EXTITrigger_t;

#define SIMPLEBTN_EXTI_TRIGGER_FALLING      EXTI_TRIGGER_FALLING /* for example: EXTI_TRIGGER_FALLING */

```

3. Implement the abstract interface at the **Other-Functions** at the beginning of the file. The examples have been provided in the code comments and will not be repeated here.
```c
/** @b ================================================================ **/
/** @b Other-Functions */

#define SIMPLEBTN_FUNC_READ_PIN(GPIOX_Base, Pin) \
    /* for example: HAL_GPIO_ReadPin((GPIO_TypeDef*)(GPIOX_Base), Pin) */

#define SIMPLEBTN_FUNC_GET_TICK() \
    /* for example: HAL_GetTick() */

#define SIMPLEBTN_FUNC_PANIC(Cause, ErrorNum, etc) \
    /* for example: do { Error_Handler(ErrorNum); } while (1) */

#define SIMPLEBTN_FUNC_CRITICAL_SECTION_BEGIN() \
    /* for example: __disable_irq() */

#define SIMPLEBTN_FUNC_CRITICAL_SECTION_END() \
    /* for example: __enable_irq() */

#define SIMPLEBTN_FUNC_START_LOW_POWER() \
    /* for example: __WFI() */
```

4. Implement the EXTI Initialization Function in the **Initialization-Function** at the beginning of the file. Here is an example of the STM32 HAL library:
```c
/** @b ================================================================ **/
/** @b Initialization-Function */


#if defined(__GNUC__) || defined(__clang__)
    static inline __attribute__((always_inline))
#elif defined(_MSC_VER) || defined(__CC_ARM)
    static __forceinline
#else
    static inline
#endif /* defined(__GNUC__) || defined(__clang__) */
void simpleButton_Private_InitEXTI(
    simpleButton_Type_GPIOBase_t    GPIOX_Base,
    simpleButton_Type_GPIOPin_t     GPIO_Pin_X,
    simpleButton_Type_EXTITrigger_t EXTI_Trigger_X
) {
    /* Initialize the AFIO Clock(F1xx) or SYSCFG Clock */
#if defined(__HAL_RCC_AFIO_CLK_ENABLE)
    __HAL_RCC_AFIO_CLK_ENABLE();
#elif defined(__HAL_RCC_SYSCFG_CLK_ENABLE)
    __HAL_RCC_SYSCFG_CLK_ENABLE();
#else
 #warning Cannot find macro for AFIO or SYSCFG !
#endif /* AFIO or SYSCFG */

    /* Initialize the GPIOx Clock */
    switch (GPIOX_Base) {
    case GPIOA_BASE:
        __HAL_RCC_GPIOA_CLK_ENABLE();
        break;
    case GPIOB_BASE:
        __HAL_RCC_GPIOB_CLK_ENABLE();
        break;
    case GPIOC_BASE:
        __HAL_RCC_GPIOC_CLK_ENABLE();
        break;
    case GPIOD_BASE:
        __HAL_RCC_GPIOD_CLK_ENABLE();
        break;
    case GPIOE_BASE:
        __HAL_RCC_GPIOE_CLK_ENABLE();
        break;
    default:
        /* ... error handler ... */
    }

    /* Configure the GPIOx */
    GPIO_InitTypeDef gpio_config;
    gpio_config.Mode = (EXTI_Trigger_X == EXTI_TRIGGER_RISING)
        ? (GPIO_MODE_IT_RISING) : (GPIO_MODE_IT_FALLING);
    gpio_config.Pin = (uint32_t) GPIO_Pin_X;
    gpio_config.Pull = (EXTI_Trigger_X == EXTI_TRIGGER_RISING)
        ? (GPIO_PULLDOWN) : (GPIO_PULLUP);
    gpio_config.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init((GPIO_TypeDef*)GPIOX_Base, &gpio_config);

    /* Initialize the EXTI */
    IRQn_Type the_exti_IRQ;
    switch (GPIO_Pin_X) {
    case GPIO_PIN_0:
        the_exti_IRQ = EXTI0_IRQn;
        break;
    case GPIO_PIN_1:
        the_exti_IRQ = EXTI1_IRQn;
        break;
    case GPIO_PIN_2:
        the_exti_IRQ = EXTI2_IRQn;
        break;
    case GPIO_PIN_3:
        the_exti_IRQ = EXTI3_IRQn;
        break;
    case GPIO_PIN_4:
        the_exti_IRQ = EXTI4_IRQn;
        break;
    case GPIO_PIN_5:
        the_exti_IRQ = EXTI9_5_IRQn;
        break;
    case GPIO_PIN_6:
        the_exti_IRQ = EXTI9_5_IRQn;
        break;
    case GPIO_PIN_7:
        the_exti_IRQ = EXTI9_5_IRQn;
        break;
    case GPIO_PIN_8:
        the_exti_IRQ = EXTI9_5_IRQn;
        break;
    case GPIO_PIN_9:
        the_exti_IRQ = EXTI9_5_IRQn;
        break;
    case GPIO_PIN_10:
        the_exti_IRQ = EXTI15_10_IRQn;
        break;
    case GPIO_PIN_11:
        the_exti_IRQ = EXTI15_10_IRQn;
        break;
    case GPIO_PIN_12:
        the_exti_IRQ = EXTI15_10_IRQn;
        break;
    case GPIO_PIN_13:
        the_exti_IRQ = EXTI15_10_IRQn;
        break;
    case GPIO_PIN_14:
        the_exti_IRQ = EXTI15_10_IRQn;
        break;
    case GPIO_PIN_15:
        the_exti_IRQ = EXTI15_10_IRQn;
        break;
    default:
        /* ... error handler ... */

    }
    HAL_NVIC_SetPriority(
        the_exti_IRQ, 
        KIM_BUTTON_NVIC_EXTI_PreemptionPriority,
        KIM_BUTTON_NVIC_EXTI_SubPriority
    );
    HAL_NVIC_EnableIRQ(the_exti_IRQ);

}
```

#### Step 2

0. Buttons can be created with **a single macro**. But in real projects we often want to have a single `.c` file to manage all the buttons we need and a `.h` file to use as an interface. The two API macros provided by this project can well complete the `create` + `declare` two work. The typical project directory structure is **the one used in steps 2.1-2.5 below** :
```markdown
.
|
+-- Simple_Button.h  # The only file provided by this project.
|
+-- my_buttons.c  # User's file, in where buttons will be created.
|
+-- my_buttons.h  # User's file, in where buttons will be declared.
|
+-- main.c  # User's file, importing "my_buttons.h", and using the buttons.

```

1. Use the **SIMPLEBTN__CREATE()** macro to create the required buttons. Create three buttons and connect them respectively to `GPIOA-Pin0`, `GPIOB-Pin0`, and `GPIOD-Pin14`, all triggered by the falling edge. Name them respectively as `SB1`, `SB2`, and `SB3`. The STM32-HAL example is as follows (the following code is located at `my_buttons.c`) :
```c
#include "Simple_Button.h"

/* no ';' after Macro */

SIMPLEBTN__CREATE(GPIOA_BASE, GPIO_PIN_0, EXTI_TRIGGER_FALLING, SB1)

SIMPLEBTN__CREATE(GPIOB_BASE, GPIO_PIN_0, EXTI_TRIGGER_FALLING, SB2)

SIMPLEBTN__CREATE(GPIOD_BASE, GPIO_PIN_14, EXTI_TRIGGER_FALLING, SB3)

```

2. The button created using the **SIMPLEBTN__DECLARE()** macro declaration (if used in another file). Following the three buttons created in 2.1, here demonstrates how to declare the three created buttons in `my_buttons.`
```c
#include "Simple_Button.h"

/* no ';' after Macro */

SIMPLEBTN__DECLARE(SB1)

SIMPLEBTN__DECLARE(SB2)

SIMPLEBTN__DECLARE(SB3)

```

3. The button initializers are called before the `while` loop in the `main` function. Following up on the previous step, here's an example:
```c
#include "my_buttons.h"

int main(void) {

    SimpleButton_SB1_Init();
    SimpleButton_SB2_Init();
    SimpleButton_SB3_Init();

    while (1) {

    }
}

```

4. Call the button asynchronous handler inside the `while` loop. Following up from the previous step, prepare `short press`, `long press`, and `double click` callbacks (see [Advanced features](#advanced-features) for more features), and pass in a `while` loop that handles buttons asynchronically, as shown in the following example (the following code is located in `main.c`) :
```c
#include "my_buttons.h"

/* Prepare the callback functions for 'short press', 'long press', and 'double-click'. By default, they have no parameters and no return values */
void TurnOn_LED(void) {
    /* The function name is arbitrary, as long as it has no parameters and no return */
    /* The function will be called after the corresponding event is triggered */
}

void DoSomething(void) {
    /* ... */
}

int main(void) {

    SimpleButton_SB1_Init();
    SimpleButton_SB2_Init();
    SimpleButton_SB3_Init();

    while (1) {
        //Pass the 'short press', 'long press', 'double click' callback function in turn, or NULL or 0 if not needed.
        SimpleButton_SB1.Methods.asynchronousHandler(
            TurnOn_LED,
            NULL,
            DoSomething
        );
        SimpleButton_SB2.Methods.asynchronousHandler(
            NULL,
            NULL,
            DoSomething
        );
        SimpleButton_SB3.Methods.asynchronousHandler(
            NULL,
            DoSomething,
            NULL
        );
    }
}

```

5. The final step is to call the button interrupt handling function in the EXTI interrupt function. Here, it is divided into two situations: 1. **You need to implement the interrupt function yourself**. 2. **There are already ready-made interrupt callback functions** (for example, the HAL library of STM32 uses CubeMX to generate code). Here are some examples to illustrate:

    - **You need to implement the interrupt function yourself**. Most single-chip microcomputer bare-metal development requires this to be done. Go to the assembly startup file to find the `Interrupt Vector Table`, then locate the interrupt corresponding to the EXTI pin and implement the interrupt function. Continuing from the previous step, taking the STM32 standard library as an example:

    ```c
        // SB1, SB2 ----- Pin0
        void EXTI0_IRQHandler(void) {
            if (EXTI_GetITStatus(EXTI_Line0) == SET) {
                SimpleButton_SB1.Methods.interruptHandler();
                SimpleButton_SB2.Methods.interruptHandler();

                EXTI_ClearITPendingBit(EXTI_Line0);
            }
        }

        // SB3 ----- Pin14
        void EXTI15_10_IRQHandler(void) {
            if (EXTI_GetITStatus(EXTI_Line14) == SET) {
                SimpleButton_SB3.Methods.interruptHandler();

                EXTI_ClearITPendingBit(EXTI_Line14);
            }
        }
    ```

    - **There are already interrupt callbacks out there**. Just find the generated callback and call `interruptHandler()` from there. Following up on the previous step, using the HAL library generated by STM32 CubeMX as an example, `stm32f1xx_hal_gpio.c` provides this weak functional interface:
    ```c
    __weak void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
    {
        /* Prevent unused argument(s) compilation warning */
        UNUSED(GPIO_Pin);
        /* NOTE: This function Should not be modified, when the callback is needed,
           the HAL_GPIO_EXTI_Callback could be implemented in the user file
        */
    }
    ```

    So, let's copy the code above to `main.c` and call `interruptHandler()` there, like so:
    ```c
    // no __weak
    void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
    {
        switch (GPIO_Pin) {
        case GPIO_PIN_0: {
            SimpleButton_SB1.Methods.interruptHandler();
            SimpleButton_SB2.Methods.interruptHandler();
            break;
        }
        case GPIO_PIN_14: {
            SimpleButton_SB3.Methods.interruptHandler();
            break;
        }
        }
    }
    ```

[Back to Contents](#contents)

---

## Advanced Features

[Back to Contents](#contents)

---

## Derivative Project

### STM32

- [HAL-Kim-J-Smith/STM32-SimpleButton]()(coming soon)

### CH32

- [StandardLib-Kim-J-Smith/CH32-SimpleButton]()(coming soon)


[Back to Contents](#contents)
