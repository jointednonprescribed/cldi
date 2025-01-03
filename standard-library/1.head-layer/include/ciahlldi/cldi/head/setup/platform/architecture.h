
#ifndef _cldi_head__setup_platform_ARCHITECTURE_H
#define _cldi_head__setup_platform_ARCHITECTURE_H 1

#include "../prerequisites.h"

/* Requires structure: cldi-head: setup/platform/arch */
#include "architecture_ENUM.h"


/* x86 or AMD64 architecture */
#if defined(__amd64__)||defined(__amd64) ||defined(__x86_64__)||defined(__x86_64)|| defined(_M_AMD64) ||defined(_M_x64)  ||defined(_M_IX86)   ||defined(i386)||defined(__i386)|| defined(__i386__) ||defined(__i486__)||defined(__i586__)  ||defined(__i686__)|| defined(__IA32__) ||defined(__X86__) ||defined(_X86_)     ||defined(__I86__) || defined(__386__)  ||defined(__THW_INTEL__) || defined(__INTEL__)
#	define __CLDI_ARCHITECTURE CLDI_ARCH_X86
/* ARM or ARM64 (AArch64) architecture */
#elif defined(__arm__)||defined(__arm)||defined(__aarch64__)||defined(_ARM)||defined(_M_ARM)|| defined(__thumb__)||defined(_M_ARMT)||defined(__TARGET_ARCH_ARM)|| defined(__TARGET_ARCH_THUMB)
#	define __CLDI_ARCHITECTURE CLDI_ARCH_ARM
	/* Alpha architecture */
#elif defined(__alpha__)||defined(__alpha)||defined(_M_ALPHA)
#	define __CLDI_ARCHITECTURE CLDI_ARCH_ALPHA
#else
#	pragma warn("CLDI: head:setup/platform: CLDI could not detect or does not explicitly support CPU architecture, setting `__CLDI_ARCHITECTURE` undefined.")
#endif


#endif /* _cldi_head__setup_platform_ARCHITECTURE_H */
