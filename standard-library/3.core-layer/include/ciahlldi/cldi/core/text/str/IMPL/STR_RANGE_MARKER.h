
#ifndef _cldi_core__text_IMPL_STR_RANGE_MARKER_H
#define _cldi_core__text_IMPL_STR_RANGE_MARKER_H 1

#include "../../../setup.h"

#include <ciahlldi/cldi/portable/types/basictypes.h>



typedef struct _cldiStrRangeMarker_t
{
	ssize_t p1, p2;
		/* The the offsets of the two
		.  points specified. */
} cldiStrRangeMarker, cldiStrRangeMarker_t;



#endif /* _cldi_core__text_IMPL_STR_RANGE_MARKER_H */
