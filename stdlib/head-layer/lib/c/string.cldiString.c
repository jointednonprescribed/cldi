


/* Implementing: cldi-head: string.h: struct _CLDISTR */
#include <cldi/head/string.h>



/* Include string error message constants from string.c: */
extern const char CLDIERRMSG_STR_FAIL_ALLOC[];
extern const char CLDIERRMSG_STR_FAIL_DROP[];
extern const char CLDIERRMSG_STR_FAIL_COPY[];
extern const char CLDIERRMSG_STR_FAIL_DROP_AFTER_COPY[];
extern const char CLDIERRMSG_STR_NULL_SELF[];
extern const char CLDIERRMSG_STR_FAIL_INIT[];
extern const char CLDIERRMSG_STR_FAIL_DROP_AFTER_INIT[];
extern const char CLDIERRMSG_STR_FAIL_GEN_IMASK[];
extern const char CLDIERRMSG_STR_FAIL_GET_ADDR[];
extern const char CLDIERRMSG_STR_FAIL_GET_OFF[];
extern const char CLDIERRMSG_STR_FAIL_DROP_AFTER_OFF[];
extern const char CLDIERRMSG_STR_FAIL_DROP_IMASK[];
extern const char CLDIERRMSG_STR_NULL_DATA[];
extern const char CLDIERRMSG_STR_FAIL_DROP_ADOPT_CHANGE[];
extern const char CLDIERRMSG_STR_FAIL_DROP_NEW_BLOCK[];
extern const char CLDIERRMSG_STR_NOAUTHOR[];
extern const char CLDIERRMSG_STR_NOOWNER[];
extern const char CLDIERRMSG_STR_NOGROUP[];


int cldiStringCompileMemFlags(int strflags)
{
	// start with owner read perms
	int flags = CLDI_MBLK_OREAD;

	// if string is not const, add owner write perms
	if (strflags & CLDI_CONST_STRING == 0) {
		flags |= CLDI_MBLK_OWRTE;
		// if string is not const, the only permission allowed for group and public
		// is read, so only read permissions will be checked and subsequently added
		// to the return.

		// add public permissions
		// public perms start at bit 2 (most significant is third from right) when
		// conforming to CLDI_MBLK_FLAG, but when conforming to CLDI_STRING_FLAG they
		// start at bit 5 (most significant is sixth from the right), so after masking,
		// the bits must be shifted right by exactly 3 places.
		flags |= ((strflags & CLDI_STRING_PREAD) >> 3);

		// add group permissions
		// group perms start at bit 5 (most significant is sixth from right) when
		// conforming to CLDI_MBLK_FLAG, but when conforming to CLDI_STRING_FLAG they
		// start at bit 7 (most significant is eighth from the right), so after masking,
		// the bits must be shifted right by exactly 2 places.
		flags |= ((strflags & CLDI_STRING_GREAD) >> 2);
	} else {
		// if string is not const, add all specified permissions (read and write) that are
		// found inside of 'strflags'.
		flags |= ((strflags & CLDI_STRING_PUBLIC_PERMS) >> 3);
		flags |= ((strflags & CLDI_STRING_GROUP_PERMS)  >> 2);
	}

	return flags;
}
int cldiStringFlagsSetFormat(int flags, CLDI_STRING_FLAG enc)
{
	flags &= CLDI_STRFLAGS_MASK;
	flags &= ~CLDI_STRING_ENCFMT;
	flags |= enc;
	return flags;
}
int cldiStringFlagsSetPerms(int flags, int perms)
{
	flags &= CLDI_STRFLAGS_MASK;
	flags &= ~CLDI_STRING_PERMS;
	flags |= perms & CLDI_STRING_PERMS;
	return flags;
}
int cldiStringFlagsSetGroupPerms(int flags, int perms)
{
	flags &= CLDI_STRFLAGS_MASK;
	flags &= ~CLDI_STRING_GROUP_PERMS;
	flags |= perms & CLDI_STRING_GROUP_PERMS;
	return flags;
}
int cldiStringFlagsSetPublicPerms(int flags, int perms)
{
	flags &= CLDI_STRFLAGS_MASK;
	flags &= ~CLDI_STRING_PUBLIC_PERMS;
	flags |= perms & CLDI_STRING_PUBLIC_PERMS;
	return flags;
}
int cldiStringFlagsSetWithMask(int flags, int mask, int newval)
{
	mask &= CLDI_STRFLAGS_MASK;
	newval &= mask;
	flags &= CLDI_STRFLAGS_MASK;
	flags &= ~mask;
	flags |= newval;
	return flags;
}


