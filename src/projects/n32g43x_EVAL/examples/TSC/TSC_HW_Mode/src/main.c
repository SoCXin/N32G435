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
 * @file main.c
 * @author Nations
 * @version V1.2.1
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#include "main.h"
#include "bsp_gpio.h"
#include "bsp_usart.h"
#include "bsp_tsc.h"

/**
 * @brief  Set system clock again,use HSE as clock source,and enable pll
 * &param  pllmul:pll multiply factor,as HSE is 8MHz
 * @retval: None
 */
static void SetSysClock_HSE_PLL(uint32_t pllmul)
{
    __IO uint32_t HSEStartUpStatus = 0;

    // It is necessary to initialize the RCC peripheral to the reset state.
    RCC_DeInit();

    // Enable HSE, open external crystal oscillator.
    RCC_ConfigHse(RCC_HSE_ENABLE);

    // Wait for HSE to be stable.
    HSEStartUpStatus = RCC_WaitHseStable();

    // Go on until the HSE is stable.
    if (HSEStartUpStatus == SUCCESS)
    {
        //----------------------------------------------------------------------//
        // Enable flash Prefetch buffer
        FLASH_PrefetchBufSet(FLASH_PrefetchBuf_EN);

        FLASH_SetLatency(FLASH_LATENCY_3);
        //----------------------------------------------------------------------//

        // AHB prescaler factor set to 1,HCLK = SYSCLK = 16M
        RCC_ConfigHclk(RCC_SYSCLK_DIV1);
        // AHB prescaler factor set to 1,PCLK2 = HCLK/1 = 16M
        RCC_ConfigPclk2(RCC_HCLK_DIV1);
        // AHB prescaler factor set to 1,PCLK1 = HCLK/1 = 16M
        RCC_ConfigPclk1(RCC_HCLK_DIV1);

        ////-----------------Set PLL clock source as HSE, set PLL frequency multiplication factor.-------------------//
        // PLLCLK = 8MHz * pllmul
        RCC_ConfigPll(RCC_PLL_SRC_HSE_DIV1, pllmul,RCC_PLLDIVCLK_DISABLE); ////RCC_PLLDIVCLK_DISABLE
        ////------------------------------------------------------------------//

        // Enable PLL
        RCC_EnablePll(ENABLE);
        // Wait for PLL to be stable.
        while (RCC_GetFlagStatus(RCC_CTRL_FLAG_PLLRDF) == RESET)
        {
        }

        // Switch PLL clock to SYSCLK.
        RCC_ConfigSysclk(RCC_SYSCLK_SRC_PLLCLK);

        // Read the clock switch status bit and make sure pllclk is selected as the system clock.
        while (RCC_GetSysclkSrc() != 0x0C)
        {
        }
    }
    else
    {   // If HSE fails to open, the program will come here, where the user can add the error code to handle.
        // When HSE fails or breaks down,mcu will automatically set HSI as the system clock.HSI is an internal high speed
        // clock of 8MHz.
        while (1)
        {
        }
    }

    SystemCoreClockUpdate();
}

/**
 * @brief  simple delay
 * &param  count: count value of delay
 * @retval: None
 */
static void Delay(u32 count)
{
    u32 i;
    for(i = 0; i < count; i++)
    {
        i = i;
    }
}

/**
 * @brief  Disable debug uart and led before enter low power mode
 * &param   None
 * @retval: None
 */
void DeInitPeripheral(void)
{
    Delay(SystemCoreClock>>12);
    Debug_USART_DeInit();
    led_gpio_DeInit();
}

/**
 * @brief  Init debug uart and led port
 * &param   None
 * @retval: None
 */
void InitPeripheral(void)
{
    /*Initialize USART as 115200 bps, 8 bit length,1 stop bit,no check bit,enable receive by interrupt */
    Debug_USART_Config();
    Delay(SystemCoreClock>>20);
    led_gpio_init();
}

/**
 * @brief  Main program.
 */
