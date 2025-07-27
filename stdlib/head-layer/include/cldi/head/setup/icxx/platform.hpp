
#ifndef _cldi_head__setup_PLATFORM_HPP
#define _cldi_head__setup_PLATFORM_HPP 1

#ifndef _cldi_head__setup_PLATFORM_H
#	include "../platform.h"
#endif

#if CLDI_C_ONLY == false



namespace cldi
{
	typedef int platform_t;
	constexpr platform_t UNKNOWN_PLATFORM     = CLDI_PLATFORM_UNKNOWN;
	constexpr platform_t WINDOWS              = CLDI_WINDOWS;
	constexpr platform_t LINUX                = CLDI_LINUX;
	constexpr platform_t OSX                  = CLDI_OSX;
	constexpr platform_t BSD                  = CLDI_BSD;
	constexpr platform_t ANDROID              = CLDI_ANDROID;
	constexpr platform_t IOS                  = CLDI_IOS;
	constexpr platform_t WASM                 = CLDI_WASM;

	typedef int compiler_t;
	constexpr compiler_t UNKNOWN_COMPILER     = CLDI_UNKNOWN_COMPILER;
	constexpr compiler_t UNKNOWN_COMP         = CLDI_UNKNOWN_COMPILER;
	constexpr compiler_t GCC                  = CLDI_GCC;
	constexpr compiler_t MSVC                 = CLDI_MSVC;
	constexpr compiler_t CLANG                = CLDI_CLANG;
	constexpr compiler_t WASM_COMPILER        = CLDI_WASM_COMPILER;
	constexpr compiler_t WASM_COMP            = CLDI_WASM_COMPILER;

	typedef int arch_t;
	constexpr arch_t     UNKNOWN_ARCHITECTURE = CLDI_UNKNOWN_ARCHITECTURE;
	constexpr arch_t     UNKNOWN_ARCH         = CLDI_UNKNOWN_ARCHITECTURE;
	constexpr arch_t     x86                  = CLDI_X86;
	constexpr arch_t     X86                  = CLDI_X86;
	constexpr arch_t     ARM                  = CLDI_ARM;
	constexpr arch_t     POWERPC              = CLDI_POWERPC;
	constexpr arch_t     PPC                  = CLDI_POWERPC;
	constexpr arch_t     WASM_ARCH            = CLDI_WASM_ARCH;

	constexpr bool       PLATFORM_UNIXLIKE    = CLDI_PLATFORM_UNIXLIKE;
	constexpr bool       PLATFORM32           = CLDI_PLATFORM32;
	constexpr platform_t PLATFORM             = CLDI_PLATFORM;
	constexpr compiler_t COMPILER             = CLDI_COMPILER;
	constexpr arch_t     ARCHITECTURE         = CLDI_ARCH;
}



#endif // CLDI_C_ONLY == false

#endif // _cldi_head__setup_PLATFORM_HPP
