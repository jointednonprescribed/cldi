
#ifndef _cldi_setup__
#define _cldi_setup__ 1



/* Included Setup Headers */
#include "version.h"

/* "prerequisites"     : Headers to be loaded at the beginning of setup. */
#include "setup/prerequisites.h"

/* "platform"          : Initiates a foundation of compiler macros, enums, directives, etc.
.                        that signal what platform and exact specifications are being targeted
.                        by the compiler. */
#include "setup/platform.h"

/* "standard-includes" : Includes all dependencies of this layer (should just be from the
.                        C and C++ standard libraries). */
#include "setup/standard-includes.h"



#endif /* _cldi_setup__ */
