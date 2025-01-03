
#ifndef _cldi_portable_
#define _cldi_portable_ 1

/* Setup CLDI module "portable". */
#include "portable/setup.h"
#include "portable/version.h"



/* Included Submodules */

/* "types" : Different basic types for managing different basic, adaptable,
.            potentially platform-specific functions.                      */
#include "portable/types.h"

/* "calls" : Different adaptable calls to different functions of the system
.            that may be different in implementation based on platform.    */
#include "portable/calls.h"



#endif /* _cldi_portable__ */
