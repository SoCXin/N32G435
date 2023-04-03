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
 * @file bsp_tsc.c
 * @author Nations
 * @version V1.2.1
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#include "bsp_tsc.h"
#include "bsp_gpio.h"

// The following is the corresponding relationship of port, TSC channel, pulse data and key of this demo.
/*  port <-------->  TSC channel    <-------->  key on board

    PA2  <--------> TSC channel 1   <-------->  KEY "T1"

    PA3  <--------> TSC channel 4   <-------->  KEY "T4"
    PA4  <--------> TSC channel 5   <-------->  KEY "T5"
    PA5  <--------> TSC channel 6   <-------->  KEY "T6"
    PB0  <--------> TSC channel 7   <-------->  KEY "T7"

    PB1  <--------> TSC channel 8   <-------->  KEY "T8"
    PB2  <--------> TSC channel 9   <-------->  KEY "T9"
    PB11 <--------> TSC channel 10  <-------->  KEY "T10"
    PB12 <--------> TSC channel 11  <-------->  KEY "T11"

    PB14 <--------> TSC channel 12  <-------->  KEY "T12"
    PC6  <--------> TSC channel 13  <-------->  KEY "T13"
    PC7  <--------> TSC channel 14  <-------->  KEY "T14"
    PB15 <--------> TSC channel 15  <-------->  KEY "T15"

    PB13 <--------> TSC channel 16  <-------->  KEY "T16"
    PC8  <--------> TSC channel 17  <-------->  KEY "T17"
    PD10 <--------> TSC channel 19  <-------->  KEY "T19"

    PA7  <--------> TSC channel 20  <-------->  KEY "T20"
    PC4  <--------> TSC channel 21  <-------->  KEY "T21"
    PC5  <--------> TSC channel 22  <-------->  KEY "T22"
    PA6  <--------> TSC channel 23  <-------->  KEY "T23"
*/

//PB7  <------->  TSC_R_CHG     <------->  TSC_OUT

static uint8_t KeyCh[KEY_NUM] = {1,4,5,6,7,8,9,10,11,12,13,14,15,16,17,19,20,21,22,23};

/******************************************************************/
/***
 * @brief   Init tsc by hardware mode,all channels used.
 * @param:  None
 * @retval: None
 */
void BSP_TSC_HwInit(void)
{
    TSC_InitType Init = {0};

    /* Select LSI as TSC clock source and enable */
    TSC_ClockConfig(TSC_CLK_SRC_LSI);

    /* Init gpio port used for TSC */
    tsc_gpio_init();

    /* Init TSC model */
    Init.Mode   = TSC_HW_DETECT_MODE;   /* HW detect mode*/
    Init.Period = TSC_DET_PERIOD_8;     /* Detect priod= 8/TSC_CLK */
    Init.Filter = TSC_DET_FILTER_1;     /* Detect filter= 1 sample */
    Init.Type   = TSC_DET_TYPE_LESS;    /* Enable less detect */
    Init.Int    = TSC_IT_DET_ENABLE;    /* Enable interrupt */
    Init.PadOpt = TSC_PAD_INTERNAL_RES; /* Use internal resistor */
    Init.Speed  = TSC_PAD_SPEED_0;      /* Low speed */
    TSC_Init(&Init);

    /*Select the internal resistance of each channel as 126K*/
    TSC_ConfigInternalResistor(TSC_CHN_SEL_ALL, TSC_RESRx_CHN_RESIST_7 );
}

/***
 * @brief   Get TSC cnt value of each channel after poweron,and set as threshold
 * @param:  None
 * @retval: None
 */
void BSP_TSC_AutoAdjust(void)
{
    uint32_t i,tCnt;

    /* Config TSC wakeup time,it is controlled by RTC module*/
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_PWR,ENABLE);    /*Enable PWR  peripheral Clock*/
    PWR_BackupAccessEnable(ENABLE);     /* Set bit 8 of PWR_CTRL1.Open PWR DBP.*/
    RCC_ConfigRtcClk(RCC_RTCCLK_SRC_LSI);   /* Set LSI as RTC clock*/
    RCC_EnableRtcClk(ENABLE);           /* Enable RTC clock*/
    RTC_EnableWakeUpTsc(0x2fe);     /* Set TSC wakeup time as 0x2FE*LSI */

    /* Get cnt value of each channel */
    for(i=0;i<KEY_NUM;i++)
    {
        __TSC_CHN_CONFIG(0x1UL << KeyCh[i]);   /* enable a channel */
        __TSC_HW_ENABLE();              /* enable hw detect */

//        while(__TSC_GET_HW_MODE()==RESET);    /* wait until tsc wakeup and start detect */
        
        while(__TSC_GET_CHN_NUMBER() != KeyCh[i]); /* make sure current detect channel is correct */

        while((tCnt=__TSC_GET_CHN_CNT())==0);   /* wait until detect done */
        __TSC_HW_DISABLE();     /* disable hw detect */

        TSC_ConfigThreshold(0x1UL << KeyCh[i], tCnt, tCnt/3);  /* set the cnt value as threshold */
    }

    RTC_EnableWakeUpTsc(0x2efa);    /* Set wakeup time as the longest in normal work */
}

/***
 * @brief   Config the interrupt of TSC
 * @param:  None
 * @retval: None
 */
void BSP_TSC_ConfigInt(void)
{
    EXTI_InitType EXTI_InitStruct;

    EXTI_InitStruct.EXTI_Line    = EXTI_LINE25;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_InitStruct.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;

    EXTI_InitPeripheral(&EXTI_InitStruct);

    NVIC_InitType NVIC_InitStructure;

    /* Configure NVIC as priority group 1. */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    /* Configure the source of interrupt.*/
    NVIC_InitStructure.NVIC_IRQChannel = TSC_IRQn;
    /* Configure preemption priority. */
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    /* Configure subpriority. */
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    /* Enable interrupt channel. */
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

}

