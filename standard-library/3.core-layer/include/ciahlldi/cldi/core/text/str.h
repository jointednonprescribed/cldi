
#ifndef _cldi_core__types_STR_H
#define _cldi_core__types_STR_H 1

/* Setup for cldi-core.            */
#include "../setup.h"

/* Requires: cldi-portable: types */
#include <ciahlldi/cldi/portable/types.h>
/*                          text/chartypes */
#include <ciahlldi/cldi/portable/text/chartypes.h>



/* ----------------------------------- */
/* String Type (`cldistr`) */

/* Type implementation */
#include "str/IMPL/STR.h"
/* String Relationship/Partnership Enumerator */
#include "str/IMPL/STR_REL.h"
/* String Range Marker structure */
#include "str/IMPL/STR_RANGE_MARKER.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Null value for cldistr */
extern const cldistr CLDISTR_NULL;
#if defined(__cplusplus) && __CLDI_no_cpp < true
#define CLDISTR_NULL _cldistr::null
#else
extern const cldistr CLDISTR_NULL;
#endif

/* Copy a string object from one struct to another safely (NOT RECOMMENDED).
.  This function disobeys proper ways of handling string ownership and borrowing. */
CLDISTAT _cldiCopyStrObject(cldistr *_cldi_restrict_ destination, const cldistr *_cldi_restrict_ source);


/* Drop ownership/borrowing of this object's data. */
CLDISTAT cldiDropStr(cldistr * self);
/* Drop ownership/borrowing of this object and its data. */
CLDISTAT cldiDropStrObject(cldistr * drop);

/* Default Initializer */
CLDISTAT cldiInitStr(cldistr * self);

/* New() function for allocation in the heap. */
cldistr* cldiNewStr(void);
CLDISTAT cldiNewStrEx(cldistr** out);

/* --- Initialize from a const C-style array or string (of variable encoding type). --- */
/* Initialize a copy of the array passed in as the origin state. */
CLDISTAT cldiInitStrNewState(
	cldistr         * err,
	CLDI_CHARTYPE     char_type,
		/* The character type of the string
		.  (refer to enum type). */
	size_t        length,
		/* The amount of characters in the string. */
	const void *const string
		/* The array to copy as the origin, this is *const
		.  (as opposed to *) so that it can remain safe
		.  (static) through a c style cast to `const char*`
		.  (or some other char type). */
);
/* - Create a modifiable state from the new origin.
.    - Alias */
#define cldiInitStrExt cldiInitStrExtendedState
CLDISTAT cldiInitStrExtendedState(
	cldistr* err,
	CLDI_CHARTYPE, size_t, const void *const,
		/* Same three arguments as above. */
	size_t             extra_capacity
		/* The extra amount of chars to create space for in the
		.  new writable version. */
);
/* - No extra capacity, just a modifiable copy. */
CLDISTAT cldiInitStrNewCopy(
	cldistr * err,
	CLDI_CHARTYPE, size_t, const void *const
		/* Same as from above. */
);
/* Use C-style zero-terminated string (UTF8/ASCII). */
CLDISTAT cldiInitStrAsCStr(
	cldistr    * self,
	const char * string
		/* The zero-terminated, C-style string to use. */
);
/* - Create a modifiable state from the new origin with some extra amount of
.    characters at the end for extra capacity. */
/*   - Alias */
#define  cldiInitStrAsCStrExt cldiInitStrExtendCStr
CLDISTAT cldiInitStrExtendCStr(
	cldistr* err,
	const char* /* Same as above. */,
	size_t     extra_capacity
		/* The extra capacity to allocate for more text. */
);
/* - No extra capacity, just create a modifiable copy. */
CLDISTAT cldiInitStrCopyCStr(
	cldistr* err,
	const char* /* Same as from above. */
);
/* Allocate a new instance in the heap. */
cldistr* cldiNewStrState(CLDI_CHARTYPE, size_t, const char *const);
cldistr* cldiNewStrExtendedState(CLDI_CHARTYPE, size_t, const char *const, size_t);
cldistr* cldiNewStrCopy(CLDI_CHARTYPE, size_t, const char *const);
cldistr* cldiNewStrAsCStr(const char*);
cldistr* cldiNewStrExtendCStr(const char*, size_t);
cldistr* cldiNewStrCopyCStr(const char*);
CLDISTAT cldiNewStrStateEx(cldistr** out, CLDI_CHARTYPE, size_t, const char *const);
CLDISTAT cldiNewStrExtendedStateEx(cldistr** out, CLDI_CHARTYPE, size_t, const char *const, size_t);
CLDISTAT cldiNewStrCopyEx(cldistr** out, CLDI_CHARTYPE, size_t, const char *const);
CLDISTAT cldiNewStrAsCStrEx(cldistr** out, const char*);
CLDISTAT cldiNewStrExtendCStrEx(cldistr** out, const char*, size_t);
CLDISTAT cldiNewStrCopyCStrEx(cldistr** out, const char*);

