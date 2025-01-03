
#ifndef _cldi_portable__text_IMPL_CHARTYPE_H
#define _cldi_portable__text_IMPL_CHARTYPE_H 1

#include "../../../setup.h"



#if defined(__cplusplus) && __CLDI_no_cpp > false
extern "C" {
#endif
typedef enum _CLDICHARTYPE
{
	/* These enumerated types will always contain their size minus 1
	.  in the 3 least significant bits of their value, so that finding
	.  their size is easy and efficient in code, the most significant bit
	.  is also used as a sign bit (which also allows the value to be sorted
	.  based on sign to exclude null and/or invalid values, as valid ones will
	.  have a positive sign), with the 4 remaining upper bits representing
	.  a 4-bit integer acting as the value's identification as a certain
	.  encoding type. */

	/* THIS ENUMERATION MUST ALWAYS BE 0.
	.  This is a completely null character type. */
	CLDI_CHARTYPE_NONE          = 0x00, /* size=1, id=0 */
	/* This is a generic "invalid string" character type. */
	CLDI_CHARTYPE_INVALID       = 0xf8, /* size=1, id=-1 */

	/* Byte-string type. */
	CLDI_CHARTYPE_BYTES         = 0x08, /* size=1, id=1 */
	CLDI_CHARTYPE_BYTES_INVALID = 0xf0, /* size=1, id=-2 */

	/* This is a character type to specify ascii-only modes and strings. */
	CLDI_CHARTYPE_ASCII         = 0x10, /* size=1, id=2 */
	/* ASCII "invalid string" type. */
	CLDI_CHARTYPE_ASCII_INVALID = 0xe8, /* size=1, id=-3 */
	/* These are all unicode character types (for UTF-8, UTF-16, and UTF-32). */
	CLDI_CHARTYPE_UTF8          = 0x18, /* size=1, id=3 */
	CLDI_CHARTYPE_UTF16         = 0x19, /* size=2, id=3 */
	CLDI_CHARTYPE_UTF32         = 0x1b, /* size=4, id=3 */
	/* Respective unicode "invalid string" types. */
	CLDI_CHARTYPE_UTF8_INVALID  = 0xe0, /* size=1, id=-4 */
	CLDI_CHARTYPE_UTF16_INVALID = 0xe1, /* size=2, id=-4 */
	CLDI_CHARTYPE_UTF32_INVALID = 0xe3, /* size=4, id=-4 */
	CLDI_CHARTYPE_UTF7_INVALID  = 0xd8, /* size=1, id=-5 */

	/* These are all character type aliases for explicitly passing C-style
	.  primitive strings and fields from standard C++ strings. These may be
	.  UTF-8 or ASCII. */
	CLDI_CHARTYPE_CSTRING =
	#if __CLDI_standard_strings_are_ascii > 0
		CLDI_CHARTYPE_ASCII,
	#else
		CLDI_CHARTYPE_UTF8,
	#endif
} CLDICHARTYPE, CLDI_CHARTYPE;
#if defined(__cplusplus) && __CLDI_no_cpp > false
}
#endif

#if defined(__cplusplus) && __CLDI_no_cpp < true
namespace cldi {
	namespace portable {
		using CHARTYPE = CLDICHARTYPE;
	}
	using portable::CHARTYPE;
}
#endif



#endif /* _cldi_portable__text_IMPL_CHARTYPE_H */
