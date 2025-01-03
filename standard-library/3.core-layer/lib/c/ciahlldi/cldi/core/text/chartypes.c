
/* Setup CLDI module "core".                 */
#include <ciahlldi/cldi/core/setup.h>

/* Implementing: cldi-core: "text/chartypes" */
#include <ciahlldi/cldi/core/text/chartypes.h>

#ifdef __cplusplus
extern "C" {
#endif



/* ----------------------------------- */
/* `CLDI_CHARTYPE` Enum */

	/* -----
	.  Returns the size of a given character type. */
	size_t
	CLDI_CHARTYPE_SIZEOF(CLDI_CHARTYPE __chartype)
	{
		if (__chartype <= 0)
			return 0;
		else if (__chartype == CLDI_CHARTYPE_UTF8)
			return 1;
		else
			return (size_t) __chartype;
	}
	/* -----
	.  Returns true if __chartype is a null or "invalid string"
	.  character type, and false otherwise.                    */
	bool
	CLDI_CHARTYPE_ISINVALID(CLDI_CHARTYPE __chartype)
	{
		return __chartype <= 0;
	}
	/* -----
	.  Returns true if the type is not null and is not invalid. */
	bool
	CLDI_CHARTYPE_ISVALID(CLDI_CHARTYPE __chartype)
	{
		return __chartype > 0;
	}
	/* -----
	.  Check for a valid counterpart to __chartype. */
	CLDI_CHARTYPE
	CLDI_CHARTYPE_VALIDOF(CLDI_CHARTYPE __chartype)
	{
		if (__chartype >= 0)
			return __chartype;
		else switch (__chartype) {
			case CLDI_CHARTYPE_INVALID       : return CLDI_CHARTYPE_NONE;
			case CLDI_CHARTYPE_ASCII_INVALID : return CLDI_CHARTYPE_ASCII;
			case CLDI_CHARTYPE_UTF8_INVALID  : return CLDI_CHARTYPE_UTF8;
			case CLDI_CHARTYPE_UTF16_INVALID : return CLDI_CHARTYPE_UTF16;
			case CLDI_CHARTYPE_UTF32_INVALID : return CLDI_CHARTYPE_UTF32;

			default: return CLDI_CHARTYPE_INVALID;
		}
	}
	/* -----
	.  Check for an invalid counterpart to __chartype. */
	CLDI_CHARTYPE
	CLDI_CHARTYPE_INVALIDOF(CLDI_CHARTYPE __chartype)
	{
		if (__chartype < 0)
			return __chartype;
		else {
			if      (__chartype == CLDI_CHARTYPE_NONE)
				return CLDI_CHARTYPE_INVALID;

			else if (__chartype == CLDI_CHARTYPE_ASCII)
				return CLDI_CHARTYPE_ASCII_INVALID;

			else if (__chartype == CLDI_CHARTYPE_UTF8)
				return CLDI_CHARTYPE_UTF8_INVALID;

			else if (__chartype == CLDI_CHARTYPE_UTF16)
				return CLDI_CHARTYPE_UTF16_INVALID;

			else if (__chartype == CLDI_CHARTYPE_UTF32)
				return CLDI_CHARTYPE_UTF32_INVALID;

			else
				return CLDI_CHARTYPE_NONE;
		}
	}
	/* -----
	.  Check if one type can be converted into another. */
	bool
	CLDI_CHARTYPE_CAN_TRANSENCODE(CLDI_CHARTYPE __convert_to, CLDI_CHARTYPE __type)
	{
		if (__convert_to <= 0 || __type <= 0)
			return false;

		else if (__convert_to == CLDI_CHARTYPE_ASCII)
			/* ASCII can only accept ascii, no other encoding
			.  can go into it. */
			return __type == CLDI_CHARTYPE_ASCII;

		else if (__convert_to == CLDI_CHARTYPE_UTF8)
			/* Anything (including ASCII) can be converted into UTF-8
			.  because it supports variable width characters. */
			return __type == CLDI_CHARTYPE_ASCII ||
			/*_*/  __type == CLDI_CHARTYPE_UTF8  ||
			/*_*/  __type == CLDI_CHARTYPE_UTF16 ||
			/*_*/  __type == CLDI_CHARTYPE_UTF32;

		else if (__convert_to == CLDI_CHARTYPE_UTF16)
			/* UTF-16 supports half-width characters, so anything
			.  smaller than UTF-32 would fit. */
			return __type == CLDI_CHARTYPE_ASCII ||
			/*_*/  __type == CLDI_CHARTYPE_UTF8  ||
			/*_*/  __type == CLDI_CHARTYPE_UTF16;

		else if (__convert_to == CLDI_CHARTYPE_UTF32)
			/* Anything can be encoded into UTF-32 with its
			.  full-width characters. */
			return __type == CLDI_CHARTYPE_ASCII ||
			/*_*/  __type == CLDI_CHARTYPE_UTF8  ||
			/*_*/  __type == CLDI_CHARTYPE_UTF16 ||
			/*_*/  __type == CLDI_CHARTYPE_UTF32;

		else return false;
	}


/* ----------------------------------- */



#ifdef __cplusplus
}
#endif
