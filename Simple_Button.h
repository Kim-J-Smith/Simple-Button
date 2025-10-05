/**
 * @file            Simple_Button.h
 * 
 * @author          Kim-J-Smith
 * 
 * @brief           A template for the button is provided
 * 
 * @version         0.0.1 ( SIMPLEBUTTON_H__ == 0001L )
 * 
 * @date            2025-10-03
 * 
 * @attention       Copyright (c) 2025 Kim-J-Smith.
 *                  All rights reserved.
 * 
 * @copyright       This project complies with the MIT License.
 *                  Refer to the LICENCE file in root for more details.
 *                  <https://github.com/Kim-J-Smith/Simple-Button>
 */
#ifndef     SIMPLEBUTTON_H__
#define     SIMPLEBUTTON_H__    0001L
#include    <stdint.h>

/** @p ================================================================ **/
/* ====================== CUSTOMIZATION BEGIN ========================== */


/*************************************************************************
 * @b Contents
 * 
 * 1. @e Head-File (Your head file depending on your chip)
 * 
 * 2. @e Simple-Button-Type (The Type of Simple-Button)
 * 
 * 3. @e Initialization-Function (To init the time-base? gpio? exti? nvic?)
 * 
 * 4. @e Other-Functions (Functions for read-pin, debug, low-power, ...)
 * 
 * 5. @e Time-Set (To set the adjustable time, such as repeat-push window. 
 *                  All these times will be set as default times, 
 *                  which can still be changed for each button.)
 * 
 * 6. @e Mode-Set (The mode of button, such as combination / timer-long-push / ...)
 * 
 * 7. @e Namespace (The namespace of Simple-Button public functions and variables)
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
/** @b Initialization-Function */

static inline void simpleButton_Private_InitEXTI(
    simpleButton_Type_GPIOBase_t    GPIOX_Base,
    simpleButton_Type_GPIOPin_t     GPIO_Pin_X,
    simpleButton_Type_EXTITrigger_t EXTI_Trigger_X
) {
    /* Write your code to initialize the GPIO/EXTI/NVIC ... */

    /* (void)xxx is used to suppress warning: "unused variables" */
    (void)GPIOX_Base;
    (void)GPIO_Pin_X;
    (void)EXTI_Trigger_X;
}

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
#define SIMPLEBTN_MODE_ENABLE_TIMER_LONG_PUSH           0
    // Enable counter repeat-push mode if this macro is defined as 1.
#define SIMPLEBTN_MODE_ENABLE_COUNTER_REPEAT_PUSH       0
    // Enable only-use-default-time mode if this macro is defined as 1.
#define SIMPLEBTN_MODE_ENABLE_ONLY_DEFAULT_TIME         0
    // Enable multi-threads mode(enable this only when you do use multi-thread) if this macro is defined as 1.
#define SIMPLEBTN_MODE_ENABLE_MULTI_THREADS             1

/** @b ================================================================ **/
/** @b Namespace */

/**
 * @brief   The namespace of Simple-Button public functions and variables.
 * 
 * @note    This namespace can be changed to avoid name conflicts.
 *          Default: SimpleButton_
 */
#define SIMPLEBTN_NAMESPACE                             SimpleButton_


/* ====================== CUSTOMIZATION END ============================ */
/** @p ================================================================ **/



/* ============== Private-Use Macro / Type / Function ================= */

// Macro for bit-field
#define SIMPLEBTN_BITFIELD(type)                        uint32_t

// Macro for debug
#if SIMPLEBTN_MODE_ENABLE_DEBUG == 1
 #define SIMPLEBTN_DEBUG
#endif /* SIMPLEBTN_MODE_ENABLE_DEBUG == 1 */

// Macro for multi-threads
#if SIMPLEBTN_MODE_ENABLE_MULTI_THREADS == 1
 #define SIMPLEBTN_FUNC_CRITICAL_SECTION_BEGIN_M() SIMPLEBTN_FUNC_CRITICAL_SECTION_BEGIN()
 #define SIMPLEBTN_FUNC_CRITICAL_SECTION_END_M() SIMPLEBTN_FUNC_CRITICAL_SECTION_END()
#else
 #define SIMPLEBTN_FUNC_CRITICAL_SECTION_BEGIN_M()
 #define SIMPLEBTN_FUNC_CRITICAL_SECTION_END_M()
#endif /* SIMPLEBTN_MODE_ENABLE_MULTI_THREADS == 1 */

// Macro for C API
#ifdef __cplusplus
 #define SIMPLEBTN_C_API extern "C"
#else
 #define SIMPLEBTN_C_API
#endif

// Macro for force-inline
#if defined(__GNUC__) || defined(__clang__)
 #define SIMPLEBTN_FORCE_INLINE static inline __attribute__((always_inline))
#elif defined(_MSC_VER) || defined(__CC_ARM)
 #define SIMPLEBTN_FORCE_INLINE static __forceinline
#else
 #define SIMPLEBTN_FORCE_INLINE static inline
#endif

// Macro for suggest-inline
#if defined(SIMPLEBTN_DEBUG)
 #if defined(__GNUC__) || defined(__clang__)
  #define SIMPLEBTN_SUGGEST_INLINE static __attribute__((noinline)) __attribute__((unused))
 #elif defined(_MSC_VER)
  #define SIMPLEBTN_SUGGEST_INLINE __pragma(warning(suppress: 4505)) static
 #elif defined(__CC_ARM)
  #define SIMPLEBTN_SUGGEST_INLINE static __attribute__((noinline))
 #else
  #define SIMPLEBTN_SUGGEST_INLINE static
 #endif /* defined(__GNUC__) || defined(__clang__) */
#else
 #define SIMPLEBTN_SUGGEST_INLINE static inline
#endif /* defined(SIMPLEBTN_DEBUG) */

