
#ifndef _cldi_core__text_IMPL_CHAR_H
#define _cldi_core__text_IMPL_CHAR_H 1

#include "../../setup.h"
#include "../../NS_DECL.hpp"

#include <ciahlldi/cldi/portable/text/IMPL/CHARTYPE.h>



#if defined(__cplusplus) && __CLDI_no_cpp > false
extern "C" {
#endif
struct _cldiCharValue
{
	CLDI_CHARTYPE character_type;

	unsigned long long character_bits;
};
#if __CLDI_no_cpp > false
#	ifdef __cplusplus
}
#	endif
typedef struct
#else
namespace cldi::core {
	using CharValue   = _cldiCharValue;
	using CharValue_t = _cldiCharValue;
	using CharVal     = _cldiCharValue;
	using CharVal_t   = _cldiCharValue;
}
typedef
#endif
	_cldiCharValue cldiCharValue, cldiCharValue_t;



#endif /*  */
