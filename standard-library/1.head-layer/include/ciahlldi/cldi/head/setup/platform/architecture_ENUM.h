
#ifndef _cldi_head__setup_platform_ARCH_H
#define _cldi_head__setup_platform_ARCH_H 1

#ifdef __cplusplus
extern "C" {
#endif


typedef enum _CLDI_ARCHITECTURE_T
{
	CLDI_ARCH_UNKNOWN = 0,

	CLDI_ARCH_X86     = 1,
	CLDI_ARCH_x86     = CLDI_ARCH_X86,

	CLDI_ARCH_ARM     = 2,

	CLDI_ARCH_ALPHA   = 3
}
CLDI_ARCH,         CLDI_ARCH_T,
CLDI_ARCHITECTURE, CLDI_ARCHITECTURE_T;


#ifdef __cplusplus
}
#endif

#endif /* _cldi_head__setup_platform_ARCH_H */