// Macro to connect 2 macro
#define SIMPLEBTN_CONNECT2(a, b) SIMPLEBTN_CONNECT2_1(a, b)
#define SIMPLEBTN_CONNECT2_1(a, b) SIMPLEBTN_CONNECT2_2(a, b)
#define SIMPLEBTN_CONNECT2_2(a, b) SIMPLEBTN_CONNECT2_3(a, b)
#define SIMPLEBTN_CONNECT2_3(a, b) SIMPLEBTN_CONNECT2_4(a, b)
#define SIMPLEBTN_CONNECT2_4(a, b) SIMPLEBTN_CONNECT2_5(a, b)
#define SIMPLEBTN_CONNECT2_5(a, b) a ## b
// Macro to connect 3 macro
#define SIMPLEBTN_CONNECT3(a, b, c) SIMPLEBTN_CONNECT3_1(a, b, c)
#define SIMPLEBTN_CONNECT3_1(a, b, c) SIMPLEBTN_CONNECT3_2(a, b, c)
#define SIMPLEBTN_CONNECT3_2(a, b, c) SIMPLEBTN_CONNECT3_3(a, b, c)
#define SIMPLEBTN_CONNECT3_3(a, b, c) SIMPLEBTN_CONNECT3_4(a, b, c)
#define SIMPLEBTN_CONNECT3_4(a, b, c) SIMPLEBTN_CONNECT3_5(a, b, c)
#define SIMPLEBTN_CONNECT3_5(a, b, c) a ## b ## c

#if (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)) \
    || (defined(__cplusplus) && __cplusplus >= 201103L)

// Macro to count args - 1
 #define SIMPLEBTN_COUNT_ARGS_IMPL(_1, _2, _3, _4, _5, _6, _7, _8,  \
    _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20,      \
    _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, N, ...) N
// Macro to count args - 2
 #define SIMPLEBTN_COUNT_ARGS(...)         \
    SIMPLEBTN_COUNT_ARGS_IMPL(__VA_ARGS__, \
        32, 31, 30, 29, 28, 27, 26, 25, \
        24, 23, 22, 21, 20, 19, 18, 17, \
        16, 15, 14, 13, 12, 11, 10, 9,  \
        8,  7,  6,  5,  4,  3,  2,  1)

#endif /* >= C99 or C++11 */

// Short-Push callback function pointer Type
typedef void (* simpleButton_Type_ShortPushCallBack_t)(void);

// Long-Push callback function pointer Type
#if SIMPLEBTN_MODE_ENABLE_TIMER_LONG_PUSH == 0
 typedef void (* simpleButton_Type_LongPushCallBack_t)(void);
#else
 typedef void (* simpleButton_Type_LongPushCallBack_t)(uint32_t longPushTime);
#endif /* SIMPLEBTN_MODE_ENABLE_TIMER_LONG_PUSH == 0 */

// Repeat-Push callback function pointer Type
#if SIMPLEBTN_MODE_ENABLE_COUNTER_REPEAT_PUSH == 0
 typedef void (* simpleButton_Type_RepeatPushCallBack_t)(void);
#else
 typedef void (* simpleButton_Type_RepeatPushCallBack_t)(uint8_t repeatCount);
#endif /* SIMPLEBTN_MODE_ENABLE_COUNTER_REPEAT_PUSH == 0 */

// Combination-Push callback function pointer Type
#if SIMPLEBTN_MODE_ENABLE_COMBINATION != 0
 typedef void (* simpleButton_Type_CombinationPushCallBack_t)(void);
#endif /* SIMPLEBTN_MODE_ENABLE_COMBINATION != 0 */

typedef void (* simpleButton_Type_AsynchronousHandler_t)(
            simpleButton_Type_ShortPushCallBack_t shortPushCallBack,
            simpleButton_Type_LongPushCallBack_t longPushCallBack,
            simpleButton_Type_RepeatPushCallBack_t repeatPushCallBack
        );

typedef void (* simpleButton_Type_InterruptHandler_t)(void);

/**
 * @enum    simpleButton_Type_ButtonState_t
 * 
 * @brief   Enum for button state.
 */
typedef enum simpleButton_Type_ButtonState_t {
    simpleButton_State_Wait_For_Interrupt = 0,

    simpleButton_State_Push_Delay,

    simpleButton_State_Wait_For_End,

    simpleButton_State_Wait_For_Repeat,

    simpleButton_State_Single_Push,

    simpleButton_State_Repeat_Push,

    simpleButton_State_Release_Delay,

    simpleButton_State_Cool_Down,

#if SIMPLEBTN_MODE_ENABLE_COMBINATION != 0

    simpleButton_State_Combination_Push,

    simpleButton_State_Combination_WaitForEnd,

    simpleButton_State_Combination_Release,

#endif /* SIMPLEBTN_MODE_ENABLE_COMBINATION != 0 */
} simpleButton_Type_ButtonState_t;

// struct for button private status.
typedef struct simpleButton_Type_PrivateBtnStatus_t {

    uint32_t                        timeStamp_loop; /* used in while loop */

    volatile uint32_t               timeStamp_interrupt; /* used in interrupt */

    volatile SIMPLEBTN_BITFIELD (simpleButton_Type_ButtonState_t) state : 8;

    uint8_t                         push_time;

} simpleButton_Type_PrivateBtnStatus_t;

// struct for combination status and config.
#if SIMPLEBTN_MODE_ENABLE_COMBINATION != 0

 struct simpleButton_Type_Button_t; // declare
 typedef struct simpleButton_Type_CmbBtnConfig_t {

    volatile struct simpleButton_Type_Button_t* previousButton;

    volatile simpleButton_Type_CombinationPushCallBack_t callBack;

 } simpleButton_Type_CmbBtnConfig_t;

#endif /* SIMPLEBTN_MODE_ENABLE_COMBINATION != 0 */

