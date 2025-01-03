
#ifndef _cldi__setup_standard_includes_PLATFORM_APIS_H
#define _cldi__setup_standard_includes_PLATFORM_APIS_H 1

#include "../prerequisites.h"
#include "../platform.h"


/* Platform-specific Headers */

/* Unix-specific Headers */
#if __CLDI_PLATFORM_UNIX_BASED > false
#	include <unistd.h>        /* Unix System Standard C Library */
#	include <sys/types.h>     /* Unix System Types */
#	include <sys/stat.h>      /* Unix System Element Status */
#	include <sys/io.h>        /* Unix System IO */
#	include <sys/signal.h>    /* Unix System Signals */
#	include <sys/mman.h>      /* For Memory Management */
#	include <sys/time.h>      /* For Time-keeping */
#	include <sys/termios.h>   /* For Terminal Interaction */
#	include <pthread.h>       /* For Posix Thread Support */
#	if __CLDI_PLATFORM == CLDI_PLATFORM_ANDROID
#		include <api-devel.h>
#	endif
/* Windows-specific Headers */
#elif __CLDI_PLATFORM == CLDI_PLATFORM_WINDOWS
#	include <windows.h>           /* Win32 API */
#	include <winnt.h>
#	include <fileapi.h>           /* For Filesystem Interaction */
#	include <heapapi.h>           /* For Memory Interaction and File-Mapping. */
#	include <processthreadsapi.h> /* For Thread and Process Control. */
#endif


#endif /* _cldi__setup_standard_includes_PLATFORM_APIS_H */
