
#ifndef _cldi_head__setup_TYPES_H
#define _cldi_head__setup_TYPES_H 1

#include "includes.h"



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
#else
#   define CLDI_LDBL_ENABLED false
typedef double cldifloatmax_t;
#endif



#endif // _cldi_head__setup_TYPES_H