// struct for public status and config.
typedef struct simpleButton_Type_PublicBtnStatus_t {

#if SIMPLEBTN_MODE_ENABLE_COMBINATION != 0
    simpleButton_Type_CmbBtnConfig_t combinationConfig;
#endif /* SIMPLEBTN_MODE_ENABLE_COMBINATION != 0 */

#if SIMPLEBTN_MODE_ENABLE_ONLY_DEFAULT_TIME == 0
    uint16_t                        longPushMinTime;
    uint16_t                        coolDownTime;
    uint16_t                        repeatWindowTime;
#endif /* SIMPLEBTN_MODE_ENABLE_ONLY_DEFAULT_TIME == 0 */
} simpleButton_Type_PublicBtnStatus_t;

// struct for public method.
typedef struct simpleButton_Type_ButtonMethod_t {

    simpleButton_Type_AsynchronousHandler_t asynchronousHandler;

    simpleButton_Type_InterruptHandler_t interruptHandler;

} simpleButton_Type_ButtonMethod_t;

/**
 * @struct      simpleButton_Type_Button_t
 * 
 * @brief       This struct record the button status and config.
 *              User should not change the value in "Private" section,
 *              unless you know what you are doing.
 */
typedef struct simpleButton_Type_Button_t {

    simpleButton_Type_ButtonMethod_t Methods;

    simpleButton_Type_PublicBtnStatus_t Public;

    simpleButton_Type_PrivateBtnStatus_t Private;

} simpleButton_Type_Button_t;


/**
 * @brief           Initialize the status and config of button object.
 * 
 * @param[inout]    self - Pointer to the button object.
 * @param[in]       GPIOX_BASE - The base address of the GPIO port 
 *                  connected to the button.
 * @param[in]       asynchronousHandler - Function pointer of asynchronous handler.
 * @param[in]       interruptHandler - Function pointer of interrupt handler.
 * 
 * @return          None
 */
SIMPLEBTN_FORCE_INLINE void simpleButton_Private_InitStruct(
    simpleButton_Type_Button_t* self,
    simpleButton_Type_AsynchronousHandler_t asynchronousHandler,
    simpleButton_Type_InterruptHandler_t interruptHandler
) {
    SIMPLEBTN_FUNC_CRITICAL_SECTION_BEGIN();

    /* Initialize the member variables and method */
    self->Private.push_time = 0;
    self->Private.state = simpleButton_State_Wait_For_Interrupt;
    self->Private.timeStamp_interrupt = 0;
    self->Private.timeStamp_loop = 0;

    self->Methods.asynchronousHandler = asynchronousHandler;
    self->Methods.interruptHandler = interruptHandler;

#if SIMPLEBTN_MODE_ENABLE_ONLY_DEFAULT_TIME == 0
    self->Public.coolDownTime = SIMPLEBTN_TIME_COOL_DOWN;
    self->Public.longPushMinTime = SIMPLEBTN_TIME_LONG_PUSH_MIN;
    self->Public.repeatWindowTime = SIMPLEBTN_TIME_REPEAT_WINDOW;
#endif /* SIMPLEBTN_MODE_ENABLE_ONLY_DEFAULT_TIME == 0 */

#if SIMPLEBTN_MODE_ENABLE_COMBINATION != 0
    self->Public.combinationConfig.previousButton = 0;
    self->Public.combinationConfig.callBack = 0;
#endif /* SIMPLEBTN_MODE_ENABLE_COMBINATION != 0 */

    SIMPLEBTN_FUNC_CRITICAL_SECTION_END();
}

/**
 * @brief           Initilize the button.
 * 
 * @param[inout]    self - Pointer to the button object.
 * @param[in]       GPIOX_BASE - The base address of the GPIO port 
 *                  connected to the button.
 * @param[in]       GPIO_Pin_X - The GPIO Pin number connected to the button.
 * @param[in]       EXTI_Trigger_X - The EXTI Trigger of the Pin.
 * @param[in]       asynchronousHandler - Function pointer of asynchronous handler.
 * @param[in]       interruptHandler - Function pointer of interrupt handler.
 * 
 * @return          None
 */
SIMPLEBTN_FORCE_INLINE void simpleButton_Private_InitButton(
    simpleButton_Type_Button_t* self,
    simpleButton_Type_GPIOBase_t GPIOX_BASE,
    simpleButton_Type_GPIOPin_t GPIO_Pin_X,
    simpleButton_Type_EXTITrigger_t EXTI_Trigger_X,
    simpleButton_Type_AsynchronousHandler_t asynchronousHandler,
    simpleButton_Type_InterruptHandler_t interruptHandler
) {

    simpleButton_Private_InitStruct(
        self,
        asynchronousHandler,
        interruptHandler
    );

    simpleButton_Private_InitEXTI(
        GPIOX_BASE,
        GPIO_Pin_X,
        EXTI_Trigger_X
    );

}

/**
 * @brief           Change the status of each button when during the EXTI interrupt
 *                  service routine.
 * 
 * @return          None
 */
SIMPLEBTN_FORCE_INLINE void simpleButton_Private_InterruptHandler(
    simpleButton_Type_Button_t* self
) {
    if (
        (simpleButton_Type_ButtonState_t)(self->Private.state) == simpleButton_State_Wait_For_Interrupt
        || (simpleButton_Type_ButtonState_t)(self->Private.state) == simpleButton_State_Wait_For_Repeat
    ) {
        self->Private.timeStamp_interrupt = SIMPLEBTN_FUNC_GET_TICK();
        self->Private.state = simpleButton_State_Push_Delay;
    }
}

SIMPLEBTN_FORCE_INLINE void
simpleButton_Private_StateWaitForInterrupt_Handler(void) {
    /* Do nothing */
}

