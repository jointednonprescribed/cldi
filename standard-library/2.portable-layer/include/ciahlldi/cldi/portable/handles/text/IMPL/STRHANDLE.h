
#ifndef _cldi_portable__handles_text_IMPL_STRHANDLE_H
#define _cldi_portable__handles_text_IMPL_STRHANDLE_H 1

#include "../../../setup.h"

#include "../../../types/basictypes.h"
#include "../../../text/chartypes/IMPL/CHARTYPE.h"



#if defined(__cplusplus) && __CLDI_no_cpp > false
extern "C" {
#endif
typedef struct _CLDISTRHANDLE
{
	/* Integer that validates (through equality with CLDISTRHANDLE_VALID_ID) that
	.  this string handle has been initialized before. */
	#define CLDISTRHANDLE_VALID_ID 0xD399E718U
	const u32_t         _valid;
	bool                _init;

	/* The character type of the string. */
	const i8_t          type;

	/* "Cache" of string options/information. This member is at least
	.  16 bits wide, so 16 is the limit for how many bit positions can
	.  be defined for understanding the data inside this member. */
	const cldihalf      _data;

	/* Acts as the current state of the string, the owned or borrowed
	.  memory storing the string's data. */
	const char *const   address;

	/* The amount of initialized characters in the string. */
	const size_t    char_count;

#if defined(__cplusplus) && __CLDI_no_cpp < true
public:
	const static _CLDISTRHANDLE null;

	_CLDISTRHANDLE(void);

	/* Initialize as null state. */
	static bool Init(_CLDISTRHANDLE& self);
	/* Initialize with new state from raw string. */
	static bool Init(_CLDISTRHANDLE& self, CLDICHARTYPE type, size_t length, const char *const string);
	/* Initialize with new state from that of another, either by copy or by borrowing (default). */
	static bool Init(_CLDISTRHANDLE& self, const _CLDISTRHANDLE& master_state, bool copy_instead_of_borrow=false);

	/* Create a new instance, and pass it over the stack. */
	static _CLDISTRHANDLE  Make(void);                                        /* new state (null) */
	static _CLDISTRHANDLE  Make(CLDICHARTYPE, size_t, const char *const); /* new state (raw) */
	static _CLDISTRHANDLE  Make(const _CLDISTRHANDLE&, bool _=false);         /* new state (other) */
	/* Allocate a new instance in the heap. */
	static _CLDISTRHANDLE* New(void);                                         /* new state (null) */
	static _CLDISTRHANDLE* New(CLDICHARTYPE, size_t, const char *const);  /* new state (raw) */
	static _CLDISTRHANDLE* New(const _CLDISTRHANDLE&, bool _=false);          /* new state (other) */

	~_CLDISTRHANDLE();

	static bool Drop(_CLDISTRHANDLE& drop);

#endif
} CLDI_STRING_HANDLE, CLDISTRHANDLE;
#ifdef __cplusplus
#	if __CLDI_no_cpp > false
}
#	else
namespace cldi
{
	namespace portable
	{
		using STRHANDLE = CLDISTRHANDLE;
		using STRING_HANDLE = CLDISTRHANDLE;
	}
	using portable::STRHANDLE;
	using portable::STRING_HANDLE;
}
#	endif
#endif



#endif /* _cldi_portable__handles_IMPL_STRHANDLE_H */
