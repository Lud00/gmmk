// Register custom effects
RGB_MATRIX_EFFECT(my_cool_effect_with_kitt)
RGB_MATRIX_EFFECT(my_cool_effect_without_kitt)
RGB_MATRIX_EFFECT(my_cool_effect_gaming)
RGB_MATRIX_EFFECT(my_valheim_effect)

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

    static const uint8_t kitt_leds_left[]  = {105, 106, 107, 108, 109, 110, 111, 112, 113};
    static const uint8_t kitt_leds_right[] = {123, 122, 121, 120, 119, 118, 117, 116, 115};
    static const uint8_t kitt_sequence[]   = {0, 1, 2, 3, 4, 5, 6, 7, 8, 7, 6, 5, 4, 3, 2, 1};
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
    for (uint8_t i = 0; i < 9; i++) {
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
        if ((i >= 105 && i <= 113) || (i >= 115 && i <= 123)) continue; // Skip KITT LEDs

        if (i >= 1 && i <= 12) {
            rgb_matrix_set_color(i, 0, 255, 0); // Green
        } else if (i == 58) {
            if (host_keyboard_led_state().caps_lock) {
                rgb_matrix_set_color(i, caps_brightness, 0, 0); // Breathing Red
            } else {
                rgb_matrix_set_color(i, 0, 0, 255); // Static Blue
            }
        } else if (i == 33) { // NumLock indicator
            if (host_keyboard_led_state().num_lock) {
                rgb_matrix_set_color(i, 255, 0, 0); // Red
            } else {
                rgb_matrix_set_color(i, 0, 0, 255); // Blue
            }
        } else if (i == 125) {
            rgb_matrix_set_color(i, 255, 0, 0); // Red
        } else if ((i >= 17 && i <= 28) || (i >= 38 && i <= 50) || (i >= 59 && i <= 69) || (i >= 76 && i <= 85)) {
            rgb_matrix_set_color(i, 255, 0, 255); // Pink
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
        if ((i >= 105 && i <= 113) || (i >= 115 && i <= 123)) continue; // Skip KITT LEDs

        if (i >= 1 && i <= 12) {
            rgb_matrix_set_color(i, 0, 255, 0); // Green
        } else if (i == 58) {
            if (host_keyboard_led_state().caps_lock) {
                rgb_matrix_set_color(i, caps_brightness, 0, 0); // Breathing Red
            } else {
                rgb_matrix_set_color(i, 0, 0, 255); // Static Blue
            }
        } else if (i == 33) {
            if (host_keyboard_led_state().num_lock) {
                rgb_matrix_set_color(i, 255, 0, 0); // Red
            } else {
                rgb_matrix_set_color(i, 0, 0, 255); // Blue
            }
        } else if (i == 125) {
            rgb_matrix_set_color(i, 255, 0, 0); // Red
        } else if ((i >= 17 && i <= 28) || (i >= 38 && i <= 50) || (i >= 59 && i <= 69) || (i >= 76 && i <= 85)) {
            rgb_matrix_set_color(i, 255, 0, 255); // Pink
        } else {
            rgb_matrix_set_color(i, 0, 0, 255); // Blue
        }
    }

    return led_max < RGB_MATRIX_LED_COUNT;
}

// Gaming theme effect
static bool my_cool_effect_gaming(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    static uint8_t pulse = 0;
    static uint8_t direction = 1;

    if (rgb_matrix_get_suspend_state()) {
        return false;
    }

    // Pulsing brightness for gaming highlight
    if (direction) {
        pulse++;
        if (pulse >= 255) direction = 0;
    } else {
        pulse--;
        if (pulse <= 30) direction = 1;
    }

    for (uint8_t i = led_min; i < led_max; i++) {
        // WASD keys (example assumes keycodes 59=A, 60=S, 61=D, 39=W) - adjust to match your layout
        if (i == 59 || i == 60 || i == 61 || i == 39) {
            rgb_matrix_set_color(i, pulse, pulse / 3, 0); // pulsing orange
        }
        else if (i == 0) {
            rgb_matrix_set_color(i, 255, 255, 0); // Esc key glowing yellow
        }
        else {
            rgb_matrix_set_color(i, 0, 0, 255); // default blue
        }
    }

    return led_max < RGB_MATRIX_LED_COUNT;
}

// Valheim-inspired theme
static bool my_valheim_effect(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    static uint8_t pulse = 0;
    static bool increasing = true;

    if (rgb_matrix_get_suspend_state()) {
        return false;
    }

    // Pulsing effect control
    pulse += increasing ? 2 : -2;
    if (pulse > 245) increasing = false;
    if (pulse < 30) increasing = true;

    for (uint8_t i = led_min; i < led_max; i++) {
        // WASD keys (movement)
        if (i == 59 || i == 60 || i == 61 || i == 39) {
            rgb_matrix_set_color(i, 255, pulse / 2, 0); // Glowing orange
        }
        // E key (interact)
        else if (i == 40) {
            rgb_matrix_set_color(i, pulse, pulse, 0); // Pulsing yellow
        }
        // Shift keys (stamina)
        else if (i == 225 || i == 229) {
            rgb_matrix_set_color(i, 0, 255, 0); // Green
        }
        // F key (Forsaken Power)
        else if (i == 62) {
            rgb_matrix_set_color(i, pulse, 0, 0); // Pulsing red
        }
        // ESC key (menu / pause)
        else if (i == 0) {
            rgb_matrix_set_color(i, 128, 0, 255); // Mystic purple
        }
        // All other keys - ambient
        else {
            rgb_matrix_set_color(i, 60, 0, 80); // Deep twilight purple
        }
    }

    return led_max < RGB_MATRIX_LED_COUNT;
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
