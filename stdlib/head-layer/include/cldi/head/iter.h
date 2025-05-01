
#pragma cldic module head:iter
#ifndef _cldi_head__ITER_H
#define _cldi_head__ITER_H 1

#include "memory.h"
#pragma cldic require head:memory

#ifdef __cplusplus
extern "C" {
#endif



/* Iterator type declaration */
typedef struct _CLDIITERATOR cldiiter_t;
/* Iterator Loop Function type 'cldiiterfunc_t':  bool <function>(cldiiter_t *iterable)
.  - Returns whether to continue the loop (true) or break out of it (false). */
cldiTemplFunction(bool, cldiiterfunc_t, cldiiter_t*);
/* Iterator Item Generator Function type 'cldiitergenfunc_t': void* <function>(cldiiter_t *iterable)
.  - Each time a loop is performed, the "current item" ptr must (can) be incremented with it,
.    This function type returns the new address to adopt on each loop, it should recognize the
.    index stored in the iterable object to determine which item to return an address for. */
cldiTemplFunction(void*, cldiitergenfunc_t, cldiiter_t*);

/* Const Iterator type declaration */
typedef struct _CLDICONSTITERATOR cldiiterc_t;
/* Iterator Loop Function type 'cldiiterfunc_t':  bool <function>(cldiiter_t *iterable)
.  - Returns whether to continue the loop (true) or break out of it (false). */
cldiTemplFunction(bool, cldiiterconst_t, cldiiterc_t*);
/* Iterator Item Generator Function type 'cldiitergenfunc_t': void* <function>(cldiiter_t *iterable)
.  - Each time a loop is performed, the "current item" ptr must (can) be incremented with it,
.    This function type returns the new address to adopt on each loop, it should recognize the
.    index stored in the iterable object to determine which item to return an address for. */
cldiTemplFunction(const void*, cldiitergenconst_t, cldiiterc_t*);

/* Generic Loop Function type 'cldiloopfunc_t': bool <function>(size_t index, void *const item)
.  - Returns whether to continue the loop (true) or break out of it (false). */
cldiTemplFunction(bool, cldiloopfunc_t, size_t, void*const);
/* Generic Loop Function type with const access 'cldiloopconst_t':
.    bool <function>(size_t index, void *const item)
.  - Returns whether to continue the loop (true) or break out of it (false). */
cldiTemplFunction(bool, cldiloopconst_t, size_t, const void*const);

/* Iterator type */
struct _CLDIITERATOR
{
	/* Starting position and current position. */
	void *origin, *current;

	/* Built-in index field, and the increment/decrement amount. */
	signed long long index, inc, len;

	/* Item Generator function for each loop. */
	cldiitergenfunc_t  itemgen;
	/* Condition Checker function for each loop. */
	cldiiterfunc_t     cond;
	/* Closing function for the end of the loop. */
	cldiiterfunc_t     closer;
};
/* Const Iterator type */
struct _CLDICONSTITERATOR
{
	/* Starting position and current position. */
	const void *origin, *current;

	/* Built-in index field, and the increment/decrement amount. */
	signed long long index, inc, len;

	/* Item Generator function for each loop. */
	cldiitergenconst_t itemgen;
	/* Condition Checker function for each loop. */
	cldiiterconst_t    cond;
	/* Closing function for the end of the loop. */
	cldiiterconst_t    closer;
};

extern const cldiiter_t CLDIITER_NULL;
extern const cldiiterc_t CLDIITERC_NULL;



#ifdef __cplusplus
}
#endif

#endif // _cldi_head__ITER_H
