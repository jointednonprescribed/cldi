
#ifndef _cldi_portable__text_IMPL_CHARTYPE_ASSOCSR_H
#define _cldi_portable__text_IMPL_CHARTYPE_ASSOCSR_H 1

#include "../../../setup.h"

#include "../../../types/basictypes.h"

#include "CHARTYPE.h"



#ifdef __cplusplus
extern "C" {
#endif

/* Get the name of the type as a string.
.  - Alias */
#define cldiChartypeToString cldiGetChartypeName
const char *  cldiGetChartypeName(CLDI_CHARTYPE type);

/* Get the true size of a given character type. */
int           cldiSizeofChartype(CLDI_CHARTYPE type);
#define       _mCldiSizeofChartype(chartype) (((chartype)&0x7)+1)
/* Get the identifier value of the type. */
int           cldiGetChartypeIdentifier(CLDI_CHARTYPE type);
/* Whether or not a given character type is invalid. */
bool          cldiChartypeIsInvalid(CLDI_CHARTYPE type);
#define       _mCldiChartypeIsInvalid(chartype) ((chartype)<=0)
/* Whether or not a given character type is valid. */
bool          cldiChartypeIsValid(CLDI_CHARTYPE type);
#define       _mCldiChartypeIsValid(chartype) ((chartype)>0)
/* Get the valid counterpart to the passed character type. */
CLDI_CHARTYPE cldiChartypeGetValid(CLDI_CHARTYPE type);
/* Get the invalid counterpart to the passed character type. */
CLDI_CHARTYPE cldiChartypeGetInvalid(CLDI_CHARTYPE type);
/* Check if one type can be converted into another. */
bool          cldiChartypesCanTransencode(CLDI_CHARTYPE conv_from, CLDI_CHARTYPE conv_to);

#ifdef __cplusplus
}
#	if __CLDI_no_cpp < true
#		include "CHARTYPE.classwrapper.hpp"
#	endif
#endif



#endif /* _cldi_portable__RangeMarkertext_IMPL_CHARTYPE_ASSOCSR_H */
