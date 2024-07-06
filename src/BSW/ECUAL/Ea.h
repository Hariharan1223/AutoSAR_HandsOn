/**
 * @file Ea.h
 * @brief EEPROM Abstraction header file
 */

#ifndef EA_H
#define EA_H

#include "Std_Types.h"
#include "MemIf_Types.h"

void Ea_Init(void);
Std_ReturnType Ea_SetMode(MemIf_ModeType Mode);
Std_ReturnType Ea_Read(uint16 BlockNumber, uint16 BlockOffset, uint8* DataBufferPtr, uint16 Length);
Std_ReturnType Ea_Write(uint16 BlockNumber, const uint8* DataBufferPtr);

#endif /* EA_H */
