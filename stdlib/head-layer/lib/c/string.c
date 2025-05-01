


/* Implementing: cldi-head: string.h */
#include <cldi/head/string.h>


const char CLDIERRMSG_STR_FAIL_ALLOC[] =
	"Failed to create new memory block for string.";
const char CLDIERRMSG_STR_FAIL_DROP[] =
	"Failed to drop the string's memory block.";
const char CLDIERRMSG_STR_FAIL_COPY[] =
	"Failed to copy/convert source string to destination.";
const char CLDIERRMSG_STR_FAIL_DROP_AFTER_COPY[] =
	"Failed to drop memory block after attempted (and failed) copy/convert operation.";
const char CLDIERRMSG_STR_NULL_SELF[] =
	"Reference to `self` must not be null or 0.";
const char CLDIERRMSG_STR_FAIL_INIT[] =
	"Failed to initialize the string.";
const char CLDIERRMSG_STR_FAIL_DROP_AFTER_INIT[] =
	"Failed to drop uninitialized string.";
const char CLDIERRMSG_STR_FAIL_GEN_IMASK[] =
	"Failed to generate an index mask for this string.";
const char CLDIERRMSG_STR_FAIL_GET_ADDR[] =
	"Failed to fetch the address for this string's memory.";
const char CLDIERRMSG_STR_FAIL_GET_OFF[] =
	"Failed to calculate the offset for this index.";
const char CLDIERRMSG_STR_FAIL_DROP_AFTER_OFF[] =
	"Failed to drop memory after attempted (and failed) 'get byte offset' operation.";
const char CLDIERRMSG_STR_FAIL_DROP_IMASK[] =
	"Failed to drop the index mask.";
const char CLDIERRMSG_STR_NULL_DATA[] =
	"String does not contain any operable data.";
const char CLDIERRMSG_STR_FAIL_DROP_ADOPT_CHANGE[] =
	"Failed to drop outdated memory block to adopt changes made to the string.";
const char CLDIERRMSG_STR_FAIL_DROP_NEW_BLOCK[] =
	"Failed to drop newly allocated memory block for string operation.";
const char CLDIERRMSG_STR_NOAUTHOR[] =
	"This thread does not have author-level permissions for this string.";
const char CLDIERRMSG_STR_NOOWNER[] =
	"This thread does not have owner-level permissions for this string.";
const char CLDIERRMSG_STR_NOGROUP[] =
	"This thread does not have group-level permissions for this string.";

size_t cldistrabs(size_t total_size, ssize_t rel_idx)
{
	size_t absv;
	if (rel_idx < 0) {
		absv = (rel_idx * (-1));
		if (absv > total_size)
			return 0;
		else
			return total_size - absv;
	} else {
		absv = rel_idx;
		return (absv >= total_size)? total_size-1 : absv;
	}
}
ssize_t cldistrrel(size_t total_size, size_t abs_idx)
{
	if (abs_idx >= total_size)
		return -1;
	else
		return (ssize_t) abs_idx;
}

