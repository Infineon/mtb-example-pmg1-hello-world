/******************************************************************************
* File Name: main.c
*
* Description: This is the source code for the PMG1 MCU Hello World Example
*              for ModusToolbox.
*
* Related Document: See README.md
*
*******************************************************************************
* Copyright 2021, Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.  All rights reserved.
*
* This software, including source code, documentation and related
* materials ("Software") is owned by Cypress Semiconductor Corporation
* or one of its affiliates ("Cypress") and is protected by and subject to
* worldwide patent protection (United States and foreign),
* United States copyright laws and international treaty provisions.
* Therefore, you may use this Software only as provided in the license
* agreement accompanying the software package from which you
* obtained this Software ("EULA").
* If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
* non-transferable license to copy, modify, and compile the Software
* source code solely for use in connection with Cypress's
* integrated circuit products.  Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
* reserves the right to make changes to the Software without notice. Cypress
* does not assume any liability arising out of the application or use of the
* Software or any product or circuit described in the Software. Cypress does
* not authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
*******************************************************************************/


/*******************************************************************************
 * Include header files
 ******************************************************************************/
#include "cybsp.h"
#include "cyhal.h"


/*******************************************************************************
* Macros
*******************************************************************************/
#define LED_DELAY_MS              (500u)
#define CY_ASSERT_FAILED          (0u)

const cyhal_uart_cfg_t uartConfig =
{
    .data_bits      = 8,
    .stop_bits      = 1,
    .parity         = CYHAL_UART_PARITY_NONE,
    .rx_buffer      = NULL,
    .rx_buffer_size = 0
};

/*******************************************************************************
* Function Name: main
********************************************************************************
* Summary:
*  System entrance point. This function performs
*  - initial setup of device
*  - configure the SCB block as UART interface
*  - prints out "Hello World" via UART interface
*  - Blinks an LED under firmware control at 1 Hz
*
* Parameters:
*  none
*
* Return:
*  int
*
*******************************************************************************/
int main(void)
{
    cy_rslt_t result;
    cyhal_uart_t uartObj;

    const char string[] = "Hello world\r\n";
    size_t stringSize = strlen(string);

    /* Initialize the device and board peripherals */
    result = cybsp_init();

    /* Board init failed. Stop program execution */
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(CY_ASSERT_FAILED);
    }

    /* Configure LED pin as a strong drive output */
    cyhal_gpio_init(CYBSP_USER_LED, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, false);

    /* Configure and enable the UART peripheral. */
    cyhal_uart_init(&uartObj, CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX, NULL, &uartConfig);

    /* Enable global interrupts */
    __enable_irq();

    /* Send a string over serial terminal */
    cyhal_uart_write(&uartObj, (void *)string, &stringSize);

    for(;;)
    {
        /* Toggle the user LED state */
        cyhal_gpio_toggle(CYBSP_USER_LED);

        /* Wait for 0.5 seconds */
        cyhal_system_delay_ms(LED_DELAY_MS);
    }
}

/* [] END OF FILE */

