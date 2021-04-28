/****************************************************/
 /* Author      : Mosad                             */
 /* Version     : v01                               */
 /* date        : 4/3/2021                          */
/****************************************************/

#ifndef COMPILER_H
#define COMPILER_H 

/* Published information */
#define    COMPILER_MODULE_ID                     0x033u
#define    COMPILER_VENDOR_ID                     0x000u

#define    COMPILER_AR_RELEASE_MAJOR_VERSION      0x01u
#define    COMPILER_AR_RELEASE_MINOR_VERSION      0x00u
#define    COMPILER_AR_RELEASE_REVISION_VERSION   0x00u

#define    COMPILER_SW_MAJOR_VERSION              0x04u
#define    COMPILER_SW_MINOR_VERSION              0x04u
#define    COMPILER_SW_PATCH_VERSION              0x00u

#define   AUTOMATIC   /* To be used for local non static variables */
#define   TYPEDEF     /* used in type definitions, where no To be memory qualifier can be specified */

#define   NULL_PTR      ((void *) 0)
#define   INLINE        inline 
#define   LOCAL_INLINE  static inline


/* 8.2.2.1 FUNC identification */ 
#define   FUNC(rettype, memclass)                      memclass rettype
#define   FUNC_P2CONST(rettype, ptrclass, memclass)    const ptrclass rettype * memclass
#define   FUNC_P2VAR(rettype, ptrclass, memclass)      ptrclass rettype * memclass

/* 8.2.3.1 Pointer definitions */ 
#define   P2VAR(ptrtype, memclass, ptrclass)           ptrclass ptrtype * memclass
#define   P2CONST(ptrtype, memclass, ptrclass)         const ptrtype memclass * ptrclass
#define   CONSTP2VAR (ptrtype, memclass, ptrclass)     ptrclass ptrtype * const memclass
#define   CONSTP2CONST (ptrtype, memclass, ptrclass)   const memclass ptrtype * const ptrclass
#define   P2FUNC(rettype, ptrclass, fctname)           rettype (*ptrclass fctname)
#define   CONSTP2FUNC(rettype, ptrclass, fctname)      rettype (* const fctname)

/* 8.2.4 Constant definitions */
#define   CONST(type, memclass)                        memclass const type

/* 8.2.5 Variable definitions */
#define   VAR(type, memclass)                          memclass type




#endif