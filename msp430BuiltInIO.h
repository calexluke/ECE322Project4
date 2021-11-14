/*
 * msp430BuiltInIO.h
 *
 *  Created on: Oct 22, 2021
 *      Author: C. ALex Luke
 */


#ifndef MSP430BUILTINIO_H_
#define MSP430BUILTINIO_H_

typedef enum {PRESSED, NOT_PRESSED} BUTTON_STATE;
typedef enum {ON, OFF} LED_STATE;

void configureBuiltInIO();
void setLED1(LED_STATE state);
void setLED2(LED_STATE state);
void toggleLED1();
void toggleLED2();
BUTTON_STATE readButton1();
BUTTON_STATE readButton2();

#endif /* MSP430BUILTINIO_H_ */