SIMPLEBTN_FORCE_INLINE void
simpleButton_Private_StatePushDelay_Handler(
    simpleButton_Type_Button_t* const self,
    const simpleButton_Type_GPIOBase_t gpiox_base,
    const simpleButton_Type_GPIOPin_t  gpio_pin_x,
    const simpleButton_Type_GPIOPinVal_t normal_pin_val
) {
    if (SIMPLEBTN_FUNC_GET_TICK() - self->Private.timeStamp_interrupt <= SIMPLEBTN_TIME_PUSH_DELAY) {
        return; /* still need wait */
    }

    if (SIMPLEBTN_FUNC_READ_PIN(gpiox_base, gpio_pin_x) != normal_pin_val) {
        self->Private.state = simpleButton_State_Wait_For_End;
    } else {
        if (self->Private.push_time == 0) {
            self->Private.state = simpleButton_State_Wait_For_Interrupt;
        } else {
            self->Private.state = simpleButton_State_Wait_For_Repeat;
        }
    }
}

SIMPLEBTN_FORCE_INLINE void
simpleButton_Private_StateWaitForEnd_Handler(
    simpleButton_Type_Button_t* const self,
    const simpleButton_Type_GPIOBase_t gpiox_base,
    const simpleButton_Type_GPIOPin_t  gpio_pin_x,
    const simpleButton_Type_GPIOPinVal_t normal_pin_val
) {
    if (SIMPLEBTN_FUNC_READ_PIN(gpiox_base, gpio_pin_x) == normal_pin_val) {
        self->Private.state = simpleButton_State_Release_Delay;
    } else if (SIMPLEBTN_FUNC_GET_TICK() - self->Private.timeStamp_interrupt > SIMPLEBTN_TIME__TIMEOUT_NORMAL) {

#if defined(SIMPLEBTN_DEBUG)
        SIMPLEBTN_FUNC_PANIC("normal long push time out", , );
#else
        self->Private.push_time = 0;
        self->Private.state = simpleButton_State_Wait_For_Interrupt;
#endif /* defined(SIMPLEBTN_DEBUG) */

    }
}

SIMPLEBTN_FORCE_INLINE void
simpleButton_Private_StateWaitForRepeat_Handler(
    simpleButton_Type_Button_t* const self
) {
    SIMPLEBTN_FUNC_CRITICAL_SECTION_END_M(); /* end multi-thread critical section */
    SIMPLEBTN_FUNC_CRITICAL_SECTION_BEGIN(); /* begin always critical section */

#if SIMPLEBTN_MODE_ENABLE_ONLY_DEFAULT_TIME == 0
    if (SIMPLEBTN_FUNC_GET_TICK() - self->Private.timeStamp_loop > (uint32_t)self->Public.repeatWindowTime)
#else
    if (SIMPLEBTN_FUNC_GET_TICK() - self->Private.timeStamp_loop > SIMPLEBTN_TIME_REPEAT_WINDOW)
#endif /* SIMPLEBTN_MODE_ENABLE_ONLY_DEFAULT_TIME == 0 */
    {

#if SIMPLEBTN_MODE_ENABLE_COUNTER_REPEAT_PUSH == 0
        self->Private.state = simpleButton_State_Single_Push;
#else
        if (self->Private.push_time == 1) {
            self->Private.state = simpleButton_State_Single_Push;
        } else {
            self->Private.state = simpleButton_State_Repeat_Push;
        }
#endif /* SIMPLEBTN_MODE_ENABLE_COUNTER_REPEAT_PUSH == 0 */

    } // end if

    SIMPLEBTN_FUNC_CRITICAL_SECTION_END(); /* end always critical section */
    SIMPLEBTN_FUNC_CRITICAL_SECTION_BEGIN_M(); /* begin multi-thread critical section */
}

// a helper function
SIMPLEBTN_FORCE_INLINE void
simpleButton_Private_Do_LongPush(
    simpleButton_Type_Button_t* const self,
    simpleButton_Type_LongPushCallBack_t longPushCallBack
) {

#if SIMPLEBTN_MODE_ENABLE_TIMER_LONG_PUSH == 0
    (void)self;
    SIMPLEBTN_FUNC_CRITICAL_SECTION_END_M(); /* end multi-thread critical section */
    if (longPushCallBack != 0) {
        longPushCallBack();
    }
    SIMPLEBTN_FUNC_CRITICAL_SECTION_BEGIN_M(); /* begin multi-thread critical section */
#else
    uint32_t longPushTime = SIMPLEBTN_FUNC_GET_TICK() - self->Private.timeStamp_interrupt;
    SIMPLEBTN_FUNC_CRITICAL_SECTION_END_M(); /* end multi-thread critical section */
    if (longPushCallBack != 0) {
        longPushCallBack(longPushTime);
    }
    SIMPLEBTN_FUNC_CRITICAL_SECTION_BEGIN_M(); /* begin multi-thread critical section */
#endif /* SIMPLEBTN_MODE_ENABLE_TIMER_LONG_PUSH == 0 */

}

SIMPLEBTN_FORCE_INLINE void
simpleButton_Private_Do_ShortPush(
    simpleButton_Type_ShortPushCallBack_t shortPushCallBack
) {
    SIMPLEBTN_FUNC_CRITICAL_SECTION_END_M(); /* end multi-thread critical section */
    if (shortPushCallBack != 0) {
        shortPushCallBack();
    }
    SIMPLEBTN_FUNC_CRITICAL_SECTION_BEGIN_M(); /* begin multi-thread critical section */
}

