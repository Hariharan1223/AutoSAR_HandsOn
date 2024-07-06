/**
 * @file Ea.c
 * @brief EEPROM Abstraction implementation
 */

#include "Ea.h"
#include "memory.h"
#include "Det.h"

#define EA_MODULE_ID           0x21
#define EA_INSTANCE_ID         0x00
#define EA_E_PARAM_POINTER     0x01
#define EA_E_PARAM_LENGTH      0x02
#define EA_E_PARAM_BLOCK_NUM   0x03

static MemIf_StatusType Ea_Status = MEMIF_UNINIT;

void Ea_Init(void) {
	Eep_Init();
	Ea_Status = MEMIF_IDLE;
}

Std_ReturnType Ea_SetMode(MemIf_ModeType Mode) {
	return Eep_SetMode(Mode);
}

Std_ReturnType Ea_Read(uint16 BlockNumber, uint16 BlockOffset, uint8* DataBufferPtr, uint16 Length) {
	if (DataBufferPtr == NULL) {
		Det_ReportError(EA_MODULE_ID, EA_INSTANCE_ID, 0x02, EA_E_PARAM_POINTER);
		return E_NOT_OK;
	}
	return Eep_Read(BlockNumber, BlockOffset, DataBufferPtr, Length);
}

Std_ReturnType Ea_Write(uint16 BlockNumber, const uint8* DataBufferPtr) {
	if (DataBufferPtr == NULL) {
		Det_ReportError(EA_MODULE_ID, EA_INSTANCE_ID, 0x03, EA_E_PARAM_POINTER);
		return E_NOT_OK;
	}
	return Eep_Write(BlockNumber, DataBufferPtr);
}

