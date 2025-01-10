
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
	CLDI_WLVL0   = CLDI_SUCCESS,

	CLDI_SUCCESS = 0,
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
} CLDISTAT;

/* This is a global variable that will be redefined for all threads and libraries
.  on a process including this header, so to obtain the current error code for the
.  CLDI Standard Library in memory, an extra method is provided. */
CLDISTAT CLDI_ERRNO = CLDI_SUCCESS;
// Get CLDI Standard Library errno value
CLDISTAT cldiGetStdlibErrno();

/* Methods associated with CLDISTAT values: */

/* Get the descriptor string associated with an error code. */
const char* cldiGetErrorName(CLDISTAT e);
const char* cldiGetStdlibErrnoName(); // Tests the CLDI Standard Library's global variable `errno`
const char* cldiGetErrnoName() // Tests the global variable `errno`
{
	return cldiGetErrorName(CLDI_ERRNO);
}

/* Check if an status value is a warning. */
#define CLDI_STAT_ISWARNING(stat) (stat) < 0
bool cldiStdlibWarning(); // Checks the CLDI Standard Library errno value
bool cldiStatWarning(CLDISTAT e) // Registers the passed stat value to this shared object's errno and checks for warning
{
	CLDI_ERRNO = e;
	return CLDI_STAT_ISWARNING(e);
}
bool cldiIsWarning() // Checks the current shared object's errno value
{
	return CLDI_STAT_ISWARNING(CLDI_ERRNO);
}
/* Check if an status value is an error. */
#define CLDI_STAT_ISERROR(stat) (stat) > 0
bool cldiStdlibError(); // Checks the CLDI Standard Library errno value
bool cldiStatError(CLDISTAT e) // Registers the passed stat value to this shared object's errno and checks for error
{
	CLDI_ERRNO = e;
	return CLDI_STAT_ISERROR(e);
}
bool cldiIsError() // Checks the current shared object's errno value
{
	return CLDI_STAT_ISERROR(CLDI_ERRNO);
}
/* Check if an status value is success. */
#define CLDI_STAT_ISSUCCESS(stat) (stat) == 0
bool cldiStdlibSuccess(); // Checks the CLDI Standard Library errno value
bool cldiStatSuccess(CLDISTAT e) // Registers the passed stat value to this shared object's errno and checks for success
{
	CLDI_ERRNO = e;
	return CLDI_STAT_ISSUCCESS(e);
}
bool cldiIsSuccess() // Checks the current shared object's errno value
{
	return CLDI_STAT_ISSUCCESS(CLDI_ERRNO);
}
/* Check if an status value is permissible. */
#define CLDI_STAT_ISPERMISSIBLE(stat) (stat) <= 0 && (stat) <= CLDI_WPERMIT_LEVEL
bool cldiStdlibPermissible(); // Checks the CLDI Standard Library errno value
bool cldiStatPermissible(CLDISTAT e) // Registers the passed stat value to this shared object's errno and checks for warning
{
	CLDI_ERRNO = e;
	return CLDI_STAT_ISPERMISSIBLE(e);
}
bool cldiIsPermissible() // Checks the current shared object's errno value
{
	return CLDI_STAT_ISPERMISSIBLE(CLDI_ERRNO);
}

#ifdef __cplusplus
}
#endif


/* C++ bindings for this file: */
#if CLDI_C_ONLY == false
namespace cldi
{
	using STAT   = CLDISTAT;
	using stat_t = CLDISTAT;

	constexpr STAT WDEFRAG_RECOMMENDED = CLDI_WDEFRAG_RECOMMENDED;

	constexpr STAT WLVL3 = CLDI_WLVL3;
	constexpr STAT WLVL2 = CLDI_WLVL2;
	constexpr STAT WLVL1 = CLDI_WLVL1;
	constexpr STAT WLVL0 = CLDI_WLVL0;

	constexpr STAT SUCCESS = CLDI_SUCCESS;
	constexpr STAT TRUE = CLDI_TRUE;
	constexpr STAT FALSE = CLDI_FALSE;

	constexpr STAT EUNKNOWN = CLDI_EUNKNOWN;

	constexpr STAT ENO_IMPL = CLDI_ENO_IMPL;

	constexpr STAT EOUT_OF_MEMORY = CLDI_EOUT_OF_MEMORY;
	constexpr STAT EDEFRAG_REQUIRED = CLDI_EDEFRAG_REQUIRED;

	constexpr STAT ENULL_ATTR = CLDI_ENULL_ATTR;
	constexpr STAT ENULL_ARG = CLDI_ENULL_ARG;
	constexpr STAT ENULL_SELF = CLDI_ENULL_SELF;
	constexpr STAT EINVALID_ATTR = CLDI_EINVALID_ATTR;
	constexpr STAT EINVALID_ARG = CLDI_EINVALID_ARG;
	constexpr STAT EINVALID_SELF = CLDI_EINVALID_SELF;

	STAT &ERRNO = CLDI_ERRNO;

	STAT        (&GetStdlibErrno)() = cldiGetStdlibErrno;
	const char* (&GetErrorName)(CLDISTAT) = cldiGetErrorName;
	const char* (&GetStdlibErrnoName)() = cldiGetStdlibErrnoName;
	const char* (&GetErrnoName)() = cldiGetErrnoName;
	bool        (&StdlibWarning)() = cldiStdlibWarning;
	bool        (&StatWarning)(CLDISTAT) = cldiStatWarning;
	bool        (&IsWarning)() = cldiIsWarning;
	bool        (&StdlibError)() = cldiStdlibError;
	bool        (&StatError)(CLDISTAT) = cldiStatError;
	bool        (&IsError)() = cldiIsError;
	bool        (&cldiStdlibSuccess)() = cldicldiStdlibSuccess;
	bool        (&cldiStatSuccess)(CLDISTAT) = cldicldiStatSuccess;
	bool        (&cldiIsSuccess)() = cldicldiIsSuccess;
	bool        (&cldiStdlibPermissible)() = cldicldiStdlibPermissible;
	bool        (&cldiStatPermissible)(CLDISTAT) = cldicldiStatPermissible;
	bool        (&cldiIsPermissible)() = cldicldiIsPermissible;
	constexpr bool STAT_ISWARNING(STAT e)
	{
		return CLDI_STAT_ISWARNING(e);
	}
	constexpr bool STAT_ISERROR(STAT e)
	{
		return CLDI_STAT_ISERROR(e);
	}
	constexpr bool STAT_ISSUCCESS(STAT e)
	{
		return CLDI_STAT_ISSUCCESS(e);
	}
	constexpr bool STAT_ISPERMISSIBLE(STAT e)
	{
		return CLDI_STAT_ISPERMISSIBLE(e);
	}
}
#endif



#endif // _cldi_head__setup_STAT_H
