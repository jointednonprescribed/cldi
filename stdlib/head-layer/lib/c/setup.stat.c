


/* Implementing cldi-head: setup/stat.h */
#include <cldi/head/setup/stat.h>



const char *const CLDI_NO_ERRNAME = "<anonymous>";
const char *const CLDI_ERRNAME_WDEFRAG_RECOMMENDED = "WDEFRAG_RECOMMENDED";
const char *const CLDI_ERRNAME_WLVL3 = "WLVL3";
const char *const CLDI_ERRNAME_WLVL2 = "WLVL2";
const char *const CLDI_ERRNAME_WLVL1 = "WLVL1";
const char *const CLDI_ERRNAME_SUCCESS = "SUCCESS";
const char *const CLDI_ERRNAME_WLVL0 = "WLVL0";
const char *const CLDI_ERRNAME_TRUE = "TRUE";
const char *const CLDI_ERRNAME_CMPE = "CMPE";
const char *const CLDI_ERRNAME_FALSE = "FALSE";
const char *const CLDI_ERRNAME_CMPL = "CMPL";
const char *const CLDI_ERRNAME_CMPG = "CMPG";
const char *const CLDI_ERRNAME_EUNKNOWN = "EUNKNOWN";
const char *const CLDI_ERRNAME_ENO_IMPL = "ENO_IMPL";
const char *const CLDI_ERRNAME_EOUT_OF_MEMORY = "EOUT_OF_MEMORY";
const char *const CLDI_ERRNAME_EDEFRAG_REQUIRED = "EDEFRAG_REQUIRED";
const char *const CLDI_ERRNAME_ETOO_FEW_ARGS = "ETOO_FEW_ARGS";
const char *const CLDI_ERRNAME_EOVERFLOW = "EOVERFLOW";
const char *const CLDI_ERRNAME_EOVERFLOW_ARG = "EOVERFLOW_ARG";
const char *const CLDI_ERRNAME_EOVERFLOW_ATTR = "EOVERFLOW_ATTR";
const char *const CLDI_ERRNAME_ENULL_ATTR = "ENULL_ATTR";
const char *const CLDI_ERRNAME_ENULL_ARG = "ENULL_ARG";
const char *const CLDI_ERRNAME_ENULL_SELF = "ENULL_SELF";
const char *const CLDI_ERRNAME_EINVALID_ATTR = "EINVALID_ATTR";
const char *const CLDI_ERRNAME_EINVALID_ARG = "EINVALID_ARG";
const char *const CLDI_ERRNAME_EINVALID_SELF = "EINVALID_SELF";
const char *const CLDI_ERRNAME_ENO_ACCESS = "ENO_ACCESS";
const char *const CLDI_ERRNAME_ENOT_READABLE = "ENOT_READABLE";
const char *const CLDI_ERRNAME_ENOT_WRITABLE = "ENOT_WRITABLE";
const char *const CLDI_ERRNAME_ENOT_EXECUTABLE = "ENOT_EXECUTABLE";
const char *const CLDI_ERRNAME_ENONEXISTENT = "ENONEXISTENT";
const char *const CLDI_ERRNAME_EINCOMPATIBLE_TYPE = "EINCOMPATIBLE_TYPE";
const char *const CLDI_NO_ERRDESC = "No description provided.";
const char *const CLDI_ERRDESC_WDEFRAG_RECOMMENDED = "Heap defragmentation is recommended.";
const char *const CLDI_ERRDESC_WLVL3 = "<Warning-Level-3>";
const char *const CLDI_ERRDESC_WLVL2 = "<Warning-Level-2>";
const char *const CLDI_ERRDESC_WLVL1 = "<Warning-Level-1>";
const char *const CLDI_ERRDESC_SUCCESS = "No error occurred.";
const char *const CLDI_ERRDESC_WLVL0 = "<Warning-Level-0>";
const char *const CLDI_ERRDESC_TRUE = "Status evaluates to true.";
const char *const CLDI_ERRDESC_CMPE = "Comparison evaluates terms as equal.";
const char *const CLDI_ERRDESC_FALSE = "Status evaluates to false.";
const char *const CLDI_ERRDESC_CMPL = "Comparison evaluates term as less.";
const char *const CLDI_ERRDESC_CMPG = "Comparison evaluates term as greater.";
const char *const CLDI_ERRDESC_EUNKNOWN = "Unknown error occurred.";
const char *const CLDI_ERRDESC_ENO_IMPL = "No implementation provided for this operation.";
const char *const CLDI_ERRDESC_EOUT_OF_MEMORY = "System or application ran out of usable memory.";
const char *const CLDI_ERRDESC_EDEFRAG_REQUIRED = "Heap defragmentation is required.";
const char *const CLDI_ERRDESC_ETOO_FEW_ARGS = "Not enough arguments were given for this operation";
const char *const CLDI_ERRDESC_EOVERFLOW = "Operation produced an overflowing result (out of bounds or undefined).";
const char *const CLDI_ERRDESC_EOVERFLOW_ARG = "Argument is an overflowed value (out of bounds or undefined).";
const char *const CLDI_ERRDESC_EOVERFLOW_ATTR = "An attribute of self is an overflowed value (out of bounds or undefined).";
const char *const CLDI_ERRDESC_ENULL_ATTR = "A required attribute of self is null.";
const char *const CLDI_ERRDESC_ENULL_ARG = "A non-optional argument was given as null.";
const char *const CLDI_ERRDESC_ENULL_SELF = "Self is constructed with null data, this operation cannot continue.";
const char *const CLDI_ERRDESC_EINVALID_ATTR;
const char *const CLDI_ERRDESC_EINVALID_ARG = "An argument was passed as an invalid value.";
const char *const CLDI_ERRDESC_EINVALID_SELF = "Self is constructed with invalid data, this operation cannot continue.";
const char *const CLDI_ERRDESC_ENO_ACCESS = "Access is denied for this operation.";
const char *const CLDI_ERRDESC_ENOT_READABLE = "Data is not readable; Attempted read of non-readable data.";
const char *const CLDI_ERRDESC_ENOT_WRITABLE = "Data is not writable; Attempted write on non-writable data. ";
const char *const CLDI_ERRDESC_ENOT_EXECUTABLE = "Data is not executable; Attempted call on non-executable data.";
const char *const CLDI_ERRDESC_ENONEXISTENT = "Attempted to reference a nonexistent entry.";
const char *const CLDI_ERRDESC_EINCOMPATIBLE_TYPE = "Attempted conflation of incompatible or inconvertable data types.";

