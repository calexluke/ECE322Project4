/*
 * servoStateMachine.h
 *
 *  Created on: Nov 13, 2021
 *      Author: alex
 */

#ifndef SERVOSTATEMACHINE_H_
#define SERVOSTATEMACHINE_H_

enum servoStates {hold, stepCW, stepCCW} servoState;
void servoSMTick(float temp);
void servoSMStateTransitions(float temp);
void servoSMStateActions();

#endif /* SERVOSTATEMACHINE_H_ */