/* Initialize from another string, using it as an origin state. */
CLDISTAT cldiInitStrOrigin(
	cldistr       * err,
	const cldistr * from
		/* The other string to initialize from */
);
/* - Create a modifiable state from the new origin. */
CLDISTAT cldiInitStrExtended(
	cldistr       * err,
	const cldistr * copy,
		/* The other string to make an extension of                 */
	size_t      extra_space
		/* Amount of items to allocate for extra space (accepts 0) */
);
/* - No extra capacity, just a modifiable copy. */
CLDISTAT cldiInitStrAs(
	cldistr* self,
	const cldistr* /* Same as from above. */
);
/* Allocate a new instance in the heap. */
cldistr* cldiNewStrFrom(const cldistr*);
cldistr* cldiNewStrExtended(const cldistr*, size_t);
cldistr* cldiNewStrAs(const cldistr*);
CLDISTAT cldiNewStrFromEx(cldistr** out, const cldistr*);
CLDISTAT cldiNewStrExtendedEx(cldistr** out, const cldistr*, size_t);
CLDISTAT cldiNewStrAsEx(cldistr** out, const cldistr*);

/* Initialize from a substring (some portion) of another string. */
CLDISTAT cldiInitStrSubstring(
	cldistr       * err,
	ssize_t     beg,
	ssize_t     end,
	const cldistr * substring_of
);
/* Initialize from a snippet (some portion starting at the beginning)
.  of another string. */
CLDISTAT cldiInitStrSnippet(
	cldistr* self,
	ssize_t, const cldistr*
		/* Same 2 arguments as from above:
		.  `end` and `substring_of`, where
		.  `beg` is the beginning of the
		.  target string. */
);
/* New methods */
cldistr* cldiNewSubstring(ssize_t, ssize_t, const cldistr*);
cldistr* cldiNewSnippet(ssize_t, const cldistr*);
CLDISTAT cldiNewSubstringEx(cldistr** out, ssize_t, ssize_t, const cldistr*);
CLDISTAT cldiNewSnippetEx(cldistr** out, ssize_t, const cldistr*);

/* Initialize relative to another string. */
CLDISTAT cldiInitStrRelative(
	cldistr       * err,
	const cldistr * other,
	CLDISTRREL      relationship
);
/* - InitStrRelative(), but with more options available. */
CLDISTAT cldiInitStrRelativeEx(
	cldistr       * err,
	const cldistr * other,
	CLDISTRREL      relationship,
	bool            create_modifiable_copy,
	size_t      extension_size
);
/* Initialize from the origin of another string. */
CLDISTAT cldiInitStrSibling(
	cldistr       * err,
	const cldistr * sibling
		/* The object to initialize as a sibling of. */
);
/* - InitStrAsSibling(), but with more options available. */
CLDISTAT cldiInitStrSiblingEx(
	cldistr       * err,
	const cldistr * sibling,
	bool            create_modifiable_copy,
	size_t      extension_size
);
/* Initialize from the origin of another string. */
CLDISTAT cldiInitStrChild(
	cldistr       * err,
	const cldistr * child
		/* The object to initialize as a sibling of. */
);
/* - InitStrAsSibling(), but with more options available. */
CLDISTAT cldiInitStrChildEx(
	cldistr         * self,
	const cldistr   * child,
	bool              create_modifiable_copy,
	size_t        extension_size
);
/* Allocate a new instance in the heap. */
cldistr* cldiNewStrRelative(const cldistr*, CLDISTRREL);
cldistr* cldiNewStrSibling(const cldistr*);
cldistr* cldiNewStrChild(const cldistr*);
CLDISTAT cldiNewStrRelativeEx(cldistr** out, const cldistr*, CLDISTRREL, bool, size_t);
CLDISTAT cldiNewStrSiblingEx(cldistr** out, const cldistr*, bool, size_t);
CLDISTAT cldiNewStrChildEx(cldistr** out, const cldistr*, bool, size_t);

/* Initialize with preallocated size for storing string data. */
CLDISTAT cldiInitStrPreallocated(
	cldistr       * self,
	CLDI_CHARTYPE   string_type,
		/* The character type of the string. */
	size_t      amount
		/* The amount of characters to allocate. */
);
/* Allocate a new instance in the heap. */
cldistr* cldiNewStrPreallocated(CLDI_CHARTYPE, size_t);
CLDISTAT cldiNewStrPreallocatedEx(cldistr** out, CLDI_CHARTYPE, size_t);


