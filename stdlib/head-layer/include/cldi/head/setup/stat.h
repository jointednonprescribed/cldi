
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
	CLDI_CMPE    = CLDI_SUCCESS,
	CLDI_FALSE,
	CLDI_CMPL    = CLDI_FALSE,
	CLDI_CMPG,
	CLDI_CMPLESS = CLDI_CMPL,
	CLDI_CMPGREATER = CLDI_CMPG,

	CLDI_EUNKNOWN,

	CLDI_ENO_IMPL,

	CLDI_EOUT_OF_MEMORY,
	CLDI_EDEFRAG_REQUIRED,

	CLDI_ETOO_FEW_ARGS,
	CLDI_EOVERFLOW,
	CLDI_EOVERFLOW_ARG,
	CLDI_EOVERFLOW_ATTR,

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
/* C Standard Library Error contexts */
typedef enum _CLDICSTDEC
{
	CLDI_CSTDEC_PRINTF,
	CLDI_CSTDEC_VPRINTF   = CLDI_CSTDEC_PRINTF,
	CLDI_CSTDEC_FPRINTF   = CLDI_CSTDEC_PRINTF,
	CLDI_CSTDEC_VFPRINTF  = CLDI_CSTDEC_PRINTF,
	CLDI_CSTDEC_SPRINTF   = CLDI_CSTDEC_PRINTF,
	CLDI_CSTDEC_SNPRINTF  = CLDI_CSTDEC_PRINTF,
	CLDI_CSTDEC_VSPRINTF  = CLDI_CSTDEC_PRINTF,
	CLDI_CSTDEC_VSNPRINTF = CLDI_CSTDEC_PRINTF,
	CLDI_CSTDEC_VASPRINTF = CLDI_CSTDEC_PRINTF,
	CLDI_CSTDEC_ASPRINTF  = CLDI_CSTDEC_PRINTF,
	CLDI_CSTDEC_VDPRINTF  = CLDI_CSTDEC_PRINTF,
	CLDI_CSTDEC_DPRINTF   = CLDI_CSTDEC_PRINTF,
} CLDI_CSTDLIB_ERRCONTEXT;

/* Globally-Defined String Constants */
extern const char *const CLDI_NO_ERRNAME;
extern const char *const CLDI_ERRNAME_WDEFRAG_RECOMMENDED;
extern const char *const CLDI_ERRNAME_WLVL3;
extern const char *const CLDI_ERRNAME_WLVL2;
extern const char *const CLDI_ERRNAME_WLVL1;
extern const char *const CLDI_ERRNAME_SUCCESS;
extern const char *const CLDI_ERRNAME_WLVL0;
extern const char *const CLDI_ERRNAME_TRUE;
extern const char *const CLDI_ERRNAME_CMPE;
extern const char *const CLDI_ERRNAME_FALSE;
extern const char *const CLDI_ERRNAME_CMPL;
extern const char *const CLDI_ERRNAME_CMPG;
extern const char *const CLDI_ERRNAME_EUNKNOWN;
extern const char *const CLDI_ERRNAME_ENO_IMPL;
extern const char *const CLDI_ERRNAME_EOUT_OF_MEMORY;
extern const char *const CLDI_ERRNAME_EDEFRAG_REQUIRED;
extern const char *const CLDI_ERRNAME_ETOO_FEW_ARGS;
extern const char *const CLDI_ERRNAME_EOVERFLOW;
extern const char *const CLDI_ERRNAME_EOVERFLOW_ARG;
extern const char *const CLDI_ERRNAME_EOVERFLOW_ATTR;
extern const char *const CLDI_ERRNAME_ENULL_ATTR;
extern const char *const CLDI_ERRNAME_ENULL_ARG;
extern const char *const CLDI_ERRNAME_ENULL_SELF;
extern const char *const CLDI_ERRNAME_EINVALID_ATTR;
extern const char *const CLDI_ERRNAME_EINVALID_ARG;
extern const char *const CLDI_ERRNAME_EINVALID_SELF;
extern const char *const CLDI_ERRNAME_ENO_ACCESS;
extern const char *const CLDI_ERRNAME_ENOT_READABLE;
extern const char *const CLDI_ERRNAME_ENOT_WRITABLE;
extern const char *const CLDI_ERRNAME_ENOT_EXECUTABLE;
extern const char *const CLDI_ERRNAME_ENONEXISTENT;
extern const char *const CLDI_ERRNAME_EINCOMPATIBLE_TYPE;
extern const char *const CLDI_NO_ERRDESC;
extern const char *const CLDI_ERRDESC_WDEFRAG_RECOMMENDED;
extern const char *const CLDI_ERRDESC_WLVL3;
extern const char *const CLDI_ERRDESC_WLVL2;
extern const char *const CLDI_ERRDESC_WLVL1;
extern const char *const CLDI_ERRDESC_SUCCESS;
extern const char *const CLDI_ERRDESC_WLVL0;
extern const char *const CLDI_ERRDESC_TRUE;
extern const char *const CLDI_ERRDESC_CMPE;
extern const char *const CLDI_ERRDESC_FALSE;
extern const char *const CLDI_ERRDESC_CMPL;
extern const char *const CLDI_ERRDESC_CMPG;
extern const char *const CLDI_ERRDESC_EUNKNOWN;
extern const char *const CLDI_ERRDESC_ENO_IMPL;
extern const char *const CLDI_ERRDESC_EOUT_OF_MEMORY;
extern const char *const CLDI_ERRDESC_EDEFRAG_REQUIRED;
extern const char *const CLDI_ERRDESC_ETOO_FEW_ARGS;
extern const char *const CLDI_ERRDESC_EOVERFLOW;
extern const char *const CLDI_ERRDESC_EOVERFLOW_ARG;
extern const char *const CLDI_ERRDESC_EOVERFLOW_ATTR;
extern const char *const CLDI_ERRDESC_ENULL_ATTR;
extern const char *const CLDI_ERRDESC_ENULL_ARG;
extern const char *const CLDI_ERRDESC_ENULL_SELF;
extern const char *const CLDI_ERRDESC_EINVALID_ATTR;
extern const char *const CLDI_ERRDESC_EINVALID_ARG;
extern const char *const CLDI_ERRDESC_EINVALID_SELF;
extern const char *const CLDI_ERRDESC_ENO_ACCESS;
extern const char *const CLDI_ERRDESC_ENOT_READABLE;
extern const char *const CLDI_ERRDESC_ENOT_WRITABLE;
extern const char *const CLDI_ERRDESC_ENOT_EXECUTABLE;
extern const char *const CLDI_ERRDESC_ENONEXISTENT;
extern const char *const CLDI_ERRDESC_EINCOMPATIBLE_TYPE;