CLDISTAT cldiInitString(cldistr_t *self)
{
	CLDI_ECTRL;

	self->len   = 0;
	self->flags = 0;
	cldiInitMemref(&self->data);

	return CLDI_ERRNO;
}
CLDISTAT cldiInitStringC(cldistr_t *self, const char *str)
{
	return cldiInitStringNCEx(self, cldistrlen(str), str, 0, CLDI_DEFAULT_CSTRING, false);
}
CLDISTAT cldiInitStringCEx(cldistr_t *self, const char *str, size_t extracap, int flags, bool utf8_src)
{
	return cldiInitStringNCEx(self, cldistrlen(str), str, extracap, flags, utf8_src);
}
CLDISTAT cldiInitStringNC(cldistr_t *self, size_t n, const char *str)
{
	return cldiInitStringNCEx(self, n, str, 0, CLDI_DEFAULT_CSTRING, false);
}
CLDISTAT cldiInitStringNCEx(cldistr_t *self, size_t n, const char *str, size_t extracap, int flags, bool utf8_src)
{
	// Any of these values being null is not going to work...
	if (self == NULL || str == NULL || n == 0) {
		cldithrowf(CLDI_ENULL_ARG, cldiInitStringNCEx, "Arguments `self`, `str`, and `n` must not be null or 0.");
		return n;
	}

	// required ec control
	CLDI_ECTRL

	// exclude internal flags
	flags &= ~CLDI_STRFLAGS_INTERNAL;

	// extract UTF-16 indicator bit
	const bool utf16 = flags & CLDI_UTF16STRING;

	// the total character capacity of self once initialized
	const size_t total_stringlen = n + extracap;

	// This values should remain 0 until the string has actually been initialized.
	self->len   = 0;
	// this value can be set right now
	self->flags = flags; // string object inherits flags
	// try to initialize self.data with new empty array, return error if it fails.
	cldiInitMemrefNewArrayEx(
		&self->data,
		utf16? cldiWCharTypeInfo: cldiCharTypeInfo, // wchar_t if UTF-16, char
		total_stringlen, //                            otherwise
		cldiStringCompileMemFlags(flags), // convert flags for memory block
		cldiStringDropBlock // string object's provided memory block destructor
	);
	CLDI_CATCH { // ec check
		cldiAddTraceback(cldiInitStringNCEx, CLDIERRMSG_STR_FAIL_ALLOC);
		return CLDI_ERRNO;
	}

	// try to copy/convert the string to the new memory.
	if (utf16) {
		// if self is targeting UTF-16, and the source is UTF-8, use UTF-8->UTF-16
		// converter function.
		if (utf8_src)
			n -= cldistrnconv8_16(n, (wchar_t*) cldiMemrefGetAddress(&self->data), str);
		// source is ascii, so use ASCII->UTF-16 converter function.
		else 
			n -= cldistrnconva_16(n, (wchar_t*) cldiMemrefGetAddress(&self->data), str);
	} else {
		// else if flags does not contain a UTF-8 indicator bit (self is targeting
		// ASCII), but source is encoded in UTF-8, use UTF-8->ASCII converter function.
		if ((flags & CLDI_UTF8STRING == 0) && utf8_src)
			n -= cldistrnconv8_a(n, (char*) cldiMemrefGetAddress(&self->data), str);
		// else, either both strings are ASCII, or self is targetting UTF-8 while
		// source is encoded in ASCII, so only an ASCII string copy is required
		// (ASCII characters are also valid UTF-8 characters).
		else
			n -= cldistrncpy(n, (char*) cldiMemrefGetAddess(&self->data), str);
	}
	if (!cldiIsPermissible() || n == 0) { // ec check
		cldiAddTraceback(cldiInitStringNCEx, CLDIERRMSG_STR_FAIL_COPY);
		cldiDropMemref(&self->data);
		CLDI_CATCH
			cldiAddTraceback(cldiInitStringNCEx, CLDIERRMSG_STR_FAIL_DROP_AFTER_COPY);
		return CLDI_ERRNO;
	} else {
		// string passed all checks and got copied/converted successfully, so set
		// len to n, and add the DEFINED flag, the string is final.
		self->len    = n;
		self->flags |= CLDI_STRING_DEFINED;

		return CLDI_ERRNO;
	}
}
CLDISTAT cldiInitStringW(cldistr_t *self, const wchar_t *str)
{
	return cldiInitStringNWEx(self, cldiwstrlen(str), str, 0, CLDI_DEFAULT_WSTRING);
}
CLDISTAT cldiInitStringWEx(cldistr_t *self, const wchar_t *str, size_t extracap, int flags)
{
	return cldiInitStringNWEx(self, cldiwstrlen(str), str, extracap, flags);
}
CLDISTAT cldiInitStringNW(cldistr_t *self, size_t n, const wchar_t *str)
{
	return cldiInitStringNWEx(self, n, str, 0, CLDI_DEFAULT_WSTRING);
}
CLDISTAT cldiInitStringNWEx(cldistr_t *self, size_t n, const wchar_t *str, size_t extracap, int flags)
{
	// Any of these values being null is not going to work...
	if (self == NULL || str == NULL || n == 0) {
		cldithrowf(CLDI_ENULL_ARG, cldiInitStringNWEx, "Arguments `self`, `str`, and `n` must notmysql be null or 0.");
		return n;
	}

	// required ec control
	CLDI_ECTRL;

	// exclude internal flags
	flags &= ~CLDI_STRFLAGS_INTERNAL;

	// extract encoding format indicator bits
	const int enc = flags & CLDI_STRING_ENCFMT;
	// test for UTF-16 target, UTF-8 target, or ASCII target
	const bool utf16 = enc > CLDI_UTF8STRING, utf8 = enc == CLDI_UTF8STRING;

	// the total character capacity of self once initialized
	const size_t total_stringlen = n + extracap;

	// This values should remain 0 until the string has actually been initialized.
	self->len   = 0;
	// this value can be set right now
	self->flags = flags; // object inherits flags
	// try to initialize self.data with new empty array, return error if it fails.
	cldiInitMemrefNewArrayEx(
		&self->data,
		utf16? cldiWCharTypeInfo: cldiCharTypeInfo, // the destination string
		total_stringlen, //                            may not be UTF-16.
		cldiStringCompileMemFlags(flags), // convert flags for memory block
		cldiStringDropBlock // string object's provided memory block destructor
	);
	CLDI_CATCH { // ec check
		cldiAddTraceback(cldiInitStringNWEx, CLDIERRMSG_STR_FAIL_ALLOC);
		return CLDI_ERRNO;
	}

	// try to copy/convert the string to the new memory.
	if (utf16) // self is meant to be encoded in UTF-16 (so only a copy is required).
		n -= cldistrncpy16(n, (wchar_t*) cldiMemrefGetAddress(&self->data), str);
	else if (utf8) // self is meant to be encoded in UTF-8
		n -= cldistrnconv16_8(n, (char*) cldiMemrefGetAddress(&self->data), str);
	else // self is meant to be encoded in ASCII
		n -= cldistrnconv16_a(n, (char*) cldiMemrefGetAddress(&self->data), str);
	if (!cldiIsPermissible() || n == 0) { // ec check
		cldiAddTraceback(cldiInitStringNWEx, CLDIERRMSG_STR_FAIL_COPY);
		cldiDropMemref(&self->data);
		CLDI_CATCH
			cldiAddTraceback(cldiInitStringNWEx, CLDIERRMSG_STR_FAIL_DROP_AFTER_COPY);
		return CLDI_ERRNO; // pass stacked ec
	} else {
		// string passed all checks and got copied/converted successfully, so set
		// len to n, and add the DEFINED flag, the string is final.
		self->len    = n;
		self->flags |= CLDI_STRING_DEFINED;

		// by this point, ec should be permissible, but if it isn't it will be
		// passed anyway.
		return CLDI_ERRNO;
	}
}
CLDISTAT cldiInitStringCopy(cldistr_t *self, const cldistr_t *copy_of)
{
	return cldiInitStringCopyEx(self, copy_of, 0, copy_of->flags);
}
CLDISTAT cldiInitStringCopyEx(cldistr_t *self, const cldistr_t *copy_of, size_t extracap, int flags)
{
	// self and copy_of must be non-null.
	if (self == NULL) {
		cldithrowf(CLDI_ENULL_SELF, cldiInitStringCopyEx, CLDIERRMSG_STR_NULL_SELF);
		return CLDI_ENULL_SELF;
	} else if (copy_of == NULL) {
		cldithrowf(CLDI_ENULL_ARG, cldiInitStringCopyEx, "Argument `copy_of` must not be null or 0.");
		return CLDI_ENULL_ARG;
	}

	// required ec control
	CLDI_ECTRL;

	// attempt to access the copy_of's data in a const context
	const void *const copydata = cldiMemrefGetConstAddress(&copy_of->data);
	CLDI_CATCH { // ec check
		return CLDI_ERRNO;
	}

	// exclude internal flags;
	flags &= ~CLDI_STRFLAGS_INTERNAL;

	// extract encoding format indicator bits from flags and copy_of
	const int enc_s = flags & CLDI_STRING_ENCFMT, enc_c = copy_of->flags & CLDI_STRING_ENCFMT;

	// get the length of the copy
	size_t copylen = cldiStringLength(copy_of);
	// the total character capacity of the string
	const size_t totalcap = copylen + extracap;

	self->len = 0;
	self->flags = flags;
	// initalize with empty data bank
	cldiInitStringEmptyEx(self, totalcap, flags);
	CLDI_CATCH // ec check
		return CLDI_ERRNO;

	void *const data = cldiMemrefGetAddress(&self->data);
	CLDI_CATCH { // ec check
		cldiAddTraceback(cldiInitStringCopyEx, "Failed to finish initializing the string; failed to fetch address from cldimemref object.");
		return CLDI_ERRNO;
	}

	if (enc_s > CLDI_UTF8STRING) {
		if (enc_c > CLDI_UTF8STRING)
			copylen -= cldistrncpy16(copylen, (wchar_t*) data, (const wchar_t*) copydata);
		else if (enc_c == CLDI_UTF8STRING)
			copylen -= cldistrnconv8_16(copylen, (wchar_t*) data, (const char*) copydata);
		else
			copylen -= cldistrnconva_16(copylen, (wchar_t*) data, (const char*) copydata);
	} else if (enc_s == CLDI_UTF8STRING) {
		if (enc_c > CLDI_UTF8STRING)
			copylen -= cldistrnconv16_8(copylen, (char*) data, (const wchar_t*) copydata);
		else if (enc_c == CLDI_UTF8STRING)
			copylen -= cldistrncpy8(copylen, (char*) data, (const char*) copydata);
		else
			copylen -= cldistrncpy(copylen, (char*) data, (const char*) copydata);
	} else {
		if (enc_c > CLDI_UTF8STRING)
			copylen -= cldistrnconv16_a(copylen, (char*) data, (const wchar_t*) copydata);
		else if (enc_c == CLDI_UTF8STRING)
			copylen -= cldistrnconv8_a(copylen, (char*) data, (const char*) copydata);
		else
			copylen -= cldistrncpy(copylen, (char*) data, (const char*) copydata);
	}
	if (!cldiIsPermissible() || copylen == 0) { // ec check
		cldiAddTraceback(cldiInitStringCopyEx, CLDIERRMSG_STR_FAIL_COPY);
		cldiDropMemref(&self->data);
		CLDI_CATCH
			cldiAddTraceback(cldiInitStringCopyEx, CLDIERRMSG_STR_FAIL_DROP_AFTER_COPY);
		return CLDI_ERRNO;
	} else {
		self->len    = copylen;
		self->flags |= CLDI_STRING_DEFINED;

		return CLDI_ERRNO;
	}
}
CLDISTAT cldiInitStringBorrowed(cldistr_t *self, const cldistr_t *borrow)
{
	return cldiInitStringBorrowedEx(self, borrow, borrow->flags);
}
CLDISTAT cldiInitStringBorrowedEx(cldistr_t *self, const cldistr_t *borrow, int flags)
{
	if (self == NULL) {
		cldithrowf(CLDI_ENULL_SELF, cldiInitStringCopyEx, CLDIERRMSG_STR_NULL_SELF);
		return CLDI_ENULL_SELF;
	} else if (borrow == NULL) {
		cldithrowf(CLDI_ENULL_ARG, cldiInitStringCopyEx, "Argument `borrow` must not be null or 0.");
		return CLDI_ENULL_ARG;
	} else if (cldiStringIsNull(borrow)) {
		return cldiInitString(self);
	}

	// required ec control
	CLDI_ECTRL;

	// exclude internal flags
	flags &= ~CLDI_STRFLAGS_INTERNAL;

	// get target encoding format of self, and current encoding format of `borrow`.
	const int enc_s = flags & CLDI_STRING_ENCFMT, enc_b = borrow->flags & CLDI_STRING_ENCFMT;

	// if both indicate the same format (2 and 3 are both equivalent in indicating
	// UTF-16), or `borrow` is ASCII, while self is targeting UTF-8, direct borrow
	// is possible, otherwise a copy is necessary since the string must be converted.
	if (
		enc_s == enc_b ||
		(enc_s == CLDI_UTF8STRING && enc_b == CLDI_ASCIISTRING) ||
		(enc_s > CLDI_UTF8STRING && enc_b > CLDI_UTF8STRING)
	){
		self->len = 0;
		self->flags = 0;
		cldiInitMemref(&self->data);
		return cldiStringBorrow(self, borrow);
	} else
		return cldiInitStringCopyEx(self, borrow, 0, flags);
}
CLDISTAT cldiInitStringEmpty(cldistr_t *self, size_t bufsize)
{
	return cldiInitStringEmptyEx(self, bufsize, CLDI_DEFAULT_CSTRING);
}
CLDISTAT cldiInitStringEmptyW(cldistr_t *self, size_t bufsize)
{
	return cldiInitStringEmptyEx(self, bufsize, CLDI_DEFAULT_WSTRING);
}
CLDISTAT cldiInitStringEmptyEx(cldistr_t *self, size_t bufsize, int flags)
{
	if (self == NULL) {
		cldithrowf(CLDI_ENULL_SELF, cldiInitStringCopyEx, CLDIERRMSG_STR_NULL_SELF);
		return CLDI_ENULL_SELF;
	} else if (bufsize == 0) {
		cldiInitString(self);
		self->flags = flags & ~CLDI_STRFLAGS_INTERNAL;
		return CLDI_ERRNO;
	}

	CLDI_ECTRL;

	// exclude internal, noninputtable bits
	flags &= ~CLDI_STRFLAGS_INTERNAL;

	// extract bit 1 (utf-16 indicator)
	const bool utf16 = (flags & 0x2);

	// length is 0, string is empty
	self->len   = 0;
	// pass flags to string
	self->flags = flags;
	// initialize memref with new char array
	cldiInitMemrefNewArrayEx(
		&self->data,
		utf16? cldiWCharTypeInfo: cldiCharTypeInfo,
		bufsize,
		cldiStringCompileMemFlags(flags),
		cldiStringDropBlock
	);
	CLDI_CATCH
		cldiAddTraceback(cldiInitStringEmptyEx, CLDIERRMSG_STR_FAIL_ALLOC);

	return CLDI_ERRNO;
}

