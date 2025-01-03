
#ifndef _cldi_portable__text_STR_H
#define _cldi_portable__text_STR_H 1

#include "../setup.h"

#include "../types/basictypes.h"
#include "chartypes.h"



/* ----------------------------------- */
/* Standard Functions */

#ifdef __cplusplus
extern "C" {
#endif

	/* Copy some array of bytes to another place in memory. */
	CLDISTAT cldiCopyBytes(
		const size_t                      amount_of_bytes,
		void            *const __restrict_arr destination,
		const void      *const __restrict_arr source
	);
	/* Copy some array of 'words' (two-byte integers) to another place in memory. */
	CLDISTAT cldiCopyWords(
		const size_t                    amount_of_words,
		i16_t         *const __restrict_arr destination,
		const u16_t   *const __restrict_arr source
	);
	/* Copy some array of numbers (four-byte integers) to another place in memory. */
	CLDISTAT cldiCopyWords32(
		const size_t                    amount_of_nums,
		u32_t         *const __restrict_arr destination,
		const u32_t   *const __restrict_arr source
	);
	/* Copy some array of numbers (eight-byte integers) to another place in memory. */
	CLDISTAT cldiCopyWords64(
		const size_t                    amount_of_nums,
		u64_t         *const __restrict_arr destination,
		const u64_t   *const __restrict_arr source
	);

	/* Copy some array of `int`s to another place in memory. */
	CLDISTAT cldiCopyInts(
		const size_t                      amount_of_ints,
		int             *const __restrict_arr destination,
		const int       *const __restrict_arr source);
	/* Copy some array of `long`s to another place in memory. */
	CLDISTAT cldiCopyLongs(
		const size_t                      amount_of_longs,
		long long       *const __restrict_arr destination,
		const long long *const __restrict_arr source);

#ifdef __cplusplus
}
#endif


/* ----------------------------------- */
/* String Operations */

#ifdef __cplusplus
extern "C" {
#endif

	/* Convert a wchar_t string to a UTF-16 string. */
	CLDISTAT cldiStringWCToUTF16(
		size_t     character_amount,
		size_t     buffer_max_items,
		const wchar_t *input_string,
		cldiwchar_t   *output_buffer
	);

#ifdef __cplusplus
}
#endif


/* ----------------------------------- */
/* String Length Operations */

