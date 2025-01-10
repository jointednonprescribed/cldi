
/* This file contains definitions/checks for a number of settings macros that
.  can be set to tweak or enable/disable library features. */

#ifndef _cldi_head__SETTINGS_H
#define _cldi_head__SETTINGS_H 1



/* Warning Permission Level (0-3) */
#ifndef CLDI_WPERMIT_LEVEL
// Default is 1 (Level 2 and 3 warnings will be treated like errors).
#   define CLDI_WPERMIT_LEVEL CLDI_WLVL1
#elif CLDI_WPERMIT_LEVEL < 0
#   pragma warn("cldi-head: CLDI_WPERMIT_LEVEL set to less-than-zero value, defaulting to 0.")
#   define CLDI_WPERMIT_LEVEL CLDI_WLVL0
#elif CLDI_WPERMIT_LEVEL > 3
#   pragma warn("cldi-head: CLDI_WPERMIT_LEVEL set to greater-than-max value, defaulting to 3 (max).")
#   define CLDI_WPERMIT_LEVEL CLDI_WLVL3
#elif CLDI_WPERMIT_LEVEL == 0
#   pragma warn("cldi-head: CLDI_WPERMIT_LEVEL set to 0, should have been CLDI_WLVL0.")
#   define CLDI_WPERMIT_LEVEL CLDI_WLVL0
#elif CLDI_WPERMIT_LEVEL == 1
#   pragma warn("cldi-head: CLDI_WPERMIT_LEVEL set to 1, should have been CLDI_WLVL1.")
#   define CLDI_WPERMIT_LEVEL CLDI_WLVL1
#elif CLDI_WPERMIT_LEVEL == 2
#   pragma warn("cldi-head: CLDI_WPERMIT_LEVEL set to 2, should have been CLDI_WLVL2.")
#   define CLDI_WPERMIT_LEVEL CLDI_WLVL2
#elif CLDI_WPERMIT_LEVEL == 3
#   pragma warn("cldi-head: CLDI_WPERMIT_LEVEL set to 3, should have been CLDI_WLVL3.")
#   define CLDI_WPERMIT_LEVEL CLDI_WLVL3
#else
#   pragma warn("cldi-head: CLDI_WPERMIT_LEVEL set to non-integer value, defaulting to 1...")
#   define CLDI_WPERMIT_LEVEL CLDI_WLVL1
#endif

/* C Compatibility Mode (This excludes all C++ features, except for extern "C") */
#ifdef CLDI_C_ONLY
#	if !defined(__cplusplus)
#		if CLDI_C_ONLY != true
#			define CLDI_C_ONLY true
#		endif
#	else
#		if CLDI_C_ONLY > true
#			define CLDI_C_ONLY true
#		elif CLDI_C_ONLY < false
#			define CLDI_C_ONLY false
#		elif CLDI_C_ONLY != 0 && CLDI_C_ONLY != 1
#			pragma warn("cldi-head: CLDI_C_ONLY was set to an improper value, defaulting to false.")
#			define CLDI_C_ONLY false
#		endif
#	endif
#else
#	ifdef __cplusplus
#		define CLDI_C_ONLY false
#	else
#		define CLDI_C_ONLY true
#	endif
#endif

/* Include Math Library (this will include C library math header, and CLDI
.  library math header, as well as C++ header) */
#ifdef CLDI_INCLUDE_MATH
#	if CLDI_INCLUDE_MATH > true
#		define CLDI_INCLUDE_MATH true
#	elif CLDI_INCLUDE_MATH < false
#		define CLDI_INCLUDE_MATH false
#	elif CLDI_INCLUDE_MATH != 0 && CLDI_INCLUDE_MATH != 1
#		pragma warn("cldi-head: CLDI_INCLUDE_MATH was set to an improper value, defaulting to false.")
#		define CLDI_INCLUDE_MATH false
#	endif
#else
#	define CLDI_INCLUDE_MATH false
#endif



#endif // _cldi_head__SETTINGS_H