/* Exception type */
typedef struct _CLDIEXCEPTION
{
	const char *exc_name, *exc_desc;
	void       *function;
	CLDISTAT    ec; // ec = "error code"
} cldiexception_t, cldiexc_t, cldierror_t;
/* This is a global variable for passing errors while keeping return type. */
extern cldiexc_t CLDI_ERROR;
// This macro is defined as a QoD feature, as well as a backwards-compatibility
// feature for code written before the cldiexception_t type was committed.
#define CLDI_ERRNO (CLDI_ERROR.ec)
/* This macro places required error control on the global CLDI_ERROR variable
.  at the beginning of a method by clearing the value of CLDI_ERROR. */
#define CLDI_ECTRL \
	CLDI_ERROR.exc_name=CLDI_ERRNAME_SUCCESS; \
	CLDI_ERROR.exc_desc=CLDI_ERRDESC_SUCCESS; \
	CLDI_ERROR.function=NULL;   \
	CLDI_ERROR.ec=CLDI_SUCCESS;
/* This macro is used for error catch statements. */
#define CLDI_CATCH if(!cldiIsPermissible())

/* Methods associated with CLDISTAT values: */

// Convert a C Standard library error into a CLDISTAT error code.
CLDISTAT cldiConvCStdlibError(CLDI_CSTDLIB_ERRCONTEXT error_context, int error);
// - Convert from C Standard Library "errno" flag
CLDISTAT cldiConvCStdlibErrno(CLDI_CSTDLIB_ERRCONTEXT error_context);

/* Get the default descriptor string associated with an error code or status
.  value. */
const char* cldiGetErrorName(CLDISTAT e);
const char* cldiGetErrnoName(); // Tests the global variable `errno`
/* Get the default description associated with an error code or status value. */
const char* cldiGetErrorDesc(CLDISTAT e);
const char* cldiGetErrnoDesc();

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

/* Methods associated with cldiexc_t objects: */

/* Create an error using just an error code. */
cldiexc_t cldierrec(CLDISTAT ec);
/* Create an error using an error code and a description (default mode). */
cldiexc_t cldierr(CLDISTAT ec, const char *desc);
/* Create an error using an error code, name, and description. */
cldiexc_t cldinerr(CLDISTAT ec, const char *name, const char *desc);
/* Create an error using an error code, specified function address (the function
.  that was running when the error occurred), and description. */
cldiexc_t cldierrf(CLDISTAT ec, void *function, const char *desc);
/* Create an error using an error code, specified function address (the function
.  that was running when the error occurred), name, and description. */
cldiexc_t cldinerrf(CLDISTAT ec, void *function, const char *name, const char *desc);

/* Throw an error using just an error code. */
cldiexc_t* cldithrowec(CLDISTAT ec);
/* Throw an error using an error code and a description (default mode). */
cldiexc_t* cldithrowd(CLDISTAT ec, const char *desc);
/* Throw an error using an error code, name, and description. */
cldiexc_t* cldinthrow(CLDISTAT ec, const char *name, const char *desc);
/* Throw an error using an error code, specified function address (the function
.  that was running when the error occurred), and description. */
cldiexc_t* cldithrowf(CLDISTAT ec, void *function, const char *desc);
/* Throw an error using an error code, specified function address (the function
.  that was running when the error occurred), name, and description. */
cldiexc_t* cldinthrowf(CLDISTAT ec, void *function, const char *name, const char *desc);
/* Throw an exception object globally on the current thread. */
cldiexc_t* cldithrow(cldiexc_t *self);

/* Add a traceback message to the current thrown error. */
void       cldiAddTraceback(void *function, const char *desc);

/* Get the error code of an exception. */
CLDISTAT    cldiExcGetErrno(cldiexc_t *self);
/* Get the specified calling function from an exception. */
void*       cldiExcGetFunction(cldiexc_t *self);
/* Get the name of an exception. */
const char* cldiExcGetName(cldiexc_t *self);
/* Get the description of an exception. */
const char* cldiExcGetDesc(cldiexc_t *self);
/* Check the exception for a specified calling function. */
bool        cldiExcSpecifiesFunction(cldiexc_t *self);

/* Check if an exception is a warning. */
bool cldiExcIsWarning(cldiexc_t *self);
/* Check if an exception is an error. */
bool cldiExcIsError(cldiexc_t *self);
/* Check if an exception is success. */
bool cldiExcIsSuccess(cldiexc_t *self);
/* Check if an exception is permissible. */
bool cldiExcIsPermissible(cldiexc_t *self);

#ifdef __cplusplus
}
#endif


/* C++ bindings for this file: */
#include "icxx/stat.hpp"



#endif // _cldi_head__setup_STAT_H
