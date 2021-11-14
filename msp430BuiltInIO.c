/*
 * msp430BuiltInIO.c
 *
 *  Created on: Oct 22, 2021
 *      Author: C. ALex Luke
 */

#include <msp430.h>
#include "msp430BuiltInIO.h"


void setLED1(LED_STATE state) {
    if (state == OFF) {
        // turn off led1
        P1OUT &= ~0x01;
    } else if (state == ON) {
        // turn on led1
        P1OUT |= 0x01;
    }
}

void setLED2(LED_STATE state) {
    if (state == OFF) {
        // turn off led2
        P9OUT &= ~(0x01 << 7);
    } else if (state == ON) {
        // turn on led2
        P9OUT |= (0x01 << 7);
    }
}

void toggleLED1() {
    P1OUT ^= BIT0;
}

void toggleLED2() {
    P9OUT ^= BIT7;
}

BUTTON_STATE readButton1() {
    // read pin input
    int input = P1IN & (0x01 << 1);
    // return state (button goes low when pressed)
    return (input == 0) ? PRESSED : NOT_PRESSED;

}

BUTTON_STATE readButton2() {
    int input = P1IN & (0x01 << 2);
    // return state (button goes low when pressed)
    return (input == 0) ? PRESSED : NOT_PRESSED;
}


void configureBuiltInIO() {
    // P1.0 output for LED1
    P1DIR |= 0x01;
    // P9.7 output for LED2
    P9DIR |= (0x01 << 7);

    // P1.1 pullup resistor
    // Button 1
    P1REN |= (0x01 << 1);
    P1OUT |= (0x01 << 1);

    // P1.2 pullup resistor
    // Button 2
    P1REN |= (0x01 << 2);
    P1OUT |= (0x01 << 2);
}
