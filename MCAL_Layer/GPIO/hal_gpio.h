#ifndef HAL_GPIO_H
#define HAL_GPIO_H

/*****************************************
 *                 Includes              *
 *****************************************/
#include "../GPIO/hal_gpio_cfg.h"
#include "pic18f4620.h"
#include "../std_types.h"
/*****************************************
 *           Macro Declarations          *
 *****************************************/
#define BIT_MASK                  (uint8)0x01
#define ALL_REG_MASK              (uint8)0xFF

#define PIN_MAX_NUMBER 8
#define PORT_MAX_NUMBER 5

// Configuration macros
#define PIN_PORT_CONFIGRATION GPIO_CONFIG_ENABLE
/*****************************************
 *       Macro Function Declarations     *
 *****************************************/
#define HWRIG8(X) (*((volatile uint8 *)(X)))

#define SET_BIT(REG, BIT_POSN)         ((REG) |= (BIT_MASK << (BIT_POSN)))
#define CLEAR_BIT(REG, BIT_POSN)       ((REG) &= ~(BIT_MASK << (BIT_POSN)))
#define TOGGLE_BIT(REG, BIT_POSN)      ((REG) ^= (BIT_MASK << (BIT_POSN)))
#define READ_BIT(REG, BIT_POSN)        (((REG) >> (BIT_POSN)) & BIT_MASK)

/*****************************************
 *          Data Type Declarations       *
 *****************************************/
typedef enum {
  LOW = 0, // 0v
  HIGH = 1 // 5v
} logic_t;

typedef enum { OUTPUT = 0 , INPUT = 1 } direction_t;

typedef enum {
  PIN0 = 0,
  PIN1 = 1,
  PIN2 = 2,
  PIN3 = 3,
  PIN4 = 4,
  PIN5 = 5,
  PIN6 = 6,
  PIN7 = 7
} pin_index_t;

typedef enum {
  PORTA_INDEX = 0,
  PORTB_INDEX = 1,
  PORTC_INDEX = 2,
  PORTD_INDEX = 3,
  PORTE_INDEX = 4
} port_index_t;

typedef struct {
  uint8 port : 3;      // Bits 0-2 (LSB side)
  uint8 pin : 3;       // Bits 3-5
  uint8 direction : 1; // Bit 6
  uint8 logic : 1;     // Bit 7 (MSB side)
} pin_config_t;

/*****************************************
 *        Function Declarations          *
 *****************************************/
Std_RetuenType gpio_pin_direction_intialize(const pin_config_t *pin_config);
Std_RetuenType gpio_pin_write_direction(const pin_config_t *pin_config ,direction_t direction);
Std_RetuenType gpio_pin_get_direction_status(const pin_config_t *pin_config,direction_t *dir_status);
Std_RetuenType gpio_pin_write_logic(const pin_config_t *pin_config, logic_t logic_status);
Std_RetuenType gpio_pin_Read_logic(const pin_config_t *pin_config,logic_t *logic_status);
Std_RetuenType gpio_pin_Toggle_logic(const pin_config_t *pin_config);

/* Port-level operations */
Std_RetuenType gpio_port_direction_intialize(port_index_t port,uint8 direction);
Std_RetuenType gpio_port_get_direction_status(port_index_t port,uint8 *dir_status);
Std_RetuenType gpio_port_write_logic(port_index_t port, uint8 logic);
Std_RetuenType gpio_port_Read_logic(port_index_t port, uint8 *logic);
Std_RetuenType gpio_port_Toggle_logic(port_index_t port);

#endif /* HAL_GPIO_H */