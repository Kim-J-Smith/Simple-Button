/**
 * @file            simple_button_config.h
 * 
 * @author          Kim-J-Smith
 * 
 * @brief           The configuration file of the Simple_Button file.
 * 
 * @version         0.8.x
 * 
 * @date            2025-10-03
 * 
 * @attention       Copyright (c) 2025 Kim-J-Smith.
 *                  All rights reserved.
 * 
 * @copyright       SPDX-License-Identifier: MIT
 *                  Refer to the LICENCE file in root for more details.
 *                  <https://github.com/Kim-J-Smith/Simple-Button>
 */
#ifndef     SIMPLEBUTTON_CONFIG_H__
#define     SIMPLEBUTTON_CONFIG_H__     1020L
#include <stdint.h>

/** @p ================================================================ **/
/* ====================== CUSTOMIZATION BEGIN ========================== */


/*************************************************************************
 * @b Contents
 * 
 * 1. @e Head-File (Your head file depending on your chip)
 * 
 * 2. @e Simple-Button-Type (The Types used by Simple-Button)
 * 
 * 3. @e Other-Functions (Functions for read-pin, debug, low-power, ...)
 * 
 * 4. @e Time-Set (To set the adjustable time, such as repeat-push window. 
 *                  All these times will be set as default times, 
 *                  which can still be changed for each button.)
 * 
 * 5. @e Mode-Set (The mode of button, such as combination / timer-long-push / ...)
 * 
 * 6. @e Namespace (The namespace of Simple-Button public functions and variables)
 * 
 * 7. @e Initialization-Function (To init the GPIO, EXTI, NVIC/PFIC, etc)
 * 
 *************************************************************************
 */

/** @b ================================================================ **/
/** @b Head-File */

/** @b ================================================================ **/
/** @b Simple-Button-Type */

// The type of GPIOX_BASE. (X can be A / B / C ...)
typedef uint32_t            simpleButton_Type_GPIOBase_t;
// The type of GPIO_PIN_X. (X can be 0 / 1 / 2 / 3 / ...)
typedef uint16_t            simpleButton_Type_GPIOPin_t;
// The type of Value of Pin. (The value usually be 0 or 1)
typedef uint8_t             simpleButton_Type_GPIOPinVal_t;
// The type of EXTI_TRIGGER_X. (X can be FALLING / RAISING / ...)
typedef uint32_t            simpleButton_Type_EXTITrigger_t;

#define SIMPLEBTN_EXTI_TRIGGER_FALLING      /* for example: EXTI_TRIGGER_FALLING */

/** @b ================================================================ **/
/** @b Other-Functions */

#define SIMPLEBTN_FUNC_READ_PIN(GPIOX_Base, Pin) \
    /* for example: HAL_GPIO_ReadPin((GPIO_TypeDef*)(GPIOX_Base), Pin) */

#define SIMPLEBTN_FUNC_GET_TICK() \
    /* for example: HAL_GetTick() or xTaskGetTickCount() */

#define SIMPLEBTN_FUNC_GET_TICK_FromISR() \
    /* for example: HAL_GetTick() or xTaskGetTickCountFromISR() */

#define SIMPLEBTN_FUNC_PANIC(Cause, ErrorNum, etc) \
    /* for example: do { Error_Handler(ErrorNum); } while (1) */ /* only used in DEBUG mode */

#define SIMPLEBTN_FUNC_CRITICAL_SECTION_BEGIN() \
    /* for example: __disable_irq() */

#define SIMPLEBTN_FUNC_CRITICAL_SECTION_END() \
    /* for example: __enable_irq() */

#define SIMPLEBTN_FUNC_START_LOW_POWER() \
    /* for example: __WFI() */

/** @b ================================================================ **/
/** @b Time-Set */

    // The delay time after you push the button.
#define SIMPLEBTN_TIME_PUSH_DELAY                       30
    // The delay time after you release the button.
#define SIMPLEBTN_TIME_RELEASE_DELAY                    30
    // The minimum time to push the button for long-push.
#define SIMPLEBTN_TIME_LONG_PUSH_MIN                    1000
    // The window time for repeat-push.
