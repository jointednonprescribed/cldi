
#ifndef _cldi_head__setup_STAT_H
#define _cldi_head__setup_STAT_H 1

#include "includes.h"



#ifdef __cplusplus
extern "C" {
#endif

typedef enum _CLDISTAT
{
	CLDI_WDEFRAG_RECOMMENDED=-1,

	CLDI_WLVL3   = CLDI_WDEFRAG_RECOMMENDED,
	CLDI_WLVL2   = CLDI_WDEFRAG_RECOMMENDED,
	CLDI_WLVL1   = CLDI_WDEFRAG_RECOMMENDED,

	CLDI_SUCCESS = 0,
	CLDI_WLVL0   = CLDI_SUCCESS,
	
	CLDI_TRUE    = CLDI_SUCCESS,
	CLDI_FALSE,

	CLDI_EUNKNOWN,

	CLDI_ENO_IMPL,

	CLDI_EOUT_OF_MEMORY,
	CLDI_EDEFRAG_REQUIRED,

	CLDI_ENULL_ATTR,
	CLDI_ENULL_ARG,
	CLDI_ENULL_SELF,
	CLDI_EINVALID_ATTR,
	CLDI_EINVALID_ARG,
	CLDI_EINVALID_SELF,

	CLDI_ENO_ACCESS,
	CLDI_ENOT_READABLE,
	CLDI_ENOT_WRITABLE,
	CLDI_ENOT_EXECUTABLE,
	CLDI_ENONEXISTENT,

	CLDI_EINCOMPATIBLE_TYPE,
} CLDISTAT;

/* This is a global variable for passing errors while keeping return type. */
extern CLDISTAT CLDI_ERRNO;

/* Methods associated with CLDISTAT values: */

/* Get the descriptor string associated with an error code. */
const char* cldiGetErrorName(CLDISTAT e);
const char* cldiGetErrnoName(); // Tests the global variable `errno`

/* Check if an status value is a warning. */
#define CLDI_STAT_ISWARNING(stat) (stat) < 0
bool cldiStatWarning(CLDISTAT e); // Registers the passed stat value to this shared object's errno and checks for warning
bool cldiIsWarning(); // Checks the current shared object's errno value
/* Check if an status value is an error. */
#define CLDI_STAT_ISERROR(stat) (stat) > 0
bool cldiStatError(CLDISTAT e); // Registers the passed stat value to this shared object's errno and checks for error
bool cldiIsError(); // Checks the current shared object's errno value
/* Check if an status value is success. */
#define CLDI_STAT_ISSUCCESS(stat) (stat) == 0
bool cldiStatSuccess(CLDISTAT e); // Registers the passed stat value to this shared object's errno and checks for success
bool cldiIsSuccess(); // Checks the current shared object's errno value
/* Check if an status value is permissible. */
#define CLDI_STAT_ISPERMISSIBLE(stat) (stat) <= 0 && (stat) <= CLDI_WPERMIT_LEVEL
bool cldiStatPermissible(CLDISTAT e); // Registers the passed stat value to this shared object's errno and checks for warning
bool cldiIsPermissible(); // Checks the current shared object's errno value

#ifdef __cplusplus
}
#endif


/* C++ bindings for this file: */
#include "icxx/stat.hpp"



#endif // _cldi_head__setup_STAT_H
