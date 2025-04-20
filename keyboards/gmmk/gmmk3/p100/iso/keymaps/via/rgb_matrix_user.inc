// !!! DO NOT ADD #pragma once !!! //

// Step 1.
// Declare the custom effect using the RGB_MATRIX_EFFECT macro
RGB_MATRIX_EFFECT(customRedBlueGreenMiami)

// Step 2.
// Define the effect inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool customRedBlueGreenMiami(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    for (uint8_t i = led_min; i < led_max; i++) {
        if (i >= 1 && i <= 12) {
            rgb_matrix_set_color(i, 0, 255, 0);    // Green
        } else if (i == 58 || i == 125) {
            rgb_matrix_set_color(i, 255, 0, 0);    // Red
        } else {
            rgb_matrix_set_color(i, 0, 0, 255);    // Blue
        }
    }

    // set left sidebar
    rgb_matrix_set_color(105, 31, 79, 255);
    rgb_matrix_set_color(106, 82, 77, 255);
    rgb_matrix_set_color(107, 113, 74, 255);
    rgb_matrix_set_color(108, 139, 70, 255);
    rgb_matrix_set_color(109, 162, 65, 255);
    rgb_matrix_set_color(110, 183, 59, 254);
    rgb_matrix_set_color(111, 203, 52, 251);
    rgb_matrix_set_color(112, 221, 43, 248);
    rgb_matrix_set_color(113, 238, 32, 244);
    rgb_matrix_set_color(114, 255, 15, 239);

    // set right sidebar
    rgb_matrix_set_color(115, 31, 79, 255);
    rgb_matrix_set_color(116, 82, 77, 255);
    rgb_matrix_set_color(117, 113, 74, 255);
    rgb_matrix_set_color(118, 139, 70, 255);
    rgb_matrix_set_color(119, 162, 65, 255);
    rgb_matrix_set_color(120, 183, 59, 254);
    rgb_matrix_set_color(121, 203, 52, 251);
    rgb_matrix_set_color(122, 221, 43, 248);
    rgb_matrix_set_color(123, 238, 32, 244);
    rgb_matrix_set_color(124, 255, 15, 239);

    return led_max < RGB_MATRIX_LED_COUNT;
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
