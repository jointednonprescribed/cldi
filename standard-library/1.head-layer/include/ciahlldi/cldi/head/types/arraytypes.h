
#ifndef _cldi_head__types_ARRAYTYPES_H
#define _cldi_head__types_ARRAYTYPES_H 1

#include "../setup.h"

#include "arraytypes/refs.h"
#include "basictypes.h"



/* Structures for int, char, and long long array data. */

#include "arraytypes/CLDIBYTEARR.h"
struct CLDIBYTEARR
{
	char *const  _data;
	const size_t length;

#if defined(__cplusplus) && __CLDI_no_cpp < true

	CLDIBYTEARR(const char *array, size_t length);
	CLDIBYTEARR();

	~CLDIBYTEARR();

	/* Get a full copy of this array in a new handle. */
	CLDIBYTEARR GetCopy() const;
	/* Get a new handle linking to this same array. */
	CLDIBYTEARR Share() const;

	/* Get the length of the array. */
	size_t      Length() const;
	/* Get the address of the array itself. */
	const char* Data() const;

#endif
};

struct CLDIINTARR
{
	int *const   _data;
	const size_t length;

#if defined(__cplusplus) && __CLDI_no_cpp < true

	CLDIINTARR(const int *array, size_t length);
	CLDIINTARR();

	~CLDIINTARR();

	/* Get a full copy of this array in a new handle. */
	CLDIINTARR GetCopy() const;
	/* Get a new handle linking to this same array. */
	CLDIINTARR Share() const;

	/* Get the length of the array. */
	size_t     Length() const;
	/* Get the address of the array itself. */
	const int* Data() const;

#endif
};

struct CLDILONGARR
{
	long long *const _data;
	const size_t     length;

#if defined(__cplusplus) && __CLDI_no_cpp < true

	CLDILONGARR(const long long *array, size_t length);
	CLDILONGARR(const long *array, size_t length);
	CLDILONGARR();

	~CLDILONGARR();

	/* Get a full copy of this array in a new handle. */
	CLDILONGARR GetCopy() const;
	/* Get a new handle linking to this same array. */
	CLDILONGARR Share() const;

	/* Get the length of the array. */
	size_t           Length() const;
	/* Get the address of the array itself. */
	const long long* Data() const;

#endif
};


/* Structure for marking a portion of a VLA. */
extern const cldiVLASect CLDIVLASECT_NULL;
struct CLDIVLASECT
{
	size_t beg, end;
	CLDISTAT errstat;

#if defined(__cplusplus) && __CLDI_no_cpp < true

	CLDIVLASECT();

	CLDIVLASECT(size_t beg, size_t end, CLDISTAT errstat = CLDI_SUCCESS);

	constexpr auto operator =(const CLDIVLASECT &rhv)
	{
		beg     = rhv.beg;
		end     = rhv.end;
		errstat = rhv.errstat;
	}

#endif
};

/* Structure for storing VLA data. */
extern const cldiVLAHandle CLDIVLAHANDLE_NULL;
struct CLDIVLAHANDLE
{
	void * _data;
	size_t _len;
	size_t _ilen;

#if defined(__cplusplus) && __CLDI_no_cpp < true


	template <typename _T>
	constexpr CLDIVLAHANDLE(const _T* address, size_t length):
		CLDIVLAHANDLE(address, sizeof(_T), length)
	{}

	CLDIVLAHANDLE(size_t item_size, size_t length, const void* address);
	CLDIVLAHANDLE(const CLDIVLAHANDLE &rhv);
	CLDIVLAHANDLE();

	~CLDIVLAHANDLE();

	CLDISTAT DropState();

	auto operator =(const CLDIVLAHANDLE &rhv);

	CLDIVLAHANDLE GetCopy() const;
	CLDISTAT      AssumeCopy(const CLDIVLAHANDLE &owner);

	const void* Data() const;
	size_t      GetItemSize() const;
	size_t      Length() const;
	size_t      ByteLength() const;

#endif
};


/* Structure for storing VLA data states. */
/* Structures referenced in this section: */
#include "texttypes/refs.h"
extern const cldiVLA CLDIVLA_NULL;
struct CLDIVLA
{
	/* The VLA's unmodifyable, 'origin' state (the data it's initialized with, or has
	.  set to it's 'default', or 'original' set of data.) */
	cldiVLAHandle origin;

	/* The modifyable, 'current' data state of this VLA, this type of array state,
	.  which is present both in cldiVLA, but also cldiStr, will, as long as it is
	.  the modifyable 'current' state, should be exclusively owned by the object holding
	.  it. If another object originates from a string or array's current state, it
	.  must create a new copy of the data, and use that frozen copy as its origin. */
	void        * _data;
	/* The size of each item. */
	size_t        _ilen;
	/* The total length of the initialized data in the current state. */
	size_t        _len;
	/* The total size of the current state's memory block; the byte capacity of the
	.  current state. */
	size_t        _cap;

#if defined(__cplusplus) && __CLDI_no_cpp < true

	template <typename _T>
	constexpr CLDIVLA(size_t origin_length, const _T* origin_data):
		CLDIVLA(sizeof(_T), origin_length, origin_data)
	{}

	CLDIVLA(size_t item_size, size_t origin_length, const void* origin_data, size_t extra_capacity=0, bool copy_origin=false);
	CLDIVLA(cldiVLAHandle origin, size_t extra_capacity=0, bool copy_origin=false);
	CLDIVLA(size_t item_size, size_t item_capacity);
	CLDIVLA(const CLDIVLA &rhv);
	CLDIVLA();

