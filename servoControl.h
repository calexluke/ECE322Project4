
/*
 * servoControl.h
 *
 *  Created on: Oct 23, 2021
 *      Author: alex
 */

#ifndef SERVOCONTROL_H_
#define SERVOCONTROL_H_

#define SMCLOCK_HZ 1000000L
#define TRIGGER_PERIOD_HZ 50  // 20ms or 50Hz

#define SERVO_MIN_PULSE_US 500L
#define SERVO_MID_PULSE_US 1500L
#define SERVO_MAX_PULSE_US 2500L

// convert to timer clock cycles
#define TRIGGER_PERIOD (SMCLOCK_HZ / TRIGGER_PERIOD_HZ)
#define SERVO_MIN_PULSE (SERVO_MIN_PULSE_US * (SMCLOCK_HZ / 1000000L))
#define SERVO_MID_PULSE (SERVO_MID_PULSE_US * (SMCLOCK_HZ / 1000000L))
#define SERVO_MAX_PULSE (SERVO_MAX_PULSE_US * (SMCLOCK_HZ / 1000000L))

#define WIDTH_RANGE (SERVO_MAX_PULSE_US - SERVO_MIN_PULSE_US)
#define STEP_SIZE 50;

typedef enum {CW_MAX, CCW_MAX, CENTER} SERVO_POSITION;


void configureTimersForServo();
void configureIOForServo();
int calculateServoPositionFromTemp(float temp);
int getCurrentServoPosition();
void stepServoClockwise();
void stepServoCounterClockwise();
void setServo(SERVO_POSITION position);

#endif /* SERVOCONTROL_H_ */
