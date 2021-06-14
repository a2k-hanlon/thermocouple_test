/**
 * @file pushbutton.c
 * @brief Pushbutton debouncing driver
 * 
 * Based on Jack Ganssle's discussion of debouncing at
 * http://www.ganssle.com/debouncing-pt2.htm
 * 
 */

#include "pushbutton.h"

/**
 * Initialize data instance for pushbutton debouncing driver
 * 
 * @param buttons Pointer to the instance of PB_Set_t to initialize
 */
void PB_init(PB_Set_t * buttons) {
    for(int i = 0; i < PB_NUM_STATES; i++) {
        buttons->readings[i] = 0;
    }
    buttons->index = 0;
    buttons->debounced_reading = 0;
    buttons->pressed_flags = 0;
}

/**
 * Updates the state of a debouncing structure instance with a new
 * reading of the buttons provided as a parameter.
 * 
 * This function should be called on a regular interval (~1-5ms), and could be
 * called from a timer interrupt.
 * 
 * @param buttons Pointer to the instance of PB_Set_t to update
 * @param reading 32 bit-wide value where each bit is the digital reading of
 * a single button. A 1 must signify a button is in the pressed state.
 */
void PB_update(PB_Set_t * buttons, uint32_t reading) {
    uint32_t last_debounced_reading = buttons->debounced_reading;

    buttons->readings[buttons->index] = reading;

    // Circularly increment index
    buttons->index++;
    if (buttons->index >= PB_NUM_STATES) buttons->index = 0;

    // Debounce - only consider the button to actually be pressed if all of the
    // last several (PB_NUM_STATES) sequential readings have been "pressed" (1)
    buttons->debounced_reading = 0xFFFFFFFF;
    for(int i = 0; i < PB_NUM_STATES; i++) {
        buttons->debounced_reading &= buttons->readings[i];
    }

    // Assert button_pressed_flag if new reading is 1 and last reading was 0
    // This is a rising edge - the button has been pressed.
    buttons->pressed_flags |= buttons->debounced_reading & ~last_debounced_reading;
}

/**
 * Check if certain buttons have been pressed since intialization or
 * the last call to this function.
 * 
 * @note Calling this function will also clear the "pressed" status for the
 * buttons selected by button_mask, so a single press of a given button will
 * only result in a 1 at that button's position returned ONCE if the function is
 * called multiple times before the next press of that button.
 * 
 * @param buttons Pointer to the instance of PB_Set_t to check
 * @param button_mask 32 bit-wide value used to select which buttons' flags are
 * returned and reset.
 * @retval 32 bit-wide value with each bit representing whether a given button
 * has been pressed. Only the bits set in button_mask might be set in the return
 * value.
 */
uint32_t PB_getButtonStatus(PB_Set_t *buttons, uint32_t button_mask) {
    uint32_t pressed_flags = buttons->pressed_flags & button_mask;
    buttons->pressed_flags &= ~pressed_flags; // clear pressed flag(s)
    return pressed_flags;
}
