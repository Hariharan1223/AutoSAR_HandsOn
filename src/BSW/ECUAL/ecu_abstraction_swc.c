/**
 * @file ecu_abstraction_swc.c
 * @brief ECU Abstraction Software Component implementation
 */
#include "ecu_abstraction_swc.h"
#include "Adc.h"
#include "Gpt.h"
#include "Det.h"

#define ECUABSTRACTION_E_PARAM_POINTER     0x01
#define ECUABSTRACTION_E_ADC_TIMEOUT       0x02
#define ECUABSTRACTION_E_ADC_READ_FAILED   0x03

#define ADC_CONVERSION_TIMEOUT             100 /* Timeout in milliseconds */
#define SPEED_SENSOR_CONSTANT              0.036f /* Conversion constant */

#define SPEED_SENSOR_ADC_CHANNEL           5 /* ADC channel for speed sensor */

static volatile float vehicleSpeed = 0.0f;

static void SpeedSensor_PeriodicTask(void)
{
	float newSpeed = EcuAbstraction_GetVehicleSpeed();
	vehicleSpeed = newSpeed;
}

Std_ReturnType EcuAbstraction_Init(void)
{
	Gpt_ConfigType gptConfig = {
		.Period = 100000 // Set timer period to 100ms for frequent speed checks
	};
	Gpt_Init(&gptConfig);
	Gpt_SetCallback(0, SpeedSensor_PeriodicTask);
	Gpt_StartTimer(0, 0);

	/* Initialize ADC*/

	Adc_ConfigType adcConfig = {
    .GroupConfig = {
        [ADC_GROUP_SPEED_SENSOR] = {
			.AdcChannel        = SPEED_SENSOR_ADC_CHANNEL,
			.AdcResolution     = ADC_RESOLUTION_12BIT,
			.AdcConversionTime = ADC_CONV_TIME_15CYCLES,
			.AdcSampleTime     = ADC_SAMPLE_TIME_28CYCLES,
			.AdcReference      = ADC_REF_VOLTAGE_5V,
			.AdcGroupPriority  = 0,
			.AdcStreamingMode  = FALSE
        }
    }
};
	Std_ReturnType status = Adc_Init(&adcConfig);
	if (status != E_OK)
	{
		Det_ReportError(MODULE_ID_ECUABSTRACTION, 0, ECUABSTRACTION_E_ADC_INIT_FAILED, 0);
		return E_NOT_OK;
	}	
	return E_OK;
}

float EcuAbstraction_GetVehicleSpeed(void)
{
	Adc_ValueGroupType adcData;
	Std_ReturnType adcStatus;

	Adc_StartGroupConversion(SPEED_SENSOR_ADC_CHANNEL);

	uint32_t startTime = Gpt_GetTimeElapsed(0);
	while (Adc_GetGroupStatus(SPEED_SENSOR_ADC_CHANNEL) != ADC_COMPLETED)
	{
		if (Gpt_GetTimeElapsed(0) - startTime > ADC_CONVERSION_TIMEOUT)
		{
			Det_ReportError(MODULE_ID_ECUABSTRACTION, 0, ECUABSTRACTION_E_ADC_TIMEOUT, 0);
			return -1.0f;
		}
	}

	adcStatus = Adc_ReadGroup(SPEED_SENSOR_ADC_CHANNEL, &adcData);
	if (adcStatus != E_OK)
	{
		Det_ReportError(MODULE_ID_ECUABSTRACTION, 0, ECUABSTRACTION_E_ADC_READ_FAILED, 0);
		return -1.0f;
	}

	float adcVoltage = adcData * (5.0f / 4095.0f); // Assuming 12-bit ADC and 5V reference
		return adcVoltage * SPEED_SENSOR_CONSTANT;
}

float EcuAbstraction_GetLatestSpeed(void)
{
	return vehicleSpeed;
}