/* ----------------------------------- */
/*      --- Getters & Setters ---      */

#if defined(__cplusplus) && __CLDI_no_cpp > false
extern "C++" {
#endif
/* Get a copy view of the modifiable state saved into a string handle (this
.  will package the address, length, and type, so that it use the string
.  in a type-safe way, while still supporting references to string states
.  that are not saved as ASCII or UTF-8, and wouldn't be represented by char*). */
CLDISTRHANDLE  cldiStrToHandle(const cldistr * self);
/* - StrToHandle(), but with more options available. */
CLDISTAT       cldiStrToHandleEx(const cldistr * self, CLDISTRHANDLE * save_into);
/* Get the string's origin state. */
CLDISTRHANDLE  cldiStrGetOrigin(const cldistr * self);
#if defined(__cplusplus) && __CLDI_no_cpp > false
}
#endif
/* Reference the string's origin state using a memory address. */
CLDISTRHANDLE* cldiStrGetOriginRef(const cldistr * self);

/* Get the length of the string's origin state. */
size_t     cldiStrLengthOfOrigin(const cldistr * self);
/* Get the total size of the string's origin state (some characters
.  are variable width). */
size_t     cldiStrSizeOfOrigin(const cldistr * self);
/* Get the character type of the origin state. */
CLDI_CHARTYPE  cldiStrTextTypeOfOrigin(const cldistr * self);

/* Get the address in memory of the string's modifiable state as char*
.  (pointer to individual bytes).
.  - Alias */
#define cldiStrData cldiStrGetBytes
const char *      cldiStrGetBytes(const cldistr * self);
/* Get the address, in memory, of the string's modifiable state.
.  - Alias */
#define cldiStrDataAddress cldiStrGetAddress
const void *const cldiStrGetAddress(const cldistr * self);
/* Get the length of the string's modifiable state (or orgin state if no
 * modifiable state), only counting actually initialized characters. */
size_t        cldiStrLength(const cldistr * self);
/* Get the total size of initialized string data (some characters are
.  variable width). */
size_t        cldiGetStrInitializedSize(const cldistr * self);
/* Get the size of the memory block allocated to store string data. */
size_t        cldiGetStrMemorySize(const cldistr * self);
/* Get the total size all together of all the memory allocated by the
.  string (origin and modifiable). */
size_t        cldiGetStrTotalSize(const cldistr * self);
/* Get the current character type of the string. */
CLDI_CHARTYPE     cldiGetStrTextType(const cldistr * self);
/* Get the size of the current character type of the string. */
size_t        cldiGetStrTextTypeSize(const cldistr * self);

/* Check if the string has any unused capacity left in its modifiable
.  state (if it has one, and false will be returned if not). */
bool cldiStrHasUnusedSpace(const cldistr * self);
/* Check if the string's modifiable state has written to all of it's
.  currently allocated memory. */
bool cldiStrHasFullTextField(const cldistr * self);
/* Check if the string is currently in a different character type (text type)
.  than its origin state. */
bool cldiStrHasChangedTextTypes(const cldistr * self);

/* Check if the string is null (no states, origin, or modifiable). */
bool cldiStrIsNull(const cldistr * self);
/* Check if the string is usable (valid, non-null, has data, etc.). */
bool cldiStrIsUsable(const cldistr * self);
/* Check if the string is unusable (null, invalid type, etc.). */
bool cldiStrIsUnusable(const cldistr * self);
/* Check that the string is not of an invalid type (null type will pass this check). */
bool cldiStrIsValid(const cldistr * self);
/* Check if the string is of an invalid type. */
bool cldiStrIsInvalid(const cldistr * self);

/* Check if the string has an origin state. */
bool cldiStrHasOriginState(const cldistr * self);
/* Check if the string has a modifiable state (is not const). */
bool cldiStrHasModifiableState(const cldistr * self);
/* Check if the string has both states (origin and modifiable). */
bool cldiStrHasBothStates(const cldistr * self);
/* Check if the string is EXCLUSIVELY writable (contains only a modifiable state). */
bool cldiStrIsExclusivelyWritable(const cldistr * self);
/* Check if the string is const (contains only an origin state). */
bool cldiStrIsConst(const cldistr * self);
/* Alias for HasModifiableState(). */
#define cldiStrIsWritable cldiStrHasModifiableState

