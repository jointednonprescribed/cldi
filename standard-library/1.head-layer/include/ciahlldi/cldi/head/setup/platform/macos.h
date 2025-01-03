
#ifndef _cldi_head__setup_platform_MACOS_H
#define _cldi_head__setup_platform_MACOS_H 1

#include "../prerequisites.h"

/* Requires structure: cldi-head: setup/platform/platform */
#include "platform_ENUM.h"


/* MacOS Platform Settings */
#define __CLDI_PLATFORM          CLDI_PLATFORM_MAC
/* Not Using the GNU C Library */
#define _cldi_USING_GLIBC       false
/* Not a BSD Platform */
#define _cldi_BSD_PLATFORM      false
/* Is a Unix-based Platform */
#define __CLDI_PLATFORM_UNIXLIKE true
/* Detect architecture width. */
#if _WORDSIZE == 64
#	define __CLDI_ARCHSIZE       CLDI_PLATFORM_64BIT /* 64-bit system */
#elif _WORDSIZE == 32
#	define __CLDI_ARCHSIZE       CLDI_PLATFORM_32BIT /* 32-bit system */
#else
#	pragma warn("CLDI: head:setup/platform: Unsupported value for unix macro '_WORDSIZE', setting `__CLDI_ARCHSIZE` based on the data model.")
#   include "data-model.h"
#   if __CLDI_CPUDM < CLDI_CPUDM_LP64
#       define __CLDI_ARCHSIZE   CLDI_PLATFORM_32BIT
#   else
#       define __CLDI_ARCHSIZE   CLDI_PLATFORM_64BIT
#   endif
#endif


#endif /* _cldi_head__setup_platform_MACOS_H */