#ifdef __cplusplus
extern "C" {
#endif

	/* Get String Length (find NULL or first invalid character). */
	size_t cldiStrlen(
		CLDI_CHARTYPE     string_type,
			/* The encoding format of the string, use CLD	I_CHARTYPE_BASIC_STRING
			.  (UTF-8 or sometimes ASCII) for basic C-style strings. */
		const void *const string
			/* The string to search, of any encoding format. This is *const so it
			.  can be safely casted to different string types (cldiUTF8Char_t*,
			.  cldiASCIIChar_t*, etc.). */
	);
	CLDISTAT cldiStrlenEx(
		size_t       *char_length_output,
			/* [out] The output location for the amount of valid characters found in
			.  the string. */
		CLDI_CHARTYPE     string_type,
			/* The encoding format of the string, use CLD	I_CHARTYPE_BASIC_STRING
			.  (UTF-8 or sometimes ASCII) for basic C-style strings. */
		const void *const string
			/* The string to search, of any encoding format. This is *const so it
			.  can be safely casted to different string types (cldiUTF8Char_t*,
			.  cldiASCIIChar_t*, etc.). */
	);

	/* - Interface for C-style strings (ASCII or UTF-8) (USE THIS ONE FOR NORMAL STRINGS). */
	#if __CLDI_standard_strings_are_ascii > false
	#	define cldiCStrlen   cldiASCIIStrlen
	#	define cldiCStrlenEx cldiASCIIStrlenEx
	#else
	#	define cldiCStrlen   cldiUTF8Strlen
	#	define cldiCStrlenEx cldiUTF8StrlenEx
	#endif

	/* Get the length of a wchar_t string. */
	size_t cldiStrlenWC(
		const wchar_t*
		/* Same argument as `string` from Strlen(), but
		.  `string_type` is assumed to be CLDI_CHARTYPE_UTF16. */
	);
	CLDISTAT cldiStrlenExWC(size_t*, const wchar_t*);

	/* Get the length of an ASCII string. */
	size_t cldiASCIIStrlen(const char*);
	size_t cldiASCIIStrlenEx(size_t*, const char*);

	/* Get the length of a UTF-8 string. */
	size_t cldiUTF8Strlen(const char*);
	CLDISTAT   cldiUTF8StrlenEx(size_t*, const char*);

	/* Get the length of a UTF-16 string. */
	size_t cldiUTF16Strlen(const cldiwchar_t*);
	CLDISTAT   cldiUTF16StrlenEx(size_t*, const cldiwchar_t*);

	/* Get the length of a UTF-32 string. */
	size_t cldiUTF32Strlen(const cldiwwchar_t*);
	CLDISTAT   cldiUTF32StrlenEx(size_t*, const cldiwwchar_t*);

	/* Get full size in bytes based on expected length. */
	size_t cldiStringSize(
		CLDI_CHARTYPE     string_type,
			/* The encoding format of the string, use CLDI_CHARTYPE_BASIC_STRING
			.  (UTF-8 or sometimes ASCII) for basic C-style strings. */
		size_t        character_count,
			/* The expected amount of chars in the string (how many whole
			.  characters to stop after). */
		const void *const string
			/* The string to check, of any string type. This is *const so it
			.  can be safely casted to different string types (cldiUTF8Char_t*,
			.  cldiASCIIChar_t*, etc.). */
	);
	size_t cldiStringSizeEx(
		size_t       *full_size_output,
			/* [out] The output location for the total amount of bytes long the the string
			.  is found to be. */
		size_t       *character_count,
			/* [in, out, optional] The expected amount of chars in the string (how many
			.  whole characters to stop after), the actual number of valid characters will
			.  also be outputted here by the function, pass as NULL to ignore. */
		CLDI_CHARTYPE     string_type,
			/* The encoding format of the string, use CLDI_CHARTYPE_BASIC_STRING
			.  (UTF-8 or sometimes ASCII) for basic C-style strings. */
		const void *const string
			/* The string to check, of any string type. This is *const so it
			.  can be safely casted to different string types (cldiUTF8Char_t*,
			.  cldiASCIIChar_t*, etc.). */
	);

	/* - Interface for C-style strings. */
	#if __CLDI_standard_strings_are_ascii > false
	#	define cldiCStringSize   cldiASCIIStringSize
	#	define cldiCStringSizeEx cldiASCIIStringSizeEx
	#else
	#	define cldiCStringSize   cldiUTF8StringSize
	#	define cldiCStringSizeEx cldiUTF8StringSizeEx
	#endif

	/* Get/check full size of a wchar_t string. */
	size_t cldiStringSizeWC(
		size_t, const wchar_t*
			/* Same arguments as from StrSize(): `expected_length`, and `string` (as UTF-16
			.  string, because `string_type` is assumed as CLDI_CHARTYPE_UTF16). */
	);
	CLDISTAT cldiStringSizeExWC(size_t*, size_t*, const wchar_t*);

	/* Get/check full size of a ASCII string. */
	size_t cldiASCIIStringSize(size_t, const char*);
	CLDISTAT   cldiASCIIStringSizeEx(size_t*, size_t*, const char*);

	/* Get/check full size of a UTF-8 string. */
	size_t cldiUTF8StringSize(size_t, const char*);
	CLDISTAT   cldiUTF8StringSizeEx(size_t*, size_t*, const char*);

	/* Get/check full size of a UTF-16 string. */
	size_t cldiUTF16StringSize(size_t, const cldiwchar_t*);
	CLDISTAT   cldiUTF16StringSizeEx(size_t*, size_t*, const cldiwchar_t*);

	/* Get/check full size of a UTF-32 string. */
	size_t cldiUTF32StringSize(size_t, const cldiwwchar_t*);
	size_t cldiUTF32StringSizeEx(size_t*, size_t*, const cldiwwchar_t*);

	/* Generate a character mask for any given-string (a character mask is an array of
	.  8-byte integers that act as shorthand symbols for denoting how many bytes would
	.  preceed any given character index, so that indices can be found in the string's
	.  memory efficiently). */
	const char* cldiGenerateStringCharacterMask(
		CLDI_CHARTYPE     type,
			/* The encoding type of the string. */
		size_t        length,
			/* The total amount of entire characters in the string. */
		const void *const string
			/* The string itself. */
	);
	CLDISTAT cldiGenerateStringCharacterMaskEx(
		const char      **mask_output,
			/* [out] The output address for the mask string itself. */
		size_t       *size_output,
			/* [out] The output address for the total size in bytes of the string. */
		size_t       *length_output,
			/* [in, out] A reference to the length of the given string, and an output
			.  address for the actual calculated length (amount of entire characters)
			.  of the string. */
		CLDI_CHARTYPE     type,
			/* The encoding type of the string. */
		const void *const string
			/* The string itself. */
	);

	/* Generate a character mask for a UTF-8 string. */
	const char* cldiGenerateUTF8CharacterMask(
		size_t  length,
			/* The total amount of entire characters in the string. */
		const char *string
			/* The string itself. */
	);
	CLDISTAT cldiGenerateUTF8CharacterMaskEx(
		const char **mask_output,
			/* [out] The output address for the mask string itself. */
		size_t  *size_output,
			/* [out] The output address for the total size in bytes of the string. */
		size_t  *length_output,
			/* [in, out] A reference to the length of the given string, and an output
			.  address for the actual calculated length (amount of entire characters)
			.  of the string. */
		const char  *string
			/* The string itself. */
	);

	/* Generate a character mask for a UTF-8 string. */
	const char* cldiGenerateUTF16CharacterMask(
		size_t          length,
			/* The total amount of entire characters in the string. */
		const cldiwchar_t *string
			/* The string itself. */
	);
	CLDISTAT cldiGenerateUTF16CharacterMaskEx(
		const char        **mask_output,
			/* [out] The output address for the mask string itself. */
		size_t         *size_output,
			/* [out] The output address for the total size in bytes of the string. */
		size_t         *length_output,
			/* [in, out] A reference to the length of the given string, and an output
			.  address for the actual calculated length (amount of entire characters)
			.  of the string. */
		const cldiwchar_t *string
			/* The string itself. */
	);

	/* Generate a character mask for a UTF-32 string. */
	const char* cldiGenerateUTF32CharacterMask(
		size_t          length,
			/* The total amount of entire characters in the string. */
		const cldiwwchar_t *string
			/* The string itself. */
	);
	CLDISTAT cldiGenerateUTF32CharacterMaskEx(
		const char        **mask_output,
			/* [out] The output address for the mask string itself. */
		size_t         *size_output,
			/* [out] The output address for the total size in bytes of the string. */
		size_t         *length_output,
			/* [in, out] A reference to the length of the given string, and an output
			.  address for the actual calculated length (amount of entire characters)
			.  of the string. */
		const cldiwwchar_t *string
			/* The string itself. */
	);


#ifdef __cplusplus
}
#endif