/* Include type for marking two indices inside of a string. */
#include "str/IMPL/STR_RANGE_MARKER.h"
/* Find the absolute position of some index in the string (ssize_t is a signed
.  size type that can be used to specify indices that can be relative to the
.  beginning of the string (positive), or the end of the string (negative),
.  this method uses this, and returns what it finds as the "absolute" index
.  of the initial index, which is relative to the beginning). */
size_t cldiGetStrAbsolutePosition(const cldistr * self, ssize_t index);
/* Find the actual offset (amount of bytes leading up to) a given index of a
.  character in the string. */
size_t cldiGetStrOffset(const cldistr * self, ssize_t index);\
/* These method requires a structure class to return all data. */
/* Find the true offsets of two indices in the string to map out a
.  set of boundaries (or a portion of the string) and return any errors
.  that are encountered. */
cldiStrRangeMarker cldiGetStrRange(
	const cldistr * self,
	ssize_t     beg,
		/* The first point, the beginning of the marker. */
	ssize_t     end
		/* the second point, the end of the marker. */
);
CLDISTAT cldiGetStrRangeEx(
	const cldistr      * self,
	ssize_t          beg,
	ssize_t          end,
	cldiStrRangeMarker * output_range_marker
);
/* --- Versions that operate using the origin. */
#define cldiGetStrAbsPositionInOrigin cldiGetStrAbsolutePositionInOrigin
#define cldiGetStrAbsolutePosInOrigin cldiGetStrAbsolutePositionInOrigin
#define cldiGetStrAbsPosInOrigin      cldiGetStrAbsolutePositionInOrigin
size_t         cldiGetStrAbsolutePositionInOrigin(const cldistr*, ssize_t);
size_t         cldiGetStrOffsetInOrigin(const cldistr*, ssize_t);
cldiStrRangeMarker cldiGetStrRangeInOrigin(const cldistr*, ssize_t, ssize_t);


/*      --- String Management ---      */

/* Copy some portion of the origin state data to some address. */
CLDISTAT cldiExportStrOriginSubstring(
	const cldistr * self,
	ssize_t     beg,
		/* The index to begin the string portion at. */
	ssize_t     end,
		/* The index to end the string portion at. */
	char          * save_to
		/* The memory to save the string portion to. */
);
/* Copy some portion (starting from the beginning, a snippet) of the
.  origin state data to some address. */
CLDISTAT cldiExportStrOriginSnippet(
	const cldistr*, ssize_t, char*
		/* Same arguments as above, but only `end` and `save_to`. */
);
/* Copy ALL data to some address. */
CLDISTAT cldiExportStrOrigin(
	const cldistr * self,
	char *       /* Same argument as from above (`save_to`). */
);
/* Write some portion of the origin state data to a file. */
CLDISTAT cldiWriteStrOriginSubstring(
	const cldistr*, ssize_t, ssize_t,
	FILE          * write_to
		/* The file to write to. */
);
CLDISTAT cldiWriteStrOriginSubstringEx(
	const cldistr*, ssize_t, ssize_t, FILE*,
	bool            flush_buffer
		/* Whether or not to flush the input buffer into the file,
		.  by default this would be true (is called with true inside of
		.  other functions like WriteStrOriginSubstring()). If this is
		.  set to false, only as much data from the selected substring
		.  portion as can fit inside the buffer at once will be copied. */
);
/* Write a snippet (some portion starting at the beginning) of the origin
.  state data to a file. */
CLDISTAT cldiWriteStrOriginSnippet(
	const cldistr*, ssize_t, FILE*
		/* Same arguments as from WriteStrOriginSubstring(), but only
		.  `end` and `write_to`. */
);
CLDISTAT cldiWriteStrOriginSnippetEx(
	const cldistr*, ssize_t, FILE*, bool
		/* Same arguments `end`, `write_to`, and `flush_buffer` as from
		.  WriteStrOriginSubstringEx(). */
);
/* Write all origin state data to a file. */
CLDISTAT cldiWriteStrOrigin(
	const cldistr*, FILE*
		/* Borrows argument `write_to` from WriteStrOriginSnippet/Substring. */
);
CLDISTAT cldiWriteStrOriginEx(
	const cldistr*, FILE*, bool
		/* Same arguments `write_to` and `flush_buffer` as from
		.  WriteStrOrigin[Snippet/Substring]Ex(). */
);