cldistr_t cldiMakeString()
{
	cldistr_t self;
	cldiInitString(&self);
	return self;
}
cldistr_t cldiMakeStringC(const char *str)
{
	cldistr_t self;
	cldiInitStringC(&self, str);
	return self;
}
cldistr_t cldiMakeStringCEx(const char *str, size_t extracap, int flags, bool utf8_src)
{
	cldistr_t self;
	cldiInitStringCEx(&self, str, extracap, flags, utf8_src);
	return self;
}
cldistr_t cldiMakeStringNC(size_t n, const char *str)
{
	cldistr_t self;
	cldiInitStringNC(&self, n, str);
	return self;
}
cldistr_t cldiMakeStringNCEx(size_t n, const char *str, size_t extracap, int flags, bool utf8_src)
{
	cldistr_t self;
	cldiInitStringNCEx(&self, n, str, extracap, flags, utf8_src);
	return self;
}
cldistr_t cldiMakeStringW(const wchar_t *str)
{
	cldistr_t self;
	cldiInitStringW(&self, str);
	return self;
}
cldistr_t cldiMakeStringWEx(const wchar_t *str, size_t extracap, int flags)
{
	cldistr_t self;
	cldiInitStringWEx(&self, str, extracap, flags);
	return self;
}
cldistr_t cldiMakeStringNW(size_t n, const wchar_t *str)
{
	cldistr_t self;
	cldiInitStringNW(&self, n, str);
	return self;
}
cldistr_t cldiMakeStringNWEx(size_t n, const wchar_t *str, size_t extracap, int flags)
{
	cldistr_t self;
	cldiInitStringNWEx(&self, n, str, extracap, flags);
	return self;
}
cldistr_t cldiMakeStringCopy(const cldistr_t *copy_of)
{
	cldistr_t self;
	cldiInitStringCopy(&self, copy_of);
	return self;
}
cldistr_t cldiMakeStringCopyEx(const cldistr_t *copy_of, size_t extracap, int flags)
{
	cldistr_t self;
	cldiInitStringCopyEx(&self, copy_of, extracap, flags);
	return self;
}
cldistr_t cldiMakeStringBorrowed(const cldistr_t *borrow)
{
	cldistr_t self;
	cldiInitStringBorrowed(&self, borrow);
	return self;
}
cldistr_t cldiMakeStringBorrowedEx(const cldistr_t *borrow, int flags)
{
	cldistr_t self;
	cldiInitStringBorrowedEx(&self, borrow, flags);
	return self;
}
cldistr_t cldiMakeStringEmpty(size_t bufsize)
{
	cldistr_t self;
	cldiInitStringEmpty(&self, bufsize);
	return self;
}
cldistr_t cldiMakeStringEmptyW(size_t bufsize)
{
	cldistr_t self;
	cldiInitStringEmptyW(&self, bufsize);
	return self;
}
cldistr_t cldiMakeStringEmptyEx(size_t bufsize, int flags)
{
	cldistr_t self;
	cldiInitStringEmptyEx(&self, bufsize, flags);
	return self;
}