/* ----------------------------------- */
/* String Copy Operations */

#ifdef __cplusplus
extern "C" {
#endif

	/* Copy a string from one place to another. */
	CLDISTAT cldiCopyString(
		CLDI_CHARTYPE                    type,
			/* The encoding type of the string. */
		size_t                       length,
			/* The total amount of characters in the string. */
		void       *const __restrict_arr copy_to,
			/* The output address for the copied ASCII data. */
		const void *const __restrict_arr copy_from
			/* The input source address for the copied ASCII data. */
	);

	#if __CLDI_standard_string_are_ascii > false
	#	define cldiCopyCString cldiCopyStringASCII
	#	define cldiCopyCStr    cldiCopyStringASCII
	#else
	#	define cldiCopyCString cldiCopyStringUTF8
	#	define cldiCopyCStr    cldiCopyStringUTF8
	#endif

	/* Copy a wchar_t string from one place to another. */
	CLDISTAT cldiCopyStringWC(
		size_t, /* Same `length` argument as from above... */
		wchar_t *__restrict_arr _0, const wchar_t *__restrict_arr _1
			/* Same `copy_to` and `copy_from` arguments as from above,
			.  they will work the same from wchar_t strings. */
	);

	/* Copy an ASCII string from one place to another. */
	CLDISTAT cldiCopyStringASCII(
		size_t, /* Same `length` argument as from above... */
		char *__restrict_arr _0, const char *__restrict_arr _1
			/* Same `copy_to` and `copy_from` arguments as from above,
			.  they will work the same from ASCII strings. */
	);

	/* Copy a UTF-8 string from one place to another. */
	CLDISTAT cldiCopyStringUTF8(
		size_t, /* Same `length` argument as from above... */
		char *__restrict_arr _0, const char *__restrict_arr _1
			/* Same `copy_to` and `copy_from` arguments as from above,
			.  they will work the same from UTF-8 strings. */
	);

	/* Copy a UTF-16 string from one place to another. */
	CLDISTAT cldiCopyStringUTF16(
		size_t, /* Same `length` argument as from above... */
		cldiwchar_t *__restrict_arr _0, const cldiwchar_t *__restrict_arr _1
			/* Same `copy_to` and `copy_from` arguments as from above,
			.  altered to cldiUTF16Char_t for UTF-16. */
	);

	/* Copy a UTF-32 string from one place to another. */
	CLDISTAT cldiCopyStringUTF32(
		size_t, /* Same `length` argument as from above... */
		cldiwwchar_t *__restrict_arr _0, const cldiwwchar_t *__restrict_arr _1
			/* Same `copy_to` and `copy_from` arguments as from above,
			.  altered to cldiUTF16Char_t for UTF-32. */
	);

#ifdef __cplusplus
}
#endif


