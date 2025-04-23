// Register custom effects
RGB_MATRIX_EFFECT(my_cool_effect_with_kitt)
RGB_MATRIX_EFFECT(my_cool_effect_with_kitt_green)
RGB_MATRIX_EFFECT(my_cool_effect_without_kitt)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#include "host.h"
#include "timer.h"
#include "rgb_matrix.h"
#include "keyboard.h"

// Track breathing animation state
static uint8_t caps_breathe_phase = 0;

// KITT-enabled effect
static bool my_cool_effect_with_kitt(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    static uint16_t last_tick = 0;
    static uint8_t anim_index = 0;
    static bool resumed = false;

    static const uint8_t kitt_leds_left[]  = {81, 82, 83, 84, 85, 86, 87, 88, 89, 90};
    static const uint8_t kitt_leds_right[] = {100, 99, 98, 97, 96, 95, 94, 93, 92, 91};
    static const uint8_t kitt_sequence[]   = {0, 1, 2, 3, 4, 5, 6, 7, 8 ,9, 8, 7, 6, 5, 4, 3, 2, 1};
    const uint8_t kitt_length = sizeof(kitt_sequence) / sizeof(kitt_sequence[0]);

    // Handle suspend state: if the keyboard is suspended, skip animations but still process key events.
    if (rgb_matrix_get_suspend_state()) {
        return false;  // Skip drawing entirely while suspended but allow keypresses.
    }

    // On resume from suspend, reset the animation
    if (resumed) {
        last_tick = timer_read();
        anim_index = 0;
        resumed = false;
    }

    // Advance the animation
    if (timer_elapsed(last_tick) > 75) {
        last_tick = timer_read();
        anim_index = (anim_index + 1) % kitt_length;
    }

    // Clear KITT LEDs
    for (uint8_t i = 0; i < 10; i++) {
        rgb_matrix_set_color(kitt_leds_left[i], 0, 0, 0);
        rgb_matrix_set_color(kitt_leds_right[i], 0, 0, 0);
    }

    // Light up active KITT LEDs
    uint8_t pos = kitt_sequence[anim_index];
    rgb_matrix_set_color(kitt_leds_left[pos], 255, 0, 0);
    rgb_matrix_set_color(kitt_leds_right[pos], 255, 0, 0);

    // Caps lock breathing effect
    if (host_keyboard_led_state().caps_lock) {
        caps_breathe_phase = (caps_breathe_phase + 2) % 255;
    }
    uint8_t caps_brightness = sin8(caps_breathe_phase);

    // Background colors
    for (uint8_t i = led_min; i < led_max; i++) {
        if ((i >= 81 && i <= 90) || (i >= 91 && i <= 100)) continue; // Skip KITT LEDs

        if (i >= 1 && i <= 12) {
            rgb_matrix_set_color(i, 0, 255, 0); // Green
        } else if (i == 43) {
            if (host_keyboard_led_state().caps_lock) {
                rgb_matrix_set_color(i, caps_brightness, 0, 0); // Breathing Red
            } else {
                rgb_matrix_set_color(i, 0, 0, 255); // Static Blue
            }
        }  else if (i == 101) {
            rgb_matrix_set_color(i, 255, 0, 0); // Red
        } else if ((i >= 14 && i <= 25) || (i >= 29 && i <= 41) || (i >= 44 && i <= 54) || (i >= 58 && i <= 68)) {
            rgb_matrix_set_color(i, 255, 0, 255); // Pink
        } else {
            rgb_matrix_set_color(i, 0, 0, 255); // Blue
        }
    }

    return led_max < RGB_MATRIX_LED_COUNT;
}

