
#ifndef _cldi_head__setup_platform_WINDOWS_H
#define _cldi_head__setup_platform_WINDOWS_H 1

#include "../prerequisites.h"

/* Requires structure: cldi-head: setup/platform/platform */
#include "platform_ENUM.h"


/* Windows Platform Settings */
#define __CLDI_PLATFORM          CLDI_PLATFORM_WINDOWS
/* Is Using the GNU C Library */
#define _cldi_USING_GLIBC       false
/* Not a BSD Platform */
#define _cldi_BSD_PLATFORM      false
/* Not a Unix-based Platform */
#define __CLDI_PLATFORM_UNIXLIKE false
/* Detect architecture width. */
#ifdef _WIN64
#	define __CLDI_ARCHSIZE       CLDI_PLATFORM_64BIT /* 64-bit system */
#else
#	define __CLDI_ARCHSIZE       CLDI_PLATFORM_32BIT /* 32-bit system */
#endif


#endif /* _cldi_head__setup_platform_WINDOWS_H */