/* ----------------------------------- */
/* String Copy Operations */

#ifdef __cplusplus
extern "C" {
#endif

	/* Copy some string into another type. */
	CLDISTAT cldiConvertStringEncoding(
		CLDI_CHARTYPE                    starting_type,
		CLDI_CHARTYPE                    encode_into,
		size_t                       amount_of_chars,
		void       *const __restrict_arr output_array,
		const void *const __restrict_arr initial_string_data
	);

	/* - ASCII does not require any conversion to be compatible with UTF-8. */
	/* - Convert UTF-16 to UTF-8. */
	CLDISTAT cldiConvertUTF8_UTF16(
		size_t                        amount_of_utf16_chars,
		char              *__restrict_arr utf8_output,
		const cldiwchar_t *__restrict_arr utf16_input
	);
	/* Convert UTF-32 to UTF-8. */
	CLDISTAT cldiConvertUTF8_UTF32(
		size_t                         amount_of_utf32_chars,
		char               *__restrict_arr utf8_output,
		const cldiwwchar_t *__restrict_arr utf32_input
	);

	/* - Convert ASCII to UTF-16. */
	CLDISTAT cldiConvertUTF16_ASCII(
		size_t                  amount_of_ascii_chars,
		cldiwchar_t *__restrict_arr utf16_output,
		const char  *__restrict_arr ascii_input
	);
	/* - Convert UTF-8 to UTF-16, return error on any characters
	.    that are too big. */
	CLDISTAT cldiConvertUTF16_UTF8(
		size_t                  amount_of_utf8_chars,
		cldiwchar_t *__restrict_arr utf16_output,
		const char  *__restrict_arr utf8_input
	);

	/* - Convert ASCII to UTF-32. */
	CLDISTAT cldiConvertUTF32_ASCII(
		size_t                   amount_of_ascii_chars,
		cldiwwchar_t *__restrict_arr utf32_output,
		const char   *__restrict_arr ascii_input
	);
	/* - Convert UTF-8 to UTF-32. */
	CLDISTAT cldiConvertUTF32_UTF8(
		size_t                   amount_of_utf8_chars,
		cldiwwchar_t *__restrict_arr utf32_output,
		const char   *__restrict_arr utf8_input
	);
	/* - Convert UTF-16 to UTF-32 */
	CLDISTAT cldiConvertUTF32_UTF16(
		size_t                        amount_of_utf16_chars,
		cldiwwchar_t      *__restrict_arr utf32_output,
		const cldiwchar_t *__restrict_arr utf16_input
	);

#ifdef __cplusplus
}
#endif


/* ----------------------------------- */



#endif /* _cldi_portable__text_STR_H */
