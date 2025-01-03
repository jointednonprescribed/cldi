
#ifndef _cldi_core__TYPES_H
#define _cldi_core__TYPES_H 1

/* Setup CLDI module "core". */
#include "setup.h"

/* Requires: cldi-portable: types */
#include <ciahlldi/cldi/portable/types.h>



/* Included 'types' Headers */

/* "arr"         : Basic heap-allocated vla (variable-length array) type. */
//#include "types/arr.h"

/* "func"        : Basic handles for storing method addresses of various types as classes. */
#include "types/func.h"

/* "file-handle" : A basic type for managing a file, while remembering its
                   stored path name and opening options (until close). */
//#include "types/file-handle.h"



#endif /* _cldi_core__TYPES_H */