SIMPLEBTN_FORCE_INLINE void
simpleButton_Private_StateSinglePush_Handler(
    simpleButton_Type_Button_t* const self,
    simpleButton_Type_ShortPushCallBack_t shortPushCallBack,
    simpleButton_Type_LongPushCallBack_t longPushCallBack
) {
    
#if SIMPLEBTN_MODE_ENABLE_ONLY_DEFAULT_TIME == 0
    if (SIMPLEBTN_FUNC_GET_TICK() - self->Private.timeStamp_interrupt > (uint32_t)self->Public.longPushMinTime)
#else
    if (SIMPLEBTN_FUNC_GET_TICK() - self->Private.timeStamp_interrupt > SIMPLEBTN_TIME_LONG_PUSH_MIN)
#endif /* SIMPLEBTN_MODE_ENABLE_ONLY_DEFAULT_TIME == 0 */
    {
        simpleButton_Private_Do_LongPush(self, longPushCallBack);
    } else {
        simpleButton_Private_Do_ShortPush(shortPushCallBack);
    }

    self->Private.push_time = 0;
    self->Private.timeStamp_loop = SIMPLEBTN_FUNC_GET_TICK();
    self->Private.state = simpleButton_State_Cool_Down;
}

SIMPLEBTN_FORCE_INLINE void
simpleButton_Private_StateRepeatPush_Handler(
    simpleButton_Type_Button_t* const self,
    simpleButton_Type_RepeatPushCallBack_t repeatPushCallBack
) {
    SIMPLEBTN_FUNC_CRITICAL_SECTION_END_M(); /* end multi-thread critical section */

    if (repeatPushCallBack != 0) {

#if SIMPLEBTN_MODE_ENABLE_COUNTER_REPEAT_PUSH == 0
        repeatPushCallBack();
#else
        repeatPushCallBack(self->Private.push_time);
#endif /* SIMPLEBTN_MODE_ENABLE_COUNTER_REPEAT_PUSH == 0 */

    } // end if

    SIMPLEBTN_FUNC_CRITICAL_SECTION_BEGIN_M(); /* begin multi-thread critical section */
    self->Private.push_time = 0;
    self->Private.timeStamp_loop = SIMPLEBTN_FUNC_GET_TICK();
    self->Private.state = simpleButton_State_Cool_Down;
}

// a helper function
SIMPLEBTN_FORCE_INLINE void
simpleButton_Private_CmbBtnAfterReleaseOK(
    simpleButton_Type_Button_t* const self
) {
#if SIMPLEBTN_MODE_ENABLE_COMBINATION != 0

    if (self->Public.combinationConfig.callBack == 0 || self->Public.combinationConfig.previousButton == 0) {
        return; /* user didn't use combination button */
    }

    /* prev-button should be [Combination]_WaitForEnd. */
    if (self->Public.combinationConfig.previousButton->Private.state != simpleButton_State_Combination_WaitForEnd) {
        if (self->Public.combinationConfig.previousButton->Private.state != simpleButton_State_Wait_For_End) {
            return; /* prev-button isn't [Combination]_WaitForEnd. */
        } else {
            self->Public.combinationConfig.previousButton->Private.state = simpleButton_State_Combination_WaitForEnd;
        }
    }

    self->Private.state = simpleButton_State_Combination_Push;

#endif /* SIMPLEBTN_MODE_ENABLE_COMBINATION != 0 */
}

// a helper function
SIMPLEBTN_FORCE_INLINE void
simpleButton_Private_ReleaseOK(
    simpleButton_Type_Button_t* const self
) {
    self->Private.push_time ++;
    self->Private.timeStamp_loop = SIMPLEBTN_FUNC_GET_TICK();

    /* enable counter-repeat-push or not */
#if SIMPLEBTN_MODE_ENABLE_COUNTER_REPEAT_PUSH == 0
    self->Private.state = (self->Private.push_time == 1)
        ? simpleButton_State_Wait_For_Repeat : simpleButton_State_Repeat_Push;
#else
    self->Private.state = (self->Private.push_time < 0xFF)
        ? simpleButton_State_Wait_For_Repeat : simpleButton_State_Repeat_Push;
#endif /* SIMPLEBTN_MODE_ENABLE_COUNTER_REPEAT_PUSH == 0 */

    simpleButton_Private_CmbBtnAfterReleaseOK(self);
}


SIMPLEBTN_FORCE_INLINE void
simpleButton_Private_StateReleaseDelay_Handler(
    simpleButton_Type_Button_t* const self,
    const simpleButton_Type_GPIOBase_t gpiox_base,
    const simpleButton_Type_GPIOPin_t  gpio_pin_x,
    const simpleButton_Type_GPIOPinVal_t normal_pin_val
) {
    if (SIMPLEBTN_FUNC_GET_TICK() - self->Private.timeStamp_loop <= SIMPLEBTN_TIME_RELEASE_DELAY) {
        return; /* still need wait */
    }

    if (SIMPLEBTN_FUNC_READ_PIN(gpiox_base, gpio_pin_x) == normal_pin_val) {
        simpleButton_Private_ReleaseOK(self);
    } else {
        self->Private.state = simpleButton_State_Wait_For_End;
    }
}

SIMPLEBTN_FORCE_INLINE void
simpleButton_Private_StateCoolDown_Handler(
    simpleButton_Type_Button_t* const self
) {
#if SIMPLEBTN_MODE_ENABLE_ONLY_DEFAULT_TIME == 0
    if (SIMPLEBTN_FUNC_GET_TICK() - self->Private.timeStamp_loop > self->Public.coolDownTime)
#else
    if (SIMPLEBTN_FUNC_GET_TICK() - self->Private.timeStamp_loop > SIMPLEBTN_TIME_COOL_DOWN)
#endif /* SIMPLEBTN_MODE_ENABLE_ONLY_DEFAULT_TIME == 0 */
    {
        self->Private.state = simpleButton_State_Wait_For_Interrupt;
    }

}

#if SIMPLEBTN_MODE_ENABLE_COMBINATION != 0
SIMPLEBTN_FORCE_INLINE void
simpleButton_Private_StateCombinationPush_Handler(
    simpleButton_Type_Button_t* const self
) {
    simpleButton_Type_CombinationPushCallBack_t cmbCallBack;
    cmbCallBack = self->Public.combinationConfig.callBack;

    SIMPLEBTN_FUNC_CRITICAL_SECTION_END_M(); /* end multi-thread critical section */

    if (cmbCallBack != 0) {
        cmbCallBack();
    }

    SIMPLEBTN_FUNC_CRITICAL_SECTION_BEGIN_M(); /* begin multi-thread critical section */
    self->Private.push_time = 0;
    self->Private.timeStamp_loop = SIMPLEBTN_FUNC_GET_TICK();
    self->Private.state = simpleButton_State_Cool_Down;
}

