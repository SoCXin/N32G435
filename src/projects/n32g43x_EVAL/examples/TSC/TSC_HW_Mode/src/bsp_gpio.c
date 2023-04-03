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
 * @file bsp_gpio.c
 * @author Nations
 * @version V1.2.1
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#include "bsp_gpio.h"

/***
 * @brief    Configure the ports of TSC channels for sample.
 * @param:  None
 * @retval: None
 */
void tsc_gpio_init(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);

    RCC_EnableAPB2PeriphClk( RCC_APB2_PERIPH_GPIOA
                            |RCC_APB2_PERIPH_GPIOB
                            |RCC_APB2_PERIPH_GPIOC
                            |RCC_APB2_PERIPH_GPIOD, 
                            ENABLE);

    /*  tsc GPIOA port 2 3 4 5 6 7*/
    /*  PA2: TSC_CH1        PA3: TSC_CH4        PA4: TSC_CH5        PA5:TSC_CH6
        PA6: TSC_CH23       PA7: TSC_CH20       */
    GPIO_InitStructure.Pin  = GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 
                            | GPIO_PIN_6 | GPIO_PIN_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Analog;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);


    /* tsc GPIOB port 0 1 2 10 11 12 13 14 15*/
    /*  PB0: TSC_CH7        PB1: TSC_CH8        PB2: TSC_CH9        PB10:TSC_CH19
        PB11:TSC_CH10       PB12:TSC_CH11       PB13:TSC_CH16       PB14:TSC_CH12
        PB15:TSC_CH15 */
    GPIO_InitStructure.Pin  = GPIO_PIN_0  | GPIO_PIN_1  | GPIO_PIN_2  | GPIO_PIN_10 
                            | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14
                            | GPIO_PIN_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Analog;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);


    /* tsc GPIOC port 4 5 6 7 8 */
    /*  PC4: TSC_CH21       PC5: TSC_CH22       PC6: TSC_CH13       PB7: TSC_CH14
        PC8: TSC_CH17 */
    GPIO_InitStructure.Pin  = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 
                            | GPIO_PIN_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Analog;
    GPIO_InitPeripheral(GPIOC, &GPIO_InitStructure);

    /* tsc GPIOD port 8 9 10 11 */
    /*  PD8: TSC_CH0        PD9: TSC_CH3        PD10:TSC_CH2        PD11:TSC_CH18 */
    GPIO_InitStructure.Pin       = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Analog;
    GPIO_InitPeripheral(GPIOD, &GPIO_InitStructure);

    /*PB7: TSC OUT*/
    GPIO_InitStructure.Pin              = GPIO_PIN_7;
    GPIO_InitStructure.GPIO_Current     = GPIO_DC_2mA;
    GPIO_InitStructure.GPIO_Mode        = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Slew_Rate   = GPIO_Slew_Rate_High;
    GPIO_InitStructure.GPIO_Alternate   = GPIO_AF9_TSC;
    GPIO_InitPeripheral(GPIOB,&GPIO_InitStructure);
}

/***
 * @brief    Configure the ports of led.
 * @param:  None
 * @retval: None
 */
void led_gpio_init(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);

    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);

    /*PC0:LED3  PC1:LED2  PC2:LED1*/
    GPIOC->POD &= ~(0x07UL);
    GPIO_InitStructure.Pin          = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2;
    GPIO_InitStructure.GPIO_Current = GPIO_DC_2mA;
    GPIO_InitStructure.GPIO_Pull    = GPIO_No_Pull;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_Out_PP;
    GPIO_InitPeripheral(GPIOC,&GPIO_InitStructure); 
}

/***
 * @brief    disable the port of LED.
  * @param:  None
  * @retval: None
  */
void led_gpio_DeInit(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);

    /*PC0:LED3  PC1:LED2  PC2:LED1*/
    GPIO_InitStructure.Pin          = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_Analog;
    GPIO_InitPeripheral(GPIOC,&GPIO_InitStructure); 
}



