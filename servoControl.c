#include <msp430.h>
#include "servoControl.h"

/*
 * servoControl.c
 *
 *  Created on: Oct 23, 2021
 *      Author: alex
 */
#define MIN_TEMP 20
#define MAX_TEMP 150
#define TEMP_RANGE MAX_TEMP - MIN_TEMP
unsigned long currentPulseWidth = SERVO_MID_PULSE;


void configureTimersForServo() {
    // Configure Timer0_A
    // PWM Period
    TA0CCR0 = TRIGGER_PERIOD;
    // CCR1 reset/set
    TA0CCTL1 = 0x00E0;
    // TACCR0 interrupt enabled
    TA0CCTL0 = CCIE;

    // Configure TimerA0 mode and GO
    TA0CTL = TASSEL__SMCLK | MC__UP | TACLR;   // SMCLK, up mode, clear TAR

    // enable interrupts
    __bis_SR_register(GIE);

}

void configureIOForServo() {
    // setup P1.6 with TA0CCR1 output signal
    // ft6989 datasheet section 6.11.24.4, Table 6-21
    // registers P1DIR, P1SEL1, P1SEL0
    // datasheet p.97 (NOT FAMILY USER GUIDE)
    P1DIR |= (0x01 << 6);
    P1SEL1 |= (0x01 << 6);
    P1SEL0 |= (0x01 << 6);
}

int calculateServoPositionFromTemp(float temp) {
    float tempProportion = (temp - MIN_TEMP) / (MAX_TEMP - MIN_TEMP);
    float targetPosition =  SERVO_MAX_PULSE - (tempProportion * WIDTH_RANGE);

    // round to nearest servo step value
    int step = STEP_SIZE;
    return ((int)targetPosition / step) * step;
}

int getCurrentServoPosition() {
    return currentPulseWidth;
}

void stepServoClockwise() {
    // narrow pulse to move servo CW
    currentPulseWidth -= STEP_SIZE;
    if (currentPulseWidth < SERVO_MIN_PULSE) {
        currentPulseWidth = SERVO_MIN_PULSE;
    }

    TA0CCR1 = currentPulseWidth;
}

void stepServoCounterClockwise() {
    // widen pulse to move servo CCW
    currentPulseWidth += STEP_SIZE;
    if (currentPulseWidth > SERVO_MAX_PULSE) {
        currentPulseWidth = SERVO_MAX_PULSE;
    }

    TA0CCR1 = currentPulseWidth;
}

void setServo(SERVO_POSITION position) {
    switch (position) {
    case CW_MAX:
        currentPulseWidth = SERVO_MIN_PULSE;
        break;
    case CCW_MAX:
        currentPulseWidth = SERVO_MAX_PULSE;
        break;
    case CENTER:
        currentPulseWidth = SERVO_MID_PULSE;
        break;
    default:
        // do nothing
        break;
    }
    TA0CCR1 = currentPulseWidth;
}
