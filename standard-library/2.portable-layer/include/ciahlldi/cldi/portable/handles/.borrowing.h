
#ifndef _cldi_portable__handles_BORROWING_H
#define _cldi_portable__handles_BORROWING_H 1

/* Setup CLDI module "portable". */
#include "../setup.h"

/* Requires: cldi-portable: types */
#include "../types.h"

#ifdef __cplusplus
extern "C" {
#endif



/* Borrowing Access Level Enum Type */
typedef enum _CLDI_BR_ACCESS_T
{
	/* Unexpected Error */
	CLDI_BR_ERROR               = 0,
	/* Invalid Entry (Error) */
	CLDI_BR_INVALID_ENTRY       = 0x1,

	/* No Access */
	CLDI_BR_NO_ACCESS           = 0x2,

	/* Minimum Access */
	CLDI_BR_ACCESS_MINIMUM      = 0x3,
	/* Below Normal Access */
	CLDI_BR_ACCESS_BELOW_NORMAL = 0x4,
	/* Normal Level of Access */
	CLDI_BR_ACCESS_NORMAL       = 0x5,
	/* Medium Level of Access */
	CLDI_BR_ACCESS_MEDIUM       = 0x6,
	/* Above Normal Level of Access */
	CLDI_BR_ACCESS_ABOVE_NORMAL = 0x7,
	/* High Level of Access */
	CLDI_BR_ACCESS_HIGH         = 0x8,
	/* Cooperative Access */
	CLDI_BR_ACCESS_COOPERATIVE  = 0x9,
	/* Very High Level of Access */
	CLDI_BR_ACCESS_VERY_HIGH    = 0xA,
	/* Maximum Level of External Access */
	CLDI_BR_ACCESS_MAXIMUM      = 0xB,

	/* Owner Status */
	CLDI_BR_OWNER               = 0xC,
} CLDI_BR_ACCESS, CLDI_BR_ACCESS_T;

/* Borrowing Options/Information Enum Type */
typedef enum _CLDI_BR_INFO_T
{} CLDI_BR_INFO, CLDI_BR_INFO_T;

/* "BorrowableClass" Base Class */
struct cldiBorrowableClass;
/* "Access Point" or "Access Scope" Type: For defining a member that can own and
.                                         borrow it's own objects (handles, etc.). */
typedef struct _cldiAccessScope_t
	cldiAccessPoint, cldiAccessPoint_t,
	cldiAccessScope, cldiAccessScope_t;
/* "Borrow Ticket" Type: Contains all information for, and acts as a receipt for any
.                        borrowing operation performed on a value of BorrowableClass class. */
typedef struct _cldiBorrowTicket_t cldiBorrowTicket, cldiBorrowTicket_t;

/* Implementations for these types: */

/* BorrowTicket */
struct _cldiBorrowTicket_t
{
	cldihalf options;
};

/* BorrowableClass */
struct cldiBorrowableClass
{
	cldihalf options, ref_counter;
};

/* AccessScope */
struct _cldiAccessScope_t
{
	struct cldiBorrowableClass SUPER_BorrowableClass;
};



#ifdef __cplusplus
}
#endif

#endif /* _cldi_portable__handles_BORROWING_H */
