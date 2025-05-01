
#pragma cldic module head:string
#ifndef _cldi_head__STRING_H
#define _cldi_head__STRING_H 1

#include "iter.h"
#pragma cldic require head:iter

#ifdef __cplusplus
#	if CLDI_C_ONLY == true
#		include <string.h>
#	else
#		include <cstring>
#	endif
extern "C" {
#endif



/* Raw string functions: */
// These functions return 0 if the operation is complete, or the number of chars
// that would've been processed if an error hadn't occurred, where CLDI_ERRNO
// will then contain the error code.

/* Based of the total length of a string, get the amount of total positions from
.  the beginning (absolute index) of the string that a given relative (signed)
.  index corresponds to. */
size_t cldistrabs(size_t total_len, ssize_t index_rel);
/* Based on the total length of a string, fit a given distance from the beginning
.  into a signed number relative to the beginning (positive index) or end
.  (negative index) of the string. */
ssize_t cldistrrel(size_t total_len, size_t index_abs);

/* Get char string length (ASCII). */
size_t cldistrlena(const char *str);
/* Get char string length (UTF-8). */
size_t cldistrlen8(const char *str);
/* Get wchar_t string length (UTF-16). */
size_t cldistrlen16(const wchar_t *wstr);
#define cldistrlen  cldistrlena
#define cldistrlenw cldistrlen16

/* Copy an ASCII string from src to dest.
.  - Copy functions return the amount of characters that were either skipped in
.    addition to the amount of characters that might have been omitted because
.    an error ocurred before they were reached. */
size_t cldistrcpya(char *__restrict__ dest, const char *__restrict__ src);
size_t cldistrncpya(size_t n, char *__restrict__ dest, const char *__restrict__ src);
// Copy into new memory block
cldimemref cldistrmcpya(const char *__restrict__ src);
cldimemref cldistrmncpya(size_t n, const char *__restrict__ src);
/* Copy a UTF-8 string from src to dest. */
size_t cldistrcpy8(char *__restrict__ dest, const char *__restrict__ src);
size_t cldistrncpy8(size_t n, char *__restrict__ dest, const char *__restrict__ src);
// Copy into new memory block
cldimemref cldistrmcpy8(const char *__restrict__ src);
cldimemref cldistrmncpy8(size_t n, const char *__restrict__ src);
/* Copy a UTF-16 string from src to dest. */
size_t cldistrcpy16(wchar_t *__restrict__ dest, const wchar_t *__restrict__ src);
size_t cldistrncpy16(size_t n, wchar_t *__restrict__ dest, const wchar_t *__restrict__ src);
// Copy into new memory block
cldimemref cldistrmcpy16(const wchar_t *__restrict__ src);
cldimemref cldistrmncpy16(size_t n, const wchar_t *__restrict__ src);
#define cldistrcpy    cldistrcpya
#define cldistrncpy   cldistrncpya
#define cldistrmcpy   cldistrmcpya
#define cldistrmncpy  cldistrmncpya
#define cldistrcpyw   cldistrcpy16
#define cldistrncpyw  cldistrncpy16
#define cldistrmcpyw  cldistrmcpy16
#define cldistrmncpyw cldistrmncpy16

/* Starting from a given point (`trunc_at`) in a string (`str`) with a given
.  total size (`total_size`), truncate a given total number of characters from
.  the string (`trunc_size`). */
// - ASCII
CLDISTAT cldistrtrunca(char *str, size_t total_size, size_t start_trunc_at, size_t trunc_size);
// - UTF-8
CLDISTAT cldistrtrunc8(char *str, size_t total_size, size_t start_trunc_at, size_t trunc_size);
// - UTF-16
CLDISTAT cldistrtrunc16(wchar_t *str, size_t total_size, size_t start_trunc_at, size_t trunc_size);
#define  cldistrtrunc  cldistrtrunca
#define  cldistrtruncw cldistrtrunc16

/* Clear all string data from a given string. */
// - ASCII
CLDISTAT cldistrclra(char *str);
CLDISTAT cldistrnclra(size_t n, char *str);
// - UTF-8
CLDISTAT cldistrclr8(char *str);
CLDISTAT cldistrnclr8(size_t n, char *str);
// - UTF-16
CLDISTAT cldistrclr16(wchar_t *str);
CLDISTAT cldistrnclr16(size_t n, wchar_t *str);

/* Compare an ASCII string, l, to another, r:
.  - String compare functions return CLDISTAT value CLDI_CMPE (which is equal
.    to CLDI_SUCCESS and CLDI_TRUE) if strings are equal, CLDI_CMPL (which is
.    equal to CLDI_FALSE) if l is shorter, yet equal to r for what length it
.    does have, and CLDI_CMPG if l is longer, yet r is equal to it for what
.    length it does have. */
CLDISTAT cldistrcmp(const char *l, const char *r);
CLDISTAT cldistrncmp(size_t n, const char *l, const char *r);
// - Compare to a UTF-8 string.
CLDISTAT cldistrcmpa_8(const char *l, const char *r);
CLDISTAT cldistrncmpa_8(size_t n, const char *l, const char *r);
// - Compare to a UTF-16 string.
CLDISTAT cldistrcmpa_16(const char *l, const wchar_t *r);
CLDISTAT cldistrncmpa_16(size_t n, const char *l, const wchar_t *r);
#define  cldistrcmpa_w  cldistrcmpa_16
#define  cldistrncmpa_w cldistrncmpa_16
/* Compare a UTF-8 string, l, to another, r. */
CLDISTAT cldistrcmp8(const char *l, const char *r);
CLDISTAT cldistrncmp8(size_t n, const char *l, const char *r);
// - Compare to an ASCII string.
CLDISTAT cldistrcmp8_a(const char *l, const char *r);
CLDISTAT cldistrncmp8_a(size_t n, const char *l, const char *r);
// - Compare to a UTF-16 string.
CLDISTAT cldistrcmp8_16(const char *l, const wchar_t *r);
CLDISTAT cldistrncmp8_16(size_t n, const char *l, const wchar_t *r);
#define  cldistrcmp8_w  cldistrcmp8_16
#define  cldistrncmp8_w cldistrncmp8_16
/* Compare a UTF-16 string, l, to another, r. */
CLDISTAT cldistrcmp16(const wchar_t *l, const wchar_t *r);
CLDISTAT cldistrncmp16(size_t n, const wchar_t *l, const wchar_t *r);
// - Compare to an ASCII string.
CLDISTAT cldistrcmp16_a(const wchar_t *l, const char *r);
CLDISTAT cldistrncmp16_a(size_t n, const wchar_t *l, const char *r);
// - Compare to a UTF-8 string.
CLDISTAT cldistrcmp16_8(const wchar_t *l, const char *r);
CLDISTAT cldistrncmp16_8(size_t n, const wchar_t *l, const char *r);
#define  cldistrcmpw    cldistrcmp16
#define  cldistrncmpw   cldistrncmp16
#define  cldistrcmpw_a  cldistrcmp16_a
#define  cldistrncmpw_a cldistrncmp16_a
#define  cldistrcmpw_8  cldistrcmp16_8
#define  cldistrncmpw_8 cldistrncmp16_8

/* Convert ASCII string to UTF-16
.  - Convert functions return the amount of characters that were either skipped
.    in addition to the amount of characters that might have been omitted because
.    an error ocurred before they were reached. */
size_t cldistrconva_16(wchar_t *dest, const char *src);
size_t cldistrnconva_16(size_t n, wchar_t *dest, const char *src);
/* Convert UTF-8 to ASCII */
size_t cldistrconv8_a(char *dest, const char *src);
size_t cldistrnconv8_a(size_t n, char *dest, const char *src);
/* Convert UTF-8 to UTF-16 */
size_t cldistrconv8_16(wchar_t *dest, const char *src);
size_t cldistrnconv8_16(size_t n, wchar_t *dest, const char *src);
/* Convert UTF-16 to ASCII */
size_t cldistrconv16_a(char *dest, const wchar_t *src);
size_t cldistrnconv16_a(size_t n, char *dest, const wchar_t *src);
/* Convert UTF-16 to UTF-8 */
size_t cldistrconv16_8(char *dest, const wchar_t *src);
size_t cldistrnconv16_8(size_t n, char *dest, const wchar_t *src);


typedef enum _CLDISTRFLAGS
{
	CLDI_STRFLAGS_MASK=0x1ff,
	CLDI_STRFLAGS_NULL=0,
//	'U' (bit 0): UTF-8 characters enabled, accept utf-8 characters in the string.
//	'W' (bit 1): UTF-16 string using wchar_t characters, incompatible with bit 0
//	             ('U')
//	'w' (bit 2): Value of 1 with bit 1 as 0 auto-converts
//	             value of 0 with bit 1 as 1 auto-converts utf-16 to utf-8, or ascii
//	             if bit 0 is also 1.
//	'C' (bit 3): Const string, define on InitString() (or other constructor) call,
//	             and forbid modification until DropString() call and reinitialization.
//	'D' (bit 4): String has been defined, this is relevant when bit 3 is 1, after this
//	             bit is 1, and bit 3 is also defined with 1, the string cannot be modified
//	             until dropped and reinitialized.
//  'RW' (bits 5 & 6): Read and write permissions for all threads (public access).
//  'rw' (bits 7 & 8): Read and write permissions for this thread's group (group access).
//  'A' (bits 9-11): 001 - Author status is given to all threads, 010 - Author status is
//                   given to threads within the same group, 100 - Author status is given
//                   the owner thread. Any combination of these bits can be used, if none
//                   are used (000), than no threads are given author status.
//	                                            A   rw RW D C w W U
	CLDI_ASCIISTRING           = 0x0,   // 0000 000 00 00 0 0 0 0 0
	CLDI_UTF8STRING            = 0x1,   // 0000 000 00 00 0 0 0 0 1
	CLDI_UTF16STRING           = 0x2,   // 0000 000 00 00 0 0 0 1 ?
	CLDI_CSTRING = CLDI_ASCIISTRING,
	CLDI_WSTRING = CLDI_UTF16STRING,

	// Bit mask for the bits that relate to string encoding format.
	CLDI_STRING_ENCFMT = CLDI_ASCIISTRING | CLDI_UTF8STRING | CLDI_UTF16STRING,

	CLDI_STRING_AUTOCONV       = 0x4,   // 0000 000 00 00 0 0 1 0 0

	CLDI_CONST_STRING          = 0x8,   // 0000 000 00 00 0 1 0 0 0
	CLDI_CONSTSTR = CLDI_CONST_STRING,

	CLDI_STRING_DEFINED        = 0x10,  // 0000 000 00 00 1 0 0 0 0

	CLDI_STRING_PREAD          = 0x40,  // 0000 000 00 10 0 0 0 0 0
	CLDI_STRING_PWRTE          = 0x20,  // 0000 000 00 01 0 0 0 0 0
	CLDI_STRING_GREAD          = 0x100, // 0000 000 10 00 0 0 0 0 0
	CLDI_STRING_GWRTE          = 0x80,  // 0000 000 01 00 0 0 0 0 0
	// Bit masks for public permissions, group permissions, and all permissions
	CLDI_STRING_PUBLIC_PERMS   = CLDI_STRING_PREAD | CLDI_STRING_PWRTE,
	CLDI_STRING_GROUP_PERMS    = CLDI_STRING_GREAD | CLDI_STRING_GWRTE,
	CLDI_STRING_PERMS          = CLDI_STRING_PUBLIC_PERMS | CLDI_STRING_GROUP_PERMS | CLDI_CONST_STRING,
	CLDI_STRING_RPERMS         = CLDI_STRING_GREAD | CLDI_STRING_PREAD,
	CLDI_STRING_WPERMS         = CLDI_STRING_GWRTE | CLDI_STRING_PWRTE,


	CLDI_STRING_OAUTH          = 0x800, // 0000 100 00 00 0 0 0 0 0
	CLDI_STRING_GAUTH          = 0x400, // 0000 010 00 00 0 0 0 0 0
	CLDI_STRING_PAUTH          = 0x200, // 0000 001 00 00 0 0 0 0 0
	// Bit mask for author priviledges
	CLDI_STRING_AUTH           = CLDI_STRING_OAUTH | CLDI_STRING_GAUTH | CLDI_STRING_PAUTH,

	// Bit mask for string flags that are not carried over to a string on inputting
	// them, because they are used internally by the string object and its
	// subroutines only.
	CLDI_STRFLAGS_INTERNAL = CLDI_STRING_DEFINED,
	// Bit mask for all string flags that are carried over to a string on inputting
	// them (external string flags).
	CLDI_STRFLAGS_EXTERNAL = CLDI_STRFLAGS_MASK & (~CLDI_STRFLAGS_INTERNAL),

	// Permissions presets
	CLDI_DEFAULT_CSTRING_PERMS        = CLDI_CSTRING | CLDI_STRING_PREAD | CLDI_STRING_GREAD,
	CLDI_DEFAULT_WSTRING_PERMS        = CLDI_WSTRING | CLDI_STRING_PREAD | CLDI_STRING_GREAD,
	CLDI_DEFAULT_ASCIISTR_PERMS       = CLDI_ASCIISTRING | CLDI_STRING_PREAD | CLDI_STRING_GREAD,
	CLDI_DEFAULT_UTF8STR_PERMS        = CLDI_UTF8STRING | CLDI_STRING_PREAD | CLDI_STRING_GREAD,
	CLDI_DEFAULT_UTF16STR_PERMS       = CLDI_UTF16STRING | CLDI_STRING_PREAD | CLDI_STRING_GREAD,
	CLDI_DEFAULT_STRING_PERMS         = CLDI_DEFAULT_CSTRING_PERMS,
	CLDI_DEFAULT_CONSTCSTR_PERMS      = CLDI_DEFAULT_CSTRING_PERMS | CLDI_CONST_STRING,
	CLDI_DEFAULT_CONSTWSTR_PERMS      = CLDI_DEFAULT_WSTRING_PERMS | CLDI_CONST_STRING,
	CLDI_DEFAULT_CONSTSTR_ASCII_PERMS = CLDI_DEFAULT_ASCIISTR_PERMS | CLDI_CONST_STRING,
	CLDI_DEFAULT_CONSTSTR_UTF8_PERMS  = CLDI_DEFAULT_UTF8STR_PERMS | CLDI_CONST_STRING,
	CLDI_DEFAULT_CONSTSTR_UTF16_PERMS = CLDI_DEFAULT_UTF16STR_PERMS | CLDI_CONST_STRING,
	CLDI_DEFAULT_CONSTSTR_PERMS       = CLDI_DEFAULT_CONSTCSTR_PERMS,

	// Author Status presets
	CLDI_DEFAULT_CSTRING_AUTH        = CLDI_CSTRING | CLDI_STRING_OAUTH,
	CLDI_DEFAULT_WSTRING_AUTH        = CLDI_WSTRING | CLDI_STRING_OAUTH,
	CLDI_DEFAULT_ASCIISTR_AUTH       = CLDI_ASCIISTRING | CLDI_STRING_OAUTH,
	CLDI_DEFAULT_UTF8STR_AUTH        = CLDI_UTF8STRING | CLDI_STRING_OAUTH,
	CLDI_DEFAULT_UTF16STR_AUTH       = CLDI_UTF16STRING | CLDI_STRING_OAUTH,
	CLDI_DEFAULT_STRING_AUTH         = CLDI_DEFAULT_CSTRING_AUTH,
	CLDI_DEFAULT_CONSTCSTR_AUTH      = CLDI_DEFAULT_CSTRING_AUTH | CLDI_CONST_STRING,
	CLDI_DEFAULT_CONSTWSTR_AUTH      = CLDI_DEFAULT_WSTRING_AUTH | CLDI_CONST_STRING,
	CLDI_DEFAULT_CONSTSTR_ASCII_AUTH = CLDI_DEFAULT_ASCIISTR_AUTH | CLDI_CONST_STRING,
	CLDI_DEFAULT_CONSTSTR_UTF8_AUTH  = CLDI_DEFAULT_UTF8STR_AUTH | CLDI_CONST_STRING,
	CLDI_DEFAULT_CONSTSTR_UTF16_AUTH = CLDI_DEFAULT_UTF16STR_AUTH | CLDI_CONST_STRING,
	CLDI_DEFAULT_CONSTSTR_AUTH       = CLDI_DEFAULT_CONSTCSTR_AUTH,

	// Flag presets
	CLDI_DEFAULT_CSTRING   = CLDI_DEFAULT_CSTRING_PERMS,
	CLDI_DEFAULT_WSTRING   = CLDI_DEFAULT_WSTRING_PERMS,
	CLDI_DEFAULT_STRING    = CLDI_DEFAULT_CSTRING,
	CLDI_DEFAULT_ASCIISTR  = CLDI_DEFAULT_ASCIISTR_PERMS,
	CLDI_DEFAULT_UTF8STR   = CLDI_DEFAULT_UTF8STR_PERMS,
	CLDI_DEFAULT_UTF16STR  = CLDI_DEFAULT_UTF16STR_PERMS,
	CLDI_DEFAULT_CONSTCSTR = CLDI_DEFAULT_CONSTCSTR_PERMS,
	CLDI_DEFAULT_CONSTWSTR = CLDI_DEFAULT_CONSTWSTR_PERMS,
	CLDI_DEFAULT_CONSTSTR  = CLDI_DEFAULT_CONSTCSTR,
	CLDI_DEFAULT_CONSTSTR_ASCII = CLDI_DEFAULT_CONSTSTR_ASCII_PERMS,
	CLDI_DEFAULT_CONSTSTR_UTF8  = CLDI_DEFAULT_CONSTSTR_UTF8_PERMS,
	CLDI_DEFAULT_CONSTSTR_UTF16 = CLDI_DEFAULT_CONSTSTR_UTF16_PERMS,
} CLDI_STRING_FLAG;
// Compile all string flags relevant to memory access and allocation into their
// proper bit positions in the return.
int cldiStringCompileMemFlags(int string_flags);
// Set the encoding format of a word of string flags
int cldiStringFlagsSetFormat(int flags, CLDI_STRING_FLAG encoding_format);
// Set the permissions of a word of string flags
int cldiStringFlagsSetPerms(int flags, int set_perms);
// Set the group permissions of a word of string flags
int cldiStringFlagsSetGroupPerms(int flags, int set_perms);
// Set the public permissions of a word of string flags
int cldiStringFlagsSetPublicPerms(int flags, int set_perms);
// Set some mask of bits within a word of string flags to some other value
int cldiStringFlagsSetWithMask(int flags, int mask, int newval);

typedef struct _CLDISTRING
{
	cldimemref data;
	size_t     len;
	int        flags;
} cldistr_t, cldistring_t;

/* Methods associated with cldistr_t: */

/* Construct as blank string (null values). */
CLDISTAT cldiInitString(cldistr_t *self);
/* Construct from c-string. */
CLDISTAT cldiInitStringC(cldistr_t *self, const char *str);
CLDISTAT cldiInitStringCEx(cldistr_t *self, const char *str, size_t extracap, int flags, bool utf8_src);
CLDISTAT cldiInitStringNC(cldistr_t *self, size_t n, const char *str);
CLDISTAT cldiInitStringNCEx(cldistr_t *self, size_t n, const char *str, size_t extracap, int flags, bool utf8_src);
/* Construct from c-style wstring. */
CLDISTAT cldiInitStringW(cldistr_t *self, const wchar_t *str);
CLDISTAT cldiInitStringWEx(cldistr_t *self, const wchar_t *str, size_t extracap, int flags);
CLDISTAT cldiInitStringNW(cldistr_t *self, size_t n, const wchar_t *str);
CLDISTAT cldiInitStringNWEx(cldistr_t *self, size_t n, const wchar_t *str, size_t extracap, int flags);
/* Construct as a copy of another string. */
CLDISTAT cldiInitStringCopy(cldistr_t *self, const cldistr_t *copy_of);
CLDISTAT cldiInitStringCopyEx(cldistr_t *self, const cldistr_t *copy_of, size_t extracap, int flags);
/* Construct borrowed from another string. */
CLDISTAT cldiInitStringBorrowed(cldistr_t *self, const cldistr_t *borrow);
CLDISTAT cldiInitStringBorrowedEx(cldistr_t *self, const cldistr_t *borrow, int flags);
/* Construct with preallocated capacity. */
CLDISTAT cldiInitStringEmpty(cldistr_t *self, size_t bufsize);
CLDISTAT cldiInitStringEmptyW(cldistr_t *self, size_t bufsize);
CLDISTAT cldiInitStringEmptyEx(cldistr_t *self, size_t bufsize, int flags);
/* Make a new instance and pass over the stack. */
cldistr_t cldiMakeString();
cldistr_t cldiMakeStringC(const char *str);
cldistr_t cldiMakeStringCEx(const char *str, size_t extracap, int flags, bool utf8_src);
cldistr_t cldiMakeStringNC(size_t n, const char *str);
cldistr_t cldiMakeStringNCEx(size_t n, const char *str, size_t extracap, int flags, bool utf8_src);
cldistr_t cldiMakeStringW(const wchar_t *str);
cldistr_t cldiMakeStringWEx(const wchar_t *str, size_t extracap, int flags);
cldistr_t cldiMakeStringNW(size_t n, const wchar_t *str);
cldistr_t cldiMakeStringNWEx(size_t n, const wchar_t *str, size_t extracap, int flags);
cldistr_t cldiMakeStringCopy(const cldistr_t *copy_of);
cldistr_t cldiMakeStringCopyEx(const cldistr_t *copy_of, size_t extracap, int flags);
cldistr_t cldiMakeStringBorrowed(const cldistr_t *borrow);
cldistr_t cldiMakeStringBorrowedEx(const cldistr_t *borrow, int flags);
cldistr_t cldiMakeStringEmpty(size_t bufsize);
cldistr_t cldiMakeStringEmptyW(size_t bufsize);
cldistr_t cldiMakeStringEmptyEx(size_t bufsize, int flags);
/* Make a new instance in the heap. */
cldimemref cldiNewString();
cldimemref cldiNewStringC(const char *str);
cldimemref cldiNewStringCEx(const char *str, size_t extracap, int flags, bool utf8_src);
cldimemref cldiNewStringNC(size_t n, const char *str);
cldimemref cldiNewStringNCEx(size_t n, const char *str, size_t extracap, int flags, bool utf8_src);
cldimemref cldiNewStringW(const wchar_t *str);
cldimemref cldiNewStringWEx(const wchar_t *str, size_t extracap, int flags);
cldimemref cldiNewStringNW(size_t n, const wchar_t *str);
cldimemref cldiNewStringNWEx(size_t n, const wchar_t *str, size_t extracap, int flags);
cldimemref cldiNewStringCopy(const cldistr_t *copy_of);
cldimemref cldiNewStringCopyEx(const cldistr_t *copy_of, size_t extracap, int flags);
cldimemref cldiNewStringBorrowed(const cldistr_t *borrow);
cldimemref cldiNewStringBorrowedEx(const cldistr_t *borrow, int flags);
cldimemref cldiNewStringEmpty(size_t bufsize);
cldimemref cldiNewStringEmptyW(size_t bufsize);
cldimemref cldiNewStringEmptyEx(size_t bufsize, int flags);

/* cldistr_t memory block destructor (for memory management). */
CLDISTAT   cldiStringDropBlock(cldimemref *blk);
/* Drop cldistr_t object. */
CLDISTAT   cldiDropString(cldistr_t *drop);

/* Convert the string to ASCII, do nothing if already ASCII. */
CLDISTAT cldiStringConvertASCII(cldistr_t *self);
/* Convert the string to UTF-8, do nothing if already UTF-8 or ASCII (change
.  flags to UTF-8). */
CLDISTAT cldiStringConvertUTF8(cldistr_t *self);
/* Convert the string to UTF-16, do nothing if already UTF-16. */
CLDISTAT cldiStringConvertUTF16(cldistr_t *self);

/* Get the size of the string's characters. */
size_t            cldiStringCharSize(const cldistr_t *self);
/* Get the initialized size of the string. */
size_t            cldiStringSize(const cldistr_t *self);
/* Get the initialized size (in bytes) of the string. */
size_t            cldiStringBytesSize(const cldistr_t *self);
/* Get the total capacity of the string's memory (in characters). */
size_t            cldiStringCapacity(const cldistr_t *self);
/* Get the total capacity of the string's memory (in bytes). */
size_t            cldiStringBytesCapacity(const cldistr_t *self);
/* Calculate the total amount of memory used by the string -- between the structure
.  itself and the memory it may or may not own, borrowed memory is not counted. */
size_t            cldiStringMemoryUsage(const cldistr_t *self);

/* Check if the string is const. */
bool              cldiStringIsConst(const cldistr_t *self);
/* Check of the string is an ASCII string. */
bool              cldiStringIsASCII(const cldistr_t *self);
/* Check if the string is a basic char string (UTF-8). */
bool              cldiIsCString(const cldistr_t *self);
/* Check if the string is a wchar_t string (UTF-16). */
bool              cldiIsWString(const cldistr_t *self);
/* Attempt to fetch string data in a non-const context. */
char*             cldiStringData(cldistr_t *self);
/* Attempt to fetch string data in a const context. */
const char*       cldiStringConstData(const cldistr_t *self);
/* Attempt to fetch string data in a non-const context, if wchar_t. */
wchar_t*          cldiStringDataW(cldistr_t *self);
/* Attempt to fetch string data in a const context, if wchar_t. */
const wchar_t*    cldiStringConstDataW(const cldistr_t *self);
/* Attempt to get the string's memory heap in a non-const context. */
cldiheap_t*       cldiStringGetHeap(cldistr_t *self);
/* Attempt to get the string's memory heap in a const context. */
const cldiheap_t* cldiStringGetHeapConst(const cldistr_t *self);

/* cldistr_t item generator for iteration (char). */
void*             cldiStringIterGenItemC(cldiiter_t *iterable);
/* cldistr_t item generator for iteration (wchar_t). */
void*             cldiStringIterGenItemW(cldiiter_t *iterable);

cldiiter_t        cldiStringIter(cldistr_t *self);
cldiiter_t        cldiStringIterRev(cldistr_t *self);
cldiiter_t        cldiStringIterAt(cldistr_t *self, ssize_t idx);
cldiiter_t        cldiStringIterRevAt(cldistr_t *self, ssize_t idx);
cldiiterconst_t   cldiStringConstIter(cldistr_t *self);
cldiiterconst_t   cldiStringConstIterRev(cldistr_t *self);
cldiiterconst_t   cldiStringConstIterAt(cldistr_t *self, ssize_t idx);
cldiiterconst_t   cldiStringConstIterRevAt(cldistr_t *self, ssize_t idx);
CLDISTAT          cldiStringForEach(cldistr_t *self, cldiloopfunc_t func);
CLDISTAT          cldiStringForEachConst(cldistr_t *self, cldiloopconst_t func);
CLDISTAT          cldiStringForEachRev(cldistr_t *self, cldiloopfunc_t func);
CLDISTAT          cldiStringForEachConstRev(cldistr_t *self, cldiloopconst_t func);

CLDISTAT          cldiStringSyncFlags(const cldistr_t *self);
int               cldiStringGetFlags(const cldistr_t *self);
int               cldiStringGetPerms(const cldistr_t *self);
CLDISTAT          cldiStringGetAuth(const cldistr_t *self);
bool              cldiStringHasFlags(const cldistr_t *self, int flags);
bool              cldiStringHasPerms(const cldistr_t *self, int perms);
CLDISTAT          cldiStringHasAuth(const cldistr_t *self, int auth);
CLDISTAT          cldiStringSetFlagsWithMask(cldistr_t *self, int mask, int flags);
CLDISTAT          cldiStringSetFlags(cldistr_t *self, int flags);
CLDISTAT          cldiStringSetPerms(cldistr_t *self, int perms);
CLDISTAT          cldiStringSetAuth(cldistr_t *self, int auth);
CLDISTAT          cldiStringSetConst(cldistr_t *self);
CLDISTAT          cldiStringRemoveFlags(cldistr_t *self, int flags);
CLDISTAT          cldiStringRemovePerms(cldistr_t *self, int perms);
CLDISTAT          cldiStringRemoveAuth(cldistr_t *self, int auth);
CLDISTAT          cldiStringRemoveConst(cldistr_t *self);
CLDISTAT          cldiStringToggleFlags(cldistr_t *self, int flags);
CLDISTAT          cldiStringToggleConst(cldistr_t *self);
bool              cldiStringAuthorAccess(const cldistr_t *self);
bool              cldiStringOwnerAccess(const cldistr_t *self);
bool              cldiStringGroupAccess(const cldistr_t *self);
bool              cldiStringIsReadable(const cldistr_t *self);
bool              cldiStringIsWritable(const cldistr_t *self);
bool              cldiStringOwnerIsAuthor(const cldistr_t *self);
bool              cldiStringGroupReadable(const cldistr_t *self);
bool              cldiStringGroupWritable(const cldistr_t *self);
bool              cldiStringGroupIsAuthor(const cldistr_t *self);
bool              cldiStringPublicReadable(const cldistr_t *self);
bool              cldiStringPublicWritable(const cldistr_t *self);
bool              cldiStringPublicIsAuthor(const cldistr_t *self);

CLDISTAT          cldiStringBorrow(cldistr_t *self, const cldistr_t *borrow_from);

CLDISTAT          cldiStringReserveTotal(cldistr_t *self, size_t total_size);
CLDISTAT          cldiStringReserve(cldistr_t *self, size_t additional_size);
CLDISTAT          cldiStringExpandEnd(cldistr_t *self, size_t expand_by);
#define           cldiStringExpand cldiStringExpandEnd
CLDISTAT          cldiStringExpandBeg(cldistr_t *self, size_t expand_by);
CLDISTAT          cldiStringExpandAt(cldistr_t *self, size_t expand_by, ssize_t expand_at);

CLDISTAT          cldiStringTrimEnd(cldistr_t *self, size_t n);
#define           cldiStringTrim cldiStringTrimEnd
CLDISTAT          cldiStringTrimBeg(cldistr_t *self, size_t n);
CLDISTAT          cldiStringTrimAt(cldistr_t *self, ssize_t trim_at, size_t n_elements);
CLDISTAT          cldiStringTrimToSize(cldistr_t *self);
CLDISTAT          cldiStringTruncEnd(cldistr_t *self, size_t n);
CLDISTAT          cldiStringTruncBeg(cldistr_t *self, size_t n);
CLDISTAT          cldiStringTruncAt(cldistr_t *self, ssize_t idx, size_t n);
CLDISTAT          cldiStringTruncAll(cldistr_t *self);
#define           cldiStringTrunc cldiStringTruncAll

CLDISTAT          cldiStringPushBack(cldistr_t *self, char c);
CLDISTAT          cldiStringPushBackW(cldistr_t *self, wchar_t wc);
#define           cldiStringPush  cldiStringPushBack
#define           cldiStringPushW cldiStringPushBackW
CLDISTAT          cldiStringPushFront(cldistr_t *self, char c);
CLDISTAT          cldiStringPushFrontW(cldistr_t *self, wchar_t wc);
CLDISTAT          cldiStringPushAt(cldistr_t *self, ssize_t push_at, char c);
CLDISTAT          cldiStringPushWAt(cldistr_t *self, ssize_t push_at, wchar_t wc);
char              cldiStringPop(cldistr_t *self);
wchar_t           cldiStringPopW(cldistr_t *self);
char              cldiStringPopFront(cldistr_t *self);
wchar_t           cldiStringPopFrontW(cldistr_t *self);
char              cldiStringPopFrom(cldistr_t *self, ssize_t pop_from);
wchar_t           cldiStringPopFromW(cldistr_t *self, ssize_t pop_from);
size_t            cldiStringAppend(cldistr_t *self, const cldistr_t *append);
size_t            cldiStringAppendBeg(cldistr_t *self, const cldistr_t *append);
size_t            cldiStringAppendAt(cldistr_t *self, ssize_t append_at, const cldistr_t *append);
size_t            cldiStringAppendSubstring(
	cldistr_t       *self,
	ssize_t          substr_beg,
	size_t           substr_len,
	const cldistr_t *append
);
size_t            cldiStringAppendSubstringBeg(
	cldistr_t       *self,
	ssize_t          substr_beg,
	size_t           substr_len,
	const cldistr_t *append
);
size_t            cldiStringAppendSubstringAt(
	cldistr_t       *self,
	ssize_t          append_at,
	ssize_t          substr_beg,
	size_t           substr_len,
	const cldistr_t *append
);
size_t            cldiStringAppendRaw(cldistr_t *self, const char *str);
size_t            cldiStringAppendRawN(cldistr_t *self, size_t n, const char *str);
size_t            cldiStringAppendRawW(cldistr_t *self, const wchar_t *wstr);
size_t            cldiStringAppendRawWN(cldistr_t *self, size_t n, const wchar_t *wstr);
size_t            cldiStringAppendBegRaw(cldistr_t *self, const char *str);
size_t            cldiStringAppendBegRawN(cldistr_t *self, size_t n, const char *str);
size_t            cldiStringAppendBegRawW(cldistr_t *self, const wchar_t *wstr);
size_t            cldiStringAppendBegRawWN(cldistr_t *self, size_t n, const wchar_t *wstr);
size_t            cldiStringAppendRawAt(cldistr_t *self, ssize_t append_at, const char *str);
size_t            cldiStringAppendRawAtN(cldistr_t *self, ssize_t append_at, size_t n, const char *str);
size_t            cldiStringAppendRawAtW(cldistr_t *self, ssize_t append_at, const wchar_t *wstr);
size_t            cldiStringAppendRawAtWN(cldistr_t *self, ssize_t append_at, size_t n, const wchar_t *wstr);

char              cldiStringGetch(const cldistr_t *self, ssize_t char_idx);
wchar_t           cldiStringGetchW(const cldistr_t *self, ssize_t wchar_idx);
CLDISTAT          cldiStringExportRawSubstr(
	const cldistr_t *self,
	ssize_t          export_idx,
	size_t           export_len,
	char            *export_to
);
CLDISTAT          cldiStringExportRawSubstrW(
	const cldistr_t *self,
	ssize_t          export_idx,
	size_t           export_len,
	wchar_t         *export_to
);
CLDISTAT          cldiStringExportSubstr(
	const cldistr_t *self,
	ssize_t          export_idx,
	size_t           export_len,
	cldistr_t       *export_to
);
CLDISTAT          cldiStringExportSubstrW(
	const cldistr_t *self,
	ssize_t          export_idx,
	size_t           export_len,
	cldistr_t       *export_to
);
cldistr_t         cldiStringSubstr(
	const cldistr_t *self,
	ssize_t          export_idx,
	size_t           export_len,
	cldistr_t       *export_to
);
cldistr_t         cldiStringSubstrW(
	const cldistr_t *self,
	ssize_t          export_idx,
	size_t           export_len,
	cldistr_t       *export_to
);
cldimemref        cldiStringNewSubstr(
	const cldistr_t *self,
	ssize_t          export_idx,
	size_t           export_len
);
cldimemref        cldiStringNewSubstrW(
	const cldistr_t *self,
	ssize_t          export_idx,
	size_t           export_len
);
cldimemref        cldiStringNewSubstrRaw(
	const cldistr_t *self,
	ssize_t          export_idx,
	size_t           export_len
);
cldimemref        cldiStringNewSubstrRawW(
	const cldistr_t *self,
	ssize_t          export_idx,
	size_t           export_len
);

size_t            cldiStringSetToCopy(cldistr_t *self, const cldistr_t *copy_of);
#define           cldiStringSet cldiStringSetToCopy
size_t            cldiStringSetToSubcopy(
	cldistr_t       *self,
	ssize_t          subcopy_beg,
	size_t           subcopy_len,
	const cldistr_t *subcopy_from
);
size_t            cldiStringSetEnd(cldistr_t *self, const cldistr_t *set_to);
size_t            cldiStringSetSubstrEnd(
	cldistr_t       *self,
	ssize_t          substr_beg,
	size_t           substr_len,
	const cldistr_t *substr_from
);
size_t            cldiStringSetBeg(cldistr_t *self, const cldistr_t *set_to);
size_t            cldiStringSetSubstrBeg(
	cldistr_t       *self,
	ssize_t          substr_beg,
	size_t           substr_len,
	const cldistr_t *substr_from
);
size_t            cldiStringSetAt(cldistr_t *self, ssize_t set_at, const cldistr_t *set_to);
size_t            cldiStringSetSubstrAt(
	cldistr_t       *self,
	ssize_t          set_at,
	ssize_t          substr_beg,
	size_t           substr_len,
	const cldistr_t *substr_from
);
size_t            cldiStringSetToRaw(cldistr_t *self, const char *set_to);
size_t            cldiStringSetEndRaw(cldistr_t *self, const char *set_to);
size_t            cldiStringSetBegRaw(cldistr_t *self, const char *set_to);
size_t            cldiStringSetRawAt(cldistr_t *self, ssize_t set_at, const char *set_to);
size_t            cldiStringSetToRawN(cldistr_t *self, size_t n, const char *set_to);
size_t            cldiStringSetEndRawN(cldistr_t *self, size_t n, const char *set_to);
size_t            cldiStringSetBegRawN(cldistr_t *self, size_t n, const char *set_to);
size_t            cldiStringSetRawAtN(cldistr_t *self, ssize_t set_at, size_t n, const char *set_to);
size_t            cldiStringSetToRawW(cldistr_t *self, const wchar_t *set_to);
size_t            cldiStringSetEndRawW(cldistr_t *self, const wchar_t *set_to);
size_t            cldiStringSetBegRawW(cldistr_t *self, const wchar_t *set_to);
size_t            cldiStringSetRawAtW(cldistr_t *self, ssize_t set_at, const wchar_t *set_to);
size_t            cldiStringSetToRawWN(cldistr_t *self, size_t n, const wchar_t *set_to);
size_t            cldiStringSetEndRawWN(cldistr_t *self, size_t n, const wchar_t *set_to);
size_t            cldiStringSetBegRawWN(cldistr_t *self, size_t n, const wchar_t *set_to);
size_t            cldiStringSetRawAtWN(cldistr_t *self, ssize_t set_at, size_t n, const wchar_t *set_to);

/* Strip() and Replace() methods return the amount of chars that have been stripped or replaced. */
/* Strip leading and trailing whitespace from the string. */
size_t            cldiStringStrip(cldistr_t *self);
/* Strip leading and trailing whitespace (except newlines) from the string. */
size_t            cldiStringStripLines(cldistr_t *self);
/* Strip leading whitespace from the string. */
size_t            cldiStringStripBeg(cldistr_t *self);
/* Strip leading whitespace (except newlines) from the string. */
size_t            cldiStringStripBegLines(cldistr_t *self);
/* Strip trailing whitespace from the string. */
size_t            cldiStringStripEnd(cldistr_t *self);
/* Strip trailing whitespace (except newlines) from the string. */
size_t            cldiStringStripEndLines(cldistr_t *self);
/* Strip all whitespace characters, even between words and symbols, from the
.  string, and replace with a single space each. */
size_t            cldiStringStripAll(cldistr_t *self);
// - Specify delimiter character to override space with.
size_t            cldiStringStripAllEx(cldistr_t *self, int delimiter_char);
/* Strip all whitespace characters (except newlines), even between words and
.  symbols, from the string, and replace with a single space each. */
size_t            cldiStringStripAllLines(cldistr_t *self);
// - Specify delimiter character to override space with.
size_t            cldiStringStripAllLinesEx(cldistr_t *self, int delimiter_char);

/* Replace all instances of some character with another. */
size_t            cldiStringReplaceChar(cldistr_t *self, int replace_char, int replace_with);
/* Replace all instances of some substring with another. */
// - UTF-8 or ASCII string input (does not matter what format `self` is).
size_t            cldiStringReplaceSubstrC(cldistr_t *self, const char *replace, const char *with);
// - UTF-16 string input.
size_t            cldiStringReplaceSubstrW(cldistr_t *self, const wchar_t *replace, const wchar_t *with);
// - cldistr_t
size_t            cldiStringReplaceSubstr(cldistr_t *self, const cldistr_t *replace, const cldistr_t *with);

/* Find the amount of instances of some character. */
size_t            cldiStringCharCount(cldistr_t *self, int char_value);
/* Find the amount of instances of some substring. */
// - ASCII or UTF-8 string.
size_t            cldiStringStrCountC(cldistr_t *self, const char *example);
// - UTF-16 string.
size_t            cldiStringStrCountW(cldistr_t *self, const wchar_t *example);
// - cldistr_t
size_t            cldiStringStrCount(cldistr_t *self, const cldistr_t *example);
/* Find the amount of instances of some character. */
size_t            cldiStringFindFirstChar(cldistr_t *self, int char_value);
/* Find the amount of instances of some substring. */
// - ASCII or UTF-8 string.
size_t            cldiStringFindFirstCStr(cldistr_t *self, const char *find);
// - UTF-16 string.
size_t            cldiStringFindFirstWStr(cldistr_t *self, const wchar_t *find);
// - cldistr_t
size_t            cldiStringFindFirstStr(cldistr_t *self, const cldistr_t *find);
/* Find the amount of instances of some character, `pass_amount` is the amount
.  of chars to pass before landing on the index to return, for instance, 0 for
.  the first instance, 3 for the fourth, and so on. */
size_t            cldiStringFindChar(cldistr_t *self, int char_value, size_t pass_amount);
/* Find the amount of instances of some substring. */
// - ASCII or UTF-8 string.
size_t            cldiStringFindCStr(cldistr_t *self, const char *find, size_t pass_amount);
// - UTF-16 string.
size_t            cldiStringFindWStr(cldistr_t *self, const wchar_t *find, size_t pass_amount);
// - cldistr_t
size_t            cldiStringFindStr(cldistr_t *self, const cldistr_t *find, size_t pass_amount);

/* Compare the beginning of the string to the contents of some other string. */
// - ASCII or UTF-8 string.
CLDISTAT          cldiStringCompareBegC(cldistr_t *self, size_t n, const char *cmp);
// - UTF-16
CLDISTAT          cldiStringCompareBegW(cldistr_t *self, size_t n, const wchar_t *cmp);
// - cldistr_t
CLDISTAT          cldiStringCompareBeg(cldistr_t *self, const cldistr_t *cmp);
/* Compare the end of the string to the contents of some other string. */
// - ASCII or UTF-8 string.
CLDISTAT          cldiStringCompareEndC(cldistr_t *self, size_t n, const char *cmp);
// - UTF-16
CLDISTAT          cldiStringCompareEndW(cldistr_t *self, size_t n, const wchar_t *cmp);
// - cldistr_t
CLDISTAT          cldiStringCompareEnd(cldistr_t *self, const cldistr_t *cmp);
/* Compare some portion in the string to the contents of some other string. */
// - ASCII or UTF-8 string.
CLDISTAT          cldiStringCompareSubstrC(cldistr_t *self, ssize_t compare_at, size_t n, const char *cmp);
// - UTF-16
CLDISTAT          cldiStringCompareSubstrW(cldistr_t *self, ssize_t compare_at, size_t n, const wchar_t *cmp);
// - cldistr_t
CLDISTAT          cldiStringCompareSubstr(cldistr_t *self, ssize_t compare_at, const cldistr_t *cmp);



#ifdef __cplusplus
}
#endif

#endif // _cldi_head__STRING_H
