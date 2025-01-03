
#ifndef _cldi_setup__prerequisites_SETTINGS_H
#define _cldi_setup__prerequisites_SETTINGS_H 1



/* Disable C++ Language Features and Standard Library (C Only Mode) (default: ifndef __cplusplus)
.   - __CLDI_no_cpp
.   - True or False (1 or 0) */
#ifndef __CLDI_no_cpp
#	ifdef __cplusplus
#   	define __CLDI_no_cpp false
#	else
#		define __CLDI_no_cpp true
#	endif
#endif

/* Define standard C-style strings and chars as ASCII/ANSI or UTF-8. (default: yes)
.   - __CLDI_standard_strings_are_ascii
.   - True or False (1 or 0) */
#ifndef __CLDI_standard_strings_are_ascii
#	define __CLDI_standard_strings_are_ascii true
#endif


/* Include C standard library 'math.h' header (default: yes)
.   - __CLDI_include_cmath
.   - If C++ library is enabled, <cmath> header will also be included.
.   - True or False (1 or 0) */
#ifndef __CLDI_include_cmath
#	define __CLDI_include_cmath false
#endif
/* Use extended double-precision floating-point type (default: yes (if available))
.   - __CLDI_use_extended_double
.   - True or False (1 or 0) */
#ifndef __CLDI_use_extended_double
#	define __CLDI_use_extended_double true
#endif



#endif /* _cldi_setup__prerequisites_SETTINGS_H */