cldiexc_t CLDI_ERROR = (cldiexception_t){
	.ec       = CLDI_SUCCESS,
	.serialid = 0,
	.function = NULL,
	.exc_name = "SUCCESS",
	.exc_desc = "No error occurred."
};

const char* cldiGetErrorName(CLDISTAT e)
{
	switch (e)
	{
		case CLDI_WDEFRAG_RECOMMENDED:
			return "WDEFRAG_RECOMMENDED";

		case CLDI_SUCCESS:
			return "SUCCESS";
		case CLDI_FALSE:
			return "FALSE";

		default:
		case CLDI_EUNKNOWN:
			return "EUNKNOWN";

		case CLDI_ENO_IMPL:
			return "ENO_IMPL";

		case CLDI_EOUT_OF_MEMORY:
			return "EOUT_OF_MEMORY";
		case CLDI_EDEFRAG_REQUIRED:
			return "EDEFRAG_REQUIRED";

		case CLDI_ENULL_ATTR:
			return "ENULL_ATTR";
		case CLDI_ENULL_ARG:
			return "ENULL_ARG";
		case CLDI_ENULL_SELF:
			return "ENULL_SELF";
		case CLDI_EINVALID_ATTR:
			return "EINVALID_ATTR";
		case CLDI_EINVALID_ARG:
			return "EINVALID_ARG";
		case CLDI_EINVALID_SELF:
			return "EINVALID_SELF";
	}
}
const char* cldiGetErrnoName()
{
	return cldiGetErrorName(CLDI_ERRNO);
}

bool cldiStatWarning(CLDISTAT e)
{
	CLDI_ERRNO = e;
	return CLDI_STAT_ISWARNING(e);
}
bool cldiIsWarning()
{
	return CLDI_STAT_ISWARNING(CLDI_ERRNO);
}

