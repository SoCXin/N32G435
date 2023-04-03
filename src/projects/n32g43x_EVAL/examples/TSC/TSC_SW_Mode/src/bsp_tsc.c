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
#include "bsp_timer.h"

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


static TSC_ETR_KEY_PARA tsc_etr_key;         // The struct is the about the process of key recognition by ETR.
static bool b_one_cycle_sample_flag = false; // Calculate after completing 10 samples for each channel.
static bool b_channel_switch_delay = false;
static uint16_t *pEtrTimCnt = NULL;
static uint8_t KeyCh[KEY_NUM] = {1,4,5,6,7,8,9,10,11,12,13,14,15,16,17,19,20,21,22,23};

/******************************************************************/
/***
* @brief    Init tsc by software mode,all channel used.
 * @param:  None
 * @retval: None
*/
void BSP_TSC_SW_Init(void)
{
    TSC_InitType Init = {0};
    
    /*Initialize the variables of TSC.*/
    memset((void*)&tsc_etr_key, 0, sizeof(TSC_ETR_KEY_PARA));

    /*------------------for test--------------------*/
    uint32_t i;
    for(i=0;i<KEY_NUM;i++)
    {
        tsc_etr_key.MaxPressSum[i]      = 0;
        tsc_etr_key.MaxReleaseSum[i]    = 0;
        tsc_etr_key.MinPressSum[i]      = 0xFFFFFFFF;
        tsc_etr_key.MinReleaseSum[i]    = 0xFFFFFFFF;
    }
    /*-----------------------------------------------*/

    TSC_ClockConfig(TSC_CLK_SRC_LSI);
    
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TSC, ENABLE);
    tsc_gpio_init();

    Init.Mode   = TSC_SW_DETECT_MODE;
    Init.Out    = TSC_OUT_TIM2_ETR;
    Init.PadOpt = TSC_PAD_INTERNAL_RES;
    Init.Speed  = TSC_PAD_SPEED_0;
    TSC_Init(&Init);

    if(Init.Out != TSC_OUT_TIM2_ETR)
    {
        TSC_EtrTimInit(TIM4);
        pEtrTimCnt = (uint16_t *)(&(TIM4->CNT));
    }
    else
    {
        TSC_EtrTimInit(TIM2);
        pEtrTimCnt = (uint16_t *)(&(TIM2->CNT));
    }
    
    /*Select the internal resistance of each channel as 126K*/
    TSC_ConfigInternalResistor(TSC_CHN_SEL_ALL, TSC_RESRx_CHN_RESIST_7 );

    __TSC_SW_CHN_NUM_CONFIG(KeyCh[0]);
    __TSC_SW_ENABLE();
    
    b_channel_switch_delay = true;
}
/******************************************************************/

/******************************************************************/
#define THRESHOLD_MIN  600
/**
* @brief  Check if all samples are done every 10ms
*         If they are done,check if there is any change of key status.
*         If key status changed,print out.
* @param: none
* @return: none
*/
void BSP_TSC_KeyCheck(void)
{
    uint32_t i = 0, j = 0, tempSum;

    if (!b_one_cycle_sample_flag)
        return;

    for (i = 0; i < KEY_NUM; i++)
    {
        tempSum = 0;
        for (j = 0; j < SUM_NUM; j++)
        {
            tempSum += tsc_etr_key.PulseSample[i][j];
        }

        if(tsc_etr_key.EtrSumThreshold[i] == 0) /*init the threshold for each channel*/
        {
            if(tempSum < THRESHOLD_MIN)
                tsc_etr_key.EtrSumThreshold[i] = THRESHOLD_MIN;
            else
                tsc_etr_key.EtrSumThreshold[i] = tempSum;
        }

        if ((tempSum <= THRESHOLD_MIN)||((tempSum+200) < tsc_etr_key.EtrSumThreshold[i]))
        {
            tsc_etr_key.key_status |= 1 << i;

            /*------------------for test--------------------*/
            if(tsc_etr_key.MaxPressSum[i] < tempSum)
            tsc_etr_key.MaxPressSum[i] = tempSum;

            if(tsc_etr_key.MinPressSum[i] > tempSum)
            tsc_etr_key.MinPressSum[i] = tempSum;
            /*-----------------------------------------------*/
        }
        else
        {
            tsc_etr_key.key_status &= ~(1 << i);

            /*------------------for test--------------------*/
            if(tsc_etr_key.MaxReleaseSum[i] < tempSum)
            tsc_etr_key.MaxReleaseSum[i] = tempSum;

            if(tsc_etr_key.MinReleaseSum[i] > tempSum)
            tsc_etr_key.MinReleaseSum[i] = tempSum;
            /*-----------------------------------------------*/
        }
    }


    if (tsc_etr_key.key_status != tsc_etr_key.key_status_pre)
    {
        BSP_TSC_KeyPrint(tsc_etr_key.key_status,tsc_etr_key.key_status_pre);
        tsc_etr_key.key_status_pre = tsc_etr_key.key_status;
    }

    b_one_cycle_sample_flag = false;
}
/******************************************************************/

