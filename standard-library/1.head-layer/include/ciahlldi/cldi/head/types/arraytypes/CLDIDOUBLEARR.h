
#ifndef _cldi_head__types_arraytypes_CLDIDOUBLEARR_H
#define _cldi_head__types_arraytypes_CLDIDOUBLEARR_H 1

#include <stddef.h>

#include "refs.h"



#ifdef __cplusplus
extern "C" {
#endif

/* Get the array itself, USE THIS INSTEAD OF REFERENCING CLDIDOUBLEARR::_data DIRECTLY. */
const char* cldiDoubleArrData(const cldiDoubleArr *self);
/* Get the array's length. */
size_t      cldiDoubleArrLength(const cldiDoubleArr *self);

/* Get a certain item in the array. */
char        cldiDoubleArrGet(const cldiDoubleArr *self, size_t idx);

#ifdef __cplusplus
}
#endif



#endif /* _cldi_head__types_arraytypes_CLDIDOUBLEARR_H */
