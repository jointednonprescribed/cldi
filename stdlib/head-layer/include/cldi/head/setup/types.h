
#ifndef _cldi_head__setup_TYPES_H
#define _cldi_head__setup_TYPES_H 1

#include "includes.h"



#ifdef __cplusplus
extern "C" {
#endif
/* Process ID and Group ID type */
#if CLDI_PLATFORM_UNIXLIKE == true
typedef pid_t cldipid_t;
#elif CLDI_PLATFORM == CLDI_WINDOWS
typedef DWORD cldipid_t;
#else
typedef uint32_t cldipid_t;
#endif
typedef int cldigid_t;
#define CLDI_GID_ISINVALID(gid) ((gid) < 0)
#define CLDI_GID_NULL    -1
#define CLDI_DEFAULT_GID 0

/* Ownership ID type */
typedef struct _CLDIOID
{
	cldipid_t owner;
	cldigid_t group;
} cldioid_t, cldiownerid_t;

cldipid_t cldiGetCurrentPID();
cldigid_t cldiGetCurrentGID();
cldioid_t cldiGetCurrentOID();


/* Maximum-precision floating point type: */
#if defined(LDBL_MANT_DIG) && LDBL_MANT_DIG > DBL_MANT_DIG
#   define CLDI_LDBL_ENABLED true
typedef long double cldifloatmax_t;
typedef long double cldifpm_t;
#	define CLDIFPM_MANT_DIG   LDBL_MANT_DIG
#	define CLDIFPM_DIG        LDBL_DIG
#	define CLDIFPM_MIN_EXP    LDBL_MIN_EXP
#	define CLDIFPM_MIN_10_EXP LDBL_MIN_10_EXP
#	define CLDIFPM_MAX_EXP    LDBL_MAX_EXP
#	define CLDIFPM_MAX_10_EXP LDBL_MAX_10_EXP
#	define CLDIFPM_MAX        LDBL_MAX
#	define CLDIFPM_EPSILON    LDBL_EPSILON
#	define CLDIFPM_MIN        LDBL_MIN
#else
#	define CLDI_LDBL_ENABLED false
typedef      double cldifloatmax_t;
typedef      double cldifpm_t;
#	define CLDIFPM_MANT_DIG   DBL_MANT_DIG
#	define CLDIFPM_DIG        DBL_DIG
#	define CLDIFPM_MIN_EXP    DBL_MIN_EXP
#	define CLDIFPM_MIN_10_EXP DBL_MIN_10_EXP
#	define CLDIFPM_MAX_EXP    DBL_MAX_EXP
#	define CLDIFPM_MAX_10_EXP DBL_MAX_10_EXP
#	define CLDIFPM_MAX        DBL_MAX
#	define CLDIFPM_EPSILON    DBL_EPSILON
#	define CLDIFPM_MIN        DBL_MIN
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
	size_t          size;
	CLDI_TYPE_TEMPL templ;
} clditypeinfo_t;

/* Predefined templates for different types represented as clditypeinfo_t objects. */
extern const clditypeinfo_t cldiNullTypeInfo;
extern const clditypeinfo_t cldiCharTypeInfo;
extern const clditypeinfo_t cldiWCharTypeInfo;
extern const clditypeinfo_t cldiShortTypeInfo;
extern const clditypeinfo_t cldiIntTypeInfo;
extern const clditypeinfo_t cldiLongTypeInfo;
extern const clditypeinfo_t cldiLLongTypeInfo;
extern const clditypeinfo_t cldiSizeTypeInfo;
extern const clditypeinfo_t cldiFloatTypeInfo;
extern const clditypeinfo_t cldiDoubleTypeInfo;
extern const clditypeinfo_t cldiFPMTypeInfo;
// Only if long double is enabled, create template for long double.
#if CLDI_LDBL_ENABLED == true
	extern const clditypeinfo_t cldiLDoubleTypeInfo;
#endif
extern const clditypeinfo_t cldiPtrTypeInfo;

// if C++ is loaded, the extern "C" block from before cldipid_t must end now.
#ifdef __cplusplus
}
#endif


/* C++ bindings for this file: */
#include "icxx/types.hpp"



#endif // _cldi_head__setup_TYPES_H
