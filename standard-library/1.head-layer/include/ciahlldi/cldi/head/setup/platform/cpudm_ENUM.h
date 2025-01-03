
#ifndef _cldi_head__setup_platform_CPUDM_H
#define _cldi_head__setup_platform_CPUDM_H 1

#ifdef __cplusplus
extern "C" {
#endif


typedef enum _CLDI_CPUDM_T
{
	CLDI_CPUDM_LP32  = 1,
	CLDI_CPUDM_ILP32 = 2,
	CLDI_CPUDM_LP64  = 3,
	CLDI_CPUDM_XLP64 = 4,
	CLDI_CPUDM_LLP64 = CLDI_CPUDM_XLP64,
	CLDI_CPUDM_ILP64 = CLDI_CPUDM_XLP64,
	CLDI_CPUDM_SLP64 = CLDI_CPUDM_XLP64
} CLDI_CPUDM, CLDI_CPUDM_T;


#ifdef __cplusplus
}
#endif

#endif /* _cldi_head__setup_platform_CPUDM_H */
