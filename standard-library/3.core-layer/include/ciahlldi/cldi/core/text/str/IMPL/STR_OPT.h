
#ifndef _cldi_core__text_str_IMPL_STR_OPT_H
#define _cldi_core__text_str_IMPL_STR_OPT_H 1



#if defined(__cplusplus) && __CLDI_no_cpp > false
extern "C" {
#endif
typedef enum _CLDISTROPT
{
	/* None value */
	CLDISTR_oNONE                  = 0,
	/* The default data value that strings start with. */
	CLDISTR_oDEFAULT               = CLDISTR_oNONE,
	/* The default values for null-valued strings. */
	CLDISTR_oNULLV_DEFAULT         = CLDISTR_oNONE,

	/* A mask for the data points that are acceptable to keep in a null-valued
	.  string object. */
	CLDISTR_oNULLABLE_MASK         = 0x0001,
	/* Inverted value to negate those bits. */
	CLDISTR_oINVERT_NULLABLE_MASK  = 0xfffe,

	/* This bit marks that the cldiStr struct itself was
	.  allocated in the heap memory. */
	CLDISTR_oHEAP_ALLOCATED        = 0x0001,
	CLDISTR_oINVERT_HEAP_ALLOCATED = 0xfffe, /* (~0x1) */

} CLDISTROPT, CLDISTR_OPT;
#if defined(__cplusplus) && __CLDI_no_cpp > false
}
#elif defined(__cplusplus)
namespace cldi
{
	namespace core
	{
		using STROPT = CLDISTROPT;
		using stropt_t = CLDISTROPT;
	}
	using core::STROPT;
	using core::stropt_t;
}
#endif



#endif /* _cldi_core__text_str_IMPL_STR_OPT_H */
