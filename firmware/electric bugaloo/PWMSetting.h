/*
 * PWMSetting.h
 *
 *  Created on: May 22, 2019
 *      Author: linqi
 */

#ifndef PWMSETTING_H_
#define PWMSETTING_H_
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

void
InitConsole(void)
{
    //
    // Enable GPIO port A which is used for UART0 pins.
    // TODO: change this to whichever GPIO port you are using.
    //
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    //
    // Configure the pin muxing for UART0 functions on port A0 and A1.
    // This step is not necessary if your part does not support pin muxing.
    // TODO: change this to select the port/pin you are using.
    //
//    GPIOPinConfigure(GPIO_PA0_U0RX);
//    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinConfigure(GPIO_PB1_U1TX);
    GPIOPinConfigure(GPIO_PB0_U1RX);

    //
    // Enable UART0 so that we can configure the clock.
    //
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);


    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
//    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
    UARTClockSourceSet(UART1_BASE, UART_CLOCK_PIOSC);

    //
    // Select the alternate (UART) function for these pins.
    // TODO: change this to select the port/pin you are using.
    //
//    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Initialize the UART for console I/O.
    //
//    UARTStdioConfig(0, 115200, 16000000);
    UARTStdioConfig(1, 115200, 16000000);

}

void
InitConsole0(void)
{
    //
    // Enable GPIO port A which is used for UART0 pins.
    // TODO: change this to whichever GPIO port you are using.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    //
    // Configure the pin muxing for UART0 functions on port A0 and A1.
    // This step is not necessary if your part does not support pin muxing.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
//    GPIOPinConfigure(GPIO_PB1_U1TX);
//    GPIOPinConfigure(GPIO_PB0_U1RX);

    //
    // Enable UART0 so that we can configure the clock.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);


    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
//    UARTClockSourceSet(UART1_BASE, UART_CLOCK_PIOSC);

    //
    // Select the alternate (UART) function for these pins.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
//    GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, 16000000);
//    UARTStdioConfig(1, 115200, 16000000);

}

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

    //confidure PB6->T0P0, PF->T2P0，PB7->T0P1
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    GPIOPinConfigure(GPIO_PB6_T0CCP0);// GPIO_PB6_T0CCP0 GPIO_PB6_M0PWM0
    GPIOPinTypeTimer(GPIO_PORTB_BASE, GPIO_PIN_6);
    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_6);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinConfigure(GPIO_PF4_T2CCP0);// GPIO_PB6_T0CCP0 GPIO_PB6_M0PWM0
    GPIOPinTypeTimer(GPIO_PORTF_BASE, GPIO_PIN_4);
    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_4);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC)){}
    GPIOPinConfigure(GPIO_PC5_M0PWM7);
    GPIOPinTypePWM(GPIO_PORTC_BASE, GPIO_PIN_5);


    //configure PF2->T1P0, PF3->T1P1
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinConfigure(GPIO_PF2_T1CCP0);
    GPIOPinTypeTimer(GPIO_PORTF_BASE, GPIO_PIN_2);
    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_2);