	~CLDIVLA();

	constexpr auto operator =(const CLDIVLA &rhv)
	{
		AssumeFullCopy(rhv);
	}

	/* Get a full copy of this VLA, with a completely independent copy of the current
	.  state, if `new_origin` is true, the origin state will be an independent copy too,
	.  otherwise the origin with be shared between the two array's (siblings). */
	CLDIVLA       GetCopy(bool new_origin=false) const;
	/* Get a handle to the origin state. */
	CLDIVLAHANDLE GetOrigin() const;
	/* Get an independent copy of the origin with a new handle. */
	CLDIVLAHANDLE GetCopyOfOrigin() const;
	/* Get an independent copy of the current state stored in a new handle. */
	CLDIVLAHANDLE GetCopyAsHandle() const;

	/* Assume (convert current object to a full copy of) another
	.  object with an independent copy of that object's current
	.  state, if `new_origin` is true, the origin state will be an
	.  independent copy too, otherwise, the origin state will just
	.  be shared between each object (siblings). */
	CLDISTAT      AssumeFullCopy(const CLDIVLA &copy_of, bool new_origin=false);
	/* Assume the origin of another object as the current state,
	.  if `move_origin` is true, the current state will become the
	.  new origin first. */
	CLDISTAT      AssumeOrigin(const CLDIVLA &origin_of, bool move_origin=false);
	/* Assume another object's current state, if `move_origin` is true,
	.  your current state will become the new origin state. */
	CLDISTAT      Assume(const CLDIVLA &state_of, bool move_origin=false);

	/* Get the address of the current state. */
	const void*   Data() const;
	/* Get the item size of the current state. */
	size_t        GetItemSize() const;
	/* Get the length (number of items) of the current state. */
	size_t        Length() const;
	/* Get the length (number of bytes) of the current state. */
	size_t        ByteLength() const;
	/* Get the total item capacity (number of items) of the current state. */
	size_t        Capacity() const;
	/* Get the total item capacity (number of bytes) of the current state. */
	size_t        ByteCapacity() const;

	/* Get the active state of this VLA. the "active state" is the current state if:
	.   - The current state exists (_data != NULL),
	.   - The current state contains data (_cap > 0 && _len > 0), AND
	.   - The current state is not null and contains valid data types (_ilen > 0)
	.  However, the origin state is the active state if:
	.   - The current state is not the active state (based on the conditions above),
	.   - The origin state exists (origin._data != NULL),
	.   - The origin state contains data (origin._len > 0), AND
	.   - The origin state is not null and contains valid data types (origin._ilen > 0)
	.  Otherwise, null VLA handle will be returned and NULL_ARG error will be thrown. */
	CLDIVLAHANDLE GetActiveState() const;
protected:
	/* Save values of the active state elsewhere, bypassing the handle. */
	CLDISTAT ImportActiveState(
		size_t      *const item_size_out,
		size_t      *const len_out,
		const void **const addr_out
	) const;
public:

	/* Create a current array state that is `item_capacity` items long,
	.  and initialized to zero. */
	CLDISTAT      CreateState(size_t item_size, size_t item_capacity);
	/* Create a current array state that is `item_capacity` items long,
	.  initialized to zero, and carries the same item length as the origin, or
	.  the current state (if existent) before starting the method, if there is
	.  no origin OR preceeding current state, this method will return a
	.  CLDI_NULL_ATTR error. */
	CLDISTAT      CreateEmptyState(size_t item_capacity);
	/* Create a new state as a copy of the origin state, `extra_capacity`
	.  refers to the amount of extra items that should be allocated in addition
	.  to the copy of the origin state. */
	CLDISTAT      CreateStateFromOrigin(size_t extra_capacity=0);
	/* Drop the current state if there is one. */
	CLDISTAT      DropState();
	/* Drop the current origin state. */
	CLDISTAT      DropOrigin();
	/* Return the data within the current state to a copy of the origin state,
	.  this will not delete the memory space that the current state occupies,
	.  it will only reinitialize it to the data within the origin, such a
	.  refactoring of the current memory space is performed, instead, by
	.  CreateStateFromOrigin(). */
	constexpr CLDISTAT ReturnToOrigin()
	{
		return CreateStateFromOrigin();
	}
	/* Drop the origin state and set the current state to the new
	.  origin state. */
	CLDISTAT      SetNewOrigin();

	/* Compare this array to some part of another and return true
	.  if the second is contained inside of the first, if an error
	.  occurs, false is returned, and CLDI_LAST_ERR will contain an
	.  error code. */
	bool          Compare(const CLDIVLA &other, const cldiVLASect &check_portion) const;
	bool          Compare(const CLDIVLAHANDLE &other, const cldiVLASect &check_portion) const;
	/* Check if two arrays are identical in length and content. */
	bool          IsIdentical(const CLDIVLA &other) const;
	bool          IsIdentical(const CLDIVLAHANDLE &other) const;
	/* Find where in this array, a certain other set of items may
	.  be found. */
	cldiVLASect   Find(const CLDIVLA &other) const;
	cldiVLASect   Find(const CLDIVLAHANDLE &other) const;

#endif
};



#if defined(__cplusplus) && __CLDI_no_Cpp < true



namespace cldi
{
	using boolarr_t   = cldiBoolArr;

	using bytearr_t   = cldiBoolArr;
	using intarr_t    = cldiIntArr;
	using longarr_t   = cldiLongArr;

	using vlahandle_t = cldiVLAHandle;
	using vla_t       = cldiVLA;
}



#endif

#endif /* _cldi_head__types_ARRAYTYPES_H */
