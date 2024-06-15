/**
 * @file: gpio.c
 * @brief Source code for gpio.c
 *
 */

/* === Headers files inclusions =============================================================== */
#include "gpio.h"
#include "inc\gpio.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

/* === Public macros definitions =============================================================== */
#ifndef GPIO_MAX_INSTANCES
#define GPIO_MAX_INSTANCES 10
#endif

/* === Private data type definition ========================================================== */
struct gpio_s {
    uint8_t port;
    uint8_t bit;
    bool output;
    bool state;
    bool used;
};

/* === Private function definition ============================================================ */
/**
 * @brief Private function to create an instance without using dynamic memory
 *
 * @return gpio_t
 */
static gpio_t allocateInstance() {
    static struct gpio_s instances[GPIO_MAX_INSTANCES] = {0};

    gpio_t result = NULL;
    for (int index = 0; index < GPIO_MAX_INSTANCES; index++) {
        if (!instances[index].used) {
            result = &instances[index];
            result->used = true;
            break;
        }
    }
    return result;
}

/* === Public function definition ============================================================ */
gpio_t gpioCreate(uint8_t port, uint8_t bit) {
#ifdef USE_DYNAMIC_MEM
    gpio_t self = malloc(sizeof(struct gpio_s));
#else
    gpio_t self = allocateInstance();
#endif
    if (self) {
        self->port = port;
        self->bit = bit;
        self->output = false;
    }
    return self;
}

void gpioSetOutput(gpio_t gpio, bool output) {
    gpio->output = output;
    HAL_GPIO_SET_OUTPUT(gpio->port, gpio->bit);
}

void gpioSetState(gpio_t gpio, bool state) {
    if (gpio->output) {
        HAL_GPIO_SET_STATE(gpio->port, gpio->bit, state);
        gpio->state = state; // Save the state internally
    }
}

bool gpioGetState(gpio_t gpio) {
    return HAL_GPIO_GET_STATE(gpio->port, gpio->bit);
}
