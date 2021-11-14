/*
 * thermistor.c
 *
 *  Created on: Nov 13, 2021
 *      Author: alex
 */
#include <msp430.h>
#include <math.h>
#include "thermistor.h"

const float vRef = 3.3; // input voltage to circuit, also reference for ADC
const int R1 = 10000; // resistor 1 in circuit, 10k Ohms
const int maxInputValue = 4096; // ADC returns 12 bit value: 2^12 = 4096

// constants for thermistor equation
const int R0 = 10000;
const float beta = 3548.0;
const float T0 = 298.15; // degrees kelvin


// internal function declarations
float calculateVoltage(int bitValue);
float calculateResistance(float voltage);
float calculateTemp(float resistance);
float fahrenheitFromKelvin(float degreesK);


// public functions

void configIOForThermistor() {
    // Configure P1.3 for ADC input
    P1SEL1 |= BIT3;
    P1SEL0 |= BIT3;
}

void configADC() {
    // Configure ADC12
    ADC12CTL0 = ADC12SHT0_2 | ADC12ON;      // Sampling time, S&H=16, ADC12 on
    ADC12CTL1 = ADC12SHP;                   // Use sampling timer
    ADC12CTL2 |= ADC12RES_2;                // 12-bit conversion results
    ADC12MCTL0 |= ADC12INCH_3;              // A3 ADC input select; Vref=AVCC (3.3V)
    ADC12IER0 |= ADC12IE0;                  // Enable ADC conv complete interrupt
}

int getTemp(int bitValue) {

    float vTherm = calculateVoltage(bitValue);
    float rTherm = calculateResistance(vTherm);
    return calculateTemp(rTherm);
}

// internal function definitions

// voltage drop across thermistor
float calculateVoltage(int bitValue) {
    float ratio = (float)bitValue / maxInputValue;
    return ratio * vRef;
}

// resistance of thermistor in ohms
// circuit is built as voltage divider with R1 = 10kOhms
// Calculate current using R1, then use that to find rTherm
float calculateResistance(float voltage) {
    // current through thermistor
    float iTherm = (vRef - voltage) / R1;
    // ohm's law
    return voltage / iTherm;
}

// degrees Fahrenheit
float calculateTemp(float resistance) {
    // thermistor equation
    float tKelvin = 1 / ( (log(resistance / R0) / beta) + (1 / T0) );
    return fahrenheitFromKelvin(tKelvin);
}

float fahrenheitFromKelvin(float degreesK) {
    return (9 * (degreesK - 273.15) / 5) + 32;
}
