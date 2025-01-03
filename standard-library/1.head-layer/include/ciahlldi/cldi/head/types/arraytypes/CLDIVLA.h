
#ifndef _cldi_head__types_arraytypes_CLDIVLA_H
#define _cldi_head__types_arraytypes_CLDIVLA_H 1

#include <stddef.h>

#include "refs.h"

#include "../basictypes.h"



#ifdef __cplusplus
extern "C" {
#endif

/* Get the array itself, USE THIS INSTEAD OF REFERENCING CLDIVLA::_data DIRECTLY. */
const void* cldiVLAData(const cldiVLA *self);
/* Get the array's length. */
size_t      cldiVLALength(const cldiVLA *self);

/* Get a certain item in the array, and output it in a provided memory address for
.  reception. */
CLDISTAT    cldiVLAGet(const cldiVLA *self, size_t idx, void **const output);

#ifdef __cplusplus
}
#endif



#endif /* _cldi_head__types_arraytypes_CLDIVLA_H */