cldimemref cldiNewString()
{
	CLDI_ECTRL;

	cldimemref r;
	cldiInitMemrefNewBlock(
		&r,
		(clditypeinfo_t){
			.size=sizeof(cldistr_t),
			.templ=CLDI_STRUCT_TYPE
		},
		CLDI_MBLK_OREAD|CLDI_MBLK_OWRTE|CLDI_MBLK_GREAD|CLDI_MBLK_PREAD|CLDI_MBLK_OAUTH
	);
	CLDI_CATCH {
		cldiAddTraceback(cldiNewString, CLDIERRMSG_STR_FAIL_ALLOC);
		return r;
	}

	cldistr_t *strptr = (cldistr_t*) cldiMemrefGetAddress(&r);

	cldiInitString(strptr);
	CLDI_CATCH {
		cldiAddTraceback(cldiNewString, CLDIERRMSG_STR_FAIL_INIT);
		cldiDropMemref(&r);
		CLDI_CATCH
			cldiAddTraceback(cldiNewString, CLDIERRMSG_STR_FAIL_DROP_AFTER_INIT);
		return r;
	}

	return r;
}
cldimemref cldiNewStringC(const char *str)
{
	CLDI_ECTRL;

	cldimemref r;
	cldiInitMemrefNewBlock(
		&r,
		(clditypeinfo_t){
			.size=sizeof(cldistr_t),
			.templ=CLDI_STRUCT_TYPE
		},
		CLDI_MBLK_OREAD|CLDI_MBLK_OWRTE|CLDI_MBLK_GREAD|CLDI_MBLK_PREAD|CLDI_MBLK_OAUTH
	);
	CLDI_CATCH {
		cldiAddTraceback(cldiNewStringC, CLDIERRMSG_STR_FAIL_ALLOC);
		return r;
	}

	cldistr_t *strptr = (cldistr_t*) cldiMemrefGetAddress(&r);

	cldiInitStringC(strptr, str);
	CLDI_CATCH {
		cldiAddTraceback(cldiNewStringC, CLDIERRMSG_STR_FAIL_INIT);
		cldiDropMemref(&r);
		CLDI_CATCH
			cldiAddTraceback(cldiNewStringC, CLDIERRMSG_STR_FAIL_DROP_AFTER_INIT);
		return r;
	}

	return r;
}
cldimemref cldiNewStringCEx(const char *str, size_t extracap, int flags, bool utf8_src)
{
	CLDI_ECTRL;

	cldimemref r;
	cldiInitMemrefNewBlock(
		&r,
		(clditypeinfo_t){
			.size=sizeof(cldistr_t),
			.templ=CLDI_STRUCT_TYPE
		},
		CLDI_MBLK_OREAD|CLDI_MBLK_OWRTE|CLDI_MBLK_GREAD|CLDI_MBLK_PREAD|CLDI_MBLK_OAUTH
	);
	CLDI_CATCH {
		cldiAddTraceback(cldiNewStringCEx, CLDIERRMSG_STR_FAIL_ALLOC);
		return r;
	}

	cldistr_t *strptr = (cldistr_t*) cldiMemrefGetAddress(&r);

	cldiInitStringCEx(strptr, str, extracap, flags, utf8_src);
	CLDI_CATCH {
		cldiAddTraceback(cldiNewStringCEx, CLDIERRMSG_STR_FAIL_INIT);
		cldiDropMemref(&r);
		CLDI_CATCH
			cldiAddTraceback(cldiNewStringCEx, CLDIERRMSG_STR_FAIL_DROP_AFTER_INIT);
		return r;
	}

	return r;
}
cldimemref cldiNewStringNC(size_t n, const char *str)
{
	CLDI_ECTRL;

	cldimemref r;
	cldiInitMemrefNewBlock(
		&r,
		(clditypeinfo_t){
			.size=sizeof(cldistr_t),
			.templ=CLDI_STRUCT_TYPE
		},
		CLDI_MBLK_OREAD|CLDI_MBLK_OWRTE|CLDI_MBLK_GREAD|CLDI_MBLK_PREAD|CLDI_MBLK_OAUTH
	);
	CLDI_CATCH {
		cldiAddTraceback(cldiNewStringNC, CLDIERRMSG_STR_FAIL_ALLOC);
		return r;
	}

	cldistr_t *strptr = (cldistr_t*) cldiMemrefGetAddress(&r);

	cldiInitStringNC(strptr, n, str);
	CLDI_CATCH {
		cldiAddTraceback(cldiNewStringNC, CLDIERRMSG_STR_FAIL_INIT);
		cldiDropMemref(&r);
		CLDI_CATCH
			cldiAddTraceback(cldiNewStringNC, CLDIERRMSG_STR_FAIL_DROP_AFTER_INIT);
		return r;
	}

	return r;
}
cldimemref cldiNewStringNCEx(size_t n, const char *str, size_t extracap, int flags, bool utf8_src)
{
	CLDI_ECTRL;

	cldimemref r;
	cldiInitMemrefNewBlock(
		&r,
		(clditypeinfo_t){
			.size=sizeof(cldistr_t),
			.templ=CLDI_STRUCT_TYPE
		},
		CLDI_MBLK_OREAD|CLDI_MBLK_OWRTE|CLDI_MBLK_GREAD|CLDI_MBLK_PREAD|CLDI_MBLK_OAUTH
	);
	CLDI_CATCH {
		cldiAddTraceback(cldiNewStringNCEx, CLDIERRMSG_STR_FAIL_ALLOC);
		return r;
	}

	cldistr_t *strptr = (cldistr_t*) cldiMemrefGetAddress(&r);

	cldiInitStringNCEx(strptr, n, str, extracap, flags, utf8_src);
	CLDI_CATCH {
		cldiAddTraceback(cldiNewStringNCEx, CLDIERRMSG_STR_FAIL_INIT);
		cldiDropMemref(&r);
		CLDI_CATCH
			cldiAddTraceback(cldiNewStringNCEx, CLDIERRMSG_STR_FAIL_DROP_AFTER_INIT);
		return r;
	}

	return r;
}
cldimemref cldiNewStringW(const wchar_t *str)
{
	CLDI_ECTRL;

	cldimemref r;
	cldiInitMemrefNewBlock(
		&r,
		(clditypeinfo_t){
			.size=sizeof(cldistr_t),
			.templ=CLDI_STRUCT_TYPE
		},
		CLDI_MBLK_OREAD|CLDI_MBLK_OWRTE|CLDI_MBLK_GREAD|CLDI_MBLK_PREAD|CLDI_MBLK_OAUTH
	);
	CLDI_CATCH {
		cldiAddTraceback(cldiNewStringW, CLDIERRMSG_STR_FAIL_ALLOC);
		return r;
	}

	cldistr_t *strptr = (cldistr_t*) cldiMemrefGetAddress(&r);

	cldiInitStringW(strptr, str);
	CLDI_CATCH {
		cldiAddTraceback(cldiNewStringW, CLDIERRMSG_STR_FAIL_INIT);
		cldiDropMemref(&r);
		CLDI_CATCH
			cldiAddTraceback(cldiNewStringW, CLDIERRMSG_STR_FAIL_DROP_AFTER_INIT);
		return r;
	}

	return r;
}
cldimemref cldiNewStringWEx(const wchar_t *str, size_t extracap, int flags)
{
	CLDI_ECTRL;

	cldimemref r;
	cldiInitMemrefNewBlock(
		&r,
		(clditypeinfo_t){
			.size=sizeof(cldistr_t),
			.templ=CLDI_STRUCT_TYPE
		},
		CLDI_MBLK_OREAD|CLDI_MBLK_OWRTE|CLDI_MBLK_GREAD|CLDI_MBLK_PREAD|CLDI_MBLK_OAUTH
	);
	CLDI_CATCH {
		cldiAddTraceback(cldiNewStringWEx, CLDIERRMSG_STR_FAIL_ALLOC);
		return r;
	}

	cldistr_t *strptr = (cldistr_t*) cldiMemrefGetAddress(&r);

	cldiInitStringWEx(strptr, str, extracap, flags);
	CLDI_CATCH {
		cldiAddTraceback(cldiNewStringWEx, CLDIERRMSG_STR_FAIL_INIT);
		cldiDropMemref(&r);
		CLDI_CATCH
			cldiAddTraceback(cldiNewStringWEx, CLDIERRMSG_STR_FAIL_DROP_AFTER_INIT);
		return r;
	}

	return r;
}
cldimemref cldiNewStringNW(size_t n, const wchar_t *str)
{
	CLDI_ECTRL;

	cldimemref r;
	cldiInitMemrefNewBlock(
		&r,
		(clditypeinfo_t){
			.size=sizeof(cldistr_t),
			.templ=CLDI_STRUCT_TYPE
		},
		CLDI_MBLK_OREAD|CLDI_MBLK_OWRTE|CLDI_MBLK_GREAD|CLDI_MBLK_PREAD|CLDI_MBLK_OAUTH
	);
	CLDI_CATCH {
		cldiAddTraceback(cldiNewStringNW, CLDIERRMSG_STR_FAIL_ALLOC);
		return r;
	}

	cldistr_t *strptr = (cldistr_t*) cldiMemrefGetAddress(&r);

	cldiInitStringNW(strptr, n, str);
	CLDI_CATCH {
		cldiAddTraceback(cldiNewStringNW, CLDIERRMSG_STR_FAIL_INIT);
		cldiDropMemref(&r);
		CLDI_CATCH
			cldiAddTraceback(cldiNewStringNW, CLDIERRMSG_STR_FAIL_DROP_AFTER_INIT);
		return r;
	}

	return r;
}
cldimemref cldiNewStringNWEx(size_t n, const wchar_t *str, size_t extracap, int flags)
{
	CLDI_ECTRL;

	cldimemref r;
	cldiInitMemrefNewBlock(
		&r,
		(clditypeinfo_t){
			.size=sizeof(cldistr_t),
			.templ=CLDI_STRUCT_TYPE
		},
		CLDI_MBLK_OREAD|CLDI_MBLK_OWRTE|CLDI_MBLK_GREAD|CLDI_MBLK_PREAD|CLDI_MBLK_OAUTH
	);
	CLDI_CATCH {
		cldiAddTraceback(cldiNewString, CLDIERRMSG_STR_FAIL_ALLOC);
		return r;
	}

	cldistr_t *strptr = (cldistr_t*) cldiMemrefGetAddress(&r);

	cldiInitStringNWEx(strptr, n, str, extracap, flags);
	CLDI_CATCH {
		cldiAddTraceback(cldiNewStringNWEx, CLDIERRMSG_STR_FAIL_INIT);
		cldiDropMemref(&r);
		CLDI_CATCH
			cldiAddTraceback(cldiNewStringNWEx, CLDIERRMSG_STR_FAIL_DROP_AFTER_INIT);
		return r;
	}

	return r;
}
cldimemref cldiNewStringCopy(const cldistr_t *copy_of)
{
	CLDI_ECTRL;

	cldimemref r;
	cldiInitMemrefNewBlock(
		&r,
		(clditypeinfo_t){
			.size=sizeof(cldistr_t),
			.templ=CLDI_STRUCT_TYPE
		},
		CLDI_MBLK_OREAD|CLDI_MBLK_OWRTE|CLDI_MBLK_GREAD|CLDI_MBLK_PREAD|CLDI_MBLK_OAUTH
	);
	CLDI_CATCH {
		cldiAddTraceback(cldiNewStringCopy, CLDIERRMSG_STR_FAIL_ALLOC);
		return r;
	}

	cldistr_t *strptr = (cldistr_t*) cldiMemrefGetAddress(&r);

	cldiInitStringCopy(strptr, copy_of);
	CLDI_CATCH {
		cldiAddTraceback(cldiNewStringCopy, CLDIERRMSG_STR_FAIL_INIT);
		cldiDropMemref(&r);
		CLDI_CATCH
			cldiAddTraceback(cldiNewString, CLDIERRMSG_STR_FAIL_DROP_AFTER_INIT);
		return r;
	}

	return r;
}
cldimemref cldiNewStringCopyEx(const cldistr_t *copy_of, size_t extracap, int flags)
{
	CLDI_ECTRL;

	cldimemref r;
	cldiInitMemrefNewBlock(
		&r,
		(clditypeinfo_t){
			.size=sizeof(cldistr_t),
			.templ=CLDI_STRUCT_TYPE
		},
		CLDI_MBLK_OREAD|CLDI_MBLK_OWRTE|CLDI_MBLK_GREAD|CLDI_MBLK_PREAD|CLDI_MBLK_OAUTH
	);
	CLDI_CATCH {
		cldiAddTraceback(cldiNewStringCopyEx, CLDIERRMSG_STR_FAIL_ALLOC);
		return r;
	}

	cldistr_t *strptr = (cldistr_t*) cldiMemrefGetAddress(&r);

	cldiInitStringCopyEx(strptr, copy_of, extracap, flags);
	CLDI_CATCH {
		cldiAddTraceback(cldiNewStringCopyEx, CLDIERRMSG_STR_FAIL_INIT);
		cldiDropMemref(&r);
		CLDI_CATCH
			cldiAddTraceback(cldiNewStringCopyEx, CLDIERRMSG_STR_FAIL_DROP_AFTER_INIT);
		return r;
	}

	return r;
}
cldimemref cldiNewStringBorrowed(const cldistr_t *borrow)
{
	CLDI_ECTRL;

	cldimemref r;
	cldiInitMemrefNewBlock(
		&r,
		(clditypeinfo_t){
			.size=sizeof(cldistr_t),
			.templ=CLDI_STRUCT_TYPE
		},
		CLDI_MBLK_OREAD|CLDI_MBLK_OWRTE|CLDI_MBLK_GREAD|CLDI_MBLK_PREAD|CLDI_MBLK_OAUTH
	);
	CLDI_CATCH {
		cldiAddTraceback(cldiNewStringBorrowed, CLDIERRMSG_STR_FAIL_ALLOC);
		return r;
	}

	cldistr_t *strptr = (cldistr_t*) cldiMemrefGetAddress(&r);

	cldiInitStringBorrowed(strptr, borrow);
	CLDI_CATCH {
		cldiAddTraceback(cldiNewStringBorrowed, CLDIERRMSG_STR_FAIL_INIT);
		cldiDropMemref(&r);
		CLDI_CATCH
			cldiAddTraceback(cldiNewStringBorrowed, CLDIERRMSG_STR_FAIL_DROP_AFTER_INIT);
		return r;
	}

	return r;
}
cldimemref cldiNewStringBorrowedEx(const cldistr_t *borrow, int flags)
{
	CLDI_ECTRL;

	cldimemref r;
	cldiInitMemrefNewBlock(
		&r,
		(clditypeinfo_t){
			.size=sizeof(cldistr_t),
			.templ=CLDI_STRUCT_TYPE
		},
		CLDI_MBLK_OREAD|CLDI_MBLK_OWRTE|CLDI_MBLK_GREAD|CLDI_MBLK_PREAD|CLDI_MBLK_OAUTH
	);
	CLDI_CATCH {
		cldiAddTraceback(cldiNewStringBorrowedEx, CLDIERRMSG_STR_FAIL_ALLOC);
		return r;
	}

	cldistr_t *strptr = (cldistr_t*) cldiMemrefGetAddress(&r);

	cldiInitStringBorrowedEx(strptr, borrow, flags);
	CLDI_CATCH {
		cldiAddTraceback(cldiNewStringBorrowedEx, CLDIERRMSG_STR_FAIL_INIT);
		cldiDropMemref(&r);
		CLDI_CATCH
			cldiAddTraceback(cldiNewStringBorrowedEx, CLDIERRMSG_STR_FAIL_DROP_AFTER_INIT);
		return r;
	}

	return r;
}
cldimemref cldiNewStringEmpty(size_t bufsize)
{
	CLDI_ECTRL;

	cldimemref r;
	cldiInitMemrefNewBlock(
		&r,
		(clditypeinfo_t){
			.size=sizeof(cldistr_t),
			.templ=CLDI_STRUCT_TYPE
		},
		CLDI_MBLK_OREAD|CLDI_MBLK_OWRTE|CLDI_MBLK_GREAD|CLDI_MBLK_PREAD|CLDI_MBLK_OAUTH
	);
	CLDI_CATCH {
		cldiAddTraceback(cldiNewStringEmpty, CLDIERRMSG_STR_FAIL_ALLOC);
		return r;
	}

	cldistr_t *strptr = (cldistr_t*) cldiMemrefGetAddress(&r);

	cldiInitStringEmpty(strptr, bufsize);
	CLDI_CATCH {
		cldiAddTraceback(cldiNewStringEmpty, CLDIERRMSG_STR_FAIL_INIT);
		cldiDropMemref(&r);
		CLDI_CATCH
			cldiAddTraceback(cldiNewStringEmpty, CLDIERRMSG_STR_FAIL_DROP_AFTER_INIT);
		return r;
	}

	return r;
}
cldimemref cldiNewStringEmptyW(size_t bufsize)
{
	CLDI_ECTRL;

	cldimemref r;
	cldiInitMemrefNewBlock(
		&r,
		(clditypeinfo_t){
			.size=sizeof(cldistr_t),
			.templ=CLDI_STRUCT_TYPE
		},
		CLDI_MBLK_OREAD|CLDI_MBLK_OWRTE|CLDI_MBLK_GREAD|CLDI_MBLK_PREAD|CLDI_MBLK_OAUTH
	);
	CLDI_CATCH {
		cldiAddTraceback(cldiNewStringEmptyW, CLDIERRMSG_STR_FAIL_ALLOC);
		return r;
	}

	cldistr_t *strptr = (cldistr_t*) cldiMemrefGetAddress(&r);

	cldiInitStringEmptyW(strptr, bufsize);
	CLDI_CATCH {
		cldiAddTraceback(cldiNewStringEmptyW, CLDIERRMSG_STR_FAIL_INIT);
		cldiDropMemref(&r);
		CLDI_CATCH
			cldiAddTraceback(cldiNewStringEmptyW, CLDIERRMSG_STR_FAIL_DROP_AFTER_INIT);
		return r;
	}

	return r;
}
cldimemref cldiNewStringEmptyEx(size_t bufsize, int flags)
{
	CLDI_ECTRL;

	cldimemref r;
	cldiInitMemrefNewBlock(
		&r,
		(clditypeinfo_t){
			.size=sizeof(cldistr_t),
			.templ=CLDI_STRUCT_TYPE
		},
		CLDI_MBLK_OREAD|CLDI_MBLK_OWRTE|CLDI_MBLK_GREAD|CLDI_MBLK_PREAD|CLDI_MBLK_OAUTH
	);
	CLDI_CATCH {
		cldiAddTraceback(cldiNewStringEmptyEx, CLDIERRMSG_STR_FAIL_ALLOC);
		return r;
	}

	cldistr_t *strptr = (cldistr_t*) cldiMemrefGetAddress(&r);

	cldiInitStringEmptyEx(strptr, bufsize, flags);
	CLDI_CATCH {
		cldiAddTraceback(cldiNewStringEmptyEx, CLDIERRMSG_STR_FAIL_INIT);
		cldiDropMemref(&r);
		CLDI_CATCH
			cldiAddTraceback(cldiNewStringEmptyEx, CLDIERRMSG_STR_FAIL_DROP_AFTER_INIT);
		return r;
	}

	return r;
}

