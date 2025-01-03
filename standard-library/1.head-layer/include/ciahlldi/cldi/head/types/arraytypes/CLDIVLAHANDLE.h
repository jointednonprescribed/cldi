
#ifndef _cldi_head__types_arraytypes_CLDIVLAHANDLE_H
#define _cldi_head__types_arraytypes_CLDIVLAHANDLE_H 1

#include <stddef.h>

#include "refs.h"



#ifdef __cplusplus
extern "C" {
#endif

/* Get the array itself, USE THIS INSTEAD OF REFERENCING CLDIVLA::_data DIRECTLY. */
const char* cldiVLAHandleData(const cldiVLA *self);
/* Get the array's length. */
size_t      cldiVLAHandleLength(const cldiVLA *self);

/* Get a certain item in the array. */
char        cldiVLAHandleGet(const cldiVLA *self, size_t idx);

#ifdef __cplusplus
}
#endif



#endif /* _cldi_head__types_arraytypes_CLDIVLAHANDLE_H */
