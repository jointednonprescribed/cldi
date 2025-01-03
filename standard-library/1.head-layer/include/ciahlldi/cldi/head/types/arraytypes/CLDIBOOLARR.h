
#ifndef _cldi_head__types_arraytypes_CLDIBOOLARR_H
#define _cldi_head__types_arraytypes_CLDIBOOLARR_H 1

#include <stddef.h>

#include "refs.h"



#ifdef __cplusplus
extern "C" {
#endif

/* Get the array itself, USE THIS INSTEAD OF REFERENCING CLDIBOOLARR::_data DIRECTLY. */
const char* cldiBoolArrData(const cldiBoolArr *self);
/* Get the array's length. */
size_t      cldiBoolArrLength(const cldiBoolArr *self);

/* Get a certain item in the array. */
char        cldiBoolArrGet(const cldiBoolArr *self, size_t idx);

#ifdef __cplusplus
}
#endif



#endif /* _cldi_head__types_arraytypes_CLDIBOOLARR_H */