CLDISTAT cldiStringDropBlock(cldimemref *drop)
{
	return CLDI_ENO_IMPL;
}
CLDISTAT cldiDropString(cldistr_t *self)
{
	if (self == NULL) {
		cldithrowf(CLDI_ENULL_SELF, cldiDropString, CLDIERRMSG_STR_NULL_SELF);
		return CLDI_ENULL_SELF;
	}

	CLDI_ECTRL;

	if (cldiMemrefIsActive(&self->data)) {
		cldiDropMemref(&self->data);
		CLDI_CATCH {
			cldiAddTraceback(cldiDropString, CLDIERRMSG_STR_FAIL_DROP);
			return CLDI_ERRNO;
		}
	}
	self->len  = 0;
	cldiInitMemref(&self->data);
	CLDI_CATCH {
		cldiAddTraceback(cldiDropString, "Failed to reinitialize self->data, member contains outdated memory address information.");
	}

	return CLDI_ERRNO;
}

CLDISTAT cldiStringConvertASCII(cldistr_t *self)
{
	if (self == NULL) {
		cldithrowf(CLDI_ENULL_SELF, cldiStringConvertASCII, CLDIERRMSG_STR_NULL_SELF);
		return CLDI_ENULL_SELF;
	} else if (self->len == 0 || cldiMemrefIsNull(&self->data)) {
		cldithrowf(CLDI_ENULL_ATTR, cldiStringConvertASCII, CLDIERRMSG_STR_NULL_DATA);
		return CLDI_ENULL_ATTR;
	} else if (self->flags & CLDI_CONST_STRING > 0) {
		cldithrowf(CLDI_ENOT_WRITABLE, cldiStringConvertASCII, "Cannot convert a const string, try making a converted copy instead.");
		return CLDI_ENOT_WRITABLE;
	}

	CLDI_ECTRL;

	// store string flags and encoding format in the stack.
	int flags = self->flags, encfmt = flags & CLDI_STRING_ENCFMT;
	if (encfmt >= CLDI_UTF16STRING) {
		const wchar_t *data = (const wchar_t*) cldiMemrefGetConstAddress(&self->data);
		CLDI_CATCH {
			cldiAddTraceback(cldiStringConvertASCII, CLDIERRMSG_STR_FAIL_GET_ADDR);
			return CLDI_ERRNO;
		}

		// store length in the stack
		size_t l = self->len;

		// try to initialize a new array for the converted data
		cldimemref conv;
		cldiInitMemrefNewArray(&conv, cldiCharTypeInfo, l, cldiStringCompileMemFlags(flags));
		CLDI_CATCH {
			cldiAddTraceback(cldiStringConvertASCII, CLDIERRMSG_STR_FAIL_ALLOC);
			return CLDI_ERRNO;
		}

		// convert the data to the new memory, and modify l based on the recorded
		// change in length
		l -= cldistrnconv16_a(l, (char*) cldiMemrefGetAddress(&conv), data);
		CLDI_CATCH {
			cldiAddTraceback(cldiStringConvertASCII, CLDIERRMSG_STR_FAIL_COPY);
			cldiDropMemref(&conv);
			CLDI_CATCH
				cldiAddTraceback(cldiStringConvertASCII, CLDIERRMSG_STR_FAIL_DROP_AFTER_COPY);
			return CLDI_ERRNO;
		}

		// try to drop the previous string and adopt the new one
		cldiDropMemref(&self->data);
		CLDI_CATCH {
			cldiAddTraceback(cldiStringConvertASCII, CLDIERRMSG_STR_FAIL_DROP_ADOPT_CHANGE);
			cldiDropMemref(&conv);
			CLDI_CATCH
				cldiAddTraceback(cldiStringConvertASCII, CLDIERRMSG_STR_FAIL_DROP_NEW_BLOCK);
			return CLDI_ERRNO;
		}

		// transfer object ownership to self via self->data.
		self->data  = conv;
		// store modified string flags in object
		self->flags = flags & (~CLDI_STRING_ENCFMT);
		// store modified string length in object
		self->len   = l;
	} else if (encfmt == CLDI_UTF8STRING) {
		// attempt to get memory reference from self->data
		char *data = (char*) cldiMemrefGetAddress(&self->data);
		CLDI_CATCH {
			cldiAddTraceback(cldiStringConvertASCII, CLDIERRMSG_STR_FAIL_GET_ADDR);
			return CLDI_ERRNO;
		}

		// find the end of valid ASCII data in the string and place a sentinel
		// there.
		data[cldistrlena(data)] = 0;
		// Flag the string as ASCII (encoding format bits are set to 0).
		self->flags &= ~CLDI_STRING_ENCFMT;
	}

	return CLDI_SUCCESS;
}
CLDISTAT cldiStringConvertUTF8(cldistr_t *self)
{
	if (self == NULL) {
		cldithrowf(CLDI_ENULL_SELF, cldiStringConvertUTF8, CLDIERRMSG_STR_NULL_SELF);
		return CLDI_ENULL_SELF;
	} else if (self->len == 0 || cldiMemrefIsNull(&self->data)) {
		cldithrowf(CLDI_ENULL_ATTR, cldiStringConvertUTF8, CLDIERRMSG_STR_NULL_DATA);
		return CLDI_ENULL_ATTR;
	} else if (self->flags & CLDI_CONST_STRING > 0) {
		cldithrowf(CLDI_ENOT_WRITABLE, cldiStringConvertUTF8, "Cannot convert a const string, try making a converted copy instead.");
		return CLDI_ENOT_WRITABLE;
	}

	CLDI_ECTRL;

	// store string flags and encoding format in the stack.
	int flags = self->flags, encfmt = flags & CLDI_STRING_ENCFMT;

	// if self is a UTF-16 string
	if (encfmt >= CLDI_UTF16STRING) {
		const wchar_t *data = (const wchar_t*) cldiMemrefGetConstAddress(&self->data);
		CLDI_CATCH {
			cldiAddTraceback(cldiStringConvertUTF8, CLDIERRMSG_STR_FAIL_GET_ADDR);
			return CLDI_ERRNO;
		}

		// store length in the stack
		size_t l = self->len;

		// try to initialize a new array for the converted data
		cldimemref conv;
		cldiInitMemrefNewArray(&conv, cldiCharTypeInfo, l, cldiStringCompileMemFlags(flags));
		CLDI_CATCH {
			cldiAddTraceback(cldiStringConvertUTF8, CLDIERRMSG_STR_FAIL_ALLOC);
			return CLDI_ERRNO;
		}

		// convert the data to the new memory, and modify l based on the recorded
		// change in length
		l -= cldistrnconv16_8(l, (char*) cldiMemrefGetAddress(&conv), data);
		CLDI_CATCH {
			cldiAddTraceback(cldiStringConvertUTF8, CLDIERRMSG_STR_FAIL_COPY);
			cldiDropMemref(&conv);
			CLDI_CATCH
				cldiAddTraceback(cldiStringConvertUTF8, CLDIERRMSG_STR_FAIL_DROP_AFTER_COPY);
			return CLDI_ERRNO;
		}

		// try to drop the previous string and adopt the new one
		cldiDropMemref(&self->data);
		CLDI_CATCH {
			cldiAddTraceback(cldiStringConvertUTF8, CLDIERRMSG_STR_FAIL_DROP_ADOPT_CHANGE);
			cldiDropMemref(&conv);
			CLDI_CATCH
				cldiAddTraceback(cldiStringConvertUTF8, CLDIERRMSG_STR_FAIL_DROP_NEW_BLOCK);
			return CLDI_ERRNO;
		}

		// transfer object ownership to self via self->data.
		self->data  = conv;
		// store modified string flags in object
		self->flags = flags | CLDI_UTF8STRING;
		// store modified string length in object
		self->len   = l;

	// else if self is an ASCII string
	} else if (encfmt == CLDI_ASCIISTRING) {
		// flag the string as UTF-8
		self->flags |= CLDI_UTF8STRING;
	}

	return CLDI_SUCCESS;
}
CLDISTAT cldiStringConvertUTF16(cldistr_t *self)
{
	if (self == NULL) {
		cldithrowf(CLDI_ENULL_SELF, cldiStringConvertUTF16, CLDIERRMSG_STR_NULL_SELF);
		return CLDI_ENULL_SELF;
	} else if (self->len == 0 || cldiMemrefIsNull(&self->data)) {
		cldithrowf(CLDI_ENULL_ATTR, cldiStringConvertUTF16, CLDIERRMSG_STR_NULL_DATA);
		return CLDI_ENULL_ATTR;
	} else if (self->flags & CLDI_CONST_STRING > 0) {
		cldithrowf(CLDI_ENOT_WRITABLE, cldiStringConvertUTF16, "Cannot convert a const string, try making a converted copy instead.");
		return CLDI_ENOT_WRITABLE;
	}

	CLDI_ECTRL;

	// store string flags and encoding format in the stack.
	int flags = self->flags, encfmt = flags & CLDI_STRING_ENCFMT;
	// store length in the stack
	size_t l = self->len;

	// try to initialize a new array for the converted data
	cldimemref conv;
	cldiInitMemrefNewArray(&conv, cldiWCharTypeInfo, l, cldiStringCompileMemFlags(flags));
	CLDI_CATCH {
		cldiAddTraceback(cldiStringConvertUTF16, CLDIERRMSG_STR_FAIL_ALLOC);
		return CLDI_ERRNO;
	}

	const char *data = (const char*) cldiMemrefGetConstAddress(&self->data);
	CLDI_CATCH {
		cldiAddTraceback(cldiStringConvertUTF16, CLDIERRMSG_STR_FAIL_GET_ADDR);
		cldiDropMemref(&conv);
		CLDI_CATCH
			cldiAddTraceback(cldiStringConvertUTF16, CLDIERRMSG_STR_FAIL_DROP_NEW_BLOCK);
		return CLDI_ERRNO;
	}

	// if self is a UTF-8 string
	if (encfmt == CLDI_UTF8STRING) {
		// convert the data to the new memory, and modify l based on the recorded
		// change in length
		l -= cldistrnconv8_16(l, (wchar_t*) cldiMemrefGetAddress(&conv), data);
		CLDI_CATCH {
			cldiAddTraceback(cldiStringConvertUTF16, CLDIERRMSG_STR_FAIL_COPY);
			cldiDropMemref(&conv);
			CLDI_CATCH
				cldiAddTraceback(cldiStringConvertUTF16, CLDIERRMSG_STR_FAIL_DROP_AFTER_COPY);
			return CLDI_ERRNO;
		}

		// try to drop the previous string and adopt the new one
		cldiDropMemref(&self->data);
		CLDI_CATCH {
			cldiAddTraceback(cldiStringConvertUTF16, CLDIERRMSG_STR_FAIL_DROP_ADOPT_CHANGE);
			cldiDropMemref(&conv);
			CLDI_CATCH
				cldiAddTraceback(cldiStringConvertUTF16, CLDIERRMSG_STR_FAIL_DROP_NEW_BLOCK);
			return CLDI_ERRNO;
		}

		// transfer object ownership to self via self->data.
		self->data  = conv;
		// store modified string flags in object
		self->flags = flags | CLDI_UTF16STRING;
		// store modified string length in object
		self->len   = l;

	// else if self is a ASCII string
	} else if (encfmt == CLDI_ASCIISTRING) {
		// convert the data to the new memory, and modify l based on the recorded
		// change in length
		l -= cldistrnconva_16(l, (char*) cldiMemrefGetAddress(&conv), data);
		CLDI_CATCH {
			cldiAddTraceback(cldiStringConvertUTF16, CLDIERRMSG_STR_FAIL_COPY);
			cldiDropMemref(&conv);
			CLDI_CATCH
				cldiAddTraceback(cldiStringConvertUTF16, CLDIERRMSG_STR_FAIL_DROP_AFTER_COPY);
			return CLDI_ERRNO;
		}

		// try to drop the previous string and adopt the new one
		cldiDropMemref(&self->data);
		CLDI_CATCH {
			cldiAddTraceback(cldiStringConvertUTF16, CLDIERRMSG_STR_FAIL_DROP_ADOPT_CHANGE);
			cldiDropMemref(&conv);
			CLDI_CATCH
				cldiAddTraceback(cldiStringConvertUTF16, CLDIERRMSG_STR_FAIL_DROP_NEW_BLOCK);
			return CLDI_ERRNO;
		}

		// transfer object ownership to self via self->data.
		self->data  = conv;
		// store modified string flags in object
		self->flags = flags | CLDI_UTF16STRING;
		// store modified string length in object
		self->len   = l;
	}

	return CLDI_SUCCESS;
}

