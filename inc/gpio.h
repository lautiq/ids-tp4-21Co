#ifndef GPIO_H
#define GPIO_H_

/**
 * @file gpio.h
 * @author Lautaro Quarin (lautaroquarin@gmail.com)
 * @brief API for controlling GPIOs
 */
/* === Header files inclusions ================================================================ */
#include <stdint.h>
#include <stdbool.h>
/* === C++ Header ============================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =============================================================== */

/* === Public data type declarations =========================================================== */
typedef struct gpio_s * gpio_t; // pointer to anonymous structure

/* === Public variable declarations ============================================================ */

/* === Public function declarations ============================================================ */
/**
 * @brief GPIO instance constructor
 *
 * @param port 8-bit port to use
 * @param bit GPIO pin to use
 * @return gpio_t
 */
gpio_t gpioCreate(uint8_t port, uint8_t bit);

/**
 * @brief Configures the GPIO instance as input or output.
 *
 * @param gpio GPIO instance to work with
 * @param output Desired state for the GPIO
 */
void gpioSetOutput(gpio_t gpio, bool output);

/**
 * @brief Sets the state of a pin configured as output.
 *
 * @param gpio GPIO instance to work with
 * @param state Desired state for the pin
 */
void gpioSetState(gpio_t gpio, bool state);

/**
 * @brief Reads the state of an instance configured as input
 *
 * @param gpio GPIO instance to work with
 * @return true - a high state is read
 * @return false - a low state is read
 */
bool gpioGetState(gpio_t gpio);

/* === End of documentation ==================================================================== */
#ifdef __cplusplus
}
#endif

#endif
