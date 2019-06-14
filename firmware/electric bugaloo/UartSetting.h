/*
 * UartSetting.h
 *
 *  Created on: May 27, 2019
 *      Author: linqi
 */

#ifndef UARTSETTING_H_
#define UARTSETTING_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/timer.h"

void init_U1()
{
    //
    // Enable the peripherals used by this example.
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    //
    // Set GPIO A0 and A1 as UART pins.
    //
    GPIOPinConfigure(GPIO_PB0_U1RX);
    GPIOPinConfigure(GPIO_PB1_U1TX);
    ROM_GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Configure the UART for 115,200, 8-N-1 operation. 230400
    //
    ROM_UARTConfigSetExpClk(UART1_BASE, ROM_SysCtlClockGet(), 115200,
                            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                             UART_CONFIG_PAR_NONE));

    //
    // Enable the UART interrupt.
    //
    ROM_IntEnable(INT_UART1);
    ROM_UARTIntEnable(UART1_BASE, UART_INT_RX | UART_INT_RT);
    return  ;
}

int UART1Read(char *RSInfo, int start)
{
//    char buf[100];
    int k =start;
    //Get all the characters until the next delimiter ( ; ) is hit
    while(1)
    {

        // Read the next character from the UART and write it to buffer
        RSInfo[k] = UARTCharGet(UART1_BASE);
        // check for delimiter
        if (RSInfo[k] == '\r') break;
        k++;
    }

    // change delimiter value to a space for processing.
    RSInfo[k] = 32;

    //return the length of the char,with a space as the end
//    return k ;
    return (k);
}

void UART1Send(const uint8_t *pui8Buffer, uint32_t ui32Count)
{
    //
    // Loop while there are more characters to send.
    //
    while(ui32Count--)
    {
        //
        // Write the next character to the UART.
        //
        ROM_UARTCharPut(UART1_BASE, *pui8Buffer++);
    }

    return ;
}



#endif /* UARTSETTING_H_ */