size_t cldiStringSize(const cldistr_t *self)
{
	return (self == NULL)? 0 : self->len;
}
size_t cldiStringCharSize(const cldistr_t *self)
{
	return
		(self == NULL)? 0 :
		(self->flags & CLDI_UTF16STRING > 0)?
			sizeof(wchar_t) :
			sizeof(char);
}
size_t cldiStringBytesSize(const cldistr_t *self)
{
	return (self == NULL)? 0 :
		self->len *
			(self->flags & CLDI_UTF16STRING > 0)?
				sizeof(wchar_t) :
				sizeof(char);
}
size_t cldiStringMemoryUsage(const cldistr_t *self)
{
	if (self == NULL)
		return 0;

	size_t sum = 0;

	sum += cldiMemrefGetBlockTotalSize(&self->data);
	sum += sizeof(cldistr_t);

	return sum;
}
size_t cldiStringCapacity(const cldistr_t *self)
{
	return (self == NULL)? 0 : cldiMemrefGetArraySize(&self->data);
}
size_t cldiStringBytesCapacity(const cldistr_t *self)
{
	return cldiMemrefIsNull(&self->data)? 0 : cldiMemrefGetBlockSize(&self->data);
}

bool cldiStringIsConst(const cldistr_t *self)
{
	return self != NULL && (self->flags & CLDI_CONST_STRING > 0);
}
bool cldiIsCString(const cldistr_t *self)
{
	return self != NULL && (self->flags & CLDI_WSTRING == 0);
}
bool cldiIsWString(const cldistr_t *self)
{
	return self != NULL && (self->flags & CLDI_WSTRING > 0);
}
char* cldiStringData(cldistr_t *self)
{
	if (self == NULL) {
		cldithrowf(CLDI_ENULL_SELF, cldiStringData, CLDIERRMSG_STR_NULL_SELF);
		return CLDI_ENULL_SELF;
	}

	CLDI_ECTRL;

	if (self->flags & CLDI_WSTRING == 0) {
		char *data = (char*) cldiMemrefGetAddress(&self->data);
		CLDI_CATCH {
			cldiAddTraceback(cldiStringData, "Failed to get address in a non-const context.");
			return NULL;
		} else
			return data;
	} else {
		cldithrowf(CLDI_EINCOMPATIBLE_TYPE, cldiStringData, "String was requested in the wrong format (encoded UTF-16, requested UTF-8).");
		return NULL;
	}
}
const char* cldiStringConstData(const cldistr_t *self)
{
	if (self == NULL) {
		cldithrowf(CLDI_ENULL_SELF, cldiStringConstData, CLDIERRMSG_STR_NULL_SELF);
		return CLDI_ENULL_SELF;
	}

	CLDI_ECTRL;

	if (self->flags & CLDI_WSTRING == 0) {
		const char *data = (const char*) cldiMemrefGetConstAddress(&self->data);
		CLDI_CATCH {
			cldiAddTraceback(cldiStringConstData, "Failed to get address in a const context.");
			return NULL;
		} else
			return data;
	} else {
		cldithrowf(CLDI_EINCOMPATIBLE_TYPE, cldiStringConstData, "String was requested in the wrong format (encoded UTF-16, requested UTF-8).");
		return NULL;
	}
}
wchar_t* cldiStringDataW(cldistr_t *self)
{
	if (self == NULL) {
		cldithrowf(CLDI_ENULL_SELF, cldiStringDataW, CLDIERRMSG_STR_NULL_SELF);
		return CLDI_ENULL_SELF;
	}

	CLDI_ECTRL;

	if (self->flags & CLDI_WSTRING > 0) {
		wchar_t *data = (wchar_t*) cldiMemrefGetAddress(&self->data);
		CLDI_CATCH {
			cldiAddTraceback(cldiStringDataW, "Failed to get address in a non-const context.");
			return NULL;
		} else
			return data;
	} else {
		cldithrowf(CLDI_EINCOMPATIBLE_TYPE, cldiStringDataW, "String was requested in the wrong format (encoded ASCII/UTF-8, requested UTF-16).");
		return NULL;
	}
}
const wchar_t* cldiStringConstDataW(const cldistr_t *self)
{
	if (self == NULL) {
		cldithrowf(CLDI_ENULL_SELF, cldiStringConstDataW, CLDIERRMSG_STR_NULL_SELF);
		return CLDI_ENULL_SELF;
	}

	CLDI_ECTRL;

	if (self->flags & CLDI_WSTRING > 0) {
		const wchar_t *data = (const wchar_t*) cldiMemrefGetConstAddress(&self->data);
		CLDI_CATCH {
			cldiAddTraceback(cldiStringConstDataW, "Failed to get address in a const context.");
			return NULL;
		} else
			return data;
	} else {
		cldithrowf(CLDI_EINCOMPATIBLE_TYPE, cldiStringConstDataW, "String was requested in the wrong format (encoded ASCII/UTF-8, requested UTF-16).");
		return NULL;
	}
}
cldiheap_t* cldiStringGetHeap(cldistr_t *self)
{
	return (self == NULL)? NULL : cldiMemrefGetHeap(&self->data);
}
const cldiheap_t* cldiStringGetHeapConst(const cldistr_t *self)
{
	return (self == NULL) ? NULL : (const cldiheap_t*) cldiMemrefGetHeap(&self->data);
}

void* cldiStringIterGenItemC(cldiiter_t *iterable)
{
	char *ptr = (char*) iterable->origin;

	return &ptr[iterable->index];
}
void* cldiStringIterGenItemW(cldiiter_t *iterable)
{
	wchar_t *ptr = (wchar_t*) iterable->origin;

	return &ptr[iterable->index];
}

