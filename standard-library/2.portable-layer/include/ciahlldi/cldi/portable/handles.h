
#ifndef _cldi_portable__HANDLES_H
#define _cldi_portable__HANDLES_H 1

/* Setup CLDI module "portable". */
#include "setup.h"

/* Requires: cldi-portable: types (sib) */
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif



/* Included Headers for Handle Implementation */

/* "borrowing" : For access points (scopes that can borrow/own), and
.                borrowing and ownership mechanics. */
#include "handles/borrowing.h"

/* "mem"       : For memory handling from platform to platform, and from thread
.                to thread. */
#include "handles/mem.h"

/* "" */



/* Handle Address Type (platform-dependent) */
#if __CLDI_PLATFORM == CLDI_PLATFORM_WINDOWS
#define _CLDI_HANDLE_GENERIC_TYPE HANDLE
#else
#define _CLDI_HANDLE_GENERIC_TYPE void*
#endif
typedef _CLDI_HANDLE_GENERIC_TYPE CLDIHANDLE;


/* Handle Type */
typedef struct _cldiHandle_t cldiHandle, cldiHandle_t;

struct cldiHandleCatalog_t
{
	/* This handle's subroutine for first-hand initialization (by owner). */
	CLDIERR (*const __init__)
	(
		/* [in]           */ cldiHandle * handle,
		/* [in], nullable */ va_list    * init_args
	);
	/* This handle's subroutine for final deletion (by owner) */
	CLDIERR (*const __del__)
	(
		/* [in]           */ cldiHandle * handle,
		/* [in], nullable */ long long    options,
		/* [in], nullable */ va_list    * del_args
	);

	/* This handle's introduction subroutine for borrowers. */
	const cldiBorrowTicket* (*const __borrow__)
	(
		/* [in]           */ cldiHandle      * handle,
		/* [in]           */ cldiAccessPoint * borrower,
		/* [in], nullable */ va_list         * borrow_args
	);
	/* This handle's conclusion subroutine for borrowers that close their ticket. */
	CLDIERR (*const __drop__)
	(
		/* [in]           */ cldiHandle      * handle,
		/* [in]           */ cldiAccessPoint * borrower,
		/* [in], nullable */ va_list         * drop_args
	);
};

struct _cldiHandle_t
{
	CLDIHANDLE handle;

	const struct cldiHandleCatalog_t *const handlers;
};



#ifdef __cplusplus
}
#endif

#endif /* _cldi_portable__HANDLES_H */
