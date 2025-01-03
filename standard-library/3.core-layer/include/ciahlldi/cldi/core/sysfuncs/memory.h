
#ifndef _cldi_portable__sysfuncs_MEMORY_H
#define _cldi_portable__sysfuncs_MEMORY_H 1

/* Setup CLDI module "core". */
#include "../setup.h"

/* Requires: cldi-portable: types */
#include <ciahlldi/cldi/portable/types.h>



/* ------------------------------------------------------- */
/* Standard Memory Ownership and Initialization Operations */

#ifdef __cplusplus
extern "C" {
#endif

void*    cldiHeapAlloc(void *heap_handle, size_t amount_of_bytes);
CLDISTAT cldiHeapAllocEx(void **var_to_output_ref, void*, size_t);
CLDISTAT cldiDropMemory(void * address);

void*    cldiRequestMemory(size_t amount_of_bytes);
void*    cldiRequestTextMemory(size_t);
void*    cldiRequestResourceMemory(size_t);

CLDISTAT cldiRequestMemoryEx(
	void      **var_to_output_ref,
	size_t  amount_of_bytes,
	long long   mem_options
);
CLDISTAT cldiRequestTextMemoryEx(void**, size_t, long long);
CLDISTAT cldiRequestResourceMemoryEx(void**, size_t, long long);

/* Borrow some claimed memory block for second-hand use. */
CLDISTAT cldiBorrowMemory(void * address);
/* Claim some requested memory as owned and active (usually after you, the
.  owner of said memory in the given case, have finished initializing it). */
CLDISTAT cldiClaimMemory(void * address);

#ifdef __cplusplus
}
#endif


/* ------------------------------------------------------- */



#endif /* _cldi_portable__sysfuncs_MEMORY_H */
