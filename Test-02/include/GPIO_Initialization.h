/*
 * This file is part of the µOS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2014 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef GPIO_INITIALIZATION_H_
#define GPIO_INITIALIZATION_H_

#include "stm32f10x.h"

// ----- pin definitions ------------------------------------------------------

// Adjust these definitions for your own board.

// Olimex STM32-H103 definitions (the GREEN pin, C12, active low)
// (SEGGER J-Link device name: STM32F103RB).

// Port numbers: 0=A, 1=B, 2=C, 3=D, 4=E, 5=F, 6=G, ...
#define GPIO_PORT_NUMBER               (0)
#define GPIO_PIN_NUMBER                (5)
#define GPIO_ACTIVE_LOW                (1)

#define GPIOx(_N)                 ((GPIO_TypeDef *)(GPIOA_BASE + (GPIOB_BASE-GPIOA_BASE)*(_N)))
#define GPIO_PIN_MASK(_N)              (1 << (_N))
#define GPIO_RCC_MASKx(_N)             (RCC_APB2Periph_GPIOA << (_N))
// ----------------------------------------------------------------------------

extern
void
GPIO_pin_init(void);

// ----------------------------------------------------------------------------

inline void
GPIO_pin_on(void);

inline void
GPIO_pin_off(void);

// ----------------------------------------------------------------------------

inline void
__attribute__((always_inline))
GPIO_pin_on(void)
{
#if (GPIO_ACTIVE_LOW)
  GPIO_ResetBits(GPIOx(GPIO_PORT_NUMBER),
      GPIO_PIN_MASK(GPIO_PIN_NUMBER));
#else
  GPIO_SetBits(GPIOx(GPIO_PORT_NUMBER),
      GPIO_PIN_MASK(GPIO_PIN_NUMBER));
#endif
}

inline void
__attribute__((always_inline))
GPIO_pin_off(void)
{
#if (GPIO_ACTIVE_LOW)
  GPIO_SetBits(GPIOx(GPIO_PORT_NUMBER),
      GPIO_PIN_MASK(GPIO_PIN_NUMBER));
#else
  GPIO_ResetBits(GPIOx(GPIO_PORT_NUMBER),
      GPIO_PIN_MASK(GPIO_PIN_NUMBER));
#endif
}

// ----------------------------------------------------------------------------

#endif // GPIO_INITIALIZATION_H_
