/**
 * @file ecuabstraction_sws.h
 * @brief Header file for ECU Abstraction Software Component
 */

#ifndef ECUABSTRACTION_SWS_H
#define ECUABSTRACTION_SWS_H

#include "Std_Types.h"

/* Error Codes */
#define ECUABSTRACTION_E_DIO_INIT_FAILED         0x01
#define ECUABSTRACTION_E_GPT_INIT_FAILED         0x02
#define ECUABSTRACTION_E_TIMER_FAILED            0x03
#define ECUABSTRACTION_E_UNKNOWN_DIAG_EVENT      0x04
#define ECUABSTRACTION_E_NVBLOCK_READ_FAILED     0x05
#define ECUABSTRACTION_E_NVBLOCK_NOT_AVAILABLE  0x06

/* Function IDs */
#define ECUABSTRACTION_INIT_ID                   0x01
#define ECUABSTRACTION_GETVELOCITY_ID            0x02
#define ECUABSTRACTION_GETMAXSPEED_ID            0x03
#define ECUABSTRACTION_HANDLEDIAGEVENT_ID        0x04

/* Function prototypes */
Std_ReturnType EcuAbstraction_Init(void);
float EcuAbstraction_GetVehicleSpeed(void);
float EcuAbstraction_GetMaximumSpeed(void);
void EcuAbstraction_HandleDiagnosticEvent(DiagnosticEventType diagnosticEvent);

#endif /* ECUABSTRACTION_SWS_H */
