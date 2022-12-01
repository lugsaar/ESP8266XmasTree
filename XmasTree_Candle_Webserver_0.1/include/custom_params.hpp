#ifndef CUSTOM_PARAMS_HPP
#define CUSTOM_PARAMS_HPP

#include <FastLED.h>

FASTLED_USING_NAMESPACE

// LED setup parameters
# define FASTLED_ALLOW_INTERRUPTS 0


#define DATA_PIN            2
#define NUM_LEDS            15
#define MAX_POWER_MILLIAMPS 500
#define LED_TYPE            WS2812B
#define COLOR_ORDER         GRB

#define BRIGHTNESS          48

#define LED_BUILTIN 2   // Set the GPIO pin where you connected your test LED or comment this line out if your dev board has a built-in LED

extern CRGB leds[];


#endif