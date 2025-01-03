
#ifndef _cldi_head__setup_platform_LINUX_H
#define _cldi_head__setup_platform_LINUX_H 1

#include "../prerequisites.h"

/* Requires structure: cldi-head: setup/platform/platform */
#include "platform_ENUM.h"


/* Linux Platform Settings */
/* Check if platform is linux-based or linux... */
#ifdef __ANDROID__
#	include "android.h"  /* Android platform */
#else
#	define __CLDI_PLATFORM          CLDI_PLATFORM_LINUX /* Else, another linux-based platform... */
/* Is a Unix-based Platform */
#	define __CLDI_PLATFORM_UNIXLIKE true
/* Not a BSD Platform */
#	define _cldi_BSD_PLATFORM false
/* GNU/Linux uses GNU C Library. */
#	include <limits.h>
#	if defined(__gnu_linux__) || \
	(defined(__GNU_LIBRARY__) && defined(__GNU_LIBRARY_MINOR)) || \
	(defined(__GLIBC__) && defined(__GLIBC_MINOR__))
#		define _cldi_USING_GLIBC   true
#	else
#		define _cldi_USING_GLIBC   false
#	endif
/* Detect architecture width. */
#	if _WORDSIZE == 64
#		define __CLDI_ARCHSIZE      CLDI_PLATFORM_64BIT /* 64-bit system */
#	elif _WORDSIZE == 32
#		define __CLDI_ARCHSIZE      CLDI_PLATFORM_32BIT /* 32-bit system */
#	else
#		pragma warn("CLDI: head:setup/platform: Unsupported value for unix macro '_WORDSIZE', setting `__CLDI_ARCHSIZE` based on the data model.")
#       include "data-model.h"
#       if __CLDI_CPUDM < CLDI_CPUDM_LP64
#           define __CLDI_ARCHSIZE  CLDI_PLATFORM_32BIT
#       else
#           define __CLDI_ARCHSIZE  CLDI_PLATFORM_64BIT
#       endif
#	endif
#endif


#endif /* _cldi_head__setup_platform_LINUX_H */
