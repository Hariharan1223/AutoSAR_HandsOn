#ifndef ADC_H
#define ADC_H

typedef unsigend int Adc_GroupType 
typedef unsigned int Adc_ValueGroupType;
#define ADC_BASE_ADDRESS 0x40000000 /* Assuming the ADC base address */

/* ADC Register Addresses */
#define ADC_CR   (*((volatile uint32_t *)(ADC_BASE_ADDRESS + 0x00))) /* Control Register */
#define ADC_SR   (*((volatile uint32_t *)(ADC_BASE_ADDRESS + 0x04))) /* Status Register */
#define ADC_DR   (*((volatile uint32_t *)(ADC_BASE_ADDRESS + 0x08))) /* Data Register */
#define ADC_SMPR (*((volatile uint32_t *)(ADC_BASE_ADDRESS + 0x0C))) /* Sampling Time Register */


/* ADC Control Register Bits */
#define ADC_CR_ADEN (1 << 0)  /* ADC Enable */
#define ADC_CR_ADSTART (1 << 2) /* ADC Start Conversion */

/* ADC Status Register Bits */
#define ADC_SR_EOC (1 << 1) /* End of Conversion */

/* ADC Sampling Time Values */
#define ADC_SMPR_SMP_VAL 7 /* Assuming a sampling time of 480 cycles */
#define ADC_GROUP_SPEED_SENSOR 1 
#define ADC_CHANNEL_5 5 /* speed sensor is connected to ADC channel 5 */
/* Error codes */
#define ADC_E_OK               0x00
#define ADC_E_PARAM_GROUP      0x01
#define ADC_E_CONV_NOT_COMPLETED 0x02
#define ADC_E_NULL_POINTER     0x03

/* Function prototypes */
Std_ReturnType Adc_Init(void);
void Adc_StartGroupConversion(Adc_GroupType Group);
Std_ReturnType Adc_ReadGroup(Adc_GroupType Group, Adc_ValueGroupType* DataBufferPtr);

/* Function to report errors */
void Adc_ReportError(uint8_t ErrorCode);

#endif /*ADC_H*/