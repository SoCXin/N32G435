/*****************************************************************************
 * Copyright (c) 2022, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file bsp_gpio.h
 * @author Nations
 * @version V1.2.1
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#ifndef __BSP_GPIO_H__
#define __BSP_GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif
    
#include "main.h"

#define LED_D1_PIN      (GPIO_PIN_2)
#define LED_D2_PIN      (GPIO_PIN_1)
#define LED_D3_PIN      (GPIO_PIN_0)

#define LED_D1_ON       (GPIOC->POD |= LED_D1_PIN)
#define LED_D2_ON       (GPIOC->POD |= LED_D2_PIN)
#define LED_D3_ON       (GPIOC->POD |= LED_D3_PIN)

#define LED_D1_OFF      (GPIOC->POD &= (~LED_D1_PIN))
#define LED_D2_OFF      (GPIOC->POD &= (~LED_D2_PIN))
#define LED_D3_OFF      (GPIOC->POD &= (~LED_D3_PIN))

#define LED_D1_REVERSE  (GPIOC->POD ^= LED_D1_PIN)
#define LED_D2_REVERSE  (GPIOC->POD ^= LED_D2_PIN)
#define LED_D3_REVERSE  (GPIOC->POD ^= LED_D3_PIN)

void tsc_gpio_init(void);
void led_gpio_init(void);
void led_gpio_DeInit(void);

#ifdef __cplusplus
}
#endif

#endif /* __BSP_GPIO_H__ */


