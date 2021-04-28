/****************************************************/
 /* Author      : Mosad                             */
 /* Version     : v01                               */
 /* date        : 4/3/2021                          */
/****************************************************/

#ifndef STD_TYPES_H
#define STD_TYPES_H 

/* Includes */
#include "Compiler.h"
#include "Platform_Types.h"

/* Published information */
#define    COMPILER_MODULE_ID                     0x031u
#define    COMPILER_VENDOR_ID                     0x000u

#define    COMPILER_AR_RELEASE_MAJOR_VERSION      0x01u
#define    COMPILER_AR_RELEASE_MINOR_VERSION      0x00u
#define    COMPILER_AR_RELEASE_REVISION_VERSION   0x00u

#define    COMPILER_SW_MAJOR_VERSION              0x04u
#define    COMPILER_SW_MINOR_VERSION              0x04u
#define    COMPILER_SW_PATCH_VERSION              0x00u

/* 8.2 Symbol definitions */

#ifndef STATUSTYPEDEFINED
	#define STATUSTYPEDEFINED
	#define E_OK 0x00u
	typedef unsigned char StatusType; /* OSEK compliance */
#endif
#define E_NOT_OK 0x01u

#define STD_HIGH 0x01u   /* Physical state 5V or 3.3V */
#define STD_LOW  0x00u   /* Physical state 0V */

#define STD_ACTIVE 0x01u /* Logical state active */
#define STD_IDLE   0x00u /* Logical state idle */

#define STD_ON  0x01u
#define STD_OFF 0x00u

/* Std_TransformerClass range */
#define STD_TRANSFORMER_UNSPECIFIED      0x00  //Transformer of a unspecified transformer class.
#define STD_TRANSFORMER_SERIALIZER       0x01  //Transformer of a serializer class.
#define STD_TRANSFORMER_SAFETY           0x02  //Transformer of a safety class.
#define STD_TRANSFORMER_SECURITY         0x03  //Transformer of a security class.
#define STD_TRANSFORMER_CUSTOM           0xFF  //Transformer of a custom class not standardized by AUTOSAR

/* 8.1 Type definitions */

typedef     uint8        Std_ReturnType;
typedef     uint8        Std_TransformerClass;

/* This type shall be used to request the version of a BSW module using the
 <Modulename>_GetVersionInfo() */
 
typedef struct {
	uint16      vendorID ;
	uint16      moduleID;
	uint8       sw_major_version;
	uint8       sw_minor_version;
	uint8       sw_patch_version;
}Std_VersionInfoType;

/* The data type Std_TransformerError is a struct which contains the error code and the
transformer class to which the error belongs */
typedef struct {
	uint8            errorCode ;
	Std_TransformerClass transformerClass ;
}Std_TransformerError;



#endif STD_TYPES_H