cldiiter_t cldiStringIter(cldistr_t *self)
{
	if (self == NULL) {
		cldithrowf(CLDI_ENULL_SELF, cldiStringIter, CLDIERRMSG_STR_NULL_SELF);
		return CLDIITER_NULL;
	}

	void *origin = cldiMemrefGetAddress(&self->data);

	return (cldiiter_t) {
		.origin  = origin,
		.current = origin,
		.index   = 0,
		.inc     = 1,
		.len     = self->len,
		.itemgen = (self->flags & CLDI_ASCIISTRING > 0)? cldiStringIterGenItemW : cldiStringIterGenItemC,
		.cond    = NULL,
		.closer  = NULL
	};
}
cldiiter_t cldiStringIterRev(cldistr_t *self)
{
	if (self == NULL && self->len > 0) {
		cldithrowf(CLDI_ENULL_SELF, cldiStringIter, CLDIERRMSG_STR_NULL_SELF);
		return CLDIITER_NULL;
	}

	size_t l = self->len - 1;

	void  *origin = cldiMemrefGetAddress(&self->data);
	bool   utf16  = self->flags & CLDI_ASCIISTRING > 0;
	if (utf16) {
		wchar_t *originw = (wchar_t*) origin;
		origin = &originw[l];
	} else {
		char *originc = (char*) origin;
		origin = &originc[l];
	}

	return (cldiiter_t) {
		.origin  = origin,
		.current = origin,
		.index   = l,
		.inc     = -1,
		.len     = self->len,
		.itemgen = utf16? cldiStringIterGenItemW : cldiStringIterGenItemC,
		.cond    = NULL,
		.closer  = NULL
	};
}
cldiiter_t cldiStringIterAt(cldistr_t *self, ssize_t idx)
{
	if (self == NULL && self->len > 0) {
		cldithrowf(CLDI_ENULL_SELF, cldiStringIter, CLDIERRMSG_STR_NULL_SELF);
		return CLDIITER_NULL;
	}

	size_t l = self->len - 1, i = cldistrabs(self->len, idx);

	void  *origin = cldiMemrefGetAddress(&self->data), *current;
	bool   utf16  = self->flags & CLDI_ASCIISTRING > 0;
	if (utf16) {
		wchar_t *originw = (wchar_t*) origin;
		current = &originw[i];
	} else {
		char *originc = (char*) origin;
		current = &originc[i];
	}

	return (cldiiter_t) {
		.origin  = origin,
		.current = current,
		.index   = i,
		.inc     = 1,
		.len     = self->len,
		.itemgen = utf16? cldiStringIterGenItemW : cldiStringIterGenItemC,
		.cond    = NULL,
		.closer  = NULL
	};
}
cldiiter_t cldiStringIterRevAt(cldistr_t *self, ssize_t idx)
{
	if (self == NULL && self->len > 0) {
		cldithrowf(CLDI_ENULL_SELF, cldiStringIter, CLDIERRMSG_STR_NULL_SELF);
		return CLDIITER_NULL;
	}

	size_t l = self->len - 1, i = cldistrabs(self->len, idx);

	void  *origin = cldiMemrefGetAddress(&self->data), *current;
	bool   utf16  = self->flags & CLDI_ASCIISTRING > 0;
	if (utf16) {
		wchar_t *originw = (wchar_t*) origin;
		origin = &originw[l];
		current = &originw[i];
	} else {
		char *originc = (char*) origin;
		origin = &originc[l];
		current = &originc[i];
	}

	return (cldiiter_t) {
		.origin  = origin,
		.current = current,
		.index   = i,
		.inc     = -1,
		.len     = self->len,
		.itemgen = utf16? cldiStringIterGenItemW : cldiStringIterGenItemC,
		.cond    = NULL,
		.closer  = NULL
	};
}
CLDISTAT cldiStringForEach(cldistr_t *self, cldiloopfunc_t func)
{
	if (self == NULL || self->len == 0) {
		cldithrowf(CLDI_ENULL_SELF, cldiStringForEach, CLDIERRMSG_STR_NULL_SELF);
		return CLDI_ENULL_SELF;
	} else if (func == NULL) {
		cldithrowf(CLDI_ENULL_SELF, cldiStringForEach, "Argument (2) `loop_func` must not be null or 0.");
		return CLDI_ENULL_SELF;
	}

	size_t l     = self->len;
	int    flags = self->flags;

	if (flags & CLDI_CONST_STRING > 0) {
		cldithrowf(CLDI_ENOT_WRITABLE, cldiStringForEach, "Attempted non-const operation on a const string.");
		return CLDI_ENOT_WRITABLE;
	}

	CLDI_ECTRL;

	if (flags & CLDI_UTF16STRING > 0) {
		wchar_t *arr = (wchar_t*) cldiMemrefGetAddress(&self->data);
		CLDI_CATCH {
			cldiAddTraceback(cldiStringForEach, CLDIERRMSG_STR_FAIL_GET_ADDR);
			return CLDI_ERRNO;
		}
		for (size_t i = 0; i < l && func(i, &arr[i]); i++);
	} else {
		char *arr = (char*) cldiMemrefGetAddress(&self->data);
		CLDI_CATCH {
			cldiAddTraceback(cldiStringForEach, CLDIERRMSG_STR_FAIL_GET_ADDR);
			return CLDI_ERRNO;
		}
		for (size_t i = 0; i < l && func(i, &arr[i]); i++);
	}
	CLDI_CATCH
		cldiAddTraceback(cldiStringForEach, "Error occurred while iterating through the string.");

	return CLDI_ERRNO;
}
CLDISTAT cldiStringForEachConst(cldistr_t *self, cldiloopconst_t func)
{
	if (self == NULL || self->len == 0) {
		cldithrowf(CLDI_ENULL_SELF, cldiStringForEach, CLDIERRMSG_STR_NULL_SELF);
		return CLDI_ENULL_SELF;
	} else if (func == NULL) {
		cldithrowf(CLDI_ENULL_SELF, cldiStringForEach, "Argument (2) `loop_func` must not be null or 0.");
		return CLDI_ENULL_SELF;
	}

	CLDI_ECTRL;

	size_t l = self->len;

	if (self->flags & CLDI_UTF16STRING > 0) {
		const wchar_t *arr = (const wchar_t*) cldiMemrefGetConstAddress(&self->data);
		CLDI_CATCH {
			cldiAddTraceback(cldiStringForEachConst, CLDIERRMSG_STR_FAIL_GET_ADDR);
			return CLDI_ERRNO;
		}
		for (size_t i = 0; i < l && func(i, &arr[i]); i++);
	} else {
		const char *arr = (const char*) cldiMemrefGetConstAddress(&self->data);
		CLDI_CATCH {
			cldiAddTraceback(cldiStringForEachConst, CLDIERRMSG_STR_FAIL_GET_ADDR);
			return CLDI_ERRNO;
		}
		for (size_t i = 0; i < l && func(i, &arr[i]); i++);
	}
	CLDI_CATCH
		cldiAddTraceback(cldiStringForEach, "Error occurred while iterating through the string.");

	return CLDI_ERRNO;
}
CLDISTAT cldiStringForEachRev(cldistr_t *self, cldiloopfunc_t func)
{
	if (self == NULL || self->len == 0) {
		cldithrowf(CLDI_ENULL_SELF, cldiStringForEach, CLDIERRMSG_STR_NULL_SELF);
		return CLDI_ENULL_SELF;
	} else if (func == NULL) {
		cldithrowf(CLDI_ENULL_SELF, cldiStringForEach, "Argument (2) `loop_func` must not be null or 0.");
		return CLDI_ENULL_SELF;
	}

	size_t l     = self->len;
	int    flags = self->flags;

	if (flags & CLDI_CONST_STRING > 0) {
		cldithrowf(CLDI_ENOT_WRITABLE, cldiStringForEach, "Attempted non-const operation on a const string.");
		return CLDI_ENOT_WRITABLE;
	}

	CLDI_ECTRL;

	if (flags & CLDI_UTF16STRING > 0) {
		wchar_t *arr = (wchar_t*) cldiMemrefGetAddress(&self->data);
		CLDI_CATCH {
			cldiAddTraceback(cldiStringForEach, CLDIERRMSG_STR_FAIL_GET_ADDR);
			return CLDI_ERRNO;
		}
		for (size_t i = l - 1; i >= 0 && func(i, &arr[i]); i--);
	} else {
		char *arr = (char*) cldiMemrefGetAddress(&self->data);
		CLDI_CATCH {
			cldiAddTraceback(cldiStringForEach, CLDIERRMSG_STR_FAIL_GET_ADDR);
			return CLDI_ERRNO;
		}
		for (size_t i = l - 1; i >= 0 && func(i, &arr[i]); i--);
	}
	CLDI_CATCH
		cldiAddTraceback(cldiStringForEach, "Error occurred while iterating through the string.");

	return CLDI_ERRNO;
}
CLDISTAT cldiStringForEachConstRev(cldistr_t *self, cldiloopconst_t func)
{
	if (self == NULL || self->len == 0) {
		cldithrowf(CLDI_ENULL_SELF, cldiStringForEach, CLDIERRMSG_STR_NULL_SELF);
		return CLDI_ENULL_SELF;
	} else if (func == NULL) {
		cldithrowf(CLDI_ENULL_SELF, cldiStringForEach, "Argument (2) `loop_func` must not be null or 0.");
		return CLDI_ENULL_SELF;
	}

	CLDI_ECTRL;

	size_t l = self->len;

	if (self->flags & CLDI_UTF16STRING > 0) {
		const wchar_t *arr = (const wchar_t*) cldiMemrefGetConstAddress(&self->data);
		CLDI_CATCH {
			cldiAddTraceback(cldiStringForEachConst, CLDIERRMSG_STR_FAIL_GET_ADDR);
			return CLDI_ERRNO;
		}
		for (size_t i = l - 1; i >= 0 && func(i, &arr[i]); i--);
	} else {
		const char *arr = (const char*) cldiMemrefGetConstAddress(&self->data);
		CLDI_CATCH {
			cldiAddTraceback(cldiStringForEachConst, CLDIERRMSG_STR_FAIL_GET_ADDR);
			return CLDI_ERRNO;
		}
		for (size_t i = l - 1; i >= 0 && func(i, &arr[i]); i--);
	}
	CLDI_CATCH
		cldiAddTraceback(cldiStringForEach, "Error occurred while iterating through the string.");

	return CLDI_ERRNO;
}