/* Copy some portion of the modifiable state data to some address. */
CLDISTAT cldiStrExportDataSubstring(
	const cldistr * self,
	ssize_t     beg,
		/* The index to begin the string portion at. */
	ssize_t     end,
		/* The index to end the string portion at. */
	char          * save_to
		/* The memory to save the string portion to. */
);
/* Copy some portion (starting from the beginning, a snippet) of the
.  data to some address. */
CLDISTAT cldiStrExportDataSnippet(
	const cldistr * self,
	ssize_t, char *
		/* Same arguments as above, but only `end` and `save_to`. */
);
/* Copy ALL data to some address. */
CLDISTAT cldiStrExportData(
	const cldistr * self,
	char *       /* Same argument as from above (`save_to`). */
);
/* Write some portion of the origin state data to a file. */
CLDISTAT cldiWriteStrSubstring(
	const cldistr*, ssize_t, ssize_t,
	FILE          * write_to
		/* The file to write to. */
);
CLDISTAT cldiWriteStrSubstringEx(
	const cldistr*, ssize_t, ssize_t, FILE*,
	bool            flush_buffer
		/* Whether or not to flush the input buffer into the file,
		.  by default this would be true (is called with true inside of
		.  other functions like WriteStrOriginSubstring()). If this is
		.  set to false, only as much data from the selected substring
		.  portion as can fit inside the buffer at once will be copied. */
);
/* Write a snippet (some portion starting at the beginning) of the origin
.  state data to a file. */
CLDISTAT cldiWriteStrSnippet(
	const cldistr*, ssize_t, FILE*
		/* Same arguments as from WriteStrOriginSubstring(), but only
		.  `end` and `write_to`. */
);
CLDISTAT cldiWriteStrSnippetEx(
	const cldistr*, ssize_t, FILE*, bool
		/* Same arguments `end`, `write_to`, and `flush_buffer` as from
		.  WriteStrOriginSubstringEx(). */
);
/* Write all origin state data to a file. */
CLDISTAT cldiWriteStr(
	const cldistr*, FILE*
		/* Borrows argument `write_to` from WriteStrOriginSnippet/Substring. */
);
CLDISTAT cldiWriteStrEx(
	const cldistr*, FILE*, bool
		/* Same arguments `write_to` and `flush_buffer` as from
		.  WriteStrOrigin[Snippet/Substring]Ex(). */
);


/* If `copy_instead` is false, you are simply sharing an origin state with
.  `save_to` (saving the other string as a sibling), however, if `copy_instead` is
.  true, make a copy of the origin for `save_to` to use as a replicant sibling,
.  all modifiable state data will be dropped. */
CLDISTAT cldiStrShareOrigin(const cldistr * self, cldistr * share_with, bool copy_instead);
/* Make a copy of the origin state, and save it to another string's
.  modifiable state, dropping all other data in the process. */
CLDISTAT cldiSaveStrOriginDataTo(const cldistr * self, cldistr * save_to);
/* Make a copy of the current data, and save it into another object's
.  modifiable state without sharing the origin state, the origin state
.  of `share_with` will not change. */
CLDISTAT cldiSaveStrDataAs(const cldistr * self, cldistr * save_to);
/* Make A full copy of the current string (share origin and modifiable data). */
CLDISTAT cldiSaveStrAs(const cldistr * self, cldistr * save_as);
/* When `copy_instead` is true, a copy of the origin state will be made, instead
.  of saving a sibling string with a shared origin state. */
CLDISTAT cldiSaveStrAsEx(const cldistr * self, cldistr save_as, bool copy_instead);

/* Allocate a new, empty modifiable state of a certain size. */
CLDISTAT cldiAllocateStrData (cldistr * self,  size_t bytes_amount);
CLDISTAT cldiAllocateStrChars(cldistr * self,  size_t chars_amount);
/* Resize the modifiable state and keep as much of the data as possible
.  with the new size (some may get cut off when reducing size). */
CLDISTAT cldiResizeStrData   (cldistr * self, ssize_t bytes_amount);
CLDISTAT cldiResizeStr       (cldistr * self, ssize_t chars_amount);
/* Expand the modifiable state by a certain number of bytes, and keep
.  all data. */
CLDISTAT cldiExpandStrData   (cldistr * self,  size_t bytes_amount);
CLDISTAT cldiExpandStr       (cldistr * self,  size_t chars_amount);
/* Recreate the modifiable state in memory (rarely useful). */
CLDISTAT cldiRecreateStr(cldistr * self);
/* Drop the current modifiable data completely (return to origin state). */
#define  cldiStrDelAll cldiDropStrData
CLDISTAT cldiDropStrData(cldistr * self);
/* Create a new modifiable state as an exact copy of the origin, and drop any
.  already existing data. */
CLDISTAT cldiStartStrFromOrigin(cldistr * self);
/* Start editing the string from the origin state, but include extra capacity
.  for mor characters. */
CLDISTAT cldiExpandStrFromOrigin(cldistr * self, size_t expand_by_amount_of_chars);


/* ----------------------------------- */
/*     --- String Manipulation ---     */