bool cldiStatError(CLDISTAT e)
{
	CLDI_ERRNO = e;
	return CLDI_STAT_ISERROR(e);
}
bool cldiIsError()
{
	return CLDI_STAT_ISERROR(CLDI_ERRNO);
}

bool cldiStatSuccess(CLDISTAT e)
{
	CLDI_ERRNO = e;
	return CLDI_STAT_ISSUCCESS(e);
}
bool cldiIsSuccess()
{
	return CLDI_STAT_ISSUCCESS(CLDI_ERRNO);
}

bool cldiStatPermissible(CLDISTAT e)
{
	CLDI_ERRNO = e;
	return CLDI_STAT_ISPERMISSIBLE(e);
}
bool cldiIsPermissible()
{
	return CLDI_STAT_ISPERMISSIBLE(CLDI_ERRNO);
}

cldiexc_t cldierrec(CLDISTAT __ec)
{
	return (cldiexc_t) {
		.exc_name=cldiGetErrorName(__ec),
		.exc_desc=CLDI_NO_ERRDESC,
		.function=NULL,
		.ec=__ec,
		.serialid = 0
	};
}
cldiexc_t cldierr(CLDISTAT __ec, const char *desc)
{
	return (cldiexc_t) {
		.exc_name=cldiGetErrorName(__ec),
		.exc_desc=desc,
		.function=NULL,
		.ec=__ec,
		.serialid = 0
	};
}
cldiexc_t cldinerr(CLDISTAT __ec, const char *name, const char *desc)
{
	return (cldiexc_t) {
		.exc_name=name,
		.exc_desc=desc,
		.function=NULL,
		.ec=__ec,
		.serialid = 0
	};
}
cldiexc_t cldierrf(CLDISTAT __ec, void *func, const char *desc)
{
	return (cldiexc_t) {
		.exc_name=cldiGetError(__ec),
		.exc_desc=desc,
		.function=func,
		.ec=__ec,
		.serialid = 0
	};
}
cldiexc_t cldinerrf(CLDISTAT __ec, void *func, const char *name, const char *desc)
{
	return (cldiexc_t) {
		.exc_name=name,
		.exc_desc=desc,
		.function=func,
		.ec=__ec,
		.serialid = 0
	};
}

// Throws an exception without copying it to CLDI_ERROR, this is used internally,
// and for this file only.
void _cldithrowexc(cldiexc_t *exc)
{
	// THIS CODE IS DUE TO CHANGE ONCE THREAD-SAFE IO FUNCTIONS ARE ADDED

	if (exc != NULL) {
		const CLDISTAT ec = exc->ec;
		if (CLDI_STAT_NOTSUCCESS(ec)) {
			const char *excname = (exc->exc_name == NULL)? cldiGetErrorName(ec) : exc->exc_name;
			const char *excdesc = (exc->exc_desc == NULL)? cldiGetErrorDesc(ec) : exc->exc_desc;

			// continue error message with error name, desc, and code
			fprintf(stderr, "Encountered an exception with code %d (%s):\n", ec, excname);
			// function is specified, print first traceback message.
			if (exc->function != NULL)
				fprintf(stderr, "\tIn function <%p>: %s\n", exc->function, excdesc);
			// else, just print error description
			else
				fprintf(stderr, "\t%s\n", excdesc);
		}
	} else {
		fprintf(stderr, "Attempt was made to throw nullptr as exception...\n");
	}
}
cldiexc_t* cldithrowec(CLDISTAT __ec)
{
	cldiexc_t e = cldierrec(__ec);

	cldithrow(&e);

	return &CLDI_ERROR;
}
cldiexc_t* cldithrowd(CLDISTAT __ec, const char *desc)
{
	cldiexc_t e = cldierr(__ec, desc);

	cldithrow(&e);

	return &CLDI_ERROR;
}
cldiexc_t* cldinthrow(CLDISTAT __ec, const char *name, const char *desc)
{
	cldiexc_t e = cldinerr(__ec, name, desc);

	cldithrow(&e);

	return &CLDI_ERROR;
}
cldiexc_t* cldithrowf(CLDISTAT __ec, void *func, const char *desc)
{
	cldiexc_t e = cldierrf(__ec, func, desc);

	cldithrow(&e);

	return &CLDI_ERROR;
}
cldiexc_t* cldinthrowf(CLDISTAT __ec, void *func, const char *name, const char *desc)
{
	cldiexc_t e = cldinerrf(__ec, func, name, desc);

	cldithrow(&e);

	return &CLDI_ERROR;
}
cldiexc_t* cldithrow(cldiexc_t *self)
{
	if (CLDI_ERRNO != CLDI_SUCCESS)
		CLDI_ERROR.serialid++;

	// set the current error to self
	CLDI_ERROR.exc_name = self->exc_name;
	CLDI_ERROR.exc_desc = self->exc_desc;
	CLDI_ERROR.function = self->function;
	CLDI_ERROR.ec       = self->ec;

	_cldithrowexc(self);

	return &CLDI_ERROR;
}

