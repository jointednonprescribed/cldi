
#ifndef _cldi_head__setup_platform_DATA_MODEL_H
#define _cldi_head__setup_platform_DATA_MODEL_H 1

#include "../prerequisites.h"

/* Requires structure: cldi-head: setup/platform/cpudm */
#include "cpudm_ENUM.h"


/* Detect CPU Data Model */
#if defined(_ILP32) || defined(__ILP32__)
#	define __CLDI_CPUDM CLDI_CPUDM_ILP32
#elif __CLDI_ARCHSIZE == CLDI_PLATFORM_32BIT
#	define __CLDI_CPUDM CLDI_CPUDM_LP32
#elif defined(_LP64) || defined(__LP64__)
#	define __CLDU_CPUDM CLDI_CPUDM_LP64
#else
#	define __CLDU_CPUDM CLDU_CPUDM_XLP64
#endif


#endif /* _cldi_head__setup_platform_DATA_MODEL_H */
