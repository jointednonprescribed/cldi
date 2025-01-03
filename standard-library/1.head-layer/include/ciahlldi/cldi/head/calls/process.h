
#ifndef _cldi_portable__calls_PROCESS_H
#define _cldi_portable__calls_PROCESS_H 1

/* Setup CLDI module "head". */
#include "../setup.h"

#ifdef __cplusplus
extern "C" {
#endif



/* Get the current process's PID. */
cldipid_t cldiGetCurrentPID();



#ifdef __cplusplus
}
#endif

#endif /* _cldi_portable__calls_PROCESS_H */
