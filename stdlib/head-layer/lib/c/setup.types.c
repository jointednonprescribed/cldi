


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


const clditypeinfo_t cldiNullTypeInfo = {
	.size = 0,
	.templ = CLDI_NULL_TYPE
};
const clditypeinfo_t cldiCharTypeInfo = {
	.size = sizeof(char),
	.templ = CLDI_INT_TYPE
};
const clditypeinfo_t cldiWCharTypeInfo = {
	.size = sizeof(wchar_t),
	.templ = CLDI_INT_TYPE
};
const clditypeinfo_t cldiShortTypeInfo = {
	.size = sizeof(short),
	.templ = CLDI_INT_TYPE
};
const clditypeinfo_t cldiIntTypeInfo = {
	.size = sizeof(int),
	.templ = CLDI_INT_TYPE
};
const clditypeinfo_t cldiLongTypeInfo = {
	.size = sizeof(long),
	.templ = CLDI_INT_TYPE
};
const clditypeinfo_t cldiLLongTypeInfo = {
	.size = sizeof(long long),
	.templ = CLDI_INT_TYPE
};
const clditypeinfo_t cldiSizeTypeInfo = {
	.size = sizeof(size_t),
	.templ = CLDI_INT_TYPE
};
const clditypeinfo_t cldiFloatTypeInfo = {
	.size = sizeof(float),
	.templ = CLDI_FLOAT_TYPE
};
const clditypeinfo_t cldiDoubleTypeInfo = {
	.size = sizeof(double),
	.templ = CLDI_FLOAT_TYPE
};
const clditypeinfo_t cldiFPMTypeInfo = {
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


