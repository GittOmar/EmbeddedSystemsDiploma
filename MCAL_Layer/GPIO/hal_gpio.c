/*
 * File:   hal_gpio.c
 * Author: pc
 *
 * Created on June 21, 2025, 11:14 AM
 */
#include "./hal_gpio.h"

volatile uint8 *tris_register[] = {&TRISA, &TRISB, &TRISC, &TRISD, &TRISE};
volatile uint8 *lat_register[] = {&LATA, &LATB, &LATC, &LATD, &LATE};
volatile uint8 *port_register[] = {&PORTA, &PORTB, &PORTC, &PORTD, &PORTE};

/**
 * @brief
 *
 * @param _pin_config
 * @return Std_RetuenType
 */

#if PIN_PORT_CONFIGRATION == GPIO_CONFIG_ENABLE

Std_RetuenType gpio_pin_direction_intialize(const pin_config_t *_pin_config) {
    Std_RetuenType ret = E_OK;
    if (_pin_config == NULL || _pin_config->pin > PIN_MAX_NUMBER - 1 ||
            _pin_config->port > PORT_MAX_NUMBER - 1) {
        ret = E_NOT_OK;
    } else {

        switch (_pin_config->direction) {
            case OUTPUT:
                CLEAR_BIT(*tris_register[_pin_config->port], _pin_config->pin);
                break;

            case INPUT:
                SET_BIT(*tris_register[_pin_config->port], _pin_config->pin);
                break;

            default:
                ret = E_NOT_OK;
        }
    }

    return ret;
}
#endif


#if PIN_PORT_CONFIGRATION == GPIO_CONFIG_ENABLE

/**
 * @brief this function is used to make the user interface more easer
 *        give the programmer the ability to assign the direction from the .c file 
 *        and make the user free from assingin the direction from utr interface
 * 
 * @param pin_config 
 * @param direction 
 * @return Std_RetuenType 
 */
Std_RetuenType gpio_pin_write_direction(const pin_config_t *pin_config, direction_t direction) {
    Std_RetuenType ret = E_OK;
    if (pin_config == NULL) {
        ret = E_NOT_OK;
    } else {
        switch ((uint8) direction) {

            case OUTPUT:
                CLEAR_BIT(*tris_register[pin_config->port], pin_config->pin);
                break;

            case INPUT:
                SET_BIT(*tris_register[pin_config->port], pin_config->pin);
                break;

            default:
                ret = E_NOT_OK;
        }
    }
    return ret;
}
#endif



/**
 * @brief
 *
 * @param _pin_config
 * @param dir_status
 * @return Std_RetuenType
 */
#if PIN_PORT_CONFIGRATION == GPIO_CONFIG_ENABLE

Std_RetuenType gpio_pin_get_direction_status(const pin_config_t *_pin_config, direction_t *dir_status) {
    Std_RetuenType ret = E_OK;

    if (_pin_config == NULL || dir_status == NULL) {
        ret = E_NOT_OK;
    } else {
        *dir_status = READ_BIT(*tris_register[_pin_config->port], _pin_config->pin);
    }
    return ret;
}
#endif
/**
 * @brief
 *
 * @param _pin_config
 * @param logic_status
 * @return Std_RetuenType
 */
#if PIN_PORT_CONFIGRATION == GPIO_CONFIG_ENABLE

Std_RetuenType gpio_pin_write_logic(const pin_config_t *_pin_config,
        logic_t logic_status) {
    Std_RetuenType ret = E_OK;
    if (_pin_config == NULL) {
        ret = E_NOT_OK;
    } else {
        switch (logic_status) {
            case LOW:
                CLEAR_BIT(*lat_register[_pin_config->port], _pin_config->pin);
                break;

            case HIGH:
                SET_BIT(*lat_register[_pin_config->port], _pin_config->pin);
                break;

            default:
                ret = E_NOT_OK;
        }
    }

    return ret;
}
#endif
/**
 * @brief
 *
 * @param _pin_config
 * @param logic_status
 * @return Std_RetuenType
 */
