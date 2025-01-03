
#ifndef _cldi__setup_PLATFORM_H
#define _cldi__setup_PLATFORM_H 1

#include "prerequisites.h"

#ifdef __cplusplus
extern "C" {
#endif



/* Arhitecture Enumeration Types */
#include "platform/architecture_ENUM.h"
/* Data Model Enumeration Types */
#include "platform/cpudm_ENUM.h"
/* Platform & Arhitecture Width Enumeration Types */
#include "platform/platform_ENUM.h"

/* Detect CPU architecture. */
#include "platform/architecture.h"
/* Detect CPU Data Model. */
#include "platform/data-model.h"
/* Detect the current platform. */
#if defined(__CLDI_PLATFORM) && __CLDI_PLATFORM == CLDI_PLATFORM_UNKNOWN
#	include "platform/stdlib.h"
#elif defined(_WIN32) || (defined(__CLDI_PLATFORM) && __CLDI_PLATFORM == CLDI_PLATFORM_WINDOWS)
#	include "platform/windows.h"
#elif (defined(_WORDSIZE) && (defined(__linux__) || defined(__ANDROID__))) || (defined(__CLDI_PLATFORM) && (__CLDI_PLATFORM==CLDI_PLATFORM_LINUX||__CLDI_PLATFORM==CLDI_PLATFORM_ANDROID))
#	include "platform/linux.h"
#elif (defined(_WORDSIZE) && (defined(macintosh) || defined(Macintosh) || (defined(__APPLE__) && defined(__MACH__)))) || (defined(__CLDI_PLATFORM) && __CLDI_PLATFORM == CLDI_PLATFORM_MACOS)
#	include "platform/macos.h"
#elif (defined(_WORDSIZE) && defined(__FreeBSD__)) || (defined(__CLDI_PLATFORM) && __CLDI_PLATFORM == CLDI_PLATFORM_FREEBSD)
#	include "platform/bsd/freebsd.h"
#elif (defined(_WORDSIZE) && defined(__NetBSD__))  || (defined(__CLDI_PLATFORM) && __CLDI_PLATFORM == CLDI_PLATFORM_NETBSD)
#	include "platform/bsd/netbsd.h"
#elif (defined(_WORDSIZE) && defined(__OpenBSD__)) || (defined(__CLDI_PLATFORM) && __CLDI_PLATFORM == CLDI_PLATFORM_OPENBSD)
#	include "platform/bsd/openbsd.h"
#elif (defined(_WORDSIZE) && (defined(__unix) || defined(__unix__))) || (defined(__CLDI_PLATFORM) && __CLDI_PLATFORM == CLDI_PLATFORM_UNIX)
#	pragma warn("CLDI: head:setup/platform: CLDI could not detect or does not explicitly support the current (unix-like) platform, attempting to load with awareness of Unix-like functionality alone.")
#	include "platform/unix.h"
#else
#	pragma warn("CLDI: head:setup/platform: CLDI could not detect or does not explicitly support the current platform, attempting to load with the C library alone.")
#	include "platform/stdlib.h"
#endif
#ifndef __CLDI_PLATFORM
#	define __CLDI_PLATFORM CLDI_PLATFORM_UNKNOWN
#endif
#ifndef _cldi_USING_GLIBC
#	if (defined(__GNU_LIBRARY__) && defined(__GNU_LIBRARY_MINOR__)) || (defined(__GLIBC__) && defined(__GLIBC_MINOR__))
#		define _cldi_USING_GLIBC true
#	else
#		define _cldi_USING_GLIBC false
#	endif
#endif
#ifndef __CLDI_PLATFORM_UNIXLIKE
#	define __CLDI_PLATFORM_UNIXLIKE false
#endif
#ifndef _cldi_BSD_PLATFORM
#	define _cldi_BSD_PLATFORM false
#endif



#ifdef __cplusplus
}

namespace ciahlldi
{
	namespace cldi
	{
		/* Import C code elements to C++ namespace */

