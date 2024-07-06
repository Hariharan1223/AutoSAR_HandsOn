/**
 * @file memory.c
 * @brief EEPROM driver implementation
 */

#include "memory.h"
#include "Det.h"
#include <string.h>

#define EEP_MODULE_ID       0x20
#define EEP_INSTANCE_ID     0x00
#define EEP_E_UNINIT        0x01
#define EEP_E_PARAM_ADDRESS 0x02
#define EEP_E_PARAM_POINTER 0x03

#define EEP_SIZE            1024  // Assuming 1KB EEPROM size

/* Simulated EEPROM memory */
static uint8 EepRom[EEP_SIZE];

/* Internal state */
static MemIf_StatusType EepStatus = MEMIF_UNINIT;

/* Internal function prototype */
static boolean Eep_ValidateAddress(Eep_AddressType Address, Eep_LengthType Length);

/* Report error function */
static void Eep_ReportError(uint16 moduleId, uint8 instanceId, uint8 apiId, uint8 errorId)
{
	Det_ReportError(moduleId, instanceId, apiId, errorId);
}

void Eep_Init(void)
{
	EepStatus = MEMIF_IDLE;
	memset(EepRom, 0xFF, EEP_SIZE);  // Initialize EEPROM to erased state
}

Std_ReturnType Eep_Read(Eep_AddressType Address, uint8* DataBufferPtr, Eep_LengthType Length)
{
	if (EepStatus == MEMIF_UNINIT)
	{
		Eep_ReportError(EEP_MODULE_ID, EEP_INSTANCE_ID, 0x02, EEP_E_UNINIT);
		return E_NOT_OK;
	}
	if (DataBufferPtr == NULL)
	{
		Eep_ReportError(EEP_MODULE_ID, EEP_INSTANCE_ID, 0x02, EEP_E_PARAM_POINTER);
		return E_NOT_OK;
	}
	if (!Eep_ValidateAddress(Address, Length))
	{
		Eep_ReportError(EEP_MODULE_ID, EEP_INSTANCE_ID, 0x02, EEP_E_PARAM_ADDRESS);
		return E_NOT_OK;
	}	
	
	memcpy(DataBufferPtr, &EepRom[Address], Length);
	return E_OK;
}

Std_ReturnType Eep_Write(Eep_AddressType Address, const uint8* DataBufferPtr, Eep_LengthType Length)
{
	if (EepStatus == MEMIF_UNINIT)
	{
		Eep_ReportError(EEP_MODULE_ID, EEP_INSTANCE_ID, 0x03, EEP_E_UNINIT);
		return E_NOT_OK;
	}
	if (DataBufferPtr == NULL)
	{
		Eep_ReportError(EEP_MODULE_ID, EEP_INSTANCE_ID, 0x03, EEP_E_PARAM_POINTER);
		return E_NOT_OK;
	}
	if (!Eep_ValidateAddress(Address, Length))
	{
		Eep_ReportError(EEP_MODULE_ID, EEP_INSTANCE_ID, 0x03, EEP_E_PARAM_ADDRESS);
		return E_NOT_OK;
	}

	memcpy(&EepRom[Address], DataBufferPtr, Length);
	return E_OK;
}

static boolean Eep_ValidateAddress(Eep_AddressType Address, Eep_LengthType Length)
{
	return (Address < EEP_SIZE) && ((Address + Length) <= EEP_SIZE);
}
