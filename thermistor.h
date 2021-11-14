/*
 * thermistor.h
 *
 *  Created on: Nov 13, 2021
 *      Author: alex
 */

#ifndef THERMISTOR_H_
#define THERMISTOR_H_

void configIOForThermistor();
void configADC();
int getTemp(int bitValue);

#endif /* THERMISTOR_H_ */
