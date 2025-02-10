


/* Implementing: cldi-head: setup/types.h */
#include <cldi/head/setup/types.h>



cldipid_t cldiGetCurrentPID()
{
#if CLDI_PLATFORM_UNIXLIKE == true
	return getpid();
#elif CLDI_PLATFORM == CLDI_WINDOWS
	return GetCurrentPID();
#else
#   error "cldi-head: GetCurrentPID() has no implementation on this system, report this problem to the developer."
#endif
}


const clditypeinfo_t cldiTypeInfoNull = {
	.size = 0,
	.templ = CLDI_NULL_TYPE
};
const clditypeinfo_t cldiTypeInfoChar = {
	.size = sizeof(char),
	.templ = CLDI_INT_TYPE
};
const clditypeinfo_t cldiTypeInfoWChar = {
	.size = sizeof(wchar_t),
	.templ = CLDI_INT_TYPE
};
const clditypeinfo_t cldiTypeInfoShort = {
	.size = sizeof(short),
	.templ = CLDI_INT_TYPE
};
const clditypeinfo_t cldiTypeInfoInt = {
	.size = sizeof(int),
	.templ = CLDI_INT_TYPE
};
const clditypeinfo_t cldiTypeInfoLong = {
	.size = sizeof(long),
	.templ = CLDI_INT_TYPE
};
const clditypeinfo_t cldiTypeInfoLLong = {
	.size = sizeof(long long),
	.templ = CLDI_INT_TYPE
};
const clditypeinfo_t cldiTypeInfoSize_t = {
	.size = sizeof(size_t),
	.templ = CLDI_INT_TYPE
};
const clditypeinfo_t cldiTypeInfoFloat = {
	.size = sizeof(float),
	.templ = CLDI_FLOAT_TYPE
};
const clditypeinfo_t cldiTypeInfoDouble = {
	.size = sizeof(double),
	.templ = CLDI_FLOAT_TYPE
};
const clditypeinfo_t cldiTypeInfoFPM = {
	.size = sizeof(cldifpm_t),
	.templ = CLDI_FLOAT_TYPE
};
// Only if long double is enabled, create template for long double.
#if CLDI_LDBL_ENABLED == true
	const clditypeinfo_t cldiTypeInfoLDouble = {
		.size = sizeof(long double),
		.templ = CLDI_FLOAT_TYPE
	};
#endif
const clditypeinfo_t cldiTypeInfoPtr = {
	.size = sizeof(char*),
	.templ = CLDI_PTR_TYPE
};


