// Register custom effects
RGB_MATRIX_EFFECT(my_cool_effect_with_kitt)
RGB_MATRIX_EFFECT(my_cool_effect_without_kitt)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#include "host.h" // Needed for host_keyboard_led_state()

// KITT-enabled effect
static bool my_cool_effect_with_kitt(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    static uint16_t last_tick = 0;
    static uint8_t anim_index = 0;

    static const uint8_t kitt_leds_left[]  = {105, 106, 107, 108, 109, 110, 111, 112, 113};
    static const uint8_t kitt_leds_right[] = {123, 122, 121, 120, 119, 118, 117, 116, 115};
    static const uint8_t kitt_sequence[]   = {0, 1, 2, 3, 4, 5, 6, 7, 8, 7, 6, 5, 4, 3, 2, 1};
    const uint8_t kitt_length = sizeof(kitt_sequence) / sizeof(kitt_sequence[0]);

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

    // Color the rest
    for (uint8_t i = led_min; i < led_max; i++) {
        if ((i >= 105 && i <= 113) || (i >= 115 && i <= 123)) continue; // Skip KITT LEDs

        if (i >= 1 && i <= 12) {
            rgb_matrix_set_color(i, 0, 255, 0); // Green
        } else if (i == 58) {
            if (host_keyboard_led_state().caps_lock) {
                rgb_matrix_set_color(i, 255, 0, 0); // Red (Caps Lock ON)
            } else {
                rgb_matrix_set_color(i, 0, 0, 255);   // Blue (Caps Lock OFF)
            }
        } else if (i == 33) { // NumLock indicator
            if (host_keyboard_led_state().num_lock) {
                rgb_matrix_set_color(i, 255, 0, 0); // Red (Num Lock ON)
            } else {
                rgb_matrix_set_color(i, 0, 0, 255); // Blue (Num Lock OFF)
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

    for (uint8_t i = led_min; i < led_max; i++) {
        if ((i >= 105 && i <= 113) || (i >= 115 && i <= 123)) continue; // Skip KITT LEDs

        if (i >= 1 && i <= 12) {
            rgb_matrix_set_color(i, 0, 255, 0); // Green
        } else if (i == 58) {
            if (host_keyboard_led_state().caps_lock) {
                rgb_matrix_set_color(i, 255, 0, 0); // Red (Caps Lock ON)
            } else {
                rgb_matrix_set_color(i, 0, 0, 255);   // Blue (Caps Lock OFF)
            }
        } else if (i == 33) { // NumLock indicator
            if (host_keyboard_led_state().num_lock) {
                rgb_matrix_set_color(i, 255, 0, 0); // Red (Num Lock ON)
            } else {
                rgb_matrix_set_color(i, 0, 0, 255); // Blue (Num Lock OFF)
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

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
