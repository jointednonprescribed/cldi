
#ifndef _cldi_head__types_arraytypes_CLDIFLOATARR_H
#define _cldi_head__types_arraytypes_CLDIFLOATARR_H 1

#include <stddef.h>

#include "refs.h"



#ifdef __cplusplus
extern "C" {
#endif

/* Get the array itself, USE THIS INSTEAD OF REFERENCING CLDIFLOATARR::_data DIRECTLY. */
const char* cldiFloatArrData(const cldiFloatArr *self);
/* Get the array's length. */
size_t      cldiFloatArrLength(const cldiFloatArr *self);

/* Get a certain item in the array. */
char        cldiFloatArrGet(const cldiFloatArr *self, size_t idx);

#ifdef __cplusplus
}
#endif



#endif /* _cldi_head__types_arraytypes_CLDIFLOATARR_H */
