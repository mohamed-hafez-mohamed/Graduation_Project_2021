/****************************************************/
 /* Author      : Mosad                             */
 /* Version     : v01                               */
 /* date        : 4/3/2021                          */
/****************************************************/

#ifndef STD_TYPES_H
#define STD_TYPES_H 

/* Published information */
#define    PLATFORM_MODULE_ID                     0x030u
#define    PLATFORM_VENDOR_ID                     0x000u

#define    PLATFORM_AR_RELEASE_MAJOR_VERSION      0x01u
#define    PLATFORM_AR_RELEASE_MINOR_VERSION      0x00u
#define    PLATFORM_AR_RELEASE_REVISION_VERSION   0x00u

#define    PLATFORM_SW_MAJOR_VERSION              0x04u
#define    PLATFORM_SW_MINOR_VERSION              0x04u
#define    PLATFORM_SW_PATCH_VERSION              0x00u


/* 8.2 Type definitions */

#ifndef TRUE 
#define TRUE 	0x1u
#endif 

#ifndef FALSE 
#define FALSE 	0x0u
#endif

typedef     unsigned char 		boolean;
typedef     signed char 		sint8;
typedef     unsigned char 		uint8;
typedef     signed short 		sint16;
typedef     unsigned short 		uint16;
typedef     signed long 		sint32;
typedef     unsigned long 		uint32;
typedef     signed long long 	sint64;
typedef     unsigned long long 	uint64;
typedef     unsigned char 		uint8_least;
typedef     unsigned short 		uint16_least;
typedef     unsigned long 		uint32_least;
typedef     signed char 		sint8_least;
typedef     signed short 		sint16_least;
typedef     signed long 		sint32_least;
typedef     float 				float32;
typedef     double 				float64;


/* Symbols */ 
#define CPU_TYPE_8 		8
#define CPU_TYPE_16 	16
#define CPU_TYPE_32 	32
#define CPU_TYPE_64 	64

#define MSB_FIRST 		0
#define LSB_FIRST 		1

#define HIGH_BYTE_FIRST 0
#define LOW_BYTE_FIRST 	1

#define CPU_TYPE			CPU_TYPE_32
#define CPU_BIT_ORDER		LSB_FIRST
#define CPU_BYTE_ORDER 		LOW_BYTE_FIRST




#endif STD_TYPES_H
