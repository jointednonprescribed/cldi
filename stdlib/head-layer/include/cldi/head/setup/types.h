
#ifndef _cldi_head__setup_TYPES_H
#define _cldi_head__setup_TYPES_H 1

#include "includes.h"



#ifdef __cplusplus
extern "C" {
#endif
/* Process ID type */
#if CLDI_PLATFORM_UNIXLIKE == true
typedef pid_t cldipid_t;
#elif CLDI_PLATFORM == CLDI_WINDOWS
typedef DWORD cldipid_t;
#else
typedef uint32_t cldipid_t;
#endif

cldipid_t cldiGetCurrentPID();


/* Maximum-precision floating point type: */
#if defined(LDBL_MANT_DIG) && LDBL_MANT_DIG > DBL_MANT_DIG
#   define CLDI_LDBL_ENABLED true
typedef long double cldifloatmax_t;
typedef long double cldifpm_t;
#else
#	define CLDI_LDBL_ENABLED false
typedef      double cldifloatmax_t;
typedef      double cldifpm_t;
#endif


/* Type Template enum (types of types) */
typedef enum _CLDITYPETEMPL
{
	CLDI_NULL_TYPE = 0,
	
	CLDI_INTEGER_TYPE,
	CLDI_INT_TYPE = CLDI_INTEGER_TYPE,
	
	CLDI_FLOAT_TYPE,

	CLDI_PTR_TYPE,

	CLDI_STRUCT_TYPE,
} CLDI_TYPE_TEMPL, CLDI_TYPE_TEMPLATE;
/* Type Info Record type */
typedef struct _CLDITYPEINFO
{
	const size_t          size;
	const CLDI_TYPE_TEMPL templ;

} clditypeinfo_t;

/* Predefined templates for different types represented as clditypeinfo_t objects. */
extern const clditypeinfo_t cldiTypeInfoNull;
extern const clditypeinfo_t cldiTypeInfoChar;
extern const clditypeinfo_t cldiTypeInfoWChar;
extern const clditypeinfo_t cldiTypeInfoShort;
extern const clditypeinfo_t cldiTypeInfoInt;
extern const clditypeinfo_t cldiTypeInfoLong;
extern const clditypeinfo_t cldiTypeInfoLLong;
extern const clditypeinfo_t cldiTypeInfoSize_t;
extern const clditypeinfo_t cldiTypeInfoFloat;
extern const clditypeinfo_t cldiTypeInfoDouble;
extern const clditypeinfo_t cldiTypeInfoFPM;
// Only if long double is enabled, create template for long double.
#if CLDI_LDBL_ENABLED == true
	extern const clditypeinfo_t cldiTypeInfoLDouble;
#endif
extern const clditypeinfo_t cldiTypeInfoPtr;

// if C++ is loaded, the extern "C" block from before cldipid_t must end now.
#ifdef __cplusplus
}
#endif


/* C++ bindings for this file: */
#include "icxx/types.hpp"



#endif // _cldi_head__setup_TYPES_H