size_t cldistroff8(const char *str, size_t total_size, size_t idx)
{
	cldimemref imask = cldistrmimask8(str, total_size);
	CLDI_CATCH {
		cldiAddTraceback(cldistroff8, CLDIERRMSG_STR_FAIL_GEN_IMASK);
		return 0;
	}

	const cldistrimask8_t *maddr = (const cldistrimask8_t*) cldiMemrefGetConstAddress(&imask);
	CLDI_CATCH {
		cldiAddTraceback(cldistroff8, CLDIERRMSG_STR_FAIL_GET_ADDR);
		cldiDropMemref(&imask);
		CLDI_CATCH {
			cldiAddTraceback(cldistroff8, CLDIERRMSG_STR_FAIL_DROP);
		}
		return 0;
	}

	size_t off = cldistroffi8(maddr, total_size, idx);
	CLDI_CATCH {
		cldiAddTraceback(cldistroff8, CLDIERRMSG_STR_FAIL_GET_OFF);
		cldiDropMemref(&imask);
		CLDI_CATCH {
			cldiAddTraceback(cldistroff8, CLDIERRMSG_STR_FAIL_DROP_AFTER_OFF);
		}
		return 0;
	}

	cldiDropMemref(&imask);
	CLDI_CATCH {
		cldiAddTraceback(cldistroff8, CLDIERRMSG_STR_FAIL_DROP);
		return 0;
	}
	return off;
}
size_t cldistroffrel8(const char *str, size_t total_size, ssize_t rel_idx)
{
	return cldistroff8(str, total_size, cldistrabs(total_size, rel_idx));
}
size_t cldistroff16(const wchar_t *str, size_t total_size, size_t idx)
{
	cldimemref imask = cldistrmimask16(str, total_size);
	CLDI_CATCH {
		cldiAddTraceback(cldistroff16, CLDIERRMSG_STR_FAIL_GEN_IMASK);
		return 0;
	}

	const cldistrimask16_t *maddr = (const cldistrimask16_t*) cldiMemrefGetConstAddress(&imask);
	CLDI_CATCH {
		cldiAddTraceback(cldistroff16, CLDIERRMSG_STR_FAIL_GET_ADDR);
		cldiDropMemref(&imask);
		CLDI_CATCH {
			cldiAddTraceback(cldistroff16, CLDIERRMSG_STR_FAIL_DROP);
		}
		return 0;
	}

	size_t off = cldistroffi16(maddr, total_size, idx);
	CLDI_CATCH {
		cldiAddTraceback(cldistroff16, CLDIERRMSG_STR_FAIL_GET_OFF);
		cldiDropMemref(&imask);
		CLDI_CATCH {
			cldiAddTraceback(cldistroff16, CLDIERRMSG_STR_FAIL_DROP_AFTER_OFF);
		}
		return 0;
	}

	cldiDropMemref(&imask);
	CLDI_CATCH {
		cldiAddTraceback(cldistroff16, CLDIERRMSG_STR_FAIL_DROP);
		return 0;
	}
	return off;
}
size_t cldistroffrel16(const wchar_t *str, size_t total_size, ssize_t rel_idx)
{
	return cldistroff16(str, total_size, cldistrabs(total_size, rel_idx));
}
size_t cldistroffi8(const cldistrimask8_t *imask, size_t total_size, size_t idx)
{
	return 0; // NEEDS IMPLEMENTATION
}
size_t cldistroffreli8(const cldistrimask8_t *imask, size_t total_size, ssize_t rel_idx)
{
	return cldistroffi8(imask, total_size, cldistrabs(total_size, rel_idx));
}
size_t cldistroffi16(const cldistrimask16_t *imask, size_t total_size, size_t idx)
{
	return 0; // NEEDS IMPLEMENTATION
}
size_t cldistroffreli16(const cldistrimask16_t *imask, size_t total_size, ssize_t rel_idx)
{
	return cldistroffi16(imask, total_size, cldistrabs(total_size, rel_idx));
}

size_t cldistrlena(const char *str)
{
	if (str == NULL) {
		cldithrowf(CLDI_ENULL_ARG, cldistrlen, "Argument (1) `str` must not be null.");
		return 0;
	}

	size_t l = 0;
	signed char c = str[0];
	for (
		size_t i = 0;   c > 0;
		// increment index ptr
		i++,
		// load next character into c
		c = str[i],
		// add 1 to `l` on the condition that c is greater than backspace
		// character (0x8).
		l += (c > 0x8)
	);

	return l;
}
size_t cldistrlen8(const char *str)
{
	if (str == NULL) {
		cldithrowf(CLDI_ENULL_ARG, cldistrlen8, "Argument (1) `str` must not be null.");
		return 0;
	}

	size_t l = 0;
	unsigned char c = str[0];
	for (
		size_t i = 0;   c != 0;
		// increment index ptr
		i++,
		// load next character into c
		c = str[i],
		// add 1 to `l` on the condition that c is greater than 
		// character (0x8).
		l += (c > 0x8)
	);

	return l;
}
size_t cldistrlen16(const wchar_t *str)
{
	if (str == NULL) {
		cldithrowf(CLDI_ENULL_ARG, cldistrlen16, "Argument (1) `str` must not be null.");
		return 0;
	}

	size_t  l  = 0;
	wchar_t wc = str[0];
	for (size_t i = 0; wc != 0 && wc <= 0xfffd; i++, wc = str[i]) {
		// verify surrogate pairs, if wc is greater than or equal to
		// U+DB00 (beginning of lower surrogates) and less than or equal
		// to U+DFFF (end of higher surrogates), handle as surrogate pair. 
		if (wc >= 0xdb00 && wc <= 0xdfff) {
			// if first surrogate character is a higher surrogate character,
			// the pair is invalid, so the string ends here.
			if (wc >= 0xdc00)
				break;
			// else, the character is a lower surrogate, so continue checking
			// the pair.
			i++; // increase index to next character in the pair
			wc = str[i]; // grab next character in the pair
			// if second character in surrogate pair is not a higher surrogate
			// character, the pair is invalid, so the string ends here.
			if (wc < 0xdc00 || wc > 0xdfff)
				break;
			// else, the pair is a valid multibyte character, so increment the
			// counter as though one character had been encountered.
			else l++;
		} else if (wc > 0x8)
			l++; // skip chars less than horizontal tab (0x9)
	}

	return l;
}