/* Append some raw string of characters at some index in the string,
.  to append some piece of string data to any chosen position in
.  the modifiable state. */
CLDISTAT cldiStrAppendCharsAt(
	cldistr         * self,
	CLDI_CHARTYPE     character_type,
		/* The character type of the raw string. */
	ssize_t       idx,
		/* The index in the base string to append to. */
	size_t        chars_amount,
		/* The amount of characters in the raw string to append,
		.  and the distance from the starting index to stop the
		.  append at. */
	const char *const chars
		/* The array of characters to append. */
);
/* Append a string in raw array form to the end of the string. */
CLDISTAT cldiStrAppendChars(
	cldistr * self,
	CLDI_CHARTYPE, size_t, const char *const
		/* 3 arguments borrowed from AppendStringAt():
		.  character_type, chars_amount, chars. */
);
/* Append a string in raw array form to the beginning of the string. */
CLDISTAT cldiStrAppendCharsBeg(
	cldistr * self,
	CLDI_CHARTYPE, size_t, const char *const
		/* 3 arguments borrowed from AppendStringAt():
		.  character_type, chars_amount, chars. */
);

/* Append a C-style primitive string to some index in the string. */
CLDISTAT cldiStrAppendCStrAt(cldistr * self, ssize_t idx, const char * string);
/* Append C-string to the end of the string. */
CLDISTAT cldiStrAppendCStr(cldistr * self, const char *);
/* Append C-string to the beginning of the string. */
CLDISTAT cldiStrAppendCStrBeg(cldistr * self, const char *);

/* Append multiple characters to some index in the string using
.  another cldistr object. */
CLDISTAT cldiStrAppendAt(cldistr * self, ssize_t idx, const cldistr * string);
/* Append string to the end. */
CLDISTAT cldiStrAppend(cldistr * self, const cldistr * string);
/* Append string to the beginning. */
CLDISTAT cldiStrAppendBeg(cldistr * self, const cldistr * string);

/* Append a substring of some string to a certain index. */
CLDISTAT cldiStrAppendSubstringAt(
	cldistr       * self,
	ssize_t     append_at,
		/* The index in the base string to append at. */
	ssize_t     substring_beg,
		/* The beginning index to start at in the appending string. */
	ssize_t     substring_end,
		/* The ending index to finish the substring at in the appending string. */
	const cldistr * take_substring_from
		/* The string to take the data portion from. */
);
/* Append a snippet (substring starting from the beginning) of a
.  string at a certain index. */
CLDISTAT cldiStrAppendSnippetAt(
	cldistr       * self,
	ssize_t     append_at,
		/* The index to append the snippet at. */
	ssize_t     snippet_end,
		/* The index in the appending string to
		.  end the snippet at (beginning will be
		.  the very beginning of the base string). */
	const cldistr * take_snippet_from
		/* The string to take the snippet from. */
);
/* Append a substring to the end of the string. */
CLDISTAT cldiStrAppendSubstring(
	cldistr * self,
	ssize_t, ssize_t, const cldistr *
		/* 3 arguments borrowed from AppendSubstringAt():
		.  - substring_beg, substring_end, take_substring_from. */
);
/* Append a snippet to the end of the string. */
CLDISTAT cldiStrAppendSnippet(
	cldistr * self,
	ssize_t, const cldistr *
		/* 2 arguments borrowed from AppendSnippetAt():
		.  - snippet_end, take_snippet_from. */
);
/* Append a substring to the beginning of the string. */
CLDISTAT cldiStrAppendSubstringBeg(
	cldistr * self,
	ssize_t, ssize_t, const cldistr *
		/* 3 arguments borrowed from AppendSubstringAt():
		.  - substring_beg, substring_end, take_substring_from. */
);
/* Append a snippet to the beginning of the string. */
CLDISTAT cldiStrAppendSnippetBeg(
	cldistr * self,
	ssize_t, const cldistr *
		/* 2 arguments borrowed from AppendSnippetAt():
		.  - snippet_end, take_snippet_from. */
);

