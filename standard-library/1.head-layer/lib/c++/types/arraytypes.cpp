
/* Implementing: cldi-head: types/arraytypes */
#include <ciahlldi/cldi/head/types/arraytypes.h>

/* Requires: cldi-head: calls/memory */
#include <ciahlldi/cldi/head/calls/memory.h>



/* struct CLDIVLAHANDLE */
const cldiVLAHandle CLDIVLAHANDLE_NULL = cldiVLAHandle();

CLDIVLAHANDLE::CLDIVLAHANDLE(size_t __ilen, size_t __len, const void* __addr):
	_ilen(__ilen),
	_len(__len),
	_data((__addr == NULL || __len == 0 || __ilen == 0)? NULL : cldiNewCopyBytes(__len * __ilen, __addr))
{}
CLDIVLAHANDLE::CLDIVLAHANDLE(const CLDIVLAHANDLE &rhv):
	_len(rhv._len), _ilen(rhv._ilen), _data(cldiShareMemory(rhv._data))
{}
CLDIVLAHANDLE::CLDIVLAHANDLE():
	_ilen(0), _len(0), _data(NULL)
{}

CLDIVLAHANDLE::~CLDIVLAHANDLE()
{
	DropState();
}

CLDISTAT CLDIVLAHANDLE::DropState()
{
	if (_data != NULL) {
		if (cldiDropMemory(_data) == CLDI_SUCCESS) {
			_data = NULL;
			_len  = 0;
			_ilen = 0;
			return CLDI_SUCCESS;
		} else {
			return CLDI_LAST_ERR;
		}
	} else {
		CLDI_LAST_ERR = CLDI_NULL_ATTR;
		return CLDI_NULL_ATTR;
	}
}

auto CLDIVLAHANDLE::operator =(const CLDIVLAHANDLE &rhv)
{
	this->~CLDIVLAHANDLE();
	if (CLDI_LAST_ERR == CLDI_SUCCESS) {
		_data = (rhv._data == NULL)? NULL :
			cldiShareMemory(rhv._data);
		_len  = rhv._len;
		_ilen = rhv._ilen;
	}
}

CLDIVLAHANDLE CLDIVLAHANDLE::GetCopy() const
{
	return cldiVLAHandle(_ilen, _len, _data);
}
CLDISTAT CLDIVLAHANDLE::AssumeCopy(const CLDIVLAHANDLE &other)
{
	if (other._data == NULL || other._len > 0 || other._ilen > 0) {
		CLDI_LAST_ERR = CLDI_INVALID_ATTRIBUTE;
		return CLDI_INVALID_ATTRIBUTE;
	} if (_data != NULL) {
		this->~CLDIVLAHANDLE();
	}

	void *const data = cldiNewCopyBytes(other._ilen * other._len, other._data);
	if (CLDI_LAST_ERR == CLDI_SUCCESS) {
		_data = data;
		_ilen = other._ilen;
		_len  = other._len;
	}

	return CLDI_LAST_ERR;
}

const void* CLDIVLAHANDLE::Data() const
{
	return _data;
}
size_t CLDIVLAHANDLE::GetItemSize() const
{
	return _ilen;
}
size_t CLDIVLAHANDLE::Length() const
{
	return _len;
}
size_t CLDIVLAHANDLE::ByteLength() const
{
	return (_ilen > 0)? (_ilen * _len) : 0;
}


/* struct CLDIVLA */
const CLDIVLA CLDIVLA_NULL = cldiVLA();

CLDIVLA::CLDIVLA(size_t _ilen, size_t origin_length, const void* origin_data, size_t extra_capacity=0, bool copy_origin=false):
	// set the origin to the provided array
	origin(_ilen, origin_length, origin_data),
	// IMPORTANT: set _data to NULL, so that a random stack value isn't assumed
	// as the address of the current state, this must always be done.
	_data(NULL),
	_ilen(0), _len(0), _cap(0)
{
	if (copy_origin)
		CreateStateFromOrigin(extra_capacity);
}
CLDIVLA::CLDIVLA(cldiVLAHandle origin_handle, size_t extra_capacity=0, bool copy_origin=false):
	origin(origin_handle), _data(NULL), _len(0), _ilen(0), _cap(0)
{
	if (copy_origin)
		CreateStateFromOrigin(extra_capacity);
}
CLDIVLA::CLDIVLA(size_t _ilen, size_t item_capacity):
	origin(), _data(NULL), _len(0), _ilen(0), _cap(0)
{
	CreateState(_ilen, item_capacity);
}
CLDIVLA::CLDIVLA(const CLDIVLA &rhv):
	origin(rhv.origin), _data(cldiNewCopyBytes(rhv._ilen * rhv._len, rhv._data)),
	_ilen((rhv._ilen == 0)? 1 : rhv._ilen),
	_len(rhv._len), _cap(rhv._cap)
{}
CLDIVLA::CLDIVLA():
	origin(), _data(NULL), _ilen(0), _len(0), _cap(0)
{}