size_t cldistrcpya(char *__restrict__ dest, const char *__restrict__ src)
{
	return cldistrncpya(cldistrlena(src), dest, src);
}
size_t cldistrncpya(size_t n, char *__restrict__ dest, const char *__restrict__ src)
{
	if (dest == NULL || src == NULL || n == 0) {
		cldithrowf(CLDI_ENULL_ARG, cldistrncpya, "Arguments (3) `src`, (2) `dest`, and (1) `n` must not be null or 0.");
		return n;
	}

	CLDI_ECTRL;

	const size_t l = n;

	signed char c;
	for (size_t i = 0, j = 0, c = src[0]; i < l && c > 0; i++, n--, c = src[i])
		if (c >= 0x9) { // skip chars less than horizontal tab (0x9)
			dest[j] = c;
			j++;
		}

	return n;
}
size_t cldistrcpy8(char *__restrict__ dest, const char *__restrict__ src)
{
	return cldistrncpy8(cldistrlen8(src), dest, src);
}
size_t cldistrncpy8(size_t n, char *__restrict__ dest, const char *__restrict__ src)
{
	if (dest == NULL || src == NULL || n == 0) {
		cldithrowf(CLDI_ENULL_ARG, cldistrncpy8, "Arguments (3) `src`, (2) `dest`, and (1) `n` must not be null or 0.");
		return n;
	}
	CLDI_ECTRL;

	const size_t l = n;

	unsigned char c;
	for (size_t i = 0, j = 0, c = src[0]; i < l && c > 0; i++, n--, c = src[i])
		if (c >= 0x9) { // skip chars less than horizontal tab (0x9)
			dest[j] = c;
			j++;
		}

	return n;
}
size_t cldistrcpy16(wchar_t *__restrict__ dest, const wchar_t *__restrict__ src)
{
	return cldistrncpy16(cldistrlen16(src), dest, src);
}
size_t cldistrncpy16(size_t n, wchar_t *__restrict__ dest, const wchar_t *__restrict__ src)
{
	if (dest == NULL || src == NULL || n == 0) {
		cldithrowf(CLDI_ENULL_ARG, cldistrncpy16, "Arguments (3) `src`, (2) `dest`, and (1) `n` must not be null or 0.");
		return n;
	}

	CLDI_ECTRL;

	const size_t l = n;

	wchar_t wc, wc2;
	for (size_t i = 0, j = 0, wc = src[0]; i < l && wc != 0; i++, n--, wc = src[i]) {
		if ((wc >= 0xdc00 && wc <= 0xdfff) || wc > 0xfffd)
			break;
		else if (wc >= 0xdb00 && wc <= 0xdbff) {
			i++;
			wc2 = src[i];
			if (wc2 >= 0xdc00 && wc2 <= 0xdfff) {
				dest[j]   = wc;
				dest[j+1] = wc2;
				j += 2;
				n--;
				continue;
			}
		} else {
			dest[j] = wc;
			j++;
			continue;
		}
	}

	return n;
}

