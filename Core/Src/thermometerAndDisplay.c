/*
 * thermometerAndDisplay.c
 *
 * Adpated from code by Edward Ma
 */

#include <stdio.h>
#include "thermometerAndDisplay.h"

//#define ADC12BIT_TO_VOLTS (3.28 / 4035) // nominally 3.3 / 4095; quickly adjusted via test
#define ADC12BIT_TO_VOLTS (3.3 / 4095)

#define K_TYPE_COEFF 24.5695 //25.08355 // degC / mV
// reverse amplifier gain, convert V to mV, convert mV to C
#define THERMOCOUPLE_SCALE_FACTOR (1/TC_GAIN_SW * 1000 * K_TYPE_COEFF) // should be about 0.135168/200, assuming TC_GAIN_HW == TC_GAIN_SW

#define JUNCTION_SCALE_FACTOR 100.0 // K / V or degC / V; NOT CALIBRATED YET; should be a rise over run, calulated from the slope of (0V, -273.15C) to a single test coordinate
#define KELVIN_OFFSET 273.15 // K = 0 degC


float thermocoupleDiffVolts2Temp(float adc_val);
float junctionVolts2Temp(float adc_val);
float thermocoupleTemp(float thermocouple_diff_temp, float junction_temp);


float tc_thermocouple_temp = 0.0;


float TC_getThermocoupleTemp()
{
    return tc_thermocouple_temp;
}

void TC_calculateThermocoupleTemp(float thermocouple_adc_val, float junction_sensor_adc_val)
{
    float thermocouple_diff_temp = thermocoupleDiffVolts2Temp(thermocouple_adc_val);
    float junction_temp = junctionVolts2Temp(junction_sensor_adc_val);
    float thermocouple_temp = thermocouple_diff_temp + junction_temp;
    tc_thermocouple_temp = thermocouple_temp;
    printf("TC=%.2f *C; ", thermocouple_temp);
}


float thermocoupleDiffVolts2Temp(float adc_val)
{
    float voltage = adc_val * ADC12BIT_TO_VOLTS;
    float temperature = voltage * THERMOCOUPLE_SCALE_FACTOR;
    printf("A=%.2f V=%.2f T=%.2f; ", adc_val, voltage, temperature);

    return temperature;
}

float junctionVolts2Temp(float adc_val)
{
    float voltage = adc_val * ADC12BIT_TO_VOLTS;
    float temperature = voltage * JUNCTION_SCALE_FACTOR - KELVIN_OFFSET;
    printf("A=%.2f V=%.2f T=%.2f; ", adc_val, voltage, temperature);

    return temperature;
}
