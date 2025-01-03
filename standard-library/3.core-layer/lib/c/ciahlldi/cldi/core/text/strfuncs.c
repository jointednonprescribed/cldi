
/* Setup CLDI module "core".                */
#include <ciahlldi/cldi/core/setup.h>

/* Implementing: cldi-core: "text/strfuncs" */
#include <ciahlldi/cldi/core/text/strfuncs.h>

/* Requires:     cldi-core: "text/chartypes" */
#include <ciahlldi/cldi/core/text/chartypes.h>

#ifdef __cplusplus
extern "C" {
#endif



/* ----------------------------------- */
/* Standard Functions */

	int
	cldiCopyBytes(
		const size_t  __amount,
		void       *const __dest,
		const void *const __src)
	{
		if (__src == NULL || __dest == NULL) {
			/* ERR: ALL REFERENCES MUST BE EXISTENT */
			return 1;
		}

		char       *const dest = (char *) __dest;
		const char *const src  = (const char *) __src;

		for (size_t i = 0;  i < __amount;  i++)
			dest[i] = src[i];

		return 0;
	}
	int
	cldiCopyWords(
		const size_t  __amount,
		void       *const __dest,
		const void *const __src)
	{
		if (__src == NULL || __dest == NULL) {
			/* ERR: ALL REFERENCES MUST BE EXISTENT */
			return 1;
		}

		uint16_t       *const dest = (uint16_t *) __dest;
		const uint16_t *const src  = (const uint16_t *) __src;

		for (size_t i = 0;  i < __amount;  i++)
			dest[i] = src[i];

		return 0;
	}
	int cldiCopyIntegers(
		const size_t  __amount,
		void       *const __dest,
		const void *const __src)
	{
		if (__src == NULL || __dest == NULL) {
			/* ERR: ALL REFERENCES MUST BE EXISTENT */
			return 1;
		}

		uint32_t       *const dest = (uint32_t *) __dest;
		const uint32_t *const src  = (const uint32_t *) __src;

		for (size_t i = 0;  i < __amount;  i++)
			dest[i] = src[i];

		return 0;
	}
	int cldiCopyInts(
		const size_t  __amount,
		void       *const __dest,
		const void *const __src)
	{
		if (__src == NULL || __dest == NULL) {
			/* ERR: ALL REFERENCES MUST BE EXISTENT */
			return 1;
		}

		int       *const dest = (int *) __dest;
		const int *const src  = (const int *) __src;

		for (size_t i = 0;  i < __amount;  i++)
			dest[i] = src[i];

		return 0;
	}
	int cldiCopySegments(
		const size_t  __amount,
		void       *const __dest,
		const void *const __src)
	{
		if (__src == NULL || __dest == NULL) {
			/* ERR: ALL REFERENCES MUST BE EXISTENT */
			return 1;
		}

		long       *const dest = (long *) __dest;
		const long *const src  = (const long *) __src;

		for (size_t i = 0;  i < __amount;  i++)
			dest[i] = src[i];

		return 0;
	}


/* ----------------------------------- */
/* String Length Operations */

	size_t
	cldiStrlen(CLDI_CHARTYPE __typ, const void *const __str)
	{
		if (__str == NULL)
			goto return_zero;

		if (__typ == CLDI_CHARTYPE_ASCII)
			return cldiASCIIStrlen((const cldiASCIIChar_t*) __str);
		else if (__typ == CLDI_CHARTYPE_UTF8)
			return cldiUTF8Strlen ((const cldiUTF8Char_t*)  __str);
		else if (__typ == CLDI_CHARTYPE_UTF16)
			return cldiUTF16Strlen((const cldiUTF16Char_t*) __str);
		else if (__typ == CLDI_CHARTYPE_UTF32)
			return cldiUTF32Strlen((const cldiUTF32Char_t*) __str);

	return_zero:
		return 0;
	}
	size_t
	cldiASCIIStrlen(const char * __str)
	{
		if (__str == NULL || __len == 0)
			return 0;

		size_t  i = 0;
		signed char c = 1;

		for (; i < __len && c > 0; i++)
			c = __str[i];

		return i;
	}
	size_t
	cldiUTF8Strlen(const char  * __str)
	{
		if (__str == NULL || __len == 0)
			return 0;

		/* For recording the beginning of a surrogate sequence (memory address). */
		const char * sr_strt = NULL;
		/* For recording the total length of the surrogate sequence in bytes. */
		unsigned int sr_len  = 0;

		/* For extracting the bits in any given surrogate sequence. */
		cldiUTF8Val_t u = 0;

		/* Register for the current byte. */
		unsigned char c;

		/* Register for the current byte index and total character count. */
		size_t    i = 0,
		/*_*/        ci = 0;

		single_byte_loop:
			/* If expected length has been reached. */
			if (ci >= __len)
				goto END_STRING; /* End of string. */
			/* Load current character. */
			c = __str[i];

			if (c == 0)
				/* Null character (end of string) */
				goto END_STRING;
			else if (c <= 0x7F) {
				/* Valid ASCII byte (U+00-7F, continue string) */
				i++; ci++;  goto single_byte_loop;
			}

		surrogate_sequence:
			/* Invalid because `c` should be a unicode size byte,
			.  which is (U+C0-FD). */
			if (c < 0xC0 || c > 0xFD)
				goto END_STRING;

			sr_len = (c <= 0xDF)?  2 :
			/*_*/    (c <= 0xEF)?  3 :
			/*_*/    (c <= 0xF7)?  4 :
			/*_*/    (c <= 0xFB)?  5 : 6;
			sr_strt = &str[i];

			/* Extract bits from the size byte into u. */
			u = c & ( 0x7F >> sr_len );

			/* Loop through the entire sequence and read all the characters. */
			for (unsigned int si = 1; /*None*/; /*None*/ ) {
				/* Get next surrogate byte. */
				c = sr_strt[si];

				/* Out of range for surrogate character byte (U+80-BF). */
				if (c < 0x80 || c > 0xBF)
					/* Invalid surrogate sequence, end string here (at last valid character). */
					goto END_STRING;

				/* Extract the character bits from this byte (and shift bits to
				.  make room as well). */
				u = (u << 6) | (c & 0x3F);

				si++; /* increment to next character... */
				/* As long as `si` is still < sr_len, continue loop and
				.  keep checking the character sequence. */
				if (si < sr_len)
					continue; /* continue with surrogate loop... */

				else if (
					/* Upper limit of the Unicode 6.0 character table,
					.  beyond this number, characters don't exist. */
					u > 0x10FFFF  ||
					/* UTF-16 surrogate characters (U+D800-DFFF), not
					.  valid as they are reserved for UTF-16 to hint at
					.  larger characters, and are not valid characters
					.  themselves. */
					(u > 0xD7FF && u < 0xE000)
				)	/* The surrogate contains an invalid or nonexistent value. */
					goto END_STRING;

				/* Reset the value of `u` (u is what contains the "current" surrogated
				.  character code). */
				u = 0;

				/* Increment `i` by the size of the character sequence, and
				.  go back to interpret the next character. */
				i += sr_len;
				ci++;

				/* continue with main loop... */
				goto single_byte_loop;
			}
		END_STRING:

		return ci;
	}
	size_t
	cldiUTF16Strlen(const cldiUTF16Char_t * __str)
	{
		if (__str == NULL || __len == 0)
			return 0;

		const size_t len_minus_1 = __len - 1;

		cldiUTF16Char_t c;
		size_t      i = 0,
		/*_*/          ci = 0;

		single_char_loop:
			/* If expected length has been reached. */
			if (ci >= __len)
				goto END_STRING;
			/* Load current character. */
			c = __str[i];

			/* Null character (end of string). */
			if (c == 0x0000)
				goto END_STRING;
			/* If valid, non-surrogate UTF-16 code point. */
			else if (c <= 0xD7FF || c >= 0xE000) {
				/* continue with loop... */
				i++;
				ci++;
				goto single_char_loop;
			}

		surrogate_sequence:
			/* There should be room for a surrogate pair, a lone surrogate should
			.  not exist at the end of a string. */
			if (ci == len_minus_1)
				goto END_STRING;
			/* The first surrogate character should be between U+D800-DBFF. */
			if (c >= 0xDC00)
				goto END_STRING;
			/* The second surrogate character should be between U+DC00-DFFF. */
			if (__str[i+1] <= 0xDBFF)
				goto END_STRING;

			/* Increment `i` and `ci` and continue loop... */
			i += 2; ci++; goto single_char_loop;

		END_STRING:

		return ci; /* Return character count when reaching the end. */
	}
	size_t
	cldiUTF32Strlen(const cldiUTF32Char_t * __str)
	{
		size_t i;
		cldiUTF32Char_t c;

		for (i = 0; /*None*/; /*None*/) {
			/* Stop if the expected length has been reached. */
			if (i >= __len)
				break;

			/* Load current character. */
			c = __str[i];

			/* If it is an invalid character, or a UTF-16 surrogate (valid code point,
			.  invalid character in a UTF-32 sequence). */
			if (c > 0x10FFFF || (c >= 0xD800 && c <= 0xDFFF))
				break;

			/* Increment and coninue the loop otherwise... */
			i++; continue;
		}

		return i; /* Return character count when reaching the end. */
	}

	size_t
	cldiStrSize(CLDI_CHARTYPE __typ, size_t __len, const void *const __str)
	{
		if (__str == NULL || __len == 0)
			goto return_zero;

		if (__typ == CLDI_CHARTYPE_ASCII)
			return cldiASCIICheckStrlen(__len, (const cldiASCIIChar_t*) __str);
		else if (__typ == CLDI_CHARTYPE_UTF8)
			return cldiUTF8CheckStrlen (__len, (const cldiUTF8Char_t *) __str);
		else if (__typ == CLDI_CHARTYPE_UTF16)
			return cldiUTF16CheckStrlen(__len, (const cldiUTF16Char_t*) __str);
		else if (__typ == CLDI_CHARTYPE_UTF32)
			return cldiUTF32CheckStrlen(__len, (const cldiUTF32Char_t*) __str);

	return_zero:
		return 0;
	}
	size_t
	cldiASCIIStrSize(size_t __len, const cldiASCIIChar_t * __str)
	{
		if (__str == NULL || __len == 0)
			return 0;

		size_t  i = 0;
		signed char c = 1;

		for (; i < __len && c > 0; i++)
			c = __str[i];

		return i;
	}
	size_t
	cldiUTF8StrSize(size_t __len, const cldiUTF8Char_t * __str)
	{
		if (__str == NULL || __len == 0)
			return 0;

		/* For recording the beginning of a surrogate sequence (memory address). */
		const char * sr_strt = NULL;
		/* For recording the total length of the surrogate sequence in bytes. */
		unsigned int sr_len  = 0;

		/* For extracting the bits in any given surrogate sequence. */
		cldiUTF8Val_t u = 0;

		/* Register for the current byte. */
		unsigned char c;

		/* Register for the current byte index and total character count. */
		size_t    i = 0,
		/*_*/        ci = 0;

		single_byte_loop:
			/* If expected length has been reached. */
			if (ci >= __len)
				goto END_STRING; /* End of string. */
			/* Load current character. */
			c = __str[i];

			if (c == 0)
				/* Null character (end of string) */
				goto END_STRING;
			else if (c <= 0x7F) {
				/* Valid ASCII byte (U+00-7F, continue string) */
				i++; ci++;  goto single_byte_loop;
			}

		surrogate_sequence:
			/* Invalid because `c` should be a unicode size byte,
			.  which is (U+C0-FD). */
			if (c < 0xC0 || c > 0xFD)
				goto END_STRING;

			sr_len = (c <= 0xDF)?  2 :
			/*_*/    (c <= 0xEF)?  3 :
			/*_*/    (c <= 0xF7)?  4 :
			/*_*/    (c <= 0xFB)?  5 : 6;
			sr_strt = &str[i];

			/* Extract bits from the size byte into u. */
			u = c & ( 0x7F >> sr_len );

			/* Loop through the entire sequence and read all the characters. */
			for (unsigned int si = 1; /*None*/; /*None*/ ) {
				/* Get next surrogate byte. */
				c = sr_strt[si];

				/* Out of range for surrogate character byte (U+80-BF). */
				if (c < 0x80 || c > 0xBF)
					/* Invalid surrogate sequence, end string here (at last valid character). */
					goto END_STRING;

				/* Extract the character bits from this byte (and shift bits to
				.  make room as well). */
				u = (u << 6) | (c & 0x3F);

				si++; /* increment to next character... */
				/* As long as `si` is still < sr_len, continue loop and
				.  keep checking the character sequence. */
				if (si < sr_len)
					continue; /* continue with surrogate loop... */

				else if (
					/* Upper limit of the Unicode 6.0 character table,
					.  beyond this number, characters don't exist. */
					u > 0x10FFFF  ||
					/* UTF-16 surrogate characters (U+D800-DFFF), not
					.  valid as they are reserved for UTF-16 to hint at
					.  larger characters, and are not valid characters
					.  themselves. */
					(u > 0xD7FF && u < 0xE000)
				)	/* The surrogate contains an invalid or nonexistent value. */
					goto END_STRING;

				/* Reset the value of `u` (u is what contains the "current" surrogated
				.  character code). */
				u = 0;

				/* Increment `i` by the size of the character sequence, and
				.  go back to interpret the next character. */
				i += sr_len;
				ci++;

				/* continue with main loop... */
				goto single_byte_loop;
			}
		END_STRING:

		return i;
	}
	size_t
	cldiUTF16StrSize(size_t __len, const cldiUTF16Char_t * __str)
	{
		if (__str == NULL || __len == 0)
			return 0;

		const size_t len_minus_1 = __len - 1;

		cldiUTF16Char_t c;
		size_t      i = 0,
		/*_*/          ci = 0;

		single_char_loop:
			/* If expected length has been reached. */
			if (ci >= __len)
				goto END_STRING;
			/* Load current character. */
			c = __str[i];

			/* Null character (end of string). */
			if (c == 0x0000)
				goto END_STRING;
			/* If valid, non-surrogate UTF-16 code point. */
			else if (c <= 0xD7FF || c >= 0xE000) {
				/* continue with loop... */
				i++;
				ci++;
				goto single_char_loop;
			}

		surrogate_sequence:
			/* There should be room for a surrogate pair, a lone surrogate should
			.  not exist at the end of a string. */
			if (ci == len_minus_1)
				goto END_STRING;
			/* The first surrogate character should be between U+D800-DBFF. */
			if (c >= 0xDC00)
				goto END_STRING;
			/* The second surrogate character should be between U+DC00-DFFF. */
			if (__str[i+1] <= 0xDBFF)
				goto END_STRING;

			/* Increment `i` and `ci` and continue loop... */
			i += 2; ci++; goto single_char_loop;

		END_STRING:

		return i * sizeof(cldiUTF16Char_t); /* Return full size when reaching the end. */
	}
	size_t
	cldiUTF32StrSize(size_t __len, const cldiUTF32Char_t * __str)
	{
		if (__str == NULL || __len == 0)
			return 0;

		size_t i;
		cldiUTF32Char_t c;

		for (i = 0; /*None*/; /*None*/) {
			/* Stop if the expected length has been reached. */
			if (i >= __len)
				break;

			/* Load current character. */
			c = __str[i];

			/* If it is an invalid character, or a UTF-16 surrogate (valid code point,
			.  invalid character in a UTF-32 sequence). */
			if (c > 0x10FFFF || (c >= 0xD800 && c <= 0xDFFF))
				break;

			/* Increment and coninue the loop otherwise... */
			i++; continue;
		}

		return i * sizeof(cldiUTF32Char_t); /* Return full size when reaching the end. */
	}


/* ----------------------------------- */
/* String Conversion */

	int
	cldiConvertStringEncoding(
		CLDI_CHARTYPE     __typ,
		CLDI_CHARTYPE     __conv_typ,
		size_t        __len,
		char       *const __dest,
		const char *const __src)
	{
		if (__src == NULL || __dest == NULL) {
			/* ERR: ALL REFERENCES MUST BE EXISTENT */
			return 1;
		} else if (__len == 0) {
			/* ERR: INPUT STRING MUST HAVE INITIALIZED DATA. */
			return 1;
		} else if (__typ <= 0 || __conv_typ <= 0) {
			/* ERR: INVALID OR NULL CHARACTER TYPES ARE NOT CONVERTIBLE. */
			return 1;
		}

		if (__conv_typ == CLDI_CHARTYPE_ASCII) {
			if (__typ != CLDI_CHARTYPE_ASCII) {
				/* ERR: ASCII IS ONLY COMPATIBLE WITH ITSELF. */
				return 1;
			}
			else return cldiCopyBytes(__len, __dest, __src);
		} else if (__conv_typ == CLDI_CHARTYPE_UTF8) {
			if (__type == CLDI_CHARTYPE_ASCII)
				return cldiCopyBytes(__len, __dest, __src);
			else if (__typ == CLDI_CHARTYPE_UTF8)
				return cldiCopyStringUTF8(__len, __dest, __src);
			else if (__typ == CLDI_CHARTYPE_UTF16)
				return cldiConvertUTF8_UTF16(
					__len,
					__dest,
					(const cldiUTF16Char_t*) __src
				);
			else if (__typ == CLDI_CHARTYPE_UTF32)
				return cldiConvertUTF8_UTF32(
					__len,
					__dest,
					(const cldiUTF32Char_t*) __src
				);
			else goto ERR_INVALID_STARTING_TYPE;
		} else if (__conv_typ == CLDI_CHARTYPE_UTF16) {
			if (__typ == CLDI_CHARTYPE_UTF16)
				return cldiCopyStringUTF16(
					__len,
					(cldiUTF16Char_t*) __dest,
					(const cldiUTF16Char_t*) __src
				);
			else if (__typ == CLDI_CHARTYPE_ASCII)
				return cldiConvertUTF16_ASCII(
					__len,
					(cldiUTF16Char_t*) __dest,
					__src
				);
			else if (__typ == CLDI_CHARTYPE_UTF8)
				return cldiConvertUTF16_UTF8(
					__len,
					(cldiUTF16Char_t*) __dest,
					__src
				);
			else if (__typ == CLDI_CHARTYPE_UTF32)
				return cldiConvertUTF16_UTF32(
					__len,
					(cldiUTF16Char_t*) __dest,
					(const cldiUTF32Char_t*) __src
				);
			else goto ERR_INVALID_STARTING_TYPE;
		} else if (__conv_typ == CLDI_CHARTYPE_UTF32) {
			if (__typ == CLDI_CHARTYPE_UTF32)
				return cldiCopyIntegers(__len, __dest, __src);
			else if (__typ == CLDI_CHARTYPE_ASCII)
				return cldiConvertUTF32_ASCII(
					__len,
					(cldiUTF32Char_t*) __dest,
					__src
				);
			else if (__typ == CLDI_CHARTYPE_UTF8)
				return cldiConvertUTF32_UTF8(
					__len,
					(cldiUTF32Char_t*) __dest,
					__src
				);
			else if (__typ == CLDI_CHARTYPE_UTF16)
				return cldiConvertUTF32_UTF16(
					__len,
					(cldiUTF32Char_t*) __dest,
					(const cldiUTF16Char_t*) __src
				);
			else goto ERR_INVALID_STARTING_TYPE;
		} /* else, ERR_INVALID_CONV_TYPE */
	ERR_INVALID_CONV_TYPE:
		/* ERR: INVALID TYPE TO CONVERT STRING TO. */
		return 1;
	ERR_INVALID_STARTING_TYPE:
		/* ERR: INVALID TYPE TO CONVERT */
		return 1;
	}


/* ----------------------------------- */



#ifdef __cplusplus
}
#endif