int cldiStringGetPerms(const cldistr_t *self)
{
	return (self == NULL)? 0 : self->flags & CLDI_STRING_PERMS;
}
int cldiStringGetFlags(const cldistr_t *self)
{
	return (self == NULL)? 0 : self->flags;
}
CLDISTAT cldiStringGetAuth(const cldistr_t *self)
{
	return (self == NULL)? 0 : self->flags & CLDI_STRING_AUTH;
}
bool cldiStringHasFlags(const cldistr_t *self, int flags)
{
	int f = flags & CLDI_STRFLAGS_MASK;
	return self != NULL && (self->flags & f == f);
}
bool cldiStringHasPerms(const cldistr_t *self, int perms)
{
	int p = perms & CLDI_STRING_PERMS;
	return self != NULL && (self->flags & p == p);
}
CLDISTAT cldiStringHasAuth(const cldistr_t *self, int auth)
{
	int a = auth & CLDI_STRING_AUTH;
	return self != NULL && (self->flags & a == a);
}
CLDISTAT cldiStringSetFlagsWithMask(cldistr_t *self, int mask, int flags)
{
	if (self == NULL) {
		cldithrowf(CLDI_ENULL_SELF, cldiStringSetFlags, CLDIERRMSG_STR_NULL_SELF);
		return CLDI_ENULL_SELF;
	} else if (!cldiStringAuthorAccess(self)) {
		cldithrowf(CLDI_ENO_ACCESS, cldiStringSetFlags, CLDIERRMSG_STR_NOAUTHOR);
		return CLDI_ENO_ACCESS;
	}

	CLDI_ECTRL;

	mask &= CLDI_STRFLAGS_EXTERNAL;
	self->flags &= ~mask;
	self->flags |= flags & mask;

	return CLDI_SUCCESS;
}
CLDISTAT cldiStringSetFlags(cldistr_t *self, int flags)
{
	if (self == NULL) {
		cldithrowf(CLDI_ENULL_SELF, cldiStringSetFlags, CLDIERRMSG_STR_NULL_SELF);
		return CLDI_ENULL_SELF;
	} else if (!cldiStringAuthorAccess(self)) {
		cldithrowf(CLDI_ENO_ACCESS, cldiStringSetFlags, CLDIERRMSG_STR_NOAUTHOR);
		return CLDI_ENO_ACCESS;
	}

	CLDI_ECTRL;

	self->flags |= flags & CLDI_STRFLAGS_EXTERNAL;

	return CLDI_SUCCESS;
}
CLDISTAT cldiStringSetPerms(cldistr_t *self, int perms)
{
	if (self == NULL) {
		cldithrowf(CLDI_ENULL_SELF, cldiStringSetFlags, CLDIERRMSG_STR_NULL_SELF);
		return CLDI_ENULL_SELF;
	} else if (!cldiStringAuthorAccess(self)) {
		cldithrowf(CLDI_ENO_ACCESS, cldiStringSetFlags, CLDIERRMSG_STR_NOAUTHOR);
		return CLDI_ENO_ACCESS;
	}

	CLDI_ECTRL;

	self->flags |= perms & CLDI_STRING_PERMS;

	return CLDI_SUCCESS;
}
CLDISTAT cldiStringSetAuth(cldistr_t *self, int auth)
{
	if (self == NULL) {
		cldithrowf(CLDI_ENULL_SELF, cldiStringSetFlags, CLDIERRMSG_STR_NULL_SELF);
		return CLDI_ENULL_SELF;
	} else if (!cldiStringAuthorAccess(self)) {
		cldithrowf(CLDI_ENO_ACCESS, cldiStringSetFlags, CLDIERRMSG_STR_NOAUTHOR);
		return CLDI_ENO_ACCESS;
	}

	CLDI_ECTRL;

	auth &= CLDI_STRING_AUTH;
	int sflags = self->flags & ~CLDI_STRFLAGS_MASK;
	sflags &= ~CLDI_STRING_AUTH;
	sflags |= auth;
	self->flags = sflags;

	return CLDI_SUCCESS;
}
CLDISTAT cldiStringSetConst(cldistr_t *self)
{
	if (self == NULL) {
		cldithrowf(CLDI_ENULL_SELF, cldiStringSetFlags, CLDIERRMSG_STR_NULL_SELF);
		return CLDI_ENULL_SELF;
	} else if (!cldiStringAuthorAccess(self)) {
		cldithrowf(CLDI_ENO_ACCESS, cldiStringSetFlags, CLDIERRMSG_STR_NOAUTHOR);
		return CLDI_ENO_ACCESS;
	}

	CLDI_ECTRL;

	self->flags |= CLDI_CONST_STRING;

	return CLDI_SUCCESS;
}
CLDISTAT cldiStringRemoveFlags(cldistr_t *self, int flags)
{
	if (self == NULL) {
		cldithrowf(CLDI_ENULL_SELF, cldiStringSetFlags, CLDIERRMSG_STR_NULL_SELF);
		return CLDI_ENULL_SELF;
	} else if (!cldiStringAuthorAccess(self)) {
		cldithrowf(CLDI_ENO_ACCESS, cldiStringSetFlags, CLDIERRMSG_STR_NOAUTHOR);
		return CLDI_ENO_ACCESS;
	}

	CLDI_ECTRL;

	self->flags &= ~(flags & CLDI_STRFLAGS_EXTERNAL);

	return CLDI_SUCCESS;
}
CLDISTAT cldiStringRemovePerms(cldistr_t *self, int perms)
{
	if (self == NULL) {
		cldithrowf(CLDI_ENULL_SELF, cldiStringSetFlags, CLDIERRMSG_STR_NULL_SELF);
		return CLDI_ENULL_SELF;
	} else if (!cldiStringAuthorAccess(self)) {
		cldithrowf(CLDI_ENO_ACCESS, cldiStringSetFlags, CLDIERRMSG_STR_NOAUTHOR);
		return CLDI_ENO_ACCESS;
	}

	CLDI_ECTRL;

	self->flags &= ~(perms & CLDI_STRING_PERMS);

	return CLDI_SUCCESS;
}
CLDISTAT cldiStringRemoveAuth(cldistr_t *self, int auth)
{
	if (self == NULL) {
		cldithrowf(CLDI_ENULL_SELF, cldiStringSetFlags, CLDIERRMSG_STR_NULL_SELF);
		return CLDI_ENULL_SELF;
	} else if (!cldiStringAuthorAccess(self)) {
		cldithrowf(CLDI_ENO_ACCESS, cldiStringSetFlags, CLDIERRMSG_STR_NOAUTHOR);
		return CLDI_ENO_ACCESS;
	}

	CLDI_ECTRL;

	auth &= CLDI_STRING_AUTH;
	self->flags &= ~auth;

	return CLDI_SUCCESS;
}
CLDISTAT cldiStringRemoveConst(cldistr_t *self)
{
	if (self == NULL) {
		cldithrowf(CLDI_ENULL_SELF, cldiStringSetFlags, CLDIERRMSG_STR_NULL_SELF);
		return CLDI_ENULL_SELF;
	} else if (!cldiStringAuthorAccess(self)) {
		cldithrowf(CLDI_ENO_ACCESS, cldiStringSetFlags, CLDIERRMSG_STR_NOAUTHOR);
		return CLDI_ENO_ACCESS;
	}

	CLDI_ECTRL;

	self->flags &= ~CLDI_CONSTSTR;

	return CLDI_SUCCESS;
}
CLDISTAT cldiStringToggleFlags(cldistr_t *self, int flags)
{
	if (self == NULL) {
		cldithrowf(CLDI_ENULL_SELF, cldiStringSetFlags, CLDIERRMSG_STR_NULL_SELF);
		return CLDI_ENULL_SELF;
	} else if (!cldiStringAuthorAccess(self)) {
		cldithrowf(CLDI_ENO_ACCESS, cldiStringSetFlags, CLDIERRMSG_STR_NOAUTHOR);
		return CLDI_ENO_ACCESS;
	}

	CLDI_ECTRL;

	flags &= ~CLDI_STRFLAGS_EXTERNAL;

	int sflags = self->flags;
	sflags &= ~CLDI_STRFLAGS_EXTERNAL;

	int ibits = (~sflags) & flags;
	sflags &= ~flags;
	sflags |= ibits;
	self->flags = sflags;

	return CLDI_SUCCESS;
}
CLDISTAT cldiStringToggleConst(cldistr_t *self)
{
	if (self == NULL) {
		cldithrowf(CLDI_ENULL_SELF, cldiStringSetFlags, CLDIERRMSG_STR_NULL_SELF);
		return CLDI_ENULL_SELF;
	} else if (!cldiStringAuthorAccess(self)) {
		cldithrowf(CLDI_ENO_ACCESS, cldiStringSetFlags, CLDIERRMSG_STR_NOAUTHOR);
		return CLDI_ENO_ACCESS;
	}

	CLDI_ECTRL;

	int sflags = self->flags;

	int ibit = (~sflags) & CLDI_CONSTSTR;
	sflags &= ~CLDI_CONSTSTR;
	sflags |= ibit;

	self->flags = sflags;

	return CLDI_SUCCESS;
}
bool cldiStringAuthorAccess(const cldistr_t *self)
{
	if (self == NULL)
		return false;
	else {
		const int sflags = self->flags, aflags = sflags & CLDI_STRING_AUTH;
		if (aflags == 0)
			return false;
		else if (aflags & CLDI_STRING_PAUTH > 0)
			return true;
		else {
			cldioid_t owner = cldiMemrefGetBlockOwner(&self->data), current = cldiGetCurrentOID();
			return (
				(owner.owner == current.owner && (aflags & CLDI_STRING_OAUTH > 0)) ||
				(owner.group == current.group && (aflags & CLDI_STRING_GAUTH > 0))
			);
		}
	}
}
bool cldiStringOwnerAccess(const cldistr_t *self)
{
	return self != NULL && (cldiMemrefGetBlockOwnerThread(&self->data) == cldiGetCurrentPID());
}
bool cldiStringGroupAccess(const cldistr_t *self)
{
	return self != NULL && (cldiMemrefGetBlockOwnerGroup(&self->data) == cldiGetCurrentGID());
}
bool cldiStringIsReadable(const cldistr_t *self)
{
	if (self == NULL || cldiMemrefIsNull(&self->data))
		return false;

	cldioid_t owner = cldiMemrefGetBlockOwner(&self->data), current = cldiGetCurrentOID();
	int flags = self->flags;

	return
		owner.owner == current.owner    ||
		(flags & CLDI_STRING_PREAD > 0) ||
		(owner.group == current.group   && (flags & CLDI_STRING_GREAD > 0));
}
bool cldiStringIsWritable(const cldistr_t *self)
{
	if (self == NULL || cldiMemrefIsNull(&self->data))
		return false;

	cldioid_t owner = cldiMemrefGetBlockOwner(&self->data), current = cldiGetCurrentOID();
	int flags = self->flags;

	return
		(flags & CLDI_STRING_PREAD > 0) ||
		(owner.owner == current.owner   && (flags & CLDI_CONSTSTR == 0)) ||
		(owner.group == current.group   && (flags & CLDI_STRING_GREAD > 0));
}
bool cldiStringOwnerIsAuthor(const cldistr_t *self)
{
	return self != NULL && (self->flags & CLDI_STRING_OAUTH == CLDI_STRING_OAUTH);
}
bool cldiStringGroupReadable(const cldistr_t *self)
{
	return self != NULL && (self->flags & CLDI_STRING_GREAD == CLDI_STRING_GREAD);
}
bool cldiStringGroupWritable(const cldistr_t *self)
{
	return self != NULL && (self->flags & CLDI_STRING_GWRTE == CLDI_STRING_GWRTE);
}
bool cldiStringGroupIsAuthor(const cldistr_t *self)
{
	return self != NULL && (self->flags & CLDI_STRING_GAUTH == CLDI_STRING_GAUTH);
}
bool cldiStringPublicReadable(const cldistr_t *self)
{
	return self != NULL && (self->flags & CLDI_STRING_PREAD == CLDI_STRING_PREAD);
}
bool cldiStringPublicWritable(const cldistr_t *self)
{
	return self != NULL && (self->flags & CLDI_STRING_PWRTE == CLDI_STRING_PWRTE);
}
bool cldiStringPublicIsAuthor(const cldistr_t *self)
{
	return self != NULL && (self->flags & CLDI_STRING_PAUTH == CLDI_STRING_PAUTH);
}