#if PIN_PORT_CONFIGRATION == GPIO_CONFIG_ENABLE

Std_RetuenType gpio_pin_Read_logic(const pin_config_t *_pin_config, logic_t *logic_status) {
    Std_RetuenType ret = E_OK;
    if (_pin_config == NULL || logic_status == NULL) {
        ret = E_NOT_OK;
    } else {
        *logic_status = READ_BIT(*port_register[_pin_config->port], _pin_config->pin);
    }

    return ret;
}
#endif
/**
 * @brief
 *
 * @param _pin_config
 * @return Std_RetuenType
 */
#if PIN_PORT_CONFIGRATION == GPIO_CONFIG_ENABLE

Std_RetuenType gpio_pin_Toggle_logic(const pin_config_t *_pin_config) {
    Std_RetuenType ret = E_OK;
    if (_pin_config == NULL) {
        ret = E_NOT_OK;
    } else {
        TOGGLE_BIT(*lat_register[_pin_config->port], _pin_config->pin);
    }

    return ret;
}
#endif

/**
 * @brief
 *
 * @param port
 * @param direction
 * @return Std_RetuenType
 */
#if PIN_PORT_CONFIGRATION == GPIO_CONFIG_ENABLE

Std_RetuenType gpio_port_direction_intialize(port_index_t port,
        uint8 direction) {
    Std_RetuenType ret = E_OK;
    if (port > PORT_MAX_NUMBER - 1) {
        ret = E_NOT_OK;
    } else {

        *tris_register[port] = direction;
    }

    return ret;
}
#endif

#if PIN_PORT_CONFIGRATION == GPIO_CONFIG_ENABLE

/**
 * @brief 
 * 
 * @param port 
 * @param dir_status 
 * @return Std_RetuenType 
 */
Std_RetuenType gpio_port_get_direction_status(port_index_t port,
        uint8 *dir_status) {
    Std_RetuenType ret = E_OK;
    if (dir_status == NULL || port > PORT_MAX_NUMBER - 1) {
        ret = E_NOT_OK;
    } else {
        *dir_status = *tris_register[port];
    }

    return ret;
}
#endif

/**
 * @brief
 *
 * @param port
 * @param logic
 * @return Std_RetuenType
 */
#if PIN_PORT_CONFIGRATION == GPIO_CONFIG_ENABLE

Std_RetuenType gpio_port_write_logic(port_index_t port, uint8 logic) {
    Std_RetuenType ret = E_OK;
    if (port > PORT_MAX_NUMBER - 1) {
        ret = E_NOT_OK;
    } else {
        *lat_register[port] = logic;
    }

    return ret;
}
#endif

#if PIN_PORT_CONFIGRATION == GPIO_CONFIG_ENABLE

/**
 * @brief 
 * 
 * @param port 
 * @param logic 
 * @return Std_RetuenType 
 */
Std_RetuenType gpio_port_Read_logic(port_index_t port, uint8 *logic) {
    Std_RetuenType ret = E_OK;
    if (logic == NULL || port > PORT_MAX_NUMBER - 1) {
        ret = E_NOT_OK;
    } else {
        *logic = *lat_register[port];
    }

    return ret;
}
#endif

/**
 * @brief
 *
 * @param port
 * @return Std_RetuenType
 */
#if PIN_PORT_CONFIGRATION == GPIO_CONFIG_ENABLE

/**
 * @brief 
 * 
 * @param port 
 * @return Std_RetuenType 
 */
Std_RetuenType gpio_port_Toggle_logic(port_index_t port) {
    Std_RetuenType ret = E_OK;
    if (port > PORT_MAX_NUMBER - 1) {
        ret = E_NOT_OK;
    } else {
        *lat_register[port] ^= ALL_REG_MASK;
    }
    return ret;
}
#endif