CLDIVLA::~CLDIVLA()
{
	if (_data != NULL) {
		DropState();
	}
}

CLDIVLA       CLDIVLA::GetCopy(bool new_origin=false) const
{
	/* Create new VLA object containing a copied or shared origin depending
	.  on `new_origin`. */
	CLDIVLA ret(new_origin? this->origin.GetCopy() : cldiVLAHandle(this->origin));

	/* Item size of `ret` will always be the same as the item size of self. */
	ret._ilen = this->_ilen;
	/* If a current state exists (_data != NULL), there is initialized data
	.  in the state (_len > 0), and state is not a null type (_ilen > 0),
	.  create a copy of the current state ( not including uninitialized
	.  items at the end of the current state's memory space) and assign that
	.  copy to `ret`. */
	if (this->_data != NULL && this->_len > 0 && ret._ilen > 0) {
		ret._data = cldiNewCopyBytes(ret._ilen * this->_len, this->_data);
		ret._len  = this->_len;
		ret._cap  = this->_len; /* must use `_len` or it will account for nonexistent characters that weren't copied. */
	}

	return ret;
}
CLDIVLAHANDLE CLDIVLA::GetOrigin() const
{
	return cldiVLAHandle(this->origin);
}
CLDIVLAHANDLE CLDIVLA::GetCopyOfOrigin() const
{
	return this->origin.GetCopy();
}
CLDIVLAHANDLE CLDIVLA::GetCopyAsHandle() const
{
	if (this->_data != NULL && this->_len > 0 && this->_ilen > 0) {
		return CLDIVLAHANDLE(this->_ilen, this->_len, cldiNewCopyBytes(this->_ilen * this->_len, this->_data));
	}
	else {
		return CLDIVLAHANDLE(0, 0, NULL);
	}
}

CLDISTAT CLDIVLA::AssumeFullCopy(const CLDIVLA &copy_of, bool new_origin=false)
{
	CLDI_LAST_ERR == CLDI_SUCCESS;

	if (this->_data != NULL) {
		this->DropState();
	}
	if (this->origin._data != NULL) {
		this->DropOrigin();
	}

	this->origin = new_origin? copy_of.origin.GetCopy() : cldiVLAHandle(copy_of.origin);
	this->_len   = copy_of._len;
	this->_cap   = copy_of._len;
	this->_ilen  = copy_of._ilen;
	this->_data  = (copy_of._data == NULL || copy_of._len == 0 || copy_of._ilen == 0)?
		NULL : cldiNewCopyBytes(copy_of._ilen * copy_of._len, copy_of._data);

	return CLDI_LAST_ERR;
}
CLDISTAT CLDIVLA::AssumeOrigin(const CLDIVLA &origin_of, bool move_origin=false)
{
	CLDI_LAST_ERR = CLDI_SUCCESS;

	if (this->_data != NULL) {
		if (move_origin) {
			this->SetNewOrigin();
		}
		this->DropState();
	}

	const CLDIVLAHANDLE *handle = &origin_of.origin;

	if (handle->_data == NULL || handle->_len == 0 || handle->_ilen == 0) {
		this->_ilen = handle->_ilen;
		this->_data = NULL;
		this->_len  = 0;
		this->_cap  = 0;
	} else {
		this->_ilen = handle->_ilen;
		this->_len  = handle->_len;
		this->_cap  = handle->_len;
		this->_data = cldiNewCopyBytes(handle->_ilen * handle->_len, handle->_data);
	}

	return CLDI_LAST_ERR;
}
CLDISTAT CLDIVLA::Assume(const CLDIVLA &state_of, bool move_origin=false)
{
	CLDI_LAST_ERR = CLDI_SUCCESS;

	if (this->_data != NULL) {
		if (move_origin) {
			this->SetNewOrigin();
		}
		this->DropState();
	}

	if (state_of._data == NULL || state_of._len == 0 || state_of._ilen == 0) {
		this->_ilen = state_of._ilen;
		this->_data = NULL;
		this->_len  = 0;
		this->_cap  = 0;
	} else {
		this->_ilen = state_of._ilen;
		this->_len  = state_of._len;
		this->_cap  = state_of._len;
		this->_data = cldiNewCopyBytes(state_of._ilen * state_of._len, state_of._data);
	}

	return CLDI_LAST_ERR;
}

