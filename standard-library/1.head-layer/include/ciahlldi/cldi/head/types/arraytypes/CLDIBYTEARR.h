
#ifndef _cldi_head__types_arraytypes_CLDIBYTEARR_H
#define _cldi_head__types_arraytypes_CLDIBYTEARR_H 1

#include <stddef.h>

#include "refs.h"



#ifdef __cplusplus
extern "C" {
#endif

/* Get the array itself, USE THIS INSTEAD OF REFERENCING CLDIBYTEARR::_data DIRECTLY. */
const char* cldiByteArrData(const cldiByteArr *self);
/* Get the array's length. */
size_t      cldiByteArrLength(const cldiByteArr *self);

/* Get a certain item in the array. */
char        cldiByteArrGet(const cldiByteArr *self, size_t idx);

#ifdef __cplusplus
}
#endif



#endif /* _cldi_head__types_arraytypes_CLDIBYTEARR_H */