/* Setting the value of any given portion of the characters
.  in the string's modifiable state to a new set of characters. */
CLDISTAT cldiSetStrCharsAt(
	cldistr         * self,
	CLDI_CHARTYPE     character_type,
		/* The character type of the string. */
	ssize_t       start_at,
		/* The index in the string to start setting values from. */
	size_t        size_of_set,
		/* The amount of chars to set into the string, and the
		.  distance from the starting index to stop setting
		.  values at. */
	const char *const set_to
		/* The values to set those chars to. */
);
/* Set the value of characters from the beginning of the string until
.  the size of the string has been reached, and all specified values
.  in range of that size. */
CLDISTAT cldiSetStrBegToChars(
	cldistr * self,
	CLDI_CHARTYPE, size_t, const char *const
		/* Same arguments from SetStringAt():
		.  `character_type`, `size_of_set`, and
		.  `set_to`, `start_at` will equal the beginning. */
);
/* Set the characters in the string leading up to the end to the
.  supplied values. */
CLDISTAT cldiSetStrEndToChars(
	cldistr * self,
	CLDI_CHARTYPE, size_t, const char *const
		/* Same arguments as SetBegToString(). */
);
/* Set chars from the beginning of the string until the size of the
.  string has been reached, but remove all chars after the ending index
.  (set the string to just the specified range of data). */
#define cldiSetStrToChars cldiSetStrChars
CLDISTAT cldiSetStrChars(
	cldistr * self,
	CLDI_CHARTYPE, size_t, const char* const
		/* Same arguments as SetStringUntil(). */
);
/* Set chars using a C-style zero-terminated string. */
CLDISTAT cldiSetStrCStrAt(
	cldistr    * self,
	ssize_t  start_at,
		/* The index in the string to start setting
		.  characters at. */
	const char * set_to
		/* The string to write into this string's data,
		.  starting at `start_at`. */
);
/* Set characters from the beginning of the string forward using a C-style string. */
CLDISTAT cldiSetStrBegToCStr(
	cldistr    * self,
	const char * /* Same as argument `set_to` from SetTextFrom(). */
);
/* Set characters leading up to the end of the string using a C-style string. */
CLDISTAT cldiSetStrEndToCStr(
	cldistr    * self,
	const char * /* Same as argument `set_to` from SetTextFrom(). */
);
/* Set characters starting from the beginning of the string, but clear all
.  characters beyond this change (set this string to only contain the passed
.  C-style string). */
#define cldiSetStrToCStr cldiSetStrCStr
CLDISTAT cldiSetStrCStr(
	cldistr    * self,
	const char * /* Same as argument `set_to` from SetTextFrom(). */
);

/* Set characters starting from the given index. */
CLDISTAT cldiSetStrAt(
	cldistr       * self,
	ssize_t     start_at,
		/* The index in the string to start setting characters at. */
	const cldistr * set_to
		/* The string containing the characters to use. */
);
/* Use specific offsets and indices to specify which exact portion
.  of the `set_to` string to use. */
CLDISTAT cldiSetStrToSubstringAt(
	cldistr       * self,
	ssize_t, const cldistr*,
		/* Same arguments as from SetAt():
		.  `start_at`, `set_to`. */
	ssize_t     portion_length,
		/* The beginning index of the portion to write. */
	ssize_t     offset
		/* The ending index of the portion to write. */
);
/* Set some part of this string to a snippet from another. */
CLDISTAT cldiSetStrToSnippetAt(
	cldistr*, ssize_t, const cldistr*, ssize_t
	/* Same arguments as from StrSetToSubstringAt(). */
);
/* Set from the beginning of the string until
.  the size of the passed string has been reached. */
int cldiSetStrBegTo(
	cldistr       * self,
	const cldistr * /* Same argument as `set_to` from SetAt(). */
);
/* Set from the beginning, but choose a specific portion in the given string. */
int cldiSetStrBegToSubstring(
	cldistr       *  self,
	const cldistr *, size_t, ssize_t
		/* Same argument as from SetToPortionAt():
		.  `set_to`, `portion_length`, and `offset`. */
);
/* Set the beginning of this string to a snippet from another. */
CLDISTAT cldiSetStrBegToSnippet(
	cldistr*, const cldistr*, ssize_t
	/* Same arguments as from StrSetToSubstringAt(). */
);
/* Set the characters at the end of the string instead of the beginning. */
int cldiSetStrEndTo(
	cldistr       * self,
	const cldistr * /* Same argument as `set_to` from SetAt(). */
);
/* Set characters leading up to the end of the string, but choose a specific
.  portion of the given string to choose specific values. */
int cldiSetStrEndToSubstring(
	cldistr       * self,
	const cldistr *, size_t, ssize_t
		/* Same arguments as from SetToPortionAt():
		.  `set_to`, `portion_length`, and `offset`. */
);
/* Set the ending of this string to a snippet from another. */
CLDISTAT cldiSetStrEndToSnippet(
	cldistr*, const cldistr*, ssize_t
	/* Same arguments as from StrSetToSubstringAt(). */
);
/* Set to contain the given string's data. */
int cldiSetStrTo(
	cldistr       * self,
	const cldistr * /* Same argument as `set_to` from SetAt(). */
);
/* Set the string to a specific portion of the given string's data. */
int cldiSetStrToSubstring(
	cldistr       * self,
	const cldistr * /* Same argument as `set_to` from SetAt(). */
);
/* Set this string to a snippet from another. */
CLDISTAT cldiSetStrToSnippet(
	cldistr*, const cldistr*, ssize_t
	/* Same arguments as from StrSetToSubstringAt(). */
);
/* Set to the data of the passed string, and resize to exclude all other chars. */
int cldiResizeStrTo(
	cldistr       * self,
	const cldistr * /* Same argument as `set_to` from SetAt(). */
);
/* Set to some portion of data from the passed string. */
int cldiResizeStrToSubstring(
	cldistr       * self,
	const cldistr *, size_t, ssize_t
		/* Same arguments as from SetToPortionAt():
		.  `set_to`, `portion_length`, and `offset`. */
);
/* Set to a snippet of the passed string. */
CLDISTAT cldiResizeStrToSnippet(
	cldistr*, const cldistr*, ssize_t
	/* Same arguments as from StrSetToSubstringAt(). */
);
/* --- Versions of all these methods that will set only using the origin of the
.      given string (all these methods take the same arguments as the methods
.      their versions of). */
CLDISTAT cldiSetStrToOriginAt(cldistr*, ssize_t, const cldistr *);
CLDISTAT cldiSetStrToOriginSubstringAt(cldistr*, ssize_t, const cldistr *, ssize_t, ssize_t);
CLDISTAT cldiSetStrToOriginSnippetAt(cldistr*, ssize_t, const cldistr*, ssize_t);
CLDISTAT cldiSetStrBegToOriginOf(cldistr*, const cldistr *);
CLDISTAT cldiSetStrBegToOriginSubstring(cldistr*, const cldistr*, ssize_t, ssize_t);
CLDISTAT cldiSetStrBegToOriginSnippet(cldistr*, const cldistr*, ssize_t);
CLDISTAT cldiSetStrEndToOriginOf(cldistr*, const cldistr*);
CLDISTAT cldiSetStrEndToOriginSubstring(cldistr*, const cldistr*, ssize_t, ssize_t);
CLDISTAT cldiSetStrEndToOriginSnippet(cldistr*, const cldistr*, ssize_t);
CLDISTAT cldiSetStrToOriginOf(cldistr*, const cldistr *);
CLDISTAT cldiSetStrToOriginSubstring(cldistr*, const cldistr*, ssize_t, ssize_t);
CLDISTAT cldiSetStrToOriginSnippet(cldistr*, const cldistr*, ssize_t);
CLDISTAT cldiResizeStrToOriginOf(cldistr*, const cldistr*);
CLDISTAT cldiResizeStrToOriginSubstring(cldistr*, const cldistr*, ssize_t, ssize_t);
CLDISTAT cldiResizeStrToOriginSnippet(cldistr*, const cldistr*, ssize_t);

