/**
 * @file EcuAbstraction.c
 * @brief ECU Abstraction Software Component implementation
 */









/**
 * @file EcuAbstraction.c
 * @brief ECU Abstraction Software Component implementation
 */

#include "EcuAbstraction.h"
#include "Dio.h"
#include "Gpt.h"
#include "Adc.h" // Include ADC driver
#include "NvBlock.h" // Assuming NVBlock SWC is used for storing maximum speed
#include "Det.h" // For AUTOSAR Development Error Tracer

/* Definitions */
#define SPEED_SENSOR_PORT       GPIO_PORT_A
#define SPEED_SENSOR_PIN        GPIO_PIN_0
#define SPEED_SENSOR_TIMER      GPT_TIMER_1
#define GPT_TIMER_RESOLUTION    1000000.0f // Timer resolution in microseconds
#define SPEED_SENSOR_CONSTANT   0.621371  // Speed sensor constant for km/h conversion

/**
 * @brief Initializes the ECU Abstraction SWC
 * @return E_OK if initialization is successful, E_NOT_OK otherwise
 */
Std_ReturnType EcuAbstraction_Init(void)
{
    Std_ReturnType retVal = E_OK;

    /* Initialize DIO driver for speed sensor pin */
    Dio_ConfigType dioConfig = {
        .portId = SPEED_SENSOR_PORT,
        .pinId = SPEED_SENSOR_PIN,
        .mode = GPIO_MODE_INPUT_PULLUP, // Assuming the sensor signal is active-low
        .level = GPIO_HIGH // Set initial level to HIGH (pull-up enabled)
    };

    if (Dio_Init(&dioConfig) != E_OK)
    {
        retVal = E_NOT_OK;
        Det_ReportError(MODULE_ID_ECUABSTRACTION, 0, ECUABSTRACTION_INIT_ID, ECUABSTRACTION_E_DIO_INIT_FAILED);
    }

    /* Initialize GPT driver for speed sensor timer */
    if (Gpt_Init(NULL) != E_OK) // Assuming no specific configuration required for the GPT
    {
        retVal = E_NOT_OK;
        Det_ReportError(MODULE_ID_ECUABSTRACTION, 0, ECUABSTRACTION_INIT_ID, ECUABSTRACTION_E_GPT_INIT_FAILED);
    }

    /* Initialize ADC driver */
    if (Adc_Init(NULL) != E_OK) // Assuming no specific configuration required for the ADC
    {
        retVal = E_NOT_OK;
        Det_ReportError(MODULE_ID_ECUABSTRACTION, 0, ECUABSTRACTION_INIT_ID, ECUABSTRACTION_E_ADC_INIT_FAILED);
    }

    return retVal;
}

/**
 * @brief Reads the vehicle speed from the digital Hall-effect speed sensor
 * @return Vehicle speed in kilometers per hour (km/h), or -1.0f if an error occurs
 */
float EcuAbstraction_GetVehicleSpeed(void)
{
    /* Perform ADC conversion to read analog value from the speed sensor */
    Adc_StartGroupConversion(SPEED_SENSOR_ADC_GROUP);

    /* Wait for ADC conversion completion */
    while (Adc_GetGroupStatus(SPEED_SENSOR_ADC_GROUP) != ADC_COMPLETED)
    {
        /* Wait for ADC conversion to complete */
    }

    /* Read ADC group data */
    Adc_ValueGroupType adcData;
    if (Adc_ReadGroup(SPEED_SENSOR_ADC_GROUP, &adcData) != E_OK)
    {
        Det_ReportError(MODULE_ID_ECUABSTRACTION, 0, ECUABSTRACTION_GETVELOCITY_ID, ECUABSTRACTION_E_ADC_READ_FAILED);
        return -1.0f;
    }

    /* Convert ADC value to vehicle speed */
    float vehicleSpeed = adcData * SPEED_SENSOR_CONSTANT;

    return vehicleSpeed;
}

/**
 * @brief Reports the maximum speed reached during the driving cycle
 * @return Maximum speed in kilometers per hour (km/h), or -1.0f if an error occurs
 */
float EcuAbstraction_GetMaximumSpeed(void)
{
    float maxSpeed = -1.0f;

    /* Check if the NVBlock SWC is available */
    if (NvBlock_IsAvailable())
    {
        /* Retrieve the maximum speed from the NVBlock SWC */
        if (NvBlock_ReadMaximumSpeed(&maxSpeed) == E_OK)
        {
            return maxSpeed;
        }
        else
        {
            Det_ReportError(MODULE_ID_ECUABSTRACTION, 0, ECUABSTRACTION_GETMAXSPEED_ID, ECUABSTRACTION_E_NVBLOCK_READ_FAILED);
            return -1.0f;
        }
    }
    else
    {
        Det_ReportError(MODULE_ID_ECUABSTRACTION, 0, ECUABSTRACTION_GETMAXSPEED_ID, ECUABSTRACTION_E_NVBLOCK_NOT_AVAILABLE);
        return -1.0f;
    }
}

/**
 * @brief Handles the diagnostic events related to the ECU Abstraction SWC
 * @param diagnosticEvent The diagnostic event to be handled
 */
void EcuAbstraction_HandleDiagnosticEvent(DiagnosticEventType diagnosticEvent)
{
    switch (diagnosticEvent)
    {
        case DIAGNOSTIC_EVENT_SPEED_SENSOR_FAULT:
            /* Log the speed sensor fault event */
            Diagnostic_LogEvent(DIAGNOSTIC_EVENT_SPEED_SENSOR_FAULT);
            break;

        case DIAGNOSTIC_EVENT_SPEED_SENSOR_RECOVERY:
            /* Log the speed sensor recovery event */
            Diagnostic_LogEvent(DIAGNOSTIC_EVENT_SPEED_SENSOR_RECOVERY);
            break;

        case DIAGNOSTIC_EVENT_MAX_SPEED_EXCEEDED:
            /* Log the maximum speed exceeded event */
            Diagnostic_LogEvent(DIAGNOSTIC_EVENT_MAX_SPEED_EXCEEDED);
            break;

        default:
            /* Unknown or unsupported diagnostic event */
            Det_ReportError(MODULE_ID_ECUABSTRACTION, 0, ECUABSTRACTION_HANDLEDIAGEVENT_ID, ECUABSTRACTION_E_UNKNOWN_DIAG_EVENT);
            break;
    }
}
