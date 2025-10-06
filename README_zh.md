# Simple-Button
[English](./README.md)
[中文](./README_zh.md)

---

## 目录

- [目录](#目录)

- [简介](#简介)
    - [设计简介](#设计简介)
    - [功能简介](#功能简介)

- [使用方法](#使用方法)
    - [概述](#概述)
    - [详细步骤](#详细步骤)

- [衍生项目](#衍生项目)

---

## 简介

### 设计简介

- 按键是嵌入式设计当中最简单、最常见也最有效的输入。如今的GitHub上已经有相当多成熟的按键开源项目了，但我仍然发现了许多这些项目没有解决的问题，于是产生了自己制作一个按键项目的想法。这个项目应当具有以下特点：

- 1. **功能全面** - “全面”指的是：至少支持*短按、长按、计时长按、双击、计数多击、组合键、长按保持*。
- 2. **部署简单** - “简单”指的是：只提供一个创建按键的接口，一行代码即可静态注册（创建）一个按键。
- 3. **使用状态机** - 目的是：非阻塞消抖的同时，具有较高的拓展性，且层次结构分明。
- 4. **使用外部中断** - 目的是：使用中断而非轮询有利于*低功耗*的支持。

- 于是，在综合考量之后，我选择**使用C语言的宏来模拟产生类似C++模板的功能**。用户只需要使用提供好的模板，就可以使用一行代码创建一个按键对象（实际上是一个结构体和三个函数）。

- 除了初始化函数需要显式调用以外，其他两个函数的调用方式是类似C++的“方法”的。这是我使用C语言进行面对对象的一次尝试。

### 功能简介

- **在[设计思想](#设计简介)的指导下，本项目实现了一个基于C99标准（或C++11标准）的纯C语言按键项目。**

1. ✅ **功能全面**： 本项目目前支持*短按、长按、计时长按、双击、计数多击、组合键、长按保持*。

2. ✅ **状态机**： 本项目使用了状态机进行代码组织，扩展性强。但用户无需了解状态机细节即可轻松使用。

3. ✅ **外部中断**： 本项目使用外部中断触发按键，*天然支持低功耗*，项目也提供一行代码判断并进入低功耗的接口。

4. ✅ **异步处理**： 回调函数异步处理，减小中断停留时间。

5. ✅ **二次确认**： 本项目对引脚触发信号进行二次确认，从而支持 GPIOX 相同编号引脚同时作为按键引脚，无需担心外部中断冲突。

6. ✅ **自定义按键**： 本项目支持对每个按键单独设置*长按判定最小时间、多击窗口时间、冷却时间*，方便按键自定义。

7. ✅ **多线程安全**： 本项目支持开启多线程模式来保证多线程安全。

8. ✅ **调试支持**： 本项目支持开启调试模式来定位异常，方便对项目进行二次开发。

[回到目录](#目录)

---

## 使用方法

### 概述

- 由于本项目是一个跨平台项目，它的所有接口都是抽象的，或者说：所有接口都需要使用者根据所使用的芯片进行自定义。从这个方面来讲，本项目只是个“半成品”。如果您希望直接“开箱即用”，可以看一看[衍生项目](#衍生项目)您需要的芯片的定制化版本。如果有，您可以直接下载，跳过步骤1，直接进行步骤2。

- 步骤1：您需要针对您的芯片进行定制化改造：
    - 1.1 - 在文件开头的 **Head-File** 添加芯片头文件。
    - 1.2 - 在文件开头的 **Simple-Button-Type** 调整类型定义。
    - 1.3 - 在文件开头的 **Other-Functions** 实现抽象接口。
    - 1.4 - 在文件开头的 **Initialization-Function** 实现EXTI初始化函数。

- 步骤2：使用项目，部署、使用按键：（ **[]** 代表可选步骤）
    - 2.1   - 使用 **SIMPLEBTN__CREATE()** 宏 创建需要的按键。
    - [2.2] - 使用 **SIMPLEBTN__DECLARE()** 宏 声明创建的按键（如果在另一个文件使用）。
    - 2.3   - 在`main`函数`while`循环之前调用按键初始化函数。
    - 2.4   - 在`while`循环内调用按键异步处理函数。
    - 2.5   - 在 EXTI 中断函数中调用按键中断处理函数。
    - [2.6] - 使用 **SIMPLEBTN__START_LOWPOWER** 宏 启用低功耗。（如果需要低功耗）

### 详细步骤

#### 步骤1

1. 在文件开头的 **Head-File** 添加芯片头文件。添加的头文件取决于具体的芯片。下方以STM32F103C8T6的HAL库举例：
```c
/** @b ================================================================ **/
/** @b Head-File */

#include "stm32f1xx_hal.h"

```

2. 在文件开头的 **Simple-Button-Type** 调整类型定义。这些类型根据具体芯片不同进行调整。例如有的芯片的GPIO_Pin_x 的类型不是`uint16_t`，而是`GPIOPin_TypeDef`，就要对下方类型进行更改。同时，应当完善`SIMPLEBTN_EXTI_TRIGGER_FALLING`的定义，补上您使用的芯片的`EXTI_TRIGGER_FALLING`值即可。
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

3. 在文件开头的 **Other-Functions** 实现抽象接口。示例已在代码注释中给出，不再赘述。
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

4. 在文件开头的 **Initialization-Function** 实现EXTI初始化函数。此处给出STM32 HAL库示例：
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

#### 步骤2

## 衍生项目

### STM32

- [HAL库-Kim-J-Smith/STM32-SimpleButton]()(敬请期待)

### CH32

- [标准库-Kim-J-Smith/CH32-SimpleButton]()(敬请期待)
