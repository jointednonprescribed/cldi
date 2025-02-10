


/* Implementing cldi-head: setup/stat.h */
#include <cldi/head/setup/stat.h>



CLDISTAT CLDI_ERRNO = CLDI_SUCCESS;


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


