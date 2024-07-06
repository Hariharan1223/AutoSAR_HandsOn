/**
 * @file memory.h
 * @brief Header file for EEPROM driver
 */

#ifndef MEMORY_H
#define MEMORY_H

#include "Std_Types.h"

#define MEMIF_UNINIT 0x00
#define MEMIF_IDLE 0x01
#define MEMIF_BUSY 0x02
#define MEMIF_JOB_OK 0x03

typedef uint8 MemIf_StatusType;
typedef uint8 MemIf_JobResultType;
typedef uint32 Eep_AddressType;
typedef uint32 Eep_LengthType;

void Eep_Init(void);
Std_ReturnType Eep_Read(Eep_AddressType Address, uint8* DataBufferPtr, Eep_LengthType Length);
Std_ReturnType Eep_Write(Eep_AddressType Address, const uint8* DataBufferPtr, Eep_LengthType Length);

#endif /* MEMORY_H */