#define SIMPLEBTN_TIME_REPEAT_WINDOW                    300
    // The cool-down time after you release the button.
#define SIMPLEBTN_TIME_COOL_DOWN                        0
    // The minimum time to push the button for long-push-hold.
#define SIMPLEBTN_TIME_HOLD_PUSH_MIN                    SIMPLEBTN_TIME_LONG_PUSH_MIN
    // The interval time to call callback function in hold-long-push mode.
#define SIMPLEBTN_TIME_HOLD_INTERVAL                    200
    // The timeout time for normal long button.
#define SIMPLEBTN_TIME__TIMEOUT_NORMAL                  (1000 * 120)
    // The timeout time for combination long button.
#define SIMPLEBTN_TIME__TIMEOUT_COMBINATION             (1000 * 240)

/** @b ================================================================ **/
/** @b Mode-Set */

    // Enable debug mode if this macro is defined as 1.
#define SIMPLEBTN_MODE_ENABLE_DEBUG                     1
    // Enable combination mode if this macro is defined as 1.
#define SIMPLEBTN_MODE_ENABLE_COMBINATION               1
    // Enable timer long-push mode if this macro is defined as 1.
#define SIMPLEBTN_MODE_ENABLE_TIMER_LONG_PUSH           1
    // Enable counter repeat-push mode if this macro is defined as 1.
#define SIMPLEBTN_MODE_ENABLE_COUNTER_REPEAT_PUSH       1
    // Enable adjustable mode if this macro is defined as 1.
#define SIMPLEBTN_MODE_ENABLE_ADJUSTABLE_TIME           1
    // Enable multi-threads mode(enable this only when you do use multi-thread) if this macro is defined as 1.
#define SIMPLEBTN_MODE_ENABLE_MULTI_THREADS             1
    // Enable long-push-hold mode if this macro is defined as 1.
#define SIMPLEBTN_MODE_ENABLE_LONGPUSH_HOLD             1

/** @b ================================================================ **/
/** @b Namespace */

/**
 * @brief   The namespace of Simple-Button public functions and variables.
 * 
 * @note    This namespace can be changed to avoid name conflicts.
 *          Default: SimpleButton_
 */
#define SIMPLEBTN_NAMESPACE                             SimpleButton_

/** @b ================================================================ **/
/** @b Initialization-Function */

/* This macro just forward the parameter to another function */
#define SIMPLEBTN_FUNC_INIT_EXTI(GPIOX_Base, GPIO_Pin_X, EXTI_Trigger_X) \
    simpleButton_Private_InitEXTI(GPIOX_Base, GPIO_Pin_X, EXTI_Trigger_X)

/* ====================== CUSTOMIZATION END ============================ */
/** @p ================================================================ **/


// Macro for force-inline
#if defined(__GNUC__) || defined(__clang__)
 #define SIMPLEBTN_FORCE_INLINE static inline __attribute__((always_inline))
#elif defined(_MSC_VER) || defined(__CC_ARM)
 #define SIMPLEBTN_FORCE_INLINE static __forceinline
#else
 #define SIMPLEBTN_FORCE_INLINE static inline
#endif

/* ================ OTHER LOCAL-PLATFORM CUSTOMIZATION ================= */

SIMPLEBTN_FORCE_INLINE
void simpleButton_Private_InitEXTI(
    simpleButton_Type_GPIOBase_t    GPIOX_Base,
    simpleButton_Type_GPIOPin_t     GPIO_Pin_X,
    simpleButton_Type_EXTITrigger_t EXTI_Trigger_X
) {
    /* Write your code to initialize the GPIO/EXTI/NVIC ... */
    /* (void)xxx is used to suppress warning: "unused variables" */

    /* If you want to initialize the GPIO and EXTI in other place,
     * you can just ignore this function and do nothing here.
     *
     * In another words, for example, I DON'T want to initialize the GPIO,
     * EXTI, and the NVIC of EXTI with function named `SimpleButton__name_Init()`,
     * then I will keep this function empty.
     */
    (void)GPIOX_Base;
    (void)GPIO_Pin_X;
    (void)EXTI_Trigger_X;
}

/* ================================ END ================================ */

#endif /* SIMPLEBUTTON_CONFIG_H__ */
