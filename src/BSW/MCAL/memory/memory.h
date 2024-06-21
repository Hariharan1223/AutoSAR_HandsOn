/* memory.h */
#ifndef MEMORY_H
#define MEMORY_H

#include "Std_Types.h" // Include the standard types header file

/* Memory instance ID */
typedef uint8_t Mem_InstanceIdType;

/* Memory address type */
typedef uint32_t Mem_AddressType;

/* Memory data type */
typedef uint8_t Mem_DataType;

/* Memory length type */
typedef uint16_t Mem_LengthType;

/* Return type for memory operations */
typedef uint8_t Std_ReturnType;

/* Error codes for memory operations */
#define MEM_E_OK               0x00
#define MEM_E_WRITE_FAILED     0x01
#define MEM_E_READ_FAILED      0x02
#define MEM_E_NULL_POINTER     0x03 // New error code for null pointer

/* Function prototypes */
Std_ReturnType Mem_Read(Mem_InstanceIdType instanceId, Mem_AddressType sourceAddress, Mem_DataType* destinationDataPtr, Mem_LengthType length);
Std_ReturnType Mem_Write(Mem_InstanceIdType instanceId, Mem_AddressType targetAddress, const Mem_DataType* sourceDataPtr, Mem_LengthType length);

#endif /* MEMORY_H */
