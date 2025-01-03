
#ifndef _cldi_portable__handles_MEM_H
#define _cldi_portable__handles_MEM_H 1

/* Setup CLDI module "portable". */
#include "../setup.h"
#include <ciahlldi/cldi/head/setup/platform.h>

#ifdef __cplusplus
extern "C" {
#endif



/* System Heap Handle */
#if   __CLDI_PLATFORM_UNIXLIKE == true
typedef void * CLDI_HEAP_HANDLE;
#elif __CLDI_PLATFORM == CLDI_PLATFORM_WINDOWS
typedef HANDLE CLDI_HEAP_HANDLE;
#else
typedef void * CLDI_HEAP_HANDLE;
#endif



#ifdef __cplusplus
}
#endif

#endif /* _cldi_portable__handles_MEM_H */
