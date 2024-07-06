/**
 * @file ecu_abstraction_swc.h
 * @brief Header file for ECU Abstraction Software Component
 */

#ifndef ECU_ABSTRACTION_SWC_H
#define ECU_ABSTRACTION_SWC_H

#include "Std_Types.h"
#include "Adc.h"
#include "Gpt.h"

/* Module ID for error reporting */
#define MODULE_ID_ECUABSTRACTION 123

/* ECU Abstraction error codes */
#define ECUABSTRACTION_E_PARAM_POINTER     0x01
#define ECUABSTRACTION_E_ADC_TIMEOUT       0x02
#define ECUABSTRACTION_E_ADC_READ_FAILED   0x03

/* Conversion constant for speed sensor */
#define SPEED_SENSOR_CONSTANT              0.036f

/* ADC channel for speed sensor */
#define SPEED_SENSOR_ADC_CHANNEL           5

/**
 * @brief Initialize the ECU Abstraction module
 * @return Std_ReturnType E_OK if successful, E_NOT_OK if an error occurs
 */
Std_ReturnType EcuAbstraction_Init(void);

/**
 * @brief Reads the vehicle speed from the digital Hall-effect speed sensor
 * @return Vehicle speed in kilometers per hour (km/h), or -1.0f if an error occurs
 */
float EcuAbstraction_GetVehicleSpeed(void);

/**
 * @brief Gets the latest vehicle speed
 * @return Latest vehicle speed in kilometers per hour (km/h)
 */
float EcuAbstraction_GetLatestSpeed(void);

/* Function to report errors */
void Det_ReportError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId);

#endif /* ECU_ABSTRACTION_SWC_H */