SIMPLEBTN_FORCE_INLINE void
simpleButton_Private_StateCombinationWaitForEnd_Handler(
    simpleButton_Type_Button_t* const self,
    const simpleButton_Type_GPIOBase_t gpiox_base,
    const simpleButton_Type_GPIOPin_t  gpio_pin_x,
    const simpleButton_Type_GPIOPinVal_t normal_pin_val
) {
    if (SIMPLEBTN_FUNC_READ_PIN(gpiox_base, gpio_pin_x) == normal_pin_val) {
        self->Private.state = simpleButton_State_Combination_Release;
    } else if (SIMPLEBTN_FUNC_GET_TICK() - self->Private.timeStamp_interrupt > SIMPLEBTN_TIME__TIMEOUT_COMBINATION) {

#if defined(SIMPLEBTN_DEBUG)
        SIMPLEBTN_FUNC_PANIC("combination long push time out", , );
#else
        self->Private.push_time = 0;
        self->Private.state = simpleButton_State_Wait_For_Interrupt;
#endif /* defined(SIMPLEBTN_DEBUG) */

    }
}

SIMPLEBTN_FORCE_INLINE void
simpleButton_Private_StateCombinationRelease_Handler(
    simpleButton_Type_Button_t* const self,
    const simpleButton_Type_GPIOBase_t gpiox_base,
    const simpleButton_Type_GPIOPin_t  gpio_pin_x,
    const simpleButton_Type_GPIOPinVal_t normal_pin_val
) {
    if (SIMPLEBTN_FUNC_GET_TICK() - self->Private.timeStamp_loop <= SIMPLEBTN_TIME_RELEASE_DELAY) {
        return; /* still need wait */
    }

    if (SIMPLEBTN_FUNC_READ_PIN(gpiox_base, gpio_pin_x) == normal_pin_val) {
        self->Private.push_time = 0;
        self->Private.timeStamp_loop = SIMPLEBTN_FUNC_GET_TICK();
        self->Private.state = simpleButton_State_Cool_Down;
    } else {
        self->Private.state = simpleButton_State_Combination_WaitForEnd;
    }
}

#endif /* SIMPLEBTN_MODE_ENABLE_COMBINATION != 0 */


SIMPLEBTN_FORCE_INLINE void
simpleButton_Private_StateDefault_Handler(
    simpleButton_Type_Button_t* const self
) {

#if defined(SIMPLEBTN_DEBUG)
    SIMPLEBTN_FUNC_PANIC("invalid button state", , );
#else
    self->Private.push_time = 0;
    self->Private.state = simpleButton_State_Wait_For_Interrupt;
#endif /* defined(SIMPLEBTN_DEBUG) */

}

/**
 * @brief           Asynchronously call the callback function in while loop.
 * @param[inout]    self - pointer to self struct.
 * @param[in]       gpiox_base - Address of GPIO port connected to the button.
 * @param[in]       gpio_pin_x - GPIO pin number connected to the button.
 * @param[in]       normal_pin_val - Normal(didn't push) pin value of button pin. (can be 1 or 0)
 * @param[in]       shortPushCB - callback function for short push.
 * @param[in]       longPushCB - callback function for long push.
 * @param[in]       repeatPushCB - callback function for repeat push.
 * @return          None
 */
SIMPLEBTN_SUGGEST_INLINE void
simpleButton_Private_AsynchronousHandler(
    simpleButton_Type_Button_t* const self,
    const simpleButton_Type_GPIOBase_t gpiox_base,
    const simpleButton_Type_GPIOPin_t  gpio_pin_x,
    const simpleButton_Type_GPIOPinVal_t normal_pin_val,
    simpleButton_Type_ShortPushCallBack_t shortPushCB,
    simpleButton_Type_LongPushCallBack_t longPushCB,
    simpleButton_Type_RepeatPushCallBack_t repeatPushCB
) {
    SIMPLEBTN_FUNC_CRITICAL_SECTION_BEGIN_M(); /* begin multi-thread critical section */

    switch ( (simpleButton_Type_ButtonState_t)(self->Private.state) ) {
    case simpleButton_State_Wait_For_Interrupt: {
        simpleButton_Private_StateWaitForInterrupt_Handler();
        break;
    }

    case simpleButton_State_Push_Delay: {
        simpleButton_Private_StatePushDelay_Handler(self, gpiox_base, gpio_pin_x, normal_pin_val);
        break;
    }

    case simpleButton_State_Wait_For_End: {
        simpleButton_Private_StateWaitForEnd_Handler(self, gpiox_base, gpio_pin_x, normal_pin_val);
        break;
    }

    case simpleButton_State_Wait_For_Repeat: {
        simpleButton_Private_StateWaitForRepeat_Handler(self);
        break;
    }

    case simpleButton_State_Single_Push: {
        simpleButton_Private_StateSinglePush_Handler(self, shortPushCB, longPushCB);
        break;
    }

    case simpleButton_State_Repeat_Push: {
        simpleButton_Private_StateRepeatPush_Handler(self, repeatPushCB);
        break;
    }

    case simpleButton_State_Release_Delay: {
        simpleButton_Private_StateReleaseDelay_Handler(self, gpiox_base, gpio_pin_x, normal_pin_val);
        break;
    }

    case simpleButton_State_Cool_Down: {
        simpleButton_Private_StateCoolDown_Handler(self);
        break;
    }

#if SIMPLEBTN_MODE_ENABLE_COMBINATION != 0

    case simpleButton_State_Combination_Push: {
        simpleButton_Private_StateCombinationPush_Handler(self);
        break;
    }

    case simpleButton_State_Combination_WaitForEnd: {
        simpleButton_Private_StateCombinationWaitForEnd_Handler(self, gpiox_base, gpio_pin_x, normal_pin_val);
        break;
    }

    case simpleButton_State_Combination_Release: {
        simpleButton_Private_StateCombinationRelease_Handler(self, gpiox_base, gpio_pin_x, normal_pin_val);
        break;
    }

#endif /* SIMPLEBTN_MODE_ENABLE_COMBINATION != 0 */

    default: {
        simpleButton_Private_StateDefault_Handler(self);
        break;
    }

    } // end switch

    SIMPLEBTN_FUNC_CRITICAL_SECTION_END_M(); /* end multi-thread critical section */
}


