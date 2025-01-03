
#ifndef _cldi_core__text_IMPL_STR_H
#define _cldi_core__text_IMPL_STR_H 1

#include "../../../setup.h"

#include "STR_RANGE_MARKER.h"
#include "STR_REL.h"
#include "STR_OPT.h"

#include <ciahlldi/cldi/portable/types/basictypes.h>
#include <ciahlldi/cldi/portable/handles/text.h>



#if defined(__cplusplus) && __CLDI_no_cpp < true
extern "C" {
#endif
struct _cldistr
{
	/* The origin state of the string, contains a character type, size, and
	.  length, and can be destructed in of itself. */
	CLDISTRHANDLE      origin;

	/* "Cache" of string options/information. This member is at least
	.  16 bits wide, so 16 is the limit for how many bit positions can
	.  be defined for understanding the data inside this member. */
	cldihalf           _data;

	/* Integer that validates (through equality with CLDISTR_VALID_ID) that
	.  the string has been initialized before. */
	#define             CLDISTR_VALID_ID  0x3424E718UL
	const u32_t        _valid;
	bool               _init;

	/* The character type of the string. */
	signed char        current_character_type;

	/* A cache of integers storing where characters in the string are that are
	.  larger than the default size for the encoding format, so that indices can
	.  be located in the string memory quickly and accurately (some encoding
	.  settings may not use this, setting it to null, and a mask may not be used
	.  at all if the string is short enough). */
	const signed char *_chmsk;

	/* Acts as the current state of the string, the owned
	.  memory storing the string's data. */
	char              *modifiable_state_address;

	/* The exact amount of initialized characters
	.  in the string. */
	size_t         initialized_length;

#if defined(__cplusplus) && __CLDI_no_cpp < true
	CLDISTAT            last_err;
public:
	static constexpr u32_t valid_id = CLDISTR_VALID_ID;
	static const _cldistr& null;

	using rangemkr_t = cldiStrRangeMarker;

	using rel_t = CLDISTRREL;
	using relationship_t = CLDISTRREL;
	constexpr static rel_t REL_ERR = CLDISTR_REL_ERR;
	constexpr static rel_t REL_UNKNOWN = CLDISTR_REL_UNKNOWN;
	constexpr static rel_t REL_PPARENT = CLDISTR_REL_PPARENT;
	constexpr static rel_t REL_PCHILD  = CLDISTR_REL_PCHILD;
	constexpr static rel_t REL_PSIBLING = CLDISTR_REL_PSIBLING;
	constexpr static rel_t REL_PARTNER = CLDISTR_REL_PARTNER;
	constexpr static rel_t NO_RELATIONSHIP = CLDISTR_NO_RELATIONSHIP;
	constexpr static rel_t REL_SIBLING = CLDISTR_REL_SIBLING;
	constexpr static rel_t REL_CHILD = CLDISTR_REL_CHILD;
	constexpr static rel_t REL_PARENT = CLDISTR_REL_PARENT;
	constexpr static rel_t REL_COPY   = CLDISTR_REL_COPY;

	_cldistr operator =(const _cldistr& rhs);

	_cldistr(void);
	_cldistr(const CLDISTRHANDLE *origin);
	_cldistr(CLDISTRHANDLE  origin);
	_cldistr(
		const _cldistr* from,
		rel_t           relationship=CLDISTR_REL_CHILD,
		bool            create_modifiable_state=true,
		size_t      extension_size=0l
	);
	_cldistr(
		CLDICHARTYPE      string_type,
		size_t        string_length,
		const void *const string,
		bool              create_modifiable_state=true,
		size_t        extension_size=0l
	);
	_cldistr(
		const char * c_string,
		bool         create_modifiable_state=true,
		size_t   extension_size=0l
	);
	_cldistr(
		const cldichar16_t * string,
		bool                 create_modifiable_state=true,
		size_t           extension_size=0l
	);
	_cldistr(
		const cldichar32_t * string,
		bool                 create_modifiable_state=true,
		size_t           extension_size=0l
	);

	static CLDISTAT Init(_cldistr& self);
	static CLDISTAT Init(_cldistr& self, const CLDISTRHANDLE *origin);
	static CLDISTAT Init(_cldistr& self, CLDISTRHANDLE origin);
	static CLDISTAT Init(
		_cldistr&       self,
		const _cldistr* other,
		rel_t           relationship=CLDISTR_REL_CHILD,
		bool            create_modifiable_state=true,
		size_t      extension_size=0l
	);
	static CLDISTAT Init(
		_cldistr&         self,
		CLDICHARTYPE      string_type,
		size_t        string_length,
		const void *const string,
		bool              create_modifiable_state=true,
		size_t        extension_size=0l
	);
	static CLDISTAT Init(
		_cldistr&         self,
		const char      * c_string,
		bool              create_modifiable_state=true,
		size_t        extension_size=0l
	);

	static _cldistr* New(void);
	static _cldistr* New(const CLDISTRHANDLE *origin);
	static _cldistr* New(CLDISTRHANDLE origin);
	static _cldistr* New(
		const _cldistr* from,
		rel_t           relationship=REL_SIBLING,
		bool            create_modifiable_state=false,
		size_t      extension_size=0l
	);
	static _cldistr* New(
		CLDICHARTYPE      string_type,
		size_t        string_length,
		const void *const string,
		bool              create_modifiable_state=true,
		size_t        extension_size=0l
	);
	static _cldistr* New(
		const char* c_string,
		bool        create_modifiable_state=true,
		size_t  extension_size=0l
	);
	static CLDISTAT New(_cldistr** out, const CLDISTRHANDLE *origin);
	static CLDISTAT New(_cldistr** out, CLDISTRHANDLE origin);
	static CLDISTAT New(
		_cldistr      **out,
		const _cldistr *from,
		rel_t           relationship=REL_SIBLING,
		bool            create_modifiable_state=false,
		size_t      extension_size=0l
	);
	static CLDISTAT New(
		_cldistr        **out,
		CLDICHARTYPE      string_type,
		size_t        string_length,
		const void *const string,
		bool              create_modifiable_state=true,
		size_t        extension_size=0l
	);
	static CLDISTAT New(
		_cldistr  **out,
		const char *c_string,
		bool        create_modifiable_state=true,
		size_t  extension_size=0l
	);

	~_cldistr();
	bool Drop(void);

#endif
};
typedef struct _cldistr cldistr, cldistr_t, CLDISTRING;
#ifdef __cplusplus
#	if __CLDI_no_cpp < true
	}
#	else
namespace cldi
{
	namespace core
	{
		using string = cldistr;
		using STRING = cldistr;
	}
	using core::string, core::STRING;
}
#	endif
#endif



#endif /* _cldi_core__text_IMPL_STR_H */
