
#pragma cldic module head:array
#ifndef _cldi_head__ARRAY_H
#define _cldi_head__ARRAY_H 1

#include "iter.h"
#pragma cldic require head:iter

#ifdef __cplusplus
extern "C" {
#endif



/* Array List type */
typedef struct _CLDIARRAYLIST
{
	cldimemref data;
	size_t     len;
} cldiarray_t, cldiarraylist_t, cldiArray, cldiArrayList;

/* Methods associated with cldiarray_t: */

/* Construct blank (null instance). */
CLDISTAT cldiInitArray(cldiarray_t *self);
/* Construct with raw array. */
CLDISTAT cldiInitArrayPtr(cldiarray_t *self, void *const ptr, size_t array_size, clditypeinfo_t ptr_type);
/* Construct with raw array and extra capacity. */
CLDISTAT cldiInitArrayPtrEx(cldiarray_t *self, void *const ptr, size_t array_size, size_t extra_cap, clditypeinfo_t ptr_type);
/* Construct with memref. */
CLDISTAT cldiInitArrayRef(cldiarray_t *self, cldimemref ref, size_t array_size, clditypeinfo_t ptr_type);
/* Construct with memref and extra capacity. */
CLDISTAT cldiInitArrayRefEx(cldiarray_t *self, cldimemref ref, size_t array_size, size_t extra_cap, clditypeinfo_t ptr_type);
/* Construct with memref (whole block). */
CLDISTAT cldiInitArrayBlock(cldiarray_t *self, cldimemref ref, clditypeinfo_t ptr_type);
/* Construct with memref (whole block) and extra capacity. */
CLDISTAT cldiInitArrayBlockEx(cldiarray_t *self, cldimemref ref, size_t extra_cap, clditypeinfo_t ptr_type);
/* Construct by borrowing from another array. */
CLDISTAT cldiInitArrayBorrowed(cldiarray_t *self, const cldiarray_t *borrow_from);
/* Cosntruct as a copy of another array. */
CLDISTAT cldiInitArrayCopy(cldiarray_t *self, const cldiarray_t *copy_of);
/* Cosntruct as a copy of another array with extra capacity. */
CLDISTAT cldiInitArrayCopyEx(cldiarray_t *self, const cldiarray_t *copy_of, size_t extra_cap);
/* Make a new instance and pass it over the stack. */
cldiarray_t cldiMakeArray();
cldiarray_t cldiMakeArrayPtr(void *const ptr, size_t array_size, clditypeinfo_t ptr_type);
cldiarray_t cldiMakeArrayPtrEx(void *const ptr, size_t array_size, size_t extra_cap, clditypeinfo_t ptr_type);
cldiarray_t cldiMakeArrayRef(cldimemref ref, size_t array_size);
cldiarray_t cldiMakeArrayRefEx(cldimemref ref, size_t array_size, size_t extra_cap);
cldiarray_t cldiMakeArrayBlock(cldimemref ref);
cldiarray_t cldiMakeArrayBlockEx(cldimemref ref, size_t extra_cap);
cldiarray_t cldiMakeArrayBorrowed(const cldiarray_t *borrow_from);
cldiarray_t cldiMakeArrayCopy(const cldiarray_t *copy_of);
cldiarray_t cldiMakeArrayCopyEx(const cldiarray_t *copy_of, size_t extra_cap);
/* Make a new instance in the heap. */
cldimemref  cldiNewArray();
cldimemref  cldiNewArrayPtr(void *const ptr, size_t array_size, clditypeinfo_t ptr_type);
cldimemref  cldiNewArrayPtrEx(void *const ptr, size_t array_size, size_t extra_cap, clditypeinfo_t ptr_type);
cldimemref  cldiNewArrayRef(cldimemref ref, size_t array_size, clditypeinfo_t ptr_type);
cldimemref  cldiNewArrayRefEx(cldimemref ref, size_t array_size, size_t extra_cap, clditypeinfo_t ptr_type);
cldimemref  cldiNewArrayBlock(cldimemref ref, clditypeinfo_t ptr_type);
cldimemref  cldiNewArrayBlockEx(cldimemref ref, size_t extra_cap, clditypeinfo_t ptr_type);
cldimemref  cldiNewArrayBorrowed(const cldiarray_t *borrow_from);
cldimemref  cldiNewArrayCopy(const cldiarray_t *copy_of);
cldimemref  cldiNewArrayCopyEx(const cldiarray_t *copy_of, size_t extra_cap);

/* Array object's memref destructor. */
CLDISTAT cldiDropBlock(cldimemref *drop);
/* Drop an array object. */
CLDISTAT cldiArrayDrop(cldiarray_t *self);
/* Drop just the array data in memory is equivalent to dropping the array itself. */
#define  cldiArrayDropData cldiArrayDrop

/* Get the capacity of elements in the array. */
size_t cldiArrayCapacity(const cldiarray_t *self);
/* Get the number of initialized elements in the array. */
size_t cldiArraySize(const cldiarray_t *self);
/* Get the size (in bytes) of the array. */
size_t cldiArrayBytesCapacity(const cldiarray_t *self);
/* Get the total size in memory that this array is reserving (not counting the object itself). */
size_t cldiArrayTotalSize(const cldiarray_t *self);
/* Get the array's type (as clditypeinfo_t). */
const clditypeinfo_t* cldiArrayType(const cldiarray_t *self);
/* Get the size of each of the array's elements. */
size_t cldiArrayElementSize(const cldiarray_t *self);

/* Reserve space for a certain total number of elements, if that space is not yet
.  reserved. */
CLDISTAT cldiArrayReserveTotal(cldiarray_t *self, size_t reserve_capacity);
/* Reserve space for a number of extra empty elements at the end of the array, if
.  that space is not yet reserved. */
CLDISTAT cldiArrayReserve(cldiarray_t *self, size_t reserve_capacity);
/* Expand the array by a certain number of empty elements (at the end). */
CLDISTAT cldiArrayExpand(cldiarray_t *self, size_t expand_by);
/* Expand the array by a certain number of empty elements (at the beginning). */
CLDISTAT cldiArrayExpandBeg(cldiarray_t *self, size_t expand_by);
/* Expand the array by a certain number of empty elements (at given index). */
CLDISTAT cldiArrayExpandAt(cldiarray_t *self, ssize_t expand_at, size_t expand_by);
/* Trim the array by a certain number of elements (at the end).
.  Keep in mind: Trim functions remove/reallocate memory rather than just
.  nullifying elements. */
CLDISTAT cldiArrayTrimEnd(cldiarray_t *self, size_t trunc_by_amount);
#define  cldiArrayTrim cldiArrayTrimEnd
/* Trim the array by a certain number of elements (at the beginning). */
CLDISTAT cldiArrayTrimBeg(cldiarray_t *self, size_t trunc_by_amount);
/* Trim the array by a certain number of elements (at a given index). */
CLDISTAT cldiArrayTrimAt(cldiarray_t *self, ssize_t trunc_at, size_t trunc_by_amount);
/* Trim any empty capacity at the end of the array. */
CLDISTAT cldiArrayTrimToSize(cldiarray_t *self);

/* Append an element to the end of the array. */
CLDISTAT cldiArrayPushBack(cldiarray_t *self, const void *element);
#define  cldiArrayPush cldiArrayPushBack
/* Append an element to the beginning of the array. */
CLDISTAT cldiArrayPushFront(cldiarray_t *self, const void *element);
/* Append an element to a certain index in the array. */
CLDISTAT cldiArrayPushAt(cldiarray_t *self, ssize_t idx, const void *element);
/* Append a number of elements to the end of the array, returns the number of
.  elements that would be written if an error had not ocurred, where CLDI_ERRNO
.  equals the error code that was passed, unless no error ocurred. */
size_t   cldiArrayAppendBack(cldiarray_t *self, size_t n, const void *elements);
#define  cldiArrayAppend cldiArrayAppendBack
/* Append a number of elements to the beginning of the array. */
size_t   cldiArrayAppendBeg(cldiarray_t *self, size_t n, const void *elements);
/* Append a number of elements to a certain index in the array. */
size_t   cldiArrayAppendAt(cldiarray_t *self, ssize_t idx, size_t n, const void *elements);
/* Truncate the whole array (set to empty):
.  - Truncate functions don't remove or reallocate memory, the remove portions
.    of the array by moving succeeding elements over top of those portions where
.    possible, and nullify elements when not. */
CLDISTAT cldiArrayTruncAll(cldiarray_t *self, size_t n);
/* Truncate some number of items starting at the end of the array. */
CLDISTAT cldiArrayTruncEnd(cldiarray_t *self, size_t n);
#define  cldiArrayTrunc cldiArrayTruncEnd
/* Truncate some number of items starting at the beginning of the array. */
CLDISTAT cldiArrayTruncBeg(cldiarray_t *self, size_t n);
/* Truncate some number of items starting at a certain index in the array. */
CLDISTAT cldiArrayTruncAt(cldiarray_t *self, ssize_t start_idx, size_t n);
/* Nullify the whole array (set all values to empty):
.  - Clear functions merely clear the values of element(s) in the array, without
.    moving elements over top or removing/reallocating memory. */
CLDISTAT cldiArrayClearAll(cldiarray_t *self);
/* Nullify some number of items starting at the end of the array. */
CLDISTAT cldiArrayClearEnd(cldiarray_t *self, size_t n);
/* Nullify some number of items starting at the beginning of the array. */
CLDISTAT cldiArrayClearBeg(cldiarray_t *self, size_t n);
/* Nullify some number of items starting at a certain index in the array. */
CLDISTAT cldiArrayClearAt(cldiarray_t *self, ssize_t idx, size_t n);
/* Nullify some number of items starting at a certain index in the array. */
CLDISTAT cldiArrayClearElement(cldiarray_t *self, ssize_t idx);

/* Refactor the array to a copy of some other array. */
CLDISTAT cldiArraySetToCopy(cldiarray_t *self, const cldiarray_t *copy_of);
/* Refactor the array to a subcopy (copy of a specific portion) of some other
.  array. */
CLDISTAT cldiArraySetToSubcopy(cldiarray_t *self, ssize_t beg_at, size_t portion_length, const cldiarray_t *copy_of);
/* Refactor the array to a copy of some raw array. */
CLDISTAT cldiArraySetToCopyRaw(cldiarray_t *self, size_t array_size, const void *const raw_array);
/* Rewrite the array data, starting at the beginning, to that of some other array. */
CLDISTAT cldiArraySetBeg(cldiarray_t *self, const cldiarray_t *set_to);
#define  cldiArraySet cldiArraySetBeg
/* Rewrite the array data, leading up to the end, to that of some other array. */
CLDISTAT cldiArraySetEnd(cldiarray_t *self, const cldiarray_t *set_to);
/* Rewrite the array data, starting at a given index, to that of some other array. */
CLDISTAT cldiArraySetAt(cldiarray_t *self, ssize_t beg_at, const cldiarray_t *set_to);
/* Rewrite the array data, starting at the beginning, to a portion of that of
.  some other array. */
CLDISTAT cldiArraySetBegToPortion(cldiarray_t *self, ssize_t beg_at, size_t portion_length, const cldiarray_t *set_to);
#define  cldiArraySetToPortion cldiArraySetBegToPortion
/* Rewrite the array data, starting at the end, to a portion of that of
.  some other array. */
CLDISTAT cldiArraySetEndToPortion(cldiarray_t *self, ssize_t beg_at, size_t portion_length, const cldiarray_t *set_to);
/* Rewrite the array data, starting at a given index, to a portion of that of
.  some other array. */
CLDISTAT cldiArraySetToPortionAt(cldiarray_t *self, ssize_t set_data_beg, ssize_t portion_beg, size_t portion_length, const cldiarray_t *set_to);
/* Rewrite the array data (starting at the beginning) of the array data to some
.  raw array. */
CLDISTAT cldiArraySetBegRaw(cldiarray_t *self, size_t array_size, const void *const set_to);
#define  cldiArraySetRaw cldiArraySetBegRaw
/* Rewrite the array data (leading up to the end) of the array data to some
.  raw array. */
CLDISTAT cldiArraySetEndRaw(cldiarray_t *self, size_t array_size, const void *const set_to);
/* Rewrite the array data (starting at a given index) of the array data to some
.  raw array. */
CLDISTAT cldiArraySetRawAt(cldiarray_t *self, ssize_t beg_at, size_t array_size, const void *const set_to);

/* Get an iterable from the array. */
cldiiter_t cldiArrayIter(cldiarray_t *self, size_t idx, size_t inc, cldiiterfunc_t cond);
/* Get an iterable from the array with closer function. */
cldiiter_t cldiArrayIterClosing(cldiarray_t *self, size_t idx, size_t inc, cldiiterfunc_t cond, cldiiterfunc_t closer);
/* Get an iterable for the array (starting from the beginning). */
cldiiter_t cldiArrayIterBeg(cldiarray_t *self);
/* Get an iterable starting at a certain index in the array and descending. */
cldiiter_t cldiArrayIterAt(cldiarray_t *self, ssize_t idx);
/* Get an iterable for the array (starting at the end). */
cldiiter_t cldiArrayIterRev(cldiarray_t *self);
/* Get an iterable starting at a certain index in the array and descending. */
cldiiter_t cldiArrayIterRevAt(cldiarray_t *self, ssize_t idx);
/* Loop through the entire array with a given function. */
void       cldiArrayForEach(cldiarray_t *self, cldiiterfunc_t func);
/* Loop through the entire array with a given function using a raw ptr and index
.  instead of iterator. */
void       cldiArrayForEachRaw(cldiarray_t *self, cldiloopfunc_t func);



#ifdef __cplusplus
}
#endif

#endif // _cldi_head__ARRAY_H