#if (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)) \
    || (defined(__cplusplus) && __cplusplus >= 201103L)

SIMPLEBTN_FORCE_INLINE uint32_t simpleButton_Private_IsIdle(const simpleButton_Type_Button_t self) {
    return (self.Private.state == simpleButton_State_Wait_For_Interrupt);
}

#define SIMPLEBTN_ISIDLE_1(Btn)         simpleButton_Private_IsIdle(Btn)

#define SIMPLEBTN_ISIDLE_2(Btn, ...)    (SIMPLEBTN_ISIDLE_1(Btn) & SIMPLEBTN_ISIDLE_1(__VA_ARGS__))

#define SIMPLEBTN_ISIDLE_3(Btn, ...)    (SIMPLEBTN_ISIDLE_1(Btn) & SIMPLEBTN_ISIDLE_2(__VA_ARGS__))

#define SIMPLEBTN_ISIDLE_4(Btn, ...)    (SIMPLEBTN_ISIDLE_1(Btn) & SIMPLEBTN_ISIDLE_3(__VA_ARGS__))

#define SIMPLEBTN_ISIDLE_5(Btn, ...)    (SIMPLEBTN_ISIDLE_1(Btn) & SIMPLEBTN_ISIDLE_4(__VA_ARGS__))

#define SIMPLEBTN_ISIDLE_6(Btn, ...)    (SIMPLEBTN_ISIDLE_1(Btn) & SIMPLEBTN_ISIDLE_5(__VA_ARGS__))

#define SIMPLEBTN_ISIDLE_7(Btn, ...)    (SIMPLEBTN_ISIDLE_1(Btn) & SIMPLEBTN_ISIDLE_6(__VA_ARGS__))

#define SIMPLEBTN_ISIDLE_8(Btn, ...)    (SIMPLEBTN_ISIDLE_1(Btn) & SIMPLEBTN_ISIDLE_7(__VA_ARGS__))

#define SIMPLEBTN_ISIDLE_9(Btn, ...)    (SIMPLEBTN_ISIDLE_1(Btn) & SIMPLEBTN_ISIDLE_8(__VA_ARGS__))

#define SIMPLEBTN_ISIDLE_10(Btn, ...)    (SIMPLEBTN_ISIDLE_1(Btn) & SIMPLEBTN_ISIDLE_9(__VA_ARGS__))

#define SIMPLEBTN_ISIDLE_11(Btn, ...)    (SIMPLEBTN_ISIDLE_1(Btn) & SIMPLEBTN_ISIDLE_10(__VA_ARGS__))

#define SIMPLEBTN_ISIDLE_12(Btn, ...)    (SIMPLEBTN_ISIDLE_1(Btn) & SIMPLEBTN_ISIDLE_11(__VA_ARGS__))

#define SIMPLEBTN_ISIDLE_13(Btn, ...)    (SIMPLEBTN_ISIDLE_1(Btn) & SIMPLEBTN_ISIDLE_12(__VA_ARGS__))

#define SIMPLEBTN_ISIDLE_14(Btn, ...)    (SIMPLEBTN_ISIDLE_1(Btn) & SIMPLEBTN_ISIDLE_13(__VA_ARGS__))

#define SIMPLEBTN_ISIDLE_15(Btn, ...)    (SIMPLEBTN_ISIDLE_1(Btn) & SIMPLEBTN_ISIDLE_14(__VA_ARGS__))

#define SIMPLEBTN_ISIDLE_16(Btn, ...)    (SIMPLEBTN_ISIDLE_1(Btn) & SIMPLEBTN_ISIDLE_15(__VA_ARGS__))

#define SIMPLEBTN_ISIDLE_17(Btn, ...)    (SIMPLEBTN_ISIDLE_1(Btn) & SIMPLEBTN_ISIDLE_16(__VA_ARGS__))

#define SIMPLEBTN_ISIDLE_18(Btn, ...)    (SIMPLEBTN_ISIDLE_1(Btn) & SIMPLEBTN_ISIDLE_17(__VA_ARGS__))

#define SIMPLEBTN_ISIDLE_19(Btn, ...)    (SIMPLEBTN_ISIDLE_1(Btn) & SIMPLEBTN_ISIDLE_18(__VA_ARGS__))

#define SIMPLEBTN_ISIDLE_20(Btn, ...)    (SIMPLEBTN_ISIDLE_1(Btn) & SIMPLEBTN_ISIDLE_19(__VA_ARGS__))

#define SIMPLEBTN_ISIDLE_21(Btn, ...)    (SIMPLEBTN_ISIDLE_1(Btn) & SIMPLEBTN_ISIDLE_20(__VA_ARGS__))

#define SIMPLEBTN_ISIDLE_22(Btn, ...)    (SIMPLEBTN_ISIDLE_1(Btn) & SIMPLEBTN_ISIDLE_21(__VA_ARGS__))

#define SIMPLEBTN_ISIDLE_23(Btn, ...)    (SIMPLEBTN_ISIDLE_1(Btn) & SIMPLEBTN_ISIDLE_22(__VA_ARGS__))