		/* A field for whether or not the GNU C Library is present. */
		constexpr bool USING_GLIBC          = _cldi_USING_GLIBC;
		/* A field for whether or not the current platform is Unix-like. */
		constexpr bool PLATFORM_IS_UNIXLIKE = __CLDI_PLATFORM_UNIXLIKE;
		/* A field for whether or not the current platform is a BSD platform. */
		constexpr bool PLATFORM_IS_BSD      = _cldi_BSD_PLATFORM;

		/* Platform flag enum */
		typedef CLDI_PLATFORM PLATFORM;

		/* A flag constant for the detected architecture width. */
		constexpr PLATFORM DETECTED_PLATFORM = __CLDI_PLATFORM;

		constexpr PLATFORM PLATFORM_WINDOWS  = CLDI_PLATFORM_WINDOWS;
			/* Platform flag for Windows systems. */
		constexpr PLATFORM PLATFORM_MAC      = CLDI_PLATFORM_MAC;
			/* Platform flag for MacOS. */
		constexpr PLATFORM PLATFORM_LINUX    = CLDI_PLATFORM_LINUX;
			/* Platform flag for Linux systems. */
		constexpr PLATFORM PLATFORM_ANDROID  = CLDI_PLATFORM_ANDROID;
			/* Platform flag for Android devices. */
		constexpr PLATFORM PLATFORM_FREEBSD  = CLDI_PLATFORM_FREEBSD;
			/* Platform flag for any FreeBSD systems. */
		constexpr PLATFORM PLATFORM_NETBSD   = CLDI_PLATFORM_NETBSD;
			/* Platform flag for any NetBSD systems. */
		constexpr PLATFORM PLATFORM_OPENBSD  = CLDI_PLATFORM_OPENBSD;
			/* Platform flag for any OpenBSD systems. */
		constexpr PLATFORM PLATFORM_UNIX     = CLDI_PLATFORM_UNIX;
			/* Platform flag for any other unix or unix-like system. */
		constexpr PLATFORM PLATFORM_UNKNOWN  = CLDI_PLATFORM_UNKNOWN;

		/* Architecture width enum */
		typedef CLDI_ARCHSIZE ARCHSIZE;

		/* A flag constant for the detected architecture width. */
		constexpr ARCHSIZE DETECTED_ARCHSIZE = __CLDI_ARCHSIZE;

		constexpr ARCHSIZE PLATFORM_64BIT    = CLDI_PLATFORM_64BIT;
			/* Flag for 64-bit systems. */
		constexpr ARCHSIZE PLATFORM_32BIT    = CLDI_PLATFORM_32BIT;
			/* Flag for 32-bit systems. */


		/* Architecture flag enum */
		typedef CLDI_ARCHITECTURE ARCHITECTURE;

		/* A flag constant for the detected architecture. */
		constexpr ARCHITECTURE DETECTED_ARCHITECTURE = __CLDI_ARCHITECTURE;

		constexpr ARCHITECTURE ARCH_X86   = CLDI_ARCH_X86;
			/* Architecture flag for x86 and AMD64 systems. */
		constexpr ARCHITECTURE ARCH_ARM   = CLDI_ARCH_ARM;
			/* Architecture flag for ARM systems. */
		constexpr ARCHITECTURE ARCH_ALPHA = CLDI_ARCH_ALPHA;
			/* Architecture flag for Alpha-based systems. */

		/* CPU Data Model flag enum */
		typedef CLDI_CPUDM CPUDM;
		using   CPU_DATA_MODEL = CLDI_CPUDM;

		/* A flag constant for the detected processor data model. */
		constexpr CPUDM DETECTED_CPU_DATA_MODEL = __CLDI_CPUDM;

		constexpr CPUDM CPUDM_LP32  = CLDI_CPUDM_LP32;
			/* Flag for LP32 processors. */
		constexpr CPUDM CPUDM_ILP32 = CLDI_CPUDM_ILP32;
			/* Flag for ILP32 processors. */
		constexpr CPUDM CPUDM_LP64  = CLDI_CPUDM_LP64;
			/* Flag for LP64 processors. */
		constexpr CPUDM CPUDM_XLP64 = CLDI_CPUDM_XLP64;
			/* Flag for LLP64, ILP64, and SLP64 processors. */
	}
}

#endif

#endif /* _cldi__setup_PLATFORM_H */