CLDISTAT clditrunca(char *__str, size_t __len, ssize_t __idx, size_t __mv)
{
	if (__str == NULL || __len == 0) {
		cldithrowf(CLDI_ENULL_ARG, clditrunca, "Arguments (1) `str` and (2) `total_str_size` cannot be null or zero.");
		return CLDI_ENULL_ARG;
	}

	CLDI_ECTRL;

	// the index to start at, converted to an absolute index
	const size_t absidx = cldistrabs(__len, __idx);
	// the end of the portion that will be truncated
	size_t truncend = absidx + __mv;
	// if the end of the proposed portion to truncate is beyond the end of the string,
	// modify `truncend` to reference the very end of the string instead.
	if (truncend >= __len)
		truncend = __len - 1;

	// the amount of characters that exist after the end of the portion that
	// will be truncated.
	const size_t mvsize = (__len - 1) - truncend;

	// if there is string data after the end of the portion that is being truncated,
	if (mvsize > 0) {
		char c;
		size_t k;
		// copy the end of the string over the truncated portion and
		// place a sentinel and the end
		for (
			size_t i = 0, j = absidx, k = truncend, c = __str[truncend];
			i < mvsize && c != 0;
			i++, j++, k++, c = __str[k]
		)	__str[j] = c;
		__str[__len-1] = 0;
	// else, there is no string data after the end of the truncated portion, so
	// cut the string short.
	} else {
		__str[absidx] = 0;
	}

	return CLDI_SUCCESS;
}
CLDISTAT clditrunc8(char *__str, size_t __len, ssize_t __idx, size_t __mv)
{
	if (__str == NULL || __len == 0) {
		cldithrowf(CLDI_ENULL_ARG, clditrunca, "Arguments (1) `str` and (2) `total_str_size` cannot be null or zero.");
		return CLDI_ENULL_ARG;
	}

	CLDI_ECTRL;

	// the index to start at, converted to an absolute index
	const size_t absidx = cldistrabs8(__str, __len, __idx);
	// the end of the portion that will be truncated
	const size_t _truncend_raw = absidx + __mv;
	const size_t truncend = cldistrabs8(__str, __len, (_truncend_raw < __len)? _truncend_raw : (-1));

	// the amount of characters that exist after the end of the portion that
	// will be truncated.
	const size_t mvsize = (__len - 1) - truncend;

	// if there is string data after the end of the portion that is being truncated,
	if (mvsize > 0) {
		char c;
		size_t j, k;
		// copy the end of the string over the truncated portion and
		// place a sentinel and the end
		for (
			size_t i = 0, j = absidx, k = truncend, c = __str[truncend];
			i < mvsize && c != 0;
			i++, j++, k++, c = __str[k]
		)	__str[j] = c;
		__str[j] = 0;
	// else, there is no string data after the end of the truncated portion, so
	// cut the string short.
	} else {
		__str[absidx] = 0;
	}

	return CLDI_SUCCESS;
}
CLDISTAT clditrunc16(wchar_t *__str, size_t __len, ssize_t __idx, size_t __mv)
{
	if (__str == NULL || __len == 0) {
		cldithrowf(CLDI_ENULL_ARG, clditrunca, "Arguments (1) `str` and (2) `total_str_size` cannot be null or zero.");
		return CLDI_ENULL_ARG;
	}

	CLDI_ECTRL;

	// the index to start at, converted to an absolute index
	const size_t absidx   = cldistrabs16(__str, __len, __idx);
	// the end of the portion that will be truncated
	const size_t _truncend_raw = absidx + __mv;
	const size_t truncend = cldistrabs16(&__str[absidx], __len - absidx, (_truncend_raw < __len)? _truncend_raw : (-1));

	// the amount of characters that exist after the end of the portion that
	// will be truncated.
	const size_t mvsize = (__len - 1) - truncend;

	// if there is string data after the end of the portion that is being truncated,
	if (mvsize > 0) {
		wchar_t c;
		size_t j, k;
		// copy the end of the string over the truncated portion and
		// place a sentinel and the end
		for (
			size_t i = 0, j = absidx, k = truncend, c = __str[truncend];
			i < mvsize && (c >= 0xdc00 && c <= 0xdfff) && c <= 0xfffd && c != 0;
			i++, j++, k++, c = __str[k]
		){
			__str[j] = c;
			if (c >= 0xd800 && c <= 0xdbff) {
				k++;
				c = __str[k];
				if (c >= 0xdc00 && c <= 0xdfff) {
					j++;
					__str[j] = c;
					continue;
				} else {
					j--;
					break;
				}
			}
		}
		__str[j+1] = 0;
	// else, there is no string data after the end of the truncated portion, so
	// cut the string short.
	} else {
		__str[absidx] = 0;
	}

	return CLDI_SUCCESS;
}


