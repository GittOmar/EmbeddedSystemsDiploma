/*
 * File:   led.c
 * Author: pc
 *
 * Created on June 21, 2025, 11:30 AM
 */
#include "led.h"

/**
 * @brief
 *
 * @param led_config
 * @return Std_RetuenType
 */
#if LED_CONFIGRATION == LED_FUN_ENABLE

Std_RetuenType
led_initialize(const led_t *led_config) // port x  pin y  make it output
{
  Std_RetuenType ret = E_OK;
  pin_config_t led = {.port = led_config->port,
                      .pin = led_config->pin,
                      .direction = OUTPUT,
                      .logic = led_config->status};

  logic_t logic_state = led.logic;
  if (led_config == NULL) {
    ret = E_NOT_OK;
  } else {

    gpio_pin_direction_intialize(&led);
    gpio_pin_write_logic(&led, logic_state);
  }
  return ret;
}
#endif

/**
 * @brief
 *
 * @param led_config
 * @return Std_RetuenType
 */
#if LED_CONFIGRATION == LED_FUN_ENABLE
Std_RetuenType led_turn_on(const led_t *led_config) {
  Std_RetuenType ret = E_OK;
  pin_config_t led = {.port = led_config->port,
                      .pin = led_config->pin,
                      .direction = OUTPUT,
                      .logic = led_config->status};

  if (led_config == NULL) {
    ret = E_NOT_OK;
  } else {

    gpio_pin_write_logic(&led, HIGH);
  }

  return ret;
}
#endif
/**
 * @brief
 *
 * @param led_config
 * @return Std_RetuenType
 */
#if LED_CONFIGRATION == LED_FUN_ENABLE
Std_RetuenType led_turn_off(const led_t *led_config) {

  Std_RetuenType ret = E_OK;
  pin_config_t led = {.port = led_config->port,
                      .pin = led_config->pin,
                      .direction = OUTPUT,
                      .logic = led_config->status};

  if (led_config == NULL) {
    ret = E_NOT_OK;
  } else {

    gpio_pin_write_logic(&led, LOW);
  }

  return ret;
}
#endif
/**
 * @brief
 *
 * @param led_config
 * @return Std_RetuenType
 */
#if LED_CONFIGRATION == LED_FUN_ENABLE
Std_RetuenType led_turn_toggle(const led_t *led_config) {

  Std_RetuenType ret = E_OK;
  pin_config_t led = {.port = led_config->port,
                      .pin = led_config->pin,
                      .direction = OUTPUT,
                      .logic = led_config->status};

  if (led_config == NULL) {
    ret = E_NOT_OK;
  } else {

    gpio_pin_Toggle_logic(&led);
  }

  return ret;
}
#endif