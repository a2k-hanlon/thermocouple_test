/*
 * thermometerAndDisplay.h
 *
 *  Adapted from code by Edward Ma
 */

#ifndef INC_THERMOMETERANDDISPLAY_H_
#define INC_THERMOMETERANDDISPLAY_H_

//#define TC_GAIN_HW 250 // 0.012mV * 100 * 2.5 = 0.012mV *250 = 3V < 3.6V
#define TC_GAIN_HW 237.22 // value as determined by circuit
// can use any value between 250 to 300, 0.012 * 300 = 3.6V <= 3.6V
#define TC_GAIN_SW 218.2 // (TC_GAIN_HW * 0.92) fudge factor

float TC_getThermocoupleTemp(void);
void TC_calculateThermocoupleTemp(float thermocouple_adc_val, float junction_sensor_adc_val);

#endif /* INC_THERMOMETERANDDISPLAY_H_ */
