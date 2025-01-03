
#ifndef _cldi_head__setup_platform_UNIX_H
#define _cldi_head__setup_platform_UNIX_H 1

#include "../prerequisites.h"

/* Requires structure: cldi-head: setup/platform/platform */
#include "platform_ENUM.h"


/* Settings for Using the C Library on Unknown Platforms */
#define __CLDI_PLATFORM          CLDI_PLATFORM_UNKNOWN
/* Check if Using the GNU C Library */
#include <limits.h>
#if (defined(__GNU_LIBRARY__) && defined(__GNU_LIBRARY_MINOR)) || \
	(defined(__GLIBC__) && defined(__GLIBC_MINOR__))
#	define _cldi_USING_GLIBC    true
#else
#	define _cldi_USING_GLIBC    false
#endif
/* Not a Unix-like Platform */
#define __CLDI_PLATFORM_UNIXLIKE true
/* Not a BSD Platform, unless specified otherwise... */
#if defined(_cldi_BSD_PLATFORM) && _cldi_BSD_PLATFORM > 0
#	define _cldi_BSD_PLATFORM   true
#else
#	define _cldi_BSD_PLATFORM   false
#endif

/* Detect architecture width based on data model. */
#ifndef _WORDSIZE
#	pragma warn("CLDI: head/setup: Unix macro `_WORDSIZE` is not defined, detecting architecture width by data model...")
#	include "data-model.h"
#	if __CLDI_CPUDM < CLDI_CPUDM_LP64
#		define __CLDI_ARCHSIZE      CLDI_PLATFORM_32BIT
#	else
#		define __CLDI_ARCHSIZE      CLDI_PLATFORM_64BIT
#	endif
#elif _WORDSIZE == 32
#	define __CLDI_ARCHSIZE          CLDI_PLATFORM_32BIT
#elif _WORDSIZE == 64
#	define __CLDI_ARCHSIZE          CLDI_PLATFORM_64BIT
#else
#	pragma warn("CLDI: head/setup: Unix macro `_WORDSIZE` is not set properly, detecting architecture width by data model...")
#	include "data-model.h"
#	if __CLDI_CPUDM < CLDI_CPUDM_LP64
#		define __CLDI_ARCHSIZE      CLDI_PLATFORM_32BIT
#	else
#		define __CLDI_ARCHSIZE      CLDI_PLATFORM_64BIT
#	endif
#endif


#endif /* _cldi_head__setup_platform_UNIX_H */
