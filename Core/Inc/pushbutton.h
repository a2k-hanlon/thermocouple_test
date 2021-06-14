/**
 * @file pushbutton.h
 * @brief Header file for pushbutton debouncing driver
 *
 */

#ifndef PUSHBUTTON_H_
#define PUSHBUTTON_H_

#include <stdint.h>

#define PB_NUM_STATES 8

typedef struct {
    volatile uint32_t readings[PB_NUM_STATES];
    volatile unsigned int index;
    volatile uint32_t debounced_reading;
    volatile uint32_t pressed_flags;
} PB_Set_t;

void PB_init(PB_Set_t * buttons);
void PB_update(PB_Set_t * buttons, uint32_t reading);
uint32_t PB_getButtonStatus(PB_Set_t *buttons, uint32_t button_mask);

#endif /* PUSHBUTTON_H_ */
