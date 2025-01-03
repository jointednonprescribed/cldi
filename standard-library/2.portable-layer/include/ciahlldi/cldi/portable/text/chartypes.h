
#ifndef _cldi_core__text_CHARTYPES_H
#define _cldi_core__text_CHARTYPES_H 1

/* Setup CLDI module "core". */
#include "../setup.h"

/* Requires: cldi-portable: types */
#include <ciahlldi/cldi/portable/types.h>



/* ----------------------------------- */
/* Proper char sizes... */

typedef uint16_t cldiwchar_t;
typedef uint32_t cldiwwchar_t;

#if defined(__cplusplus) && __CLDI_no_cpp > false
namespace cldi
{
	using wchar_t  = cldiwchar_t;
	using wwchar_t = cldiwwchar_t;
}
#endif

/* Include Enumerated Character Types */
#include "chartypes/IMPL/CHARTYPE.h"
/* Methods associated with character types */
#include "chartypes/IMPL/CHARTYPE.assocsr.h"


/* ----------------------------------- */



#endif /* _cldi_core__text_CHARTYPES_H */
