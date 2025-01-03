
#ifndef _cldi_head__types_arraytypes_CLDIINTARR_H
#define _cldi_head__types_arraytypes_CLDIINTARR_H 1

#include <stddef.h>

#include "refs.h"



#ifdef __cplusplus
extern "C" {
#endif

/* Get the array itself, USE THIS INSTEAD OF REFERENCING CLDIINTARR::_data DIRECTLY. */
const char* cldiIntArrData(const cldiIntArr *self);
/* Get the array's length. */
size_t      cldiIntArrLength(const cldiIntArr *self);

/* Get a certain item in the array. */
char        cldiIntArrGet(const cldiIntArr *self, size_t idx);

#ifdef __cplusplus
}
#endif



#endif /* _cldi_head__types_arraytypes_CLDIINTARR_H */