void cldiAddTraceback(void *func, const char *desc)
{
	// THIS CODE IS DUE TO CHANGE ONCE THREAD-SAFE IO FUNCTIONS ARE ADDED

	if (!(CLDI_STAT_ISSUCCESS(CLDI_ERRNO))) {
		fprintf(stderr, "\tIn function <%p>: %s\n", func, desc);
	}
}

CLDISTAT cldiExcGetErrno(const cldiexc_t *self)
{
	if (self == NULL)
		return CLDI_ENULL_ARG;
	else
		return self->ec;
}
void* cldiExcGetFunction(const cldiexc_t *self)
{
	if (self == NULL)
		return CLDI_ENULL_ARG;
	else
		return self->function;
}
const char* cldiExcGetName(const cldiexc_t *self)
{
	if (self == NULL)
		return CLDI_ENULL_ARG;
	else
		return self->exc_name;
}
const char* cldiExcGetDesc(const cldiexc_t *self)
{
	if (self == NULL)
		return CLDI_ENULL_ARG;
	else
		return self->exc_desc;
}
unsigned long long cldiExcGetSerial(const cldiexc_t *self)
{
	return (self == NULL)? 0 : self->serialid;
}
bool cldiExcSpecifiesFunction(const cldiexc_t *self)
{
	if (self == NULL)
		return false;
	else
		return self->function != NULL;
}
cldiexc_t*  cldiExcClear(cldiexc_t *self)
{
	if (self != NULL) {
		if (self->ec != CLDI_SUCCESS) {
			self->serialid++;
			self->ec = CLDI_SUCCESS;
		}
		self->exc_name = CLDI_ERRNAME_SUCCESS;
		self->exc_desc = CLDI_ERRDESC_SUCCESS;
		self->function = NULL;
	}
	return self;
}

bool cldiExcIsWarning(const cldiexc_t *self)
{
	if (self == NULL)
		return false;
	else
		return CLDI_STAT_ISWARNING(self->ec);
}
bool cldiExcIsError(const cldiexc_t *self)
{
	if (self == NULL)
		return false;
	else
		return CLDI_STAT_ISERROR(self->ec);
}
bool cldiExcIsSuccess(const cldiexc_t *self)
{
	if (self == NULL)
		return false;
	else
		return CLDI_STAT_ISSUCCESS(self->ec);
}
bool cldiExcIsPermissible(const cldiexc_t *self)
{
	if (self == NULL)
		return false;
	else
		return CLDI_STAT_ISPERMISSIBLE(self->ec);
}
bool cldiExcNotWarning(const cldiexc_t *self)
{
	if (self == NULL)
		return true;
	else
		return CLDI_STAT_NOTWARNING(self->ec);
}
bool cldiExcNotError(const cldiexc_t *self)
{
	if (self == NULL)
		return true;
	else
		return CLDI_STAT_NOTERROR(self->ec);
}
bool cldiExcNotSuccess(const cldiexc_t *self)
{
	if (self == NULL)
		return true;
	else
		return CLDI_STAT_NOTSUCCESS(self->ec);
}
bool cldiExcNotPermissible(const cldiexc_t *self)
{
	if (self == NULL)
		return true;
	else
		return CLDI_STAT_NOTPERMISSIBLE(self->ec);
}


