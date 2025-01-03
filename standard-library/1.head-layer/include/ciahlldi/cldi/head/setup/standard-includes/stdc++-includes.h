
#if !defined(_cldi_setup__standard_includes_STD_INCLUDES_H) && defined(__cplusplus)
#define _cldi_setup__standard_includes_STD_INCLUDES_H 1

#include "../prerequisites.h"



/* Handle C Library Includes */
#include "stdc-includes.h"

/* C++ Imports of standard C headers */
#include <cstdbool>
#include <cstdarg>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstdlib>
#include <cstring>

/* C Math library */
#if __CLDI_include_cmath == true
#	include <cmath>
#endif

/* C++ Library Includes */
#include <string>   /* Standard string features  */
#include <array>    /* Standard array features   */
#include <memory>   /* Standard memory features  */



#endif /* _cldi_setup__standard_includes_STD_INCLUDES_H */
