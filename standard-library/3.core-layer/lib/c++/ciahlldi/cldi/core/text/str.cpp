
/* C++ Implementation For: cldi-core: text/str */
#include <ciahlldi/cldi/core/text/str.h>

/* Common Source Code: */
#include <ciahlldi/cldi/core/common-source/text/str.c>

/* Requires: cldi-core: sysfuncs/memory */
#include <ciahlldi/cldi/core/sysfuncs/memory.h>
/*           cldi-portable: text/str */
#include <ciahlldi/cldi/portable/text/str.h>



const _cldistr& _cldistr::null = CLDISTR_NULL;


_cldistr _cldistr::operator=(const _cldistr& rhs)
{
	_cldistr s(&rhs.origin);

	s._data = rhs._data;
	s._init = rhs._init;
	s.modifiable_state_address =
		(rhs._init)?
		cldiBorrowMemory(rhs.modifiable_state_address):
		rhs.modifiable_state_address;
	s.current_character_type   = rhs.current_character_type;
	s.initialized_length       = rhs.initialized_length;
	s.last_err                 = rhs.last_err;

	return s;
}


_cldistr::~_cldistr()
{
	this->Drop();
}

_cldistr::_cldistr(void):
	origin(CLDISTRHANDLE_NULL),
	_valid(CLDISTR_VALID_ID), _init(true), _data(CLDISTR_oNULLV_DEFAULT),
	current_character_type(CLDI_CHARTYPE_NONE),
	modifiable_state_address(NULL),
	initialized_length(0),
	last_err(CLDI_SUCCESS)
{}
_cldistr::_cldistr(const CLDISTRHANDLE *__o):
	_valid(CLDISTR_VALID_ID), _init(true), _data(CLDISTR_oDEFAULT),
	_chmsk(NULL), last_err(CLDI_SUCCESS),
	origin(cldiMakeSharedStrHandle(__o)),
	modifiable_state_address(NULL),
	current_character_type(CLDI_CHARTYPE_NONE),
	initialized_length(0)
{}
_cldistr::_cldistr(CLDISTRHANDLE __o):
	_valid(CLDISTR_VALID_ID), _init(true), _data(CLDISTR_oDEFAULT),
	_chmsk(NULL), last_err(CLDI_SUCCESS),
	origin(
		(cldiBorrowMemory(__o.address) != CLDI_SUCCESS)?
		CLDISTRHANDLE_NULL:
		__o
	),
	modifiable_state_address(NULL),
	current_character_type(CLDI_CHARTYPE_NONE),
	initialized_length(0)
{}
_cldistr::_cldistr(
	const cldistr*  __from,
	_cldistr::rel_t __rel=CLDISTR_REL_COPY,
	bool            __cp=true,
	size_t      __ext=0l
):
	last_err(CLDI_SUCCESS), modifiable_state_address(NULL),
	origin(
		(__rel == CLDISTR_REL_COPY)?
		_cldiInitStrRelCopy(this, &(this->last_err), __from, __ext):
		(__rel == CLDISTR_REL_CHILD || __rel == CLDISTR_REL_PCHILD)?
		_cldiInitStrChild(this, &(this->last_err), __from, __cp, __ext):
		(__rel == CLDISTR_REL_PARENT || __rel == CLDISTR_REL_PPARENT)?
		_cldiInitStrParent(this, &(this->last_err), __from):
		(__rel == CLDISTR_REL_SIBLING || __rel == CLDISTR_REL_PSIBLING)?
		_cldiInitStrSibling(this, &(this->last_err), __from, __cp, __ext):
		_cldiInitStrNull(this)
	),
	_valid(CLDISTR_VALID_ID), _init(true)
{
	this->_data =
		(this->modifiable_state_address == NULL)?
		CLDISTR_oNULLV_DEFAULT:
		CLDISTR_oDEFAULT;
}
_cldistr::_cldistr(
	CLDICHARTYPE      __typ,
	size_t        __len,
	const void *const __str,
	bool              __cp=true,
	size_t        __ext=0l
):
	last_err(CLDI_SUCCESS), modifiable_state_address(NULL),
	origin(_cldiInitStrStateRaw(this, &(this->last_err), __typ, __len, __str, __cp, __ext)),
	_valid(CLDISTR_VALID_ID), _init(true)
{
	this->_data =
		(this->modifiable_state_address == NULL)?
		CLDISTR_oNULLV_DEFAULT:
		CLDISTR_oDEFAULT;
}
_cldistr::_cldistr(const char* __str, bool __cp=true, size_t __ext=0l):
	_cldistr(CLDI_CHARTYPE_CSTRING, cldiCStrlen(__str), __str, __cp, __ext)
{}
_cldistr::_cldistr(const cldichar16_t* __str, bool __cp=true, size_t __ext=0l):
	_cldistr(CLDI_CHARTYPE_UTF16, cldiUTF16Strlen(__str), __str, __cp, __ext)
{}
_cldistr::_cldistr(const cldichar32_t* __str, bool __cp=true, size_t __ext=0l):
	_cldistr(CLDI_CHARTYPE_UTF32, cldiUTF32Strlen(__str), __str, __cp, __ext)
{}

CLDISTAT _cldistr::Init(cldistr& self)
{
	self = cldistr();
}