// KITT-enabled effect green
static bool my_cool_effect_with_kitt_green(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    static uint16_t last_tick = 0;
    static uint8_t anim_index = 0;
    static bool resumed = false;

    static const uint8_t kitt_leds_left[]  = {81, 82, 83, 84, 85, 86, 87, 88, 89, 90};
    static const uint8_t kitt_leds_right[] = {100, 99, 98, 97, 96, 95, 94, 93, 92, 91};
    static const uint8_t kitt_sequence[]   = {0, 1, 2, 3, 4, 5, 6, 7, 8 ,9, 8, 7, 6, 5, 4, 3, 2, 1};
    const uint8_t kitt_length = sizeof(kitt_sequence) / sizeof(kitt_sequence[0]);

    // Handle suspend state: if the keyboard is suspended, skip animations but still process key events.
    if (rgb_matrix_get_suspend_state()) {
        return false;  // Skip drawing entirely while suspended but allow keypresses.
    }

    // On resume from suspend, reset the animation
    if (resumed) {
        last_tick = timer_read();
        anim_index = 0;
        resumed = false;
    }

    // Advance the animation
    if (timer_elapsed(last_tick) > 75) {
        last_tick = timer_read();
        anim_index = (anim_index + 1) % kitt_length;
    }

    // Clear KITT LEDs
    for (uint8_t i = 0; i < 10; i++) {
        rgb_matrix_set_color(kitt_leds_left[i], 0, 0, 0);
        rgb_matrix_set_color(kitt_leds_right[i], 0, 0, 0);
    }

    // Light up active KITT LEDs
    uint8_t pos = kitt_sequence[anim_index];
    rgb_matrix_set_color(kitt_leds_left[pos], 255, 0, 0);
    rgb_matrix_set_color(kitt_leds_right[pos], 255, 0, 0);

    // Caps lock breathing effect
    if (host_keyboard_led_state().caps_lock) {
        caps_breathe_phase = (caps_breathe_phase + 2) % 255;
    }
    uint8_t caps_brightness = sin8(caps_breathe_phase);

    // Background colors
    for (uint8_t i = led_min; i < led_max; i++) {
        if ((i >= 81 && i <= 90) || (i >= 91 && i <= 100)) continue; // Skip KITT LEDs

        if (i >= 1 && i <= 12) {
            rgb_matrix_set_color(i, 255, 0, 0); // Red
        } else if (i == 43) {
            if (host_keyboard_led_state().caps_lock) {
                rgb_matrix_set_color(i, caps_brightness, 0, 0); // Breathing Red
            } else {
                rgb_matrix_set_color(i, 0, 0, 255); // Static Blue
            }
        }  else if (i == 101) {
            rgb_matrix_set_color(i, 255, 0, 0); // Red
        } else if ((i >= 14 && i <= 25) || (i >= 29 && i <= 41) || (i >= 44 && i <= 54) || (i >= 58 && i <= 68)) {
            rgb_matrix_set_color(i, 0, 255, 0); // Green
        } else {
            rgb_matrix_set_color(i, 0, 0, 255); // Blue
        }
    }

    return led_max < RGB_MATRIX_LED_COUNT;
}

// KITT-disabled effect
static bool my_cool_effect_without_kitt(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    static uint8_t caps_breathe_phase = 0;

    // Handle suspend state: if the keyboard is suspended, skip animations but still process key events.
    if (rgb_matrix_get_suspend_state()) {
        return false;  // Skip drawing entirely while suspended but allow keypresses.
    }

    // Caps lock breathing effect
    if (host_keyboard_led_state().caps_lock) {
        caps_breathe_phase = (caps_breathe_phase + 2) % 255;
    }

    uint8_t caps_brightness = sin8(caps_breathe_phase);

    // Update LED colors
    for (uint8_t i = led_min; i < led_max; i++) {
        if ((i >= 81 && i <= 90) || (i >= 91 && i <= 100)) continue; // Skip KITT LEDs

        if (i >= 1 && i <= 12) {
            rgb_matrix_set_color(i, 0, 255, 0); // Green
        } else if (i == 43) {
            if (host_keyboard_led_state().caps_lock) {
                rgb_matrix_set_color(i, caps_brightness, 0, 0); // Breathing Red
            } else {
                rgb_matrix_set_color(i, 0, 0, 255); // Static Blue
            }
        } else if (i == 101) {
            rgb_matrix_set_color(i, 255, 0, 0); // Red
        } else if ((i >= 14 && i <= 25) || (i >= 29 && i <= 41) || (i >= 44 && i <= 54) || (i >= 58 && i <= 68)) {
            rgb_matrix_set_color(i, 255, 0, 255); // Pink
        } else {
            rgb_matrix_set_color(i, 0, 0, 255); // Blue
        }
    }

    return led_max < RGB_MATRIX_LED_COUNT;
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
