
#ifndef _cldi_head__setup_platform_STDLIB_H
#define _cldi_head__setup_platform_STDLIB_H 1

#include "../prerequisites.h"

/* Requires structure: cldi-head: setup/platform/platform */
#include "platform_ENUM.h"


/* Settings for Using the C Library on Unknown Platforms */
#define __CLDI_PLATFORM             CLDI_PLATFORM_UNKNOWN
/* Check if Using the GNU C Library */
#include <limits.h>
#if (defined(__GNU_LIBRARY__) && defined(__GNU_LIBRARY_MINOR)) || \
	(defined(__GLIBC__) && defined(__GLIBC_MINOR__))
#	define _cldi_USING_GLIBC       true
#else
#	define _cldi_USING_GLIBC       false
#endif
/* Check if a Unix-like Platform */
#if defined(__CLDI_PLATFORM_UNIXLIKE) && __CLDI_PLATFORM_UNIXLIKE > 0
#	define __CLDI_PLATFORM_UNIXLIKE true
#else
#	define __CLDI_PLATFORM_UNIXLIKE false
#endif
/* Check if a BSD Platform */
#if defined(_cldi_BSD_PLATFORM) && _cldi_BSD_PLATFORM > 0
#	define _cldi_BSD_PLATFORM      true
#else
#	define _cldi_BSD_PLATFORM      false
#endif

/* Detect architecture width based on data model. */
#pragma warn("CLDI: head/setup: Detecting architecture width by data model...")
#include "data-model.h"
#if __CLDI_CPUDM < CLDI_CPUDM_LP64
#   define __CLDI_ARCHSIZE       CLDI_PLATFORM_32BIT
#else
#   define __CLDI_ARCHSIZE       CLDI_PLATFORM_64BIT
#endif


#endif /* _cldi_head__setup_platform_STDLIB_H */