const void* CLDIVLA::Data() const
{
	return _data;
}
size_t CLDIVLA::GetItemSize() const
{
	return _ilen;
}
size_t CLDIVLA::Length() const
{
	return _len;
}
size_t CLDIVLA::ByteLength() const
{
	return _ilen * _len;
}
size_t CLDIVLA::Capacity() const
{
	return _cap;
}
size_t CLDIVLA::ByteCapacity() const
{
	return _ilen * _cap;
}

cldiVLAHandle CLDIVLA::GetActiveState() const
{
	CLDI_LAST_ERR = CLDI_SUCCESS;

	const void *p;
	size_t s, l;

	if (this->_data == NULL || this->_ilen == 0 || this->_len == 0) {
		// If no valid origin state exists, report NULL_ARG error and
		// return false.
		if (this->origin._data == NULL || this->origin._ilen == 0 || this->origin._len == 0) {
			CLDI_LAST_ERR = CLDI_NULL_ATTR;
			return CLDIVLAHANDLE_NULL;
		} else {
			// Otherwise (valid origin does exist), use origin state.
			return cldiVLAHandle(origin);
		}
	} else {
		// Otherwise (valid current state does exist) use current state.
		return GetCopyAsHandle();
	}

	return CLDIVLAHANDLE_NULL;
}
CLDISTAT CLDIVLA::ImportActiveState(
	size_t *const item_size_out, size_t *const len_out, const void **const addr_out) const
{
	CLDI_LAST_ERR = CLDI_SUCCESS;

	// If not valid current state exists, check origin state.
	if (this->_data == NULL || this->_ilen == 0 || this->_len == 0) {
		// If no valid origin state exists, report NULL_ARG error and
		// return false.
		if (this->origin._data == NULL || this->origin._ilen == 0 || this->origin._len == 0) {
			CLDI_LAST_ERR = CLDI_NULL_ARG;
			return CLDI_NULL_ARG;
		} else {
			// Otherwise (valid origin does exist), use origin state.
			*item_size_out = origin._ilen;
			*len_out       = origin._len;
			*addr_out      = origin._data;
		}
	} else {
		// Otherwise (valid current state does exist) use current state.
		*item_size_out = _ilen;
		*len_out       = _len;
		*addr_out      = _data;
	}

	return CLDI_LAST_ERR;
}

CLDISTAT CLDIVLA::CreateState(size_t _ilen, size_t item_capacity)
{
	if (_ilen == 0 || item_capacity == 0) {
		CLDI_LAST_ERR = CLDI_NULL_ARG;
		return CLDI_NULL_ARG;
	}
	void *const new_state = cldiReqMemory(_ilen * item_capacity, CLDI_MEM_DEFAULT);

	if (CLDI_LAST_ERR == CLDI_SUCCESS) {
		if (_data != NULL) {
			this->DropState();
		}
		_data = new_state;
		_len  = 0;
		_ilen = _ilen;
		_cap  = item_capacity;
	}

	return CLDI_LAST_ERR;
}
CLDISTAT CLDIVLA::CreateEmptyState(size_t item_capacity)
{
	CLDI_LAST_ERR = CLDI_SUCCESS;

	// if current state has no item size, then use that of origin,
	// if origin has no item size, set to zero to mark the problem.
	const size_t _ilen = (_ilen > 0)? _ilen : (origin._ilen > 0)? origin._ilen : 0;
	// if set to zero, then no reference for item size exists, so return
	// CLDI_NULL_ATTR error.
	if (_ilen == 0) {
		CLDI_LAST_ERR = CLDI_NULL_ATTR;
		return CLDI_NULL_ATTR;
	}

	// drop current state if it exists
	if (_data != NULL) {
		this->DropState();
	}

	// create the new state
	this->CreateState(_ilen, item_capacity);

	return CLDI_LAST_ERR;
}
CLDISTAT CLDIVLA::CreateStateFromOrigin(size_t extra_capacity=0)
{
	CLDI_LAST_ERR = CreateEmptyState(origin._len + extra_capacity);

	if (CLDI_LAST_ERR == CLDI_SUCCESS) {
		cldiCopyBytes(origin._ilen * origin._len, origin._data, _data);
		if (CLDI_LAST_ERR == CLDI_SUCCESS) {
			_len = origin._len;
		}
	}

	return CLDI_LAST_ERR;
}
CLDISTAT CLDIVLA::DropState()
{
	/* Attempt to drop the memory address. */
	if (cldiDropMemory(_data) != CLDI_SUCCESS)
		goto RET_LAST_ERR; // jump to return last error

	_data = NULL;
	_len  = 0;
	_cap  = 0;
	_ilen = 0;

RET_LAST_ERR:
	return CLDI_LAST_ERR;
}
CLDISTAT CLDIVLA::DropOrigin()
{
	CLDI_LAST_ERR = CLDI_SUCCESS;

	origin = CLDIVLAHANDLE_NULL;

	return CLDI_LAST_ERR;
}
CLDISTAT CLDIVLA::SetNewOrigin()
{
	CLDI_LAST_ERR = CLDI_SUCCESS;

	origin = GetCopyAsHandle();

	return CLDI_LAST_ERR;
}

