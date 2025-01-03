
#ifndef _cldi_core__types_ARR_H
#define _cldi_core__types_ARR_H 1

/* Setup CLDI module "core". */
#include "../setup.h"

/* Requires: cldi-portable: types */
#include <ciahlldi/cldi/portable/types.h>

#ifdef __cplusplus
extern "C" {
#endif




/* ----------------------------------- */
/* Const Array Type (`cldiConstArr`) */

	typedef struct _cldiConstArr_t
	{
		const size_t  slot_size;

		const void *const address;

		const size_t  item_count;
	} cldiConstArr, cldiConstArr_t;

	/* Null value for this type. */
	extern const cldiConstArr CLDICONSTARR_NULL;


/* ----------------------------------- */
/* Array Type (`cldiArr`) */

	typedef struct _cldiArr_t
	{
		/* The origin state of the array to fall back on as an original, acts as the "parent"
		.  to this type. */
		cldiConstArr      origin_state;

		/* Acts as the current state of the string, the owned memory storing the
		.  string's data. */
		void            * modifiable_state_address;

		/* The number of objects in the array. */
		size_t        initialized_length;
		/* The array's capacity (amount of objects) that can be stored in its memory. */
		size_t        object_capacity;

		/* Any variable stored information about the type. */
		unsigned int      data;

	} cldiArr, cldiArr_t;

	/* All memory allocate for this type will be assumed to be zero-initialized. */

	/* Drop ownership/borrowing of this object (delete if it becomes unused).
	.  - Make sure you use this first every time you plan
	.    to re-Init() an object. */
	bool cldiArr_Drop(cldiArr * self);

	/* Initialize from a const C-style raw array. */
	bool cldiArr_InitFromArray(
		cldiArr         * self,
		size_t        item_size,
			/* The size of each item. */
		size_t            length,
			/* The amount of objects in the array to initialize from. */
		const void *const array
			/* The array to initialize from. */
	);
	/* - Initialize from an array, then produce a modifiable extension of it. */
	bool cldiArr_InitAsArray(
		cldiArr         * self,
		size_t        item_size,
			/* Same as in the above. */
		size_t        length,
			/* Same as in the above. */
		size_t        extra_capacity,
			/* Extra amount of "slots" for items to append to the end. */
		const void *const array
			/* Same as in the above. */
	);
	/* - Initialize from an array, then produce a modifiable copy of it (no extra capacity). */
	bool cldiArr_InitAsArrayCopy(
		cldiArr         * self,
		size_t        item_size,
			/* Same as in the above. */
		size_t        length,
			/* Same as in the above. */
		const void *const array
			/* Same as in the above. */
	);

	/* Initialize empty and with no origin, but with pre-allocated capacity to store objects. */
	bool cldiArr_InitPreallocated(
		cldiArr  * self,
		size_t char_size,
			/* The size of each item. */
		size_t preallocated
			/* The amount of items to pre-allocate space for. */
	);


	/* ----------------------------------- */
	/*      --- Getters & Setters ---      */

	/* Get a reference to the origin state of this object. */
	cldiArr*          cldiArr_RefOriginState(const cldiArr * self);
	/* Get the string's origin state. */
	cldiArr           cldiArr_GetOriginState(const cldiArr * self);
	/* Get the size of each item in the array. */
	size_t        cldiArr_ItemSize(const cldiArr * self);
	/* Get the memory address of the modifiable state. */
	const void *const cldiArr_ModifiableStateAddress(const cldiArr * self);
	/* Get the amount of initialized items in the modifiable state. */
	size_t        cldiArr_InitializedLength(const cldiArr * self);
	/* Get the total size in memory of the initialized array data in the modifiable
	.  state. */
	size_t        cldiArr_InitializedSize(const cldiArr * self);
	/* Get the full capacity of the modifiable state (by amount of items). */
	size_t        cldiArr_Capacity(const cldiArr * self);
	/* Get the total size in bytes of the modifyable state in memory. */
	size_t        cldiArr_GetFullSize(const cldiArr * self);
	/* Get the total amount of bytes used by the object in memory. */
	size_t        cldiArr_GetTotalSize(const cldiArr * self);
	/* Aliases for InitializedLength() and ModifiableStateAddress(): */
	#define cldiArr_Length   cldiArr_InitializedLength
	#define cldiArr_Data     cldiArr_ModifyableStateAddress


/* ----------------------------------- */



#ifdef __cplusplus
}
#endif

#endif /* _cldi_core__types_ARR_H */
