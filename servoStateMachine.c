/*
 * servoStateMachine.c
 *
 *  Created on: Nov 13, 2021
 *      Author: alex
 */

#include "msp430BuiltInIO.h"
#include "servoStateMachine.h"
#include "servoControl.h"

void servoSMTick(float temp) {
    servoSMStateTransitions(temp);
    servoSMStateActions();
}

void servoSMStateTransitions(float temp) {
    int targetStep = calculateServoPositionFromTemp(temp);
    int position = getCurrentServoPosition();

    switch (servoState) {
        case hold:
            if (position < targetStep) {
                servoState = stepCCW;
            } else if (position > targetStep) {
                servoState = stepCW;
            } else {
                servoState = hold;
            }
        break;
        case stepCCW:
            if (position < targetStep) {
                servoState = stepCCW;
            } else {
                servoState = hold;
            }
        break;
        case stepCW:
            if (position > targetStep) {
                servoState = stepCW;
            } else {
                servoState = hold;
            }
        break;
        default:
        break;
    }

}

void servoSMStateActions() {
    switch (servoState) {
        case hold:
            // do nothing with servo, set LEDs for debug
            setLED1(OFF);
            setLED2(OFF);
        break;

        case stepCCW:
            stepServoCounterClockwise();
            // set LEDs for debug
            toggleLED1();
        break;

        case stepCW:
            stepServoClockwise();
            // set LEDs for debug
            toggleLED2();
        break;

        default:
            // do nothing
        break;
    }
}


