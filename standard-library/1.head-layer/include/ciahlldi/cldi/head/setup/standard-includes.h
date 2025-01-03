
#ifndef _cldi_setup__STANDARD_INCLUDES_H
#define _cldi_setup__STANDARD_INCLUDES_H 1

#include "prerequisites.h"
#include "platform.h"



/* Standard Library Includes */

/* C Library Includes   */
#include "standard-includes/stdc-includes.h"

/* C++ Library Includes */
#if _cldi_cpp_library_features == true
#	include "standard-includes/stdc++-includes.h"
#endif

/* Platform-specific Includes */
#include "standard-includes/platform-apis.h"



#endif /* _cldi_setup__STANDARD_INCLUDES_H */
