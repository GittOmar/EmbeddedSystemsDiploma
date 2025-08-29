/*******************************************************************************
 * @file       hal_adc.h
 * @brief      Driver/Module Description
 * @date       2025/08/28
 * @time       20:38
 * @author     Omar Ibrahim
 ******************************************************************************/

#ifndef hal_adc_H_
#define hal_adc_H_

/*****************************************
 *                 Includes              *
 *****************************************/
#include "hal_adc_cfg.h"
#include "../std_types.h"
#include "pic18f4620.h"
#include "./../INTERRUPT/./mcal_internal_interrupt.h"
/*****************************************
 *           Macro Declarations          *
 *****************************************/
#define ADC_CONVERSION_STATE             (ADCON0bits.GO_DONE) 
#define ADC_STILL_CONVERT                 0x01U 

#define INTERNAL_VOLTAGE_SOURECE     0x00U
#define EXTERNAL_VOLTAGE_SOURECE     0x01U

#define SubtractionCOff              14U
#define One_Byte                      8U
/*****************************************
 *       Macro Function Declarations     *
 *****************************************/
#define ADC_MODULE_ENABLE()                            (ADCON0bits.ADON = 1)  /** ADC Enable  */
#define ADC_MODULE_DISABLE()                           (ADCON0bits.ADON = 0)  /** ADC Disable  */

#define ADC_START_CONVERSION()                         (ADCON0bits.GO_DONE = 1)  /** Start Conversion  */

#define RESULT_FORMATE_RIGHT_justified()                  (ADCON2bits.ADFM = 1)  /** Formate  */                                                                                                                    


#define ADC_RESULT_LSByte                              (ADRESL)    /** L_SByte  */   
#define ADC_RESULT_MSByte                              (ADRESH)    /** M_SByte  */

#define ADC_Vref_VssVDD()                              do{ ADCON1bits.VCFG0 = 0; \
                                                           ADCON1bits.VCFG1 = 0;}while(0)
               
#define ADC_Vref_EXTERNAL_SOURCE()                     do{ ADCON1bits.VCFG0 = 1; \
                                                           ADCON1bits.VCFG1 = 1; }while(0) 

#define ADC_PORT_AB_ANALOG_DIGITAL_CFG(_x)              (ADCON1bits.PCFG = (uint8)_x)    /** A/D pin cfg  */
#define ADC_CH_SELECT(_x)                               (ADCON0bits.CHS  = (uint8)_x)    /** choose the channel want to use   */ 
#define ADC_acquisition_time(_x)                        (ADCON2bits.ACQT = (uint8)_x)    /** Determine the ACQ time  */
#define ADC_Clk_Conversion(_x)                          (ADCON2bits.ADCS = (uint8)_x)    /** Determine The CLK_Conversion  */
/*****************************************
 *          Data Type Declarations       *
 *****************************************/
typedef enum{ /**ADC_ channel*/
ADC_AN0,
ADC_AN1,
ADC_AN2,
ADC_AN3,
ADC_AN4,
ADC_AN5,
ADC_AN6,
ADC_AN7,
ADC_AN8,
ADC_AN9,
ADC_AN10,
ADC_AN11,
ADC_AN12,
}adc_channel_t;

typedef enum{
ADC_0_TAD,
ADC_2_TAD,
ADC_4_TAD,
ADC_6_TAD,
ADC_8_TAD,
ADC_12_TAD,
ADC_16_TAD,
ADC_20_TAD
}adc_acquisition_time_t;

typedef enum{
ADC_CONVERSION_CLK_FOSC_DIV_2,
ADC_CONVERSION_CLK_FOSC_DIV_8,
ADC_CONVERSION_CLK_FOSC_DIV_32,
ADC_CONVERSION_CLK_FRC,
ADC_CONVERSION_CLK_FOSC_DIV_4,
ADC_CONVERSION_CLK_FOSC_DIV_16,
ADC_CONVERSION_CLK_FOSC_DIV_64
}adc_clock_conversion_t;


typedef struct{
InterruotHandler          InterruotHandler; 
adc_channel_t             channel;
adc_acquisition_time_t    acquisition_time; /** Minimum Time is 2Tad  */
adc_clock_conversion_t    clock_conversion;
uint8 adc_voltage_source : 1;  
}adc_cfg_t;


/*****************************************
 *        Function Declarations          *
 *****************************************/
Std_RetuenType hal_adc_init(const adc_cfg_t *ADC);
Std_RetuenType hal_adc_deinit(const adc_cfg_t *ADC);
Std_RetuenType hal_adc_read_analog_pin(const adc_cfg_t *ADC,adc_channel_t UsedChannel,uint16 *AnalogValue);

#endif /* hal_adc_H_ */