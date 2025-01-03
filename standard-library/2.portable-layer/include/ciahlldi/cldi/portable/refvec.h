
#ifndef _cldi_portable__REFVEC_H
#define _cldi_portable__REFVEC_H 1

#include "setup.h"

/* Requires: types/basic-types */
#include "types/basictypes.h"

#ifdef __cplusplus
extern "C" {
#endif



/* Reference Vector Structure Implementation */
typedef struct _cldiMemoryVector
{ const void *_o, *_d; }
cldiMemoryVector, cldiMemVector;


/* Make a new memory vector struct from one or two addresses. */
cldiMemVector cldiMakeMemVecFrom(void * from, void * to);
cldiMemVector cldiMakeMemVecTo(void * to);

/* Calculate the distance from the origin to the terminal of a reference vector. */
double cldiGetMemVecMagnitude(cldiMemVector vec);
/* Get the origin address of a memory vector. */
void*  cldiGetMemVecOrigin(cldiMemVector vec);
/* Get the destination address of a memory vector. */
void*  cldiGetMemVecDestination(cldiMemVector vec);


#ifdef __cplusplus
}
#endif

#endif /* _cldi_portable__REFVEC_H */
