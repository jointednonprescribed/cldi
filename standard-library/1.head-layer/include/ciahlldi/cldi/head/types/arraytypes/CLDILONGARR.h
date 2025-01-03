
#ifndef _cldi_head__types_arraytypes_CLDILONGARR_H
#define _cldi_head__types_arraytypes_CLDILONGARR_H 1

#include <stddef.h>

#include "refs.h"



#ifdef __cplusplus
extern "C" {
#endif

/* Get the array itself, USE THIS INSTEAD OF REFERENCING CLDILONGARR::_data DIRECTLY. */
const char* cldiLongArrData(const cldiLongArr *self);
/* Get the array's length. */
size_t      cldiLongArrLength(const cldiLongArr *self);

/* Get a certain item in the array. */
char        cldiLongArrGet(const cldiLongArr *self, size_t idx);

#ifdef __cplusplus
}
#endif



#endif /* _cldi_head__types_arraytypes_CLDILONGARR_H */
