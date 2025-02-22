
#ifndef _cldi_head__setup_STAT_HPP
#define _cldi_head__setup_STAT_HPP 1

#ifndef _cldi_head__setup_STAT_H
#	include "../stat.h"
#endif

#if CLDI_C_ONLY == false



namespace cldi
{
	using STAT   = ::CLDISTAT;
	using stat_t = ::CLDISTAT;

	constexpr STAT WDEFRAG_RECOMMENDED = ::CLDI_WDEFRAG_RECOMMENDED;

	constexpr STAT WLVL3 = ::CLDI_WLVL3;
	constexpr STAT WLVL2 = ::CLDI_WLVL2;
	constexpr STAT WLVL1 = ::CLDI_WLVL1;
	constexpr STAT WLVL0 = ::CLDI_WLVL0;

	constexpr STAT SUCCESS = ::CLDI_SUCCESS;
	constexpr STAT TRUE = ::CLDI_TRUE;
	constexpr STAT FALSE = ::CLDI_FALSE;

	constexpr STAT EUNKNOWN = ::CLDI_EUNKNOWN;

	constexpr STAT ENO_IMPL = ::CLDI_ENO_IMPL;

	constexpr STAT EOUT_OF_MEMORY = ::CLDI_EOUT_OF_MEMORY;
	constexpr STAT EDEFRAG_REQUIRED = ::CLDI_EDEFRAG_REQUIRED;

	constexpr STAT ENULL_ATTR = ::CLDI_ENULL_ATTR;
	constexpr STAT ENULL_ARG = ::CLDI_ENULL_ARG;
	constexpr STAT ENULL_SELF = ::CLDI_ENULL_SELF;
	constexpr STAT EINVALID_ATTR = ::CLDI_EINVALID_ATTR;
	constexpr STAT EINVALID_ARG = ::CLDI_EINVALID_ARG;
	constexpr STAT EINVALID_SELF = ::CLDI_EINVALID_SELF;

	constexpr STAT ENO_ACCESS = ::CLDI_ENO_ACCESS;
	constexpr STAT ENOT_READABLE = ::CLDI_ENOT_READABLE;
	constexpr STAT ENOT_WRITABLE = ::CLDI_ENOT_WRITABLE;
	constexpr STAT ENOT_EXECUTABLE = ::CLDI_ENOT_EXECUTABLE;
	constexpr STAT ENONEXISTENT = ::CLDI_ENONEXISTENT;

	constexpr STAT EINCOMPATIBLE_TYPE = ::CLDI_EINCOMPATIBLE_TYPE;

	using CSTDLIB_ERRCONTEXT = ::CLDI_CSTDLIB_ERRCONTEXT;

	constexpr CSTDLIB_ERRCONTEXT CSTDEC_PRINTF = ::CLDI_CSTDEC_PRINTF;
	constexpr CSTDLIB_ERRCONTEXT CSTDEC_VPRINTF = ::CLDI_CSTDEC_VPRINTF;
	constexpr CSTDLIB_ERRCONTEXT CSTDEC_FPRINTF = ::CLDI_CSTDEC_FPRINTF;
	constexpr CSTDLIB_ERRCONTEXT CSTDEC_VFPRINTF = ::CLDI_CSTDEC_VFPRINTF;
	constexpr CSTDLIB_ERRCONTEXT CSTDEC_SPRINTF = ::CLDI_CSTDEC_SPRINTF;
	constexpr CSTDLIB_ERRCONTEXT CSTDEC_SNPRINTF = ::CLDI_CSTDEC_SNPRINTF;
	constexpr CSTDLIB_ERRCONTEXT CSTDEC_VSPRINTF = ::CLDI_CSTDEC_VSPRINTF;
	constexpr CSTDLIB_ERRCONTEXT CSTDEC_VSNPRINTF = ::CLDI_CSTDEC_VSNPRINTF;
	constexpr CSTDLIB_ERRCONTEXT CSTDEC_VASPRINTF = ::CLDI_CSTDEC_VASPRINTF;
	constexpr CSTDLIB_ERRCONTEXT CSTDEC_ASPRINTF = ::CLDI_CSTDEC_ASPRINTF;
	constexpr CSTDLIB_ERRCONTEXT CSTDEC_VDPRINTF = ::CLDI_CSTDEC_VDPRINTF;
	constexpr CSTDLIB_ERRCONTEXT CSTDEC_DPRINTF = ::CLDI_CSTDEC_DPRINTF;

	inline STAT &ERRNO = CLDI_ERRNO;

	/* Function for converting C++ standard library errors into CLDISTAT error
	.  codes. */
	template <typename _E>
	CLDISTAT ConvCppStdlibError(CSTDLIB_ERRCONTEXT error_context, _E error)
	{
		static_assert(
			std::is_base_of<std::exception, _E>::value,
			"cldi-head: cldi::ConvCppStdlibError() can only be used with type argument of std::exception or child classes of such."
		);
		switch (error_context)
		{
			default:
				return EUNKNOWN;
		}
	}

	inline CLDISTAT    (&ConvCStdlibError)(CSTDLIB_ERRCONTEXT, int) = ::cldiConvCStdlibError;
	inline CLDISTAT    (&ConvCStdlibErrno)(CSTDLIB_ERRCONTEXT) = ::cldiConvCStdlibErrno;
	inline const char* (&GetErrorName)(STAT) = ::cldiGetErrorName;
	inline const char* (&GetErrnoName)() = ::cldiGetErrnoName;
	inline bool        (&StatWarning)(STAT) = ::cldiStatWarning;
	inline bool        (&IsWarning)() = ::cldiIsWarning;
	inline bool        (&StatError)(STAT) = ::cldiStatError;
	inline bool        (&IsError)() = ::cldiIsError;
	inline bool        (&StatSuccess)(STAT) = ::cldiStatSuccess;
	inline bool        (&IsSuccess)() = ::cldiIsSuccess;
	inline bool        (&StatPermissible)(STAT) = ::cldiStatPermissible;
	inline bool        (&IsPermissible)() = ::cldiIsPermissible;
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



#endif // CLDI_C_ONLY == false

#endif // _cldi_head__setup_STAT_HPP
