
#ifndef _cldi_head__setup_PLATFORM_H
#define _cldi_head__setup_PLATFORM_H 1

#include "../settings.h"



/* Platform Information types */

#ifdef __cplusplus
extern "C" {
#endif

/* Platform Selection enum */
typedef enum _CLDIPLATFORM
{
	CLDI_PLATFORM_UNKNOWN=0,
	CLDI_WINDOWS,
	CLDI_LINUX,
	CLDI_OSX,
	CLDI_BSD,
	CLDI_ANDROID,
	CLDI_IOS,
	CLDI_WASM,
} cldiplatform_t;

/* Compiler Selection enum */
typedef enum _CLDICOMPILER
{
	CLDI_UNKNOWN_COMPILER=0,
	CLDI_GCC,
	CLDI_MSVC,
	CLDI_CLANG,
	CLDI_WASM_COMPILER,
	CLDI_WASM_COMP=CLDI_WASM_COMPILER,
} cldicompiler_t;

/* Architecture Selection enum */
typedef enum _CLDIARCHITECTURE
{
	CLDI_UNKNOWN_ARCHITECTURE=0,
	CLDI_UNKNOWN_ARCH=CLDI_UNKNOWN_ARCHITECTURE,
	CLDI_X86,
	CLDI_x86 = CLDI_X86,
	CLDI_ARM,
	CLDI_POWERPC,
	CLDI_PPC = CLDI_POWERPC,
	CLDI_WASM_ARCH,
} cldiarch_t;

#ifdef __cplusplus
}
#endif


/* Detect Windows System */
#ifdef _WIN32
#	define CLDI_PLATFORM_UNIXLIKE  false
#	define CLDI_PLATFORM           CLDI_WINDOWS
#	ifdef _WIN64
#		define CLDI_PLATFORM32 false
#	else
#		define CLDI_PLATFORM32 true
#	endif

/* Detect Linux System */
#elif defined(__linux) || defined(__linux__) || defined(__gnu_linux__)
#	define CLDI_PLATFORM_UNIXLIKE true
	/* Detect Android System. */
#	ifdef __ANDROID__
#		define CLDI_PLATFORM CLDI_ANDROID
#	else
#		define CLDI_PLATFORM CLDI_LINUX
#	endif
#	if !defined (__WORDSIZE) || __WORDSIZE == 64
#		define CLDI_PLATFORM32 false
#	else
#		define CLDI_PALTFORM32 true
#	endif

/* Detect OSX System */
#elif defined(__APPLE__) && defined(__MACH__)
#	define CLDI_PLATFORM_UNIXLIKE true
#	define CLDI_PLATFORM          CLDI_OSX
#	if !defined (__WORDSIZE) || __WORDSIZE == 64
#		define CLDI_PLATFORM32 false
#	else
#		define CLDI_PALTFORM32 true
#	endif

/* Detect BSD System */
#elif defined(__bsd__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__FreeBSD__)
#	define CLDI_PLATFORM_UNIXLIKE true
#	define CLDI_PLATFORM          CLDI_BSD
#	if !defined (__WORDSIZE) || __WORDSIZE == 64
#		define CLDI_PLATFORM32 false
#	else
#		define CLDI_PALTFORM32 true
#	endif

/* Detect Other System */
#elif defined(__unix) || defined(__unix__)
#	define CLDI_PLATFORM_UNIXLIKE true
#	define CLDI_PLATFORM          CLDI_UNIX
#	if !defined (__WORDSIZE) || __WORDSIZE == 64
#		define CLDI_PLATFORM32 false
#	else
#		define CLDI_PALTFORM32 true
#	endif

/* Detect Browser-Integrated C/C++ WebAssembly Target */

/* Unsupported platform, so throw error. */
#else
#	define CLDI_PLATFORM          CLDI_UNKNOWN_PLATFORM
#	define CLDI_PLATFORM32        false
#	define CLDI_PLATFORM_UNIXLIKE false
#	error "CLDI: Compiling on an unsupported or unrecognized platform, terminating compilation..."
#endif

#if !defined(CLDI_COMPILER) || CLDI_COMPILER != CLDI_WASM_COMP
/* Detect GCC */
#	ifdef __GNUC__
#		define CLDI_COMPILER CLDI_GCC

/* Detect Microsoft Visual C/C++ */


/* Detect CLang */
#	elif defined(__clang__)
#		define CLDI_COMPILER CLDI_CLANG

/* Detect WebAssembly Compiler */

/* Unsupported compiler, so throw a warning. */
#	else
#		define CLDI_COMPILER CLDI_UNKNOWN_COMPILER
#		pragma warn("CLDI: Warning - Compiling with an unrecognized compiler...")
#	endif
#endif

#if !defined(CLDI_ARCH) || CLDI_ARCH != CLDI_WASM_ARCH
/* Detect x86 Architecture */
#	if defined(__i386__) || defined(__amd64__) || defined(__x86__) || defined(__x86_64__)
#		define CLDI_ARCH CLDI_X86

/* Detect ARM Architecture */
#	elif defined(__arm__) || defined(__aarch64__)
#		define CLDI_ARCH CLDI_ARM

/* Detect PowerPC Architecture */
#	elif defined(__ppc64__) || defined(__powerpc__)
#		define CLDI_ARCH CLDI_POWERPC

/* Unsupported architecture, so throw an error. */
#	else
#		define CLDI_ARCH CLDI_UNKNOWN_ARCHITECTURE
#		error "CLDI: Compiling for unsupported or unrecognized CPU architecture, terminating compilation..."
#	endif
#endif



/* C++ bindings for this file: */
#if CLDI_C_ONLY == false
namespace cldi
{
	using platform_t = cldiplatform_t;
	constexpr platform_t UNKNOWN_PLATFORM     = CLDI_UNKNOWN_PLATFORM;
	constexpr platform_t WINDOWS              = CLDI_WINDOWS;
	constexpr platform_t LINUX                = CLDI_LINUX;
	constexpr platform_t OSX                  = CLDI_OSX;
	constexpr platform_t BSD                  = CLDI_BSD;
	constexpr platform_t ANDROID              = CLDI_ANDROID;
	constexpr platform_t IOS                  = CLDI_IOS;
	constexpr platform_t WASM                 = CLDI_WASM;

	using compiler_t = cldicompiler_t;
	constexpr compiler_t UNKNOWN_COMPILER     = CLDI_UNKNOWN_COMPILER;
	constexpr compiler_t UNKNOWN_COMP         = CLDI_UNKNOWN_COMPILER;
	constexpr compiler_t GCC                  = CLDI_GCC;
	constexpr compiler_t MSVC                 = CLDI_MSVC;
	constexpr compiler_t CLANG                = CLDI_CLANG;
	constexpr compiler_t WASM_COMPILER        = CLDI_WASM_COMPILER;
	constexpr compiler_t WASM_COMP            = CLDI_WASM_COMPILER;

	using arch_t = cldiarch_t;
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
#endif



#endif // _cldi_head__setup_PLATFORM_H
