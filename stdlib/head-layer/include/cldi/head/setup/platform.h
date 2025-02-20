
#ifndef _cldi_head__setup_PLATFORM_H
#define _cldi_head__setup_PLATFORM_H 1

#include "../settings.h"



/* Platform Information types */

/* Platform Selectors */
#define CLDI_PLATFORM_UNKNOWN      0
#define CLDI_WINDOWS               1
#define CLDI_LINUX                 2
#define CLDI_OSX                   3
#define CLDI_BSD                   4
#define CLDI_ANDROID               5
#define CLDI_IOS                   6
#define CLDI_WASM                  7

/* Compiler Selectors */
#define CLDI_UNKNOWN_COMPILER      0
#define CLDI_GCC                   1
#define CLDI_MSVC                  2
#define CLDI_CLANG                 3
#define CLDI_WASM_COMPILER         4
#define CLDI_WASM_COMP             CLDI_WASM_COMPILER

/* Architecture Selectors */
#define CLDI_UNKNOWN_ARCHITECTURE  0
#define CLDI_UNKNOWN_ARCH          CLDI_UNKNOWN_ARCHITECTURE
#define CLDI_X86                   1
#define CLDI_x86                   CLDI_X86
#define CLDI_ARM                   2
#define CLDI_POWERPC               3
#define CLDI_PPC                   CLDI_POWERPC
#define CLDI_WASM_ARCH             4


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


/* Defining a platform-independent macro for __cdecl */
#if CLDI_PLATFORM == CLDI_WINDOWS
#	define __cldi_cdecl(type) __cdecl (type)
#else
#	define __cldi_cdecl(type) (type)
#endif


/* C++ bindings for this file: */
#include "icxx/platform.hpp"



#endif // _cldi_head__setup_PLATFORM_H