/******************************************************************/
/**
* @brief Print the key press and release infomation.
* @param current_key: key status deteced now
* @param last_key:    key status deteced last time
* @return : none
*/
void BSP_TSC_KeyPrint(uint32_t current_key, uint32_t last_key)
{
    uint32_t i = 0, key_change;

    key_change = current_key^last_key;

    for (i = 0; i < KEY_NUM; i++)
    {
        if (key_change & (1 << i))
        {
            if(current_key & (1<<i))
                printf("T%d pressed,key=0x%x!\r\n",KeyCh[i],(unsigned int)current_key);
            else
                printf("T%d released,key=0x%x!\r\n",KeyCh[i],(unsigned int)current_key);
        }
    }

//    if (current_key == 0)
//    {
//        printf("No valid key!\r\n");
//        return;
//    }
}
/******************************************************************/

/******************************************************************/
/**
* @brief  Do it in TIM3 interrupt process.
*         Calculate the number of pulses for each channel one by one during TIM3 period.
*         The pulses are counted by TIM2
* @param: None
* @return: None
*/
void BSP_TSC_TimIrqCheck(void)
{
    static uint32_t keycnt  = 0;
    static uint32_t num     = 0;
    uint32_t tempDelta;

    if(b_one_cycle_sample_flag)     /*if the data of last loop is not dealed with user, wait*/
        return;

    /*Keep last value of TIMx->CNT*/
    tsc_etr_key.EtrCntPre = tsc_etr_key.EtrCnt;

    /* Get current value of TIMx->CNT*/
    tsc_etr_key.EtrCnt = *pEtrTimCnt;

    if (b_channel_switch_delay==true)
    {
        b_channel_switch_delay = false;
        return;
    }

    /* Calculate the number of pulses in 100us(between two TIM3 IRQS)*/
    if (tsc_etr_key.EtrCnt >= tsc_etr_key.EtrCntPre)
        tempDelta = tsc_etr_key.EtrCnt - tsc_etr_key.EtrCntPre;
    else
        tempDelta = tsc_etr_key.EtrCnt+0xFFFF-tsc_etr_key.EtrCntPre;

    /*save the pulse for each sample in every Channel*/
    tsc_etr_key.PulseSample[keycnt][num] = tempDelta;
    
    if(keycnt<(KEY_NUM-1)) /* switch to next channel */
        keycnt++;
    else            /* Get sample of last channel */
    {
        keycnt = 0;    /* switch to the first channel */
        num++;          /* loop count */
        if(num >= SUM_NUM)       /*Get enough samples for each channel*/
        {
            num = 0;        /* reset the loop count */
            b_one_cycle_sample_flag = true; /*set mark for sample finished*/
        }
    }

    __TSC_SW_CHN_NUM_CONFIG(KeyCh[keycnt]);
    b_channel_switch_delay = true;
}