#define SIMPLEBTN_ISIDLE_24(Btn, ...)    (SIMPLEBTN_ISIDLE_1(Btn) & SIMPLEBTN_ISIDLE_23(__VA_ARGS__))

#define SIMPLEBTN_ISIDLE_25(Btn, ...)    (SIMPLEBTN_ISIDLE_1(Btn) & SIMPLEBTN_ISIDLE_24(__VA_ARGS__))

#define SIMPLEBTN_ISIDLE_26(Btn, ...)    (SIMPLEBTN_ISIDLE_1(Btn) & SIMPLEBTN_ISIDLE_25(__VA_ARGS__))

#define SIMPLEBTN_ISIDLE_27(Btn, ...)    (SIMPLEBTN_ISIDLE_1(Btn) & SIMPLEBTN_ISIDLE_26(__VA_ARGS__))

#define SIMPLEBTN_ISIDLE_28(Btn, ...)    (SIMPLEBTN_ISIDLE_1(Btn) & SIMPLEBTN_ISIDLE_27(__VA_ARGS__))

#define SIMPLEBTN_ISIDLE_29(Btn, ...)    (SIMPLEBTN_ISIDLE_1(Btn) & SIMPLEBTN_ISIDLE_28(__VA_ARGS__))

#define SIMPLEBTN_ISIDLE_30(Btn, ...)    (SIMPLEBTN_ISIDLE_1(Btn) & SIMPLEBTN_ISIDLE_29(__VA_ARGS__))

#define SIMPLEBTN_ISIDLE_31(Btn, ...)    (SIMPLEBTN_ISIDLE_1(Btn) & SIMPLEBTN_ISIDLE_30(__VA_ARGS__))

#define SIMPLEBTN_ISIDLE_32(Btn, ...)    (SIMPLEBTN_ISIDLE_1(Btn) & SIMPLEBTN_ISIDLE_31(__VA_ARGS__))

#define SIMPLEBTN_ALLISIDLE(...)    \
    SIMPLEBTN_CONNECT2(SIMPLEBTN_ISIDLE_, SIMPLEBTN_COUNT_ARGS(__VA_ARGS__))(__VA_ARGS__)

/**
 * @brief   Start low power if all of the buttons are idle.
 * @param   __VA_ARGS__ - button object. (passing 1 ~ 32 parameters is OK)
 * @return  None
 */
#define SIMPLEBTN__START_LOWPOWER(...)  \
    do {                                            \
        SIMPLEBTN_FUNC_CRITICAL_SECTION_BEGIN();    \
        if (SIMPLEBTN_ALLISIDLE(__VA_ARGS__)) {     \
            SIMPLEBTN_FUNC_START_LOW_POWER();       \
        }                                           \
        SIMPLEBTN_FUNC_CRITICAL_SECTION_END();      \
    } while (0)

#endif /* >= C99 or C++11 */


#define SIMPLEBTN__CREATE(GPIOx_BASE, GPIO_Pin_x, EXTI_Trigger_x, __name)       \
    simpleButton_Type_Button_t                                                  \
    SIMPLEBTN_CONNECT2(SIMPLEBTN_NAMESPACE, __name) = {0};                      \
                                                                                \
    static void                                                                 \
    SIMPLEBTN_CONNECT2(simpleButton_Private_AsyHandler_, __name)(               \
        simpleButton_Type_ShortPushCallBack_t  shortPushCallBack,               \
        simpleButton_Type_LongPushCallBack_t   longPushCallBack,                \
        simpleButton_Type_RepeatPushCallBack_t repeatPushCallBack               \
    ) {                                                                         \
        const uint8_t normalPinVal =                                            \
            ((EXTI_Trigger_x) == SIMPLEBTN_EXTI_TRIGGER_FALLING) ? 1 : 0;       \
                                                                                \
        simpleButton_Private_AsynchronousHandler(                               \
            &(SIMPLEBTN_CONNECT2(SIMPLEBTN_NAMESPACE, __name)),                 \
            (GPIOx_BASE),                                                       \
            (GPIO_Pin_x),                                                       \
            normalPinVal,                                                       \
            shortPushCallBack,                                                  \
            longPushCallBack,                                                   \
            repeatPushCallBack                                                  \
        );                                                                      \
    }                                                                           \
                                                                                \
    static void                                                                 \
    SIMPLEBTN_CONNECT2(simpleButton_Private_ITHandler_, __name)(void) {         \
        simpleButton_Private_InterruptHandler(                                  \
            &(SIMPLEBTN_CONNECT2(SIMPLEBTN_NAMESPACE, __name))                  \
        );                                                                      \
    }                                                                           \
                                                                                \
    SIMPLEBTN_C_API void                                                        \
    SIMPLEBTN_CONNECT3(SIMPLEBTN_NAMESPACE, __name, _Init)(void) {              \
        simpleButton_Private_InitButton(                                        \
            &(SIMPLEBTN_CONNECT2(SIMPLEBTN_NAMESPACE, __name)),                 \
            (GPIOx_BASE),                                                       \
            (GPIO_Pin_x),                                                       \
            (EXTI_Trigger_x),                                                   \
            &(SIMPLEBTN_CONNECT2(simpleButton_Private_AsyHandler_, __name)),    \
            &(SIMPLEBTN_CONNECT2(simpleButton_Private_ITHandler_, __name))      \
        );                                                                      \
    }



#define SIMPLEBTN__DECLARE(__name)                                              \
    extern simpleButton_Type_Button_t                                           \
    SIMPLEBTN_CONNECT2(SIMPLEBTN_NAMESPACE, __name);                            \
    SIMPLEBTN_C_API void                                                        \
    SIMPLEBTN_CONNECT3(SIMPLEBTN_NAMESPACE, __name, _Init)(void);


#endif /* SIMPLEBUTTON_H__ */