bool CLDIVLA::Compare(const CLDIVLA &other, const CLDIVLASECT &portion) const
{
	CLDI_LAST_ERR = CLDI_SUCCESS;

	/* `l1`: length of `other`,
	.  `l2`: length of `this`,
	.  `s1`: item size of `other`,
	.  `s2`: item size of `this`,
	.  `p1`: address of `other`,
	.  `p2`: address of `this`. */
	size_t      l1,  l2, s1, s2;
	const char *p1, *p2;
	// If `other` contains no valid current state, check origin.
	if (other._data == NULL || other._ilen == 0 || other._len == 0) {
		// If `other` contains no valid origin state, return false and report
		// NULL_ARG error.
		if (other.origin._data == NULL || other.origin._ilen == 0 || other.origin._len == 0) {
			CLDI_LAST_ERR = CLDI_NULL_ARG;
			return false;
		} else {
			// Otherwise (origin exists, but current state does not),
			// save origin state values into `p1`, `l1`, and `s1`.
			p1 = static_cast<const char*>(other.origin._data);
			l1 = other.origin._len;
			s1 = other.origin._ilen;
		}
	} else {
		// Otherwise (current state exists), save current state values
		// into `p1`, `l1`, and `s1`.
		p1 = static_cast<const char*>(other._data);
		l1 = other._len;
		s1 = other._ilen;
	}
	// If no valid current state exists, check origin state. */
	if (this->_data == NULL || this->_ilen == 0 || this->_len == 0) {
		// If no valid origin state exists, report NULL_ARG error and
		// return false.
		if (this->origin._data == NULL || this->origin._ilen == 0 || this->origin._len == 0) {
			CLDI_LAST_ERR = CLDI_NULL_ARG;
			return false;
		} else {
			// Otherwise (origin state does exist, but current state does
			// not), save origin state values into `p2`, `l2`, and `s2`.
			p2 = static_cast<const char*>(this->origin._data);
			l2 = this->origin._len;
			s2 = this->origin._ilen;
		}
	} else {
		// Otherwise (current state does exist) save current state values
		// into `p2`, `l2`, `s2`.
		p2 = static_cast<const char*>(this->_data);
		l2 = this->_len;
		s2 = this->_ilen;
	}

	// Make sure both arrays have the same item size.
	if (s1 != s2) {
		CLDI_LAST_ERR = CLDI_INVALID_ATTRIBUTE;
		return false;
	}

	// `portion_diff` is the difference between `portion.beg` and
	// `portion.end`. `portion_end` is `portion.end` but fixed for
	// the size (in bytes) of each item.
	const size_t portion_diff = portion.end - portion.beg, portion_end = portion.end * _ilen;

	// Make sure the selected portion is within bounds of this array.
	if (portion.beg > l2 || portion.end > l2) {
		CLDI_LAST_ERR = CLDI_OVERLOADED_ARG;
		return false;
	}

	// `l1b` is `l1`, but adjusted for a byte-to-byte scan of that
	// many array items. `i1` is a secondary index that is used for
	// tracking the current position within `other` (`p1`)
	// independent of the position in the current state (`p2`, `i2`).
	// `i1` is called so because it is declared first, and other
	// variables related to properties of `other` take the same
	// naming format.
	// l1 = length of `other` (number of items)
	// l1 - 1 = final index of `other` (position of last item)
	// (l1-1) * s2 = total number of bytes from the beginning to
	// the end of the last item in `other`
	// ((l1-1) * s2) + 1 = the number the index will be when it
	// must stop the loop.
	size_t l1b = ((l1-1) * s2)+1, i1 = 0;
	// loop through each array portion, comparing each array
	// byte-by-byte.
	for (size_t i2 = portion.beg * s2; i2 < portion_end; i2++) {
		// if at the end of `other`, but loop is still running,
		// return true, if comparison matches so far, and the end
		// of `other` has been reached, a match is found.
		if (i1 >= l1b) {
			return true;
		}
		// if a difference is found within the bounds of `other`
		// and `portion` return false, no true match.
		if (p2[i2] != p1[i1]) {
			return false;
		}
		// i2 and i1 both must be incremented, so increment
		// i1 manually.
        i1++;
	}

	return true;
}
bool CLDIVLA::Compare(const CLDIVLAHANDLE &other, const CLDIVLASECT &portion) const
{
	CLDI_LAST_ERR = CLDI_SUCCESS;

	// make sure `other` contains a valid state to compare to.
	if (other._data == NULL || other._ilen == 0 || other._len == 0) {
		CLDI_LAST_ERR = CLDI_NULL_ATTR;
		return false;
	}

	/* `l1`: length of `other`,
	.  `l2`: length of `this`,
	.  `s1`: item size of `other`,
	.  `s2`: item size of `this`,
	.  `p1`: address of `other`,
	.  `p2`: address of `this`. */
	size_t l1 = other._len, l2, s1 = other._ilen, s2;
	const char *p1 = static_cast<const char*>(other._data), *p2;
	// If no valid current state exists, check origin state.
	if (this->_data == NULL || this->_ilen == 0 || this->_len == 0) {
		// If no valid origin state exists, report NULL_ARG error and
		// return false.
		if (this->origin._data == NULL || this->origin._ilen == 0 || this->origin._len == 0) {
			CLDI_LAST_ERR = CLDI_NULL_ATTR;
			return false;
		} else {
			// Otherwise (valid origin does exist), use origin state.
			p2 = static_cast<const char*>(this->origin._data);
			l2 = this->origin._len;
			s2 = this->origin._ilen;
		}
	} else {
		// Otherwise (valid current state does exist) use current state.
		p2 = static_cast<const char*>(this->_data);
		l2 = this->_len;
		s2 = this->_ilen;
	}

	if (l1 != l2) {
		return false;
	} else {
		for (size_t i = 0; i < l1; i++) {
			if (p1[i] != p2[i]) {
				return false;
			}
		}
		return true;
	}
}
bool CLDIVLA::IsIdentical(const CLDIVLA &other) const
{
	CLDI_LAST_ERR = CLDI_SUCCESS;

	size_t      l1,  l2;
	const char *p1, *p2;
	/* Get active state address in `other`. */
	if (other._data == NULL || other._ilen == 0 || other._len == 0) {
		if (other.origin._data == NULL || other.origin._ilen == 0 || other.origin._len == 0) {
			return false;
		} else {
			p1 = static_cast<const char*>(other.origin._data);
			l1 = other.origin._len;
		}
	} else {
		p1 = static_cast<const char*>(other._data);
		l1 = other._len;
	}
	/* Get active state address in `this`. */
	if (this->_data == NULL || this->_ilen == 0 || this->_len == 0) {
		if (this->origin._data == NULL || this->origin._ilen == 0 || this->origin._len == 0) {
			CLDI_LAST_ERR = CLDI_SUCCESS;
			return false;
		} else {
			p2 = static_cast<const char*>(this->origin._data);
			l2 = this->origin._len;
		}
	} else {
		p2 = static_cast<const char*>(this->_data);
		l2 = this->_len;
	}

	if (l1 != l2) {
		return false;
	} else {
		for (size_t i = 0; i < l1; i++) {
			if (p1[i] != p2[i]) {
				return false;
			}
		}
		return true;
	}
}
bool CLDIVLA::IsIdentical(const CLDIVLAHANDLE &other) const
{
	CLDI_LAST_ERR = CLDI_SUCCESS;

	if (other._data == NULL || other._ilen == 0 || other._len == 0) {
		CLDI_LAST_ERR = CLDI_NULL_ATTR;
		return false;
	}

	size_t l1 = other._len, l2;
	const char *p1 = static_cast<const char*>(other._data), *p2;
	/* Get active state address in `this`. */
	if (this->_data == NULL || this->_ilen == 0 || this->_len == 0) {
		if (this->origin._data == NULL || this->origin._ilen == 0 || this->origin._len == 0) {
			CLDI_LAST_ERR = CLDI_NULL_ATTR;
			return false;
		} else {
			p2 = static_cast<const char*>(this->origin._data);
			l2 = this->origin._len;
		}
	} else {
		p2 = static_cast<const char*>(this->_data);
		l2 = this->_len;
	}

	if (l1 != l2) {
		return false;
	} else {
		for (size_t i = 0; i < l1; i++) {
			if (p1[i] != p2[i]) {
				return false;
			}
		}
		return true;
	}
}