/* Clear all initialized characters in the string data, setting to
.  uninitialized data (not deleting any memory). */
CLDISTAT cldiClearStrBuffer(cldistr * self);
/* Clear all initialized characters from a certain point onward. */
CLDISTAT cldiTrimStrBuffer(
	cldistr     * self,
	ssize_t   start_clearing_at
		/* Start clearing characters at this point onward. */
);
/* Delete all characters UP TO a certain point. */
CLDISTAT cldiStrDelFromBeginning(
	cldistr     * self,
	ssize_t   up_to
		/* Delete all characters up to this point. */
);
/* Delete a certain portion of the data instead of one entire end. */
CLDISTAT cldiStrDelPortion(
	cldistr     * self,
	ssize_t   start_at,
		/* The start index of the portion to delete. */
	size_t    amount
		/* The amount of characters to delete in the block of the string's
		.  memory that will be deleted. */
);

/* Get a substring of this string (portion between two indices). */
CLDISTAT cldiStrSubstring(
	const cldistr * self,
	ssize_t     beg,
		/* The index to start at. */
	ssize_t     end,
		/* The index to end at. */
	cldistr       * save_to
		/* The object to save the substring into. */
);
/* Get a snippet of this string (portion starting at the beginning,
.  and ending behind a given index). */
CLDISTAT cldiStrSnippet(
	const cldistr * self,
	ssize_t     snippet_end,
		/* The ending index of the snippet. */
	cldistr       * save_to
		/* The object to save the snippet into. */
);

/* ----------------------------------- */
/*      --- String Comparison ---      */

/* Compare this string to another to see if they are the same. */
#define cldiCompareStr cldiCompareStrTo
bool cldiCompareStrTo(const cldistr * self, const cldistr * equal_to);
bool cldiCompareStrToCStr(const cldistr * self, const char * string);
bool cldiCompareStrToChars(
	const cldistr   * self,
	CLDICHARTYPE      string_type,
	size_t        compare_length,
	const char *const string
);

#ifdef __cplusplus
}
#endif


/* ----------------------------------- */



#endif /* _cldi_core__types_STR_H */
