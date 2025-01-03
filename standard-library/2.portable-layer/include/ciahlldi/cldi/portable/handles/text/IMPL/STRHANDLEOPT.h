
#ifndef _cldi_portable__handles_text_IMPL_STRHANDLE_OPT_H
#define _cldi_portable__handles_text_IMPL_STRHANDLE_OPT_H 1

#include "../../../setup.h"

#include "../../../types/basictypes.h"



#ifdef __cplusplus
extern "C" {
#endif
typedef enum _CLDISTRHANDLEOPT
{
	/* None value */
	CLDISTRHANDLE_oNONE                  = 0,
	/* The default data value that strings start with. */
	CLDISTRHANDLE_oDEFAULT               = CLDISTRHANDLE_oNONE,
	/* The default values for null-valued strings. */
	CLDISTRHANDLE_oNULLV_DEFAULT         = CLDISTRHANDLE_oNONE,

	/* A mask for the data points that are acceptable to keep in a null-valued
	.  string handle. */
	CLDISTRHANDLE_oNULLABLE_MASK         = 0x0001,
	/* Inverted value to negate those bits. */
	CLDISTRHANDLE_oINVERT_NULLABLE_MASK  = 0xfffe,

	/* This bit marks that the cldiStr struct itself was
	.  allocated in the heap memory. */
	CLDISTRHANDLE_oHEAP_ALLOCATED        = 0x0001,
	/* Inverted value to negate those bits. */
	CLDISTRHANDLE_oINVERT_HEAP_ALLOCATED = 0xfffe, /* (~0x1) */
} CLDISTRHANDLEOPT, CLDI_STRING_HANDLE_OPTIONS;
#ifdef __cplusplus
}
#	if __CLDI_no_cpp > false
namespace cldi
{
	using STRHANDLEOPT = CLDISTRHANDLEOPT;
	using STRING_HANDLE_OPTIONS = CLDISTRHANDLEOPT;
}
#	endif
#endif



#endif /* _cldi_portable__handles_IMPL_STRHANDLE_OPT_H */