//    GPIOPinConfigure(GPIO_PF3_T1CCP1);
//    GPIOPinTypeTimer(GPIO_PORTF_BASE, GPIO_PIN_3);
//    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_3);
    GPIOPinConfigure(GPIO_PF3_M1PWM7);// GPIO_PF2_M1PWM6
    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_3);


}
void init_Timer01()
{
    //configure Timer0A,1A,
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);

    TimerConfigure(TIMER0_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PWM);
    TimerConfigure(TIMER1_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PWM);

    //key to change the pwm freq
    TimerLoadSet(TIMER0_BASE, TIMER_A, 1000);//5kHZ
    TimerMatchSet(TIMER0_BASE, TIMER_A,
                  TimerLoadGet(TIMER0_BASE, TIMER_A) / 3);
    TimerEnable(TIMER0_BASE, TIMER_A);

    TimerLoadSet(TIMER1_BASE, TIMER_A, 1000);
    TimerMatchSet(TIMER1_BASE, TIMER_A,
                  TimerLoadGet(TIMER1_BASE, TIMER_A) / 3);
    TimerEnable(TIMER1_BASE, TIMER_A);

    //configure Timer2A,
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);
    TimerConfigure(TIMER2_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PWM);
    TimerLoadSet(TIMER2_BASE, TIMER_A, 1000);//5kHZ
    TimerMatchSet(TIMER2_BASE, TIMER_A,
                  TimerLoadGet(TIMER2_BASE, TIMER_A) / 3);
    TimerEnable(TIMER2_BASE, TIMER_A);
}
void init_PWM01()
{
    //Set the clock
   SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC |   SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

   //Configure PWM Clock to match system
   SysCtlPWMClockSet(SYSCTL_PWMDIV_1);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);  //The Tiva Launchpad has two modules (0 and 1). Module 1 covers the LED pins
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM1)){}
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM0)){}

    //Configure PWM Options
    PWMGenConfigure(PWM1_BASE,PWM_GEN_3, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
    PWMGenConfigure(PWM0_BASE,PWM_GEN_3, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);

    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, 3200);//5kZ//lin
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_3, 3200);

    //Set PWM duty-50% (Period /2)
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7,0);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7,0);


    // Enable the PWM generator
    PWMGenEnable(PWM1_BASE, PWM_GEN_3);
    PWMGenEnable(PWM0_BASE, PWM_GEN_3);

    // Turn on the Output pins
    PWMOutputState(PWM1_BASE, PWM_OUT_7_BIT, true);
    PWMOutputState(PWM0_BASE, PWM_OUT_7_BIT, true);

}
void setPWM01(int freq0, int duty0,int freq1,  int duty1, int base)
{
    if(freq0 ==0 )
    {
        PWMGenDisable(PWM0_BASE, PWM_GEN_3);
//        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, 0x0);
    }
    else
    {
        PWMGenPeriodSet(PWM0_BASE, PWM_GEN_3, base/freq0);
        PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7,PWMGenPeriodGet(PWM0_BASE, PWM_GEN_3)/duty0);
        PWMGenEnable(PWM0_BASE, PWM_GEN_3);
        PWMOutputState(PWM0_BASE, PWM_OUT_7_BIT, true);
    }

    if(freq1 == 0)
    {
        PWMGenDisable(PWM1_BASE, PWM_GEN_3);
//        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x0);
    }
    else
    {
        PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, base/freq1);//5kZ//lin3200
        //Set PWM duty-50% (Period /2)
        PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7, PWMGenPeriodGet(PWM1_BASE, PWM_GEN_3)/duty1);
        // Enable the PWM generator
        PWMGenEnable(PWM1_BASE, PWM_GEN_3);
        // Turn on the Output pins
        PWMOutputState(PWM1_BASE, PWM_OUT_7_BIT, true);
    }
}
void setTimer01(int freq0, int duty0, int freq1, int duty1,int base)
{
    if(freq0==0)
    {
        TimerDisable(TIMER2_BASE, TIMER_A);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0x0);
    }
    else
    {
        //key to change the pwm freq
        TimerLoadSet(TIMER0_BASE, TIMER_A, base/freq0);//5kHZ
        TimerMatchSet(TIMER0_BASE, TIMER_A,
                      TimerLoadGet(TIMER0_BASE, TIMER_A)-(TimerLoadGet(TIMER0_BASE, TIMER_A) / duty0));
        TimerEnable(TIMER0_BASE, TIMER_A);//qinjielin for testing


        TimerLoadSet(TIMER2_BASE, TIMER_A, base/freq0);//5kHZ
        TimerMatchSet(TIMER2_BASE, TIMER_A,
                      TimerLoadGet(TIMER2_BASE, TIMER_A)-(TimerLoadGet(TIMER2_BASE, TIMER_A) / duty0));
        TimerEnable(TIMER2_BASE, TIMER_A);//qinjieLin for testing
    }

    if(freq1 ==0)
    {
        TimerDisable(TIMER1_BASE, TIMER_A);
    }
    else
    {
        TimerLoadSet(TIMER1_BASE, TIMER_A, base/freq1);
        TimerMatchSet(TIMER1_BASE, TIMER_A,
                      TimerLoadGet(TIMER1_BASE, TIMER_A) - (TimerLoadGet(TIMER1_BASE, TIMER_A) / duty1));
        TimerEnable(TIMER1_BASE, TIMER_A);
    }
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
        TimerDisable(TIMER2_BASE, TIMER_A);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0x0);
    }

    if(freq1 == 0)
    {
        PWMGenDisable(PWM0_BASE, PWM_GEN_3);
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, 0x0);
    }

    if(freq2 == 0 )
    {
        TimerDisable(TIMER1_BASE, TIMER_A);
//        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x0);
    }

    if(freq3 == 0)
    {
        PWMGenDisable(PWM1_BASE, PWM_GEN_3);
    }
}





#endif /* PWMSETTING_H_ */
