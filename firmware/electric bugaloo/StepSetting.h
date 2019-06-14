/*
 * StepSetting.h
 *
 *  Created on: May 31, 2019
 *      Author: linqi
 */

#ifndef STEPSETTING_H_
#define STEPSETTING_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"
#include <driverlib/pwm.h>
#include "utils/uartstdio.h"
#include <string.h>

//*****************************************************************************
//
// Configure Timer1B as a 16-bit PWM with a duty cycle of 66%.
//
//*****************************************************************************
void init_StepPin()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE))    {    }
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD))    {    }
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_4);
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_3);
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_2);
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_1);
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_0);
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_4, 0x0);
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, 0x0);
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, 0x0);
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, 0x0);
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 0x0);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))    {    }
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC))    {    }

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_4);
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_5);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);

    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0x0);
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, 0x0);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x0);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x0);
}
void setDirection(int D0,int D1,int D2,int D3)
{
    if(D0 == 1)
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, GPIO_PIN_0);
    else
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 0x0);
    if(D1 == 1)
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, GPIO_PIN_1);
    else
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, 0x0);
    if(D2 == 1)
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, GPIO_PIN_2);
    else
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, 0x0);
    if(D3 == 1)
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, GPIO_PIN_3);
    else
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, 0x0);

}
void setEndeffector(int D4)
{
    if(D4 == 1)
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_4, GPIO_PIN_4);
    else
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_4, 0x0);
}
void disablePins(int freq0,int freq1,int freq2,int freq3)
{
    if(freq0 == 0 )
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0x0);
    }

    if(freq1 == 0)
    {
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, 0x0);
    }

    if(freq2 == 0 )
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x0);
    }

    if(freq3 == 0)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x0);
    }
}
void setLevel(int D0,int D1,int D2,int D3)
{
    if(D0 == 1)
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_PIN_4);
    else
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0x0);
    if(D1 == 1)
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, GPIO_PIN_5);
    else
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, 0x0);
    if(D2 == 1)
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
    else
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x0);
    if(D3 == 1)
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
    else
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x0);

}



#endif /* STEPSETTING_H_ */
