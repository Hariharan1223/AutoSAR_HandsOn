/* memory.c */
#include "memory.h"

/* Define the memory storage area */
uint8_t memoryStorage[MEMORY_SIZE];

/* Function to read data from memory */
Std_ReturnType Mem_Read(Mem_InstanceIdType instanceId, Mem_AddressType sourceAddress, Mem_DataType* destinationDataPtr, Mem_LengthType length)
{
    /* Check for null pointer */
    if (destinationDataPtr == NULL) {
        return MEM_E_NULL_POINTER; // Return error for null pointer
    }

    /* Check if the sourceAddress is within the valid memory range */
    if (sourceAddress + length > MEMORY_SIZE) {
        return MEM_E_READ_FAILED; // Return error if reading beyond memory boundary
    }

    /* Copy data from memory storage to the destinationDataPtr */
    for (Mem_LengthType i = 0; i < length; i++) {
        destinationDataPtr[i] = memoryStorage[sourceAddress + i];
    }

    return MEM_E_OK; // Return success
}

/* Function to write data to memory */
Std_ReturnType Mem_Write(Mem_InstanceIdType instanceId, Mem_AddressType targetAddress, const Mem_DataType* sourceDataPtr, Mem_LengthType length)
{
    /* Check for null pointer */
    if (sourceDataPtr == NULL) {
        return MEM_E_NULL_POINTER; // Return error for null pointer
    }

    /* Check if the targetAddress is within the valid memory range */
    if (targetAddress + length > MEMORY_SIZE) {
        return MEM_E_WRITE_FAILED; // Return error if writing beyond memory boundary
    }

    /* Copy data from sourceDataPtr to the memory storage */
    for (Mem_LengthType i = 0; i < length; i++) {
        memoryStorage[targetAddress + i] = sourceDataPtr[i];
    }

    return MEM_E_OK; // Return success
}

