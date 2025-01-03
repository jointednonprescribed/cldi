
#ifndef _cldi_portable__handles_TEXT_H
#define _cldi_portable__handles_TEXT_H 1

/* Setup CLDI module "portable" */
#include "../setup.h"

/* Requires: cldi-portable: text (cldi/portable/text) */
#include "../text.h"

#ifdef __cplusplus
extern "C" {
#endif



/* ----------------------------------- */
/* `CLDISTR_DATA_BIT` Enum,
.  Responsible for containing all of the possible bits
.  to encounter within the cldiStr::data instance member,
.  this integer member is at least 16 bits wide, so 16 is
.  the limit for how many bit positions can be used. */
#include "text/IMPL/STRHANDLEOPT.h"


/* ----------------------------------- */
/* Const String Type (`CLDISTRHANDLE`) */

/* Type implementation */
#include "text/IMPL/STRHANDLE.h"

/* Null value for CLDISTRHANDLE:
.  Defined as a completely blank, null
.  structure value for a const string to
.  use as a NULL value.                 */
extern const CLDISTRHANDLE CLDISTRHANDLE_NULL;
#define CLDISTRHANDLE_NULL_INIT (CLDISTRHANDLE) \
{	._valid     = CLDISTRHANDLE_VALID_ID,       \
	._data      = CLDISTRHANDLE_oDEFAULT,       \
	.type       = CLDI_CHARTYPE_NONE,           \
	.address    = NULL,                         \
	.char_count = 0}


/* Default Initializer */
bool cldiInitStrHandleNull(CLDISTRHANDLE * self);

/* Make() and New() */
CLDISTRHANDLE   cldiMakeStrHandle(void);
CLDISTRHANDLE * cldiNewStrHandle(void);

/* Drop the string state. */
bool cldiDropStrHandle(CLDISTRHANDLE * self);

/* Set the string to a new state from a raw string. */
bool cldiInitStrHandleNewState(
	CLDISTRHANDLE   * self,
	CLDI_CHARTYPE     type,
		/* The string type (ASCII, UTF-8, etc.) */
	size_t        length,
		/* The amount of characters in the string, not
		.  necessarily the amount of bytes in the string. */
	const char *const string
		/* The memory address of the string, casted to
		.  const char *. */
);
/* Set the string to a full copy of another string. */
bool cldiInitStrHandleAsCopy(
	CLDISTRHANDLE       * self,
	const CLDISTRHANDLE * copy_of
		/* The string to copy. */
);
/* Set the string to share the string state with that of another. */
bool cldiInitSharedStrHandle(
	CLDISTRHANDLE       * self,
	const CLDISTRHANDLE * shared_with
		/* The string that will share with self. */
);
/* "Make methods" for creating an instance and returning it over the stack. */
CLDISTRHANDLE   cldiMakeStrHandleNewState(CLDI_CHARTYPE, size_t, const char *const);
CLDISTRHANDLE   cldiMakeStrHandleAsCopy  (const CLDISTRHANDLE *);
CLDISTRHANDLE   cldiMakeSharedStrHandle  (const CLDISTRHANDLE *);
/* "New methods" for creating an instance in the heap, and returning a reference. */
CLDISTRHANDLE * cldiNewStrHandleState    (CLDI_CHARTYPE, size_t, const char *const);
CLDISTRHANDLE * cldiNewStrHandleAsCopy   (const CLDISTRHANDLE *);
CLDISTRHANDLE * cldiNewSharedStrHandle   (const CLDISTRHANDLE *);


/* Get the string's memory address. */
const void *  cldiStrHandleGetAddress(const CLDISTRHANDLE * self);
/* Get a const char * pointing to the bytes in the string.  */
const char *  cldiStrHandleGetBytes(const CLDISTRHANDLE * self);
/* Get the length of the string (amount of characters). */
size_t    cldiStrHandleLength(const CLDISTRHANDLE * self);
/* Get the total size of the state in memory (some string types
.  (encoding types) will contain multi-byte characters). */
size_t    cldiStrHandleGetSize(const CLDISTRHANDLE * self);
/* Get the total size known to be used by this string object. */
size_t    cldiStrHandleGetTotalSize(const CLDISTRHANDLE * self);
/* Get the character type of the string. */
CLDI_CHARTYPE cldiStrHandleGetTextType(const CLDISTRHANDLE * self);

/* Check if the string has a valid state. */
bool cldiStrHandleHasValidState(const CLDISTRHANDLE * self);
/* Check if the string is empty (doesn't contain any data, or is
.  null, invalid strings do not pass). */
bool cldiStrHandleIsEmpty(const CLDISTRHANDLE * self);
/* Check if the string is null rather than invalid. */
bool cldiStrHandleIsNull(const CLDISTRHANDLE * self);
/* Check if the string is actually invalid in its
.  current state (null is invalid). */
bool cldiStrHandleIsInvalid(const CLDISTRHANDLE * self);
/* Check if the string is actually valid, it may not
.  have a string state, but it may be valid (null does
.  not pass). */
bool cldiStrHandleIsValid(const CLDISTRHANDLE * self);


/* ----------------------------------- */



#ifdef __cplusplus
}
#endif

#endif /* _cldi_portable__handles_TEXT_H */