int main(void)
{
    uint32_t LowPowerDelay;
    
    // HSE,SYSCLK = 8M * RCC_PLLMul_x, x:[2,3,...32],maximum frequency 108M
    SetSysClock_HSE_PLL(RCC_PLL_MUL_2);

    InitPeripheral();   /*Init debug uart and led port*/
    LED_D1_ON;
    
    BSP_TSC_HwInit();   /* Init TSC mode */
    LED_D2_ON;
    
    BSP_TSC_AutoAdjust();   /* Config TSC threshold */
    LED_D3_ON;

    BSP_TSC_ConfigInt();    /* Enable TSC interrupt */

    if(!(__TSC_GET_HW_DET_TYPE(TSC_FLAG_LESS_DET)))
        printf("__TSC_GET_HW_DET_TYPE error!\r\n");

    printf("/****TSC demo for hardware detect mode,wake up MCU from low power mode!****/\r\n");
    Delay(SystemCoreClock>>1);

    LowPowerDelay = 15;
    while(LowPowerDelay>0)
    {
        printf("Wait %d seconds before enter low power mode!\r\n",(int)LowPowerDelay);
        LowPowerDelay--;
        Delay(SystemCoreClock>>2);
    }
    
  #ifdef TSC_LOWPOWER_DEBUG
    DBG->CTRL |= DBG_CTRL_SLEEP|DBG_CTRL_STOP|DBG_CTRL_STDBY;
  #endif
  
    while (1)
    {
        __TSC_CHN_CONFIG(TSC_CHN_SEL_ALL);      /*Enable all channels of TSC*/
        printf("TSC wake up loop start!\r\n");

        __TSC_HW_ENABLE();                  /* Enalbe hw detect*/
        printf("Enter sleep mode!\r\n");
        DeInitPeripheral();                 /*Deinit debug uart and led port*/
        PWR_EnterSLEEPMode(0,PWR_SLEEPENTRY_WFI);   /* Enter sleep mode */

        InitPeripheral();   /* Wake up from sleep mode, init debug uart and led port */
        LED_D1_ON;
        printf("T%d press,exit sleep mode!\r\n",(int)(__TSC_GET_CHN_NUMBER()));
        Delay(SystemCoreClock>>2);

        __TSC_HW_ENABLE();              /* Enalbe hw detect*/
        printf("Enter low power sleep mode!\r\n");
        DeInitPeripheral();                 /*Deinit debug uart and led port*/
        PWR_EnterLowPowerSleepMode(0,PWR_SLEEPENTRY_WFI);   /* Enter low power sleep mode */

        PWR_ExitLowPowerRunMode();  /* Wake up from low power sleep mode, than exit low power run mode */
        SetSysClock_HSE_PLL(RCC_PLL_MUL_2);     /* Config PLL */
        InitPeripheral();   /* Init debug uart and led port */
        LED_D2_ON;
        printf("T%d press,exit low power sleep mode!\r\n",(int)(__TSC_GET_CHN_NUMBER()));
        Delay(SystemCoreClock>>2);

        __TSC_HW_ENABLE();              /* Enalbe hw detect*/
        printf("Enter stop2 mode!\r\n");
        DeInitPeripheral();                 /*Deinit debug uart and led port*/
        PWR_EnterSTOP2Mode(PWR_STOPENTRY_WFI,PWR_CTRL3_RAM1RET|PWR_CTRL3_RAM2RET);  /* Enter stop2 mode */

        Delay(SystemCoreClock>>20);
        SetSysClock_HSE_PLL(RCC_PLL_MUL_2);
        InitPeripheral();   /* Wake up from stop2 mode, init debug uart and led port */
        LED_D3_ON;
        printf("T%d press,exit stop2 mode!\r\n",(int)(__TSC_GET_CHN_NUMBER()));
        Delay(SystemCoreClock>>2);
    }
}

/******************************************************************/

/******************************************************************/

/**
 * @brief Assert failed function by user.
 * @param file The name of the call that failed.
 * @param line The source line number of the call that failed.
 */
#ifdef USE_FULL_ASSERT
void assert_failed(const uint8_t* expr, const uint8_t* file, uint32_t line)
{
    while (1)
    {
    }
}
#endif // USE_FULL_ASSERT
/******************************************************************/


