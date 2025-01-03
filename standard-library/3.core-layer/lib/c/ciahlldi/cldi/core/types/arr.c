
/* Setup for cldi-core.                      */
#include <ciahlldi/cldi/core/setup.h>

/* Implementing: cldi-core:     types/arr    */
#include <ciahlldi/cldi/core/types/arr.h>

/* Requires:     cldi-portable: calls/memory */
#include <ciahlldi/cldi/portable/calls/memory.h>

#ifdef __cplusplus
extern "C" {
#endif



/* ----------------------------------- */
/* `cldiArr` Type */

	bool cldiArr_InitConst(
		cldiArr       * self,
		size_t            __charsize,
		size_t            __len,
		const cldiArr * __origin)
	{
		return cldiArr_InitConstAsOrigin(self, __charsize, __len, __origin, false, 0);
	}
	bool cldiArr_InitConstAsOrigin(
		cldiArr       * self,
		size_t            __charsize,
		size_t            __len,
		const cldiArr * __origin,
		bool              __copy,
		size_t            __extra)
	{
		int                  copy_err  = 0;
		CldiMem_RequestErr_t alloc_err = 0;

		char * new_space   = NULL;

		size_t full_size   = 0,
		/*  */ full_length = __len * __charsize;

		if (__copy) {
			full_size          = (__extra * __charsize) + full_length;
			new_space          = CldiMem_eRequestInContext(full_size, &alloc_err);
			copy_err           = strncpy(new_space, __origin, full_length);
		}

		*self = {
			.character_size  = __charsize,

			.mutable_data    = new_space,
			.array_size      = full_size,
			.array_length    = __len,

			.original_length = __len,
			.immutable_data  = __origin,

			.clean_original  = false
		};

		return true;
	}


/* ----------------------------------- */



#ifdef __cplusplus
}
#endif
