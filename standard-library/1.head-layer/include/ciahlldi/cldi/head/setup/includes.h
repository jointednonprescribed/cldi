
#ifndef _cldi_head__setup_INCLUDES_H
#define _cldi_head__setup_INCLUDES_H

#include "platform.h"



/* C/C++ Standard Library Includes */
#if CLDI_C_ONLY == true
#	include <stdbool.h>
#	include <stdarg.h>
#	include <stdio.h>
#	include <stdint.h>
#	include <stddef.h>
#	include <stdlib.h>
#   include <float.h>
#	include <string.h>
#	if CLDI_INCLUDE_MATH == true
#		include <math.h>
#	endif
#else
#	include <cstdbool>
#	include <cstdarg>
#	include <cstdio>
#	include <cstdint>
#	include <cstddef>
#	include <cstdlib>
#   include <cfloat>
#	include <cstring>
#	include <string>
#	include <vector>
#	include <array>
#	if CLDI_INCLUDE_MATH == true
#		include <cmath>
#		include <math>
#	endif
#	if CLDI_INCLUDE_TIME == true
#		include <chrono>
#	endif
#endif

/* System-Specific Includes */
// Unix Includes
#if CLDI_PLATFORM_UNIXLIKE == true
#	include <unistd.h>
#	include <dlfcn.h>
#	include <sys/stat.h>
#	include <sys/mman.h>
#	if CLDI_INCLUDE_TIME == true
#		include <sys/time.h>
#	endif
#endif
#if CLDI_PLATFORM == CLDI_WINDOWS
#	include <windows.h>
#	include <winnt.h>
#	include <heapapi.h>
#	include <processthreadsapi.h>
#endif



#endif // _cldi_head__setup_INCLUDES_H
