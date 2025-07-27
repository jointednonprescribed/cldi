
#ifndef _cldi_head__math_DOMAIN_H
#define _cldi_head__math_DOMAIN_H 1

/* Subheader of head/math.h */
#ifndef _cldi_head__MATH_H
#	include "../math.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif



/* Domain Escape Codes enum:
.  - Contains code for the domain object to avoid using a finite domain in memory,
.    and instead applies an abstract domain to the function (such as infinite sets).
.  - 'D' (bits 0-5): An integer (0-31) that indicates what type of set the domain
.                    contains. This can be a finite set stored inside of a matrix
.                    object (different columns indicate different parameters in the
.                    function), or a built-in, well-ordered, infinite, set.
.  - 'wxyzabc' (bits 6-12): These bits indicate which parameters to change for and
.                           input into the function, anything not indicated will be
.                           either outputted by the function or ignored, the function
.                           can also choose to ignore any of the parameters indicated
.                           based on its in-built dimensionality.
.  - 'R' (bit 12): Indicates whether to reverse the known order of the set. */
typedef enum _CLDIDOMAINESC
{ //                                   R wxyzabc D
	CLDI_FINITE_DOMAIN    = 0, //      0 0000000 00000
	CLDI_DOMAINESC_NULL   = CLDI_FINITE_DOMAIN,

	CLDI_REPEATED_DOMAIN  = 1, //      0 0000000 00001
	CLDI_CONSTANT_DOMAIN  = CLDI_REPEATED_DOMAIN,

	CLDI_N_DOMAIN         = 2, //      0 0000000 00010
	CLDI_DOMAIN_NATURAL   = CLDI_N_DOMAIN,

	CLDI_Z_DOMAIN         = 3, //      0 0000000 00011
	CLDI_DOMAIN_INTEGERS  = CLDI_Z_DOMAIN,

	CLDI_Q_DOMAIN         = 4, //      0 0000000 00100
	CLDI_DOMAIN_RATIONAL  = CLDI_Q_DOMAIN,

	CLDI_R_DOMAIN         = 5, //      0 0000000 00101
	CLDI_DOMAIN_REAL      = CLDI_R_DOMAIN,

	CLDI_C_DOMAIN         = 6, //      0 0000000 00110
	CLDI_DOMAIN_COMPLEX   = CLDI_C_DOMAIN,

	CLDI_P_DOMAIN         = 7, //      0 0000000 00111
	CLDI_DOMAIN_PRIME     = CLDI_P_DOMAIN,

	CLDI_D_DOMAIN         = 8, //      0 0000000 01000
	CLDI_DOMAIN_COMPOSITE = CLDI_D_DOMAIN,

	CLDI_2N_DOMAIN        = 9, //      0 0000000 01001
	CLDI_DOMAIN_EVEN      = CLDI_2N_DOMAIN,

	CLDI_2NP1_DOMAIN      = 10, //     0 0000000 01010
	CLDI_DOMAIN_ODD       = CLDI_2NP1_DOMAIN,

	CLDI_DOMAINTYPE_MASK  = 0x1f, //   0 0000000 11111

	CLDI_W_DOMAIN         = 0x800, //  0 1000000 00000
	CLDI_X_DOMAIN         = 0x400, //  0 0100000 00000
	CLDI_Y_DOMAIN         = 0x200, //  0 0010000 00000
	CLDI_Z_DOMAIN         = 0x100, //  0 0001000 00000
	CLDI_A_DOMAIN         = 0x80, //   0 0000100 00000
	CLDI_B_DOMAIN         = 0x40, //   0 0000010 00000
	CLDI_C_DOMAIN         = 0x20, //   0 0000001 00000

	CLDI_DOMAINPARAM_MASK = 0xfe0, //  0 1111111 00000

	CLDI_REVERSE_DOMAIN   = 0x1000, // 1 0000000 00000
} CLDI_DOMAIN_ESCCODE; 

/* Vector Domain type */
typedef struct _CLDIDOMAIN
{
	cldimatrix_t domain;
	cldiiterc_t  iter;
	char        _paramc, _paramspec;
} cldidomain_t;

/* Methods associated with Vector Domains: */

/* Construct as a null instance. */
CLDISTAT cldiInitDomain(cldidomain_t *self) CLDINOEXCEPT;
/* Construct the domain using a matrix of values.
.  - Column 1: Values for `w`. // NOTE: If flags (and subsequently, the `paramc` 
.  - Column 2: Values for `x`. // (parameter count) member) specify the absence
.  - Column 3: Values for `y`. // of any of the supported 7 domain parameters,
.  - Column 4: Values for `z`. // the column counts will be adjusted accordingly,
.  - Column 5: Values for `a`. // so that no empty, unnecessary columns are created.
.  - Column 6: Values for `b`.
.  - Column 7: Values for `c`.
.  - Row 0: Casted 'Domain-type' escape codes for columns 1-7.
.  - Row 1: Values (if any) from previous iteration.
.  - Row 2: Mirrored values (if any) from previous iteration.
.  - Row 3+: All domain values for operation.  */
CLDISTAT cldiInitDomainValues(cldidomain_t *self, const cldimatrix_t *fill_values);
/* Construct using explicit flags (See CLDI_DOMAIN_ESCCODE). */
CLDISTAT cldiInitDomainValuesEx(cldidomain_t *self, const cldimatrix_t *fill_values, int flags);
/* Construct as a copy of another domain. */
CLDISTAT cldiInitDomainCopy(cldidomain_t *self, const cldidomain_t *copy_of);
/* Construct by borrowing another domain. */
CLDISTAT cldiInitDomainBorrowed(cldidomain_t *self, const cldidomain_t *borrow);
/* Construct with a preallocated amount of rows. */
CLDISTAT cldiInitDomainEmpty(cldidomain_t *self, size_t rowcount);
// - Specify explicit flags.
CLDISTAT cldiInitDomainEmptyEx(cldidomain_t *self, size_t rowcount, int flags);

/* Reinitialize a domain object, do not use these methods EVER unless they've
.  already been initialized using one of the above Init() methods. */
CLDISTAT cldiRefactorDomain(cldidomain_t *self);
CLDISTAT cldiRefactorDomainValues(cldidomain_t *self, const cldimatrix_t *fill_values);
CLDISTAT cldiRefactorDomainValuesEx(cldidomain_t *self, const cldimatrix_t *fill_values, int flags);
CLDISTAT cldiRefactorDomainCopy(cldidomain_t *self, const cldidomain_t *copy_of);
CLDISTAT cldiRefactorDomainBorrowed(cldidomain_t *self, const cldidomain_t *borrow);
CLDISTAT cldiRefactorDomainEmpty(cldidomain_t *self, size_t rowcount);
CLDISTAT cldiRefactorDomainEmptyEx(cldidomain_t *self, size_t rowcount, int flags);

/* Allocate a new domain object in the heap. */
cldimemref cldiNewDomain();
cldimemref cldiNewDomainValues(const cldimatrix_t *fill_values);
cldimemref cldiNewDomainValuesEx(const cldimatrix_t *fill_values, int flags);
cldimemref cldiNewDomainCopy(const cldidomain_t *copy_of);
cldimemref cldiNewDomainBorrowed(const cldidomain_t *borrow);
cldimemref cldiNewDomainEmpty(size_t rowcount);
cldimemref cldiNewDomainEmptyEx(size_t rowcount, int flags);

/* Drop the domain. */
CLDISTAT cldiDropDomain(cldidomain_t *self);

/* Add a value into the domain at a given row index, in a given column. */
CLDISTAT cldiDomainAddValue(cldidomain_t *self, size_t row, size_t col, cldifpm_t value);
/* Add multiple values, equaling one given value, starting at a certain row, to a given column. */
CLDISTAT cldiDomainAddRepeatVals(cldidomain_t *self, size_t row, size_t col, size_t n, cldifpm_t value);
/* Add multiple values, starting at a certain row, to a given column. */
CLDISTAT cldiDomainAddValues(cldidomain_t *self, size_t row, size_t col, size_t n, const cldifpm_t *value);
/* Add a row to the domain (each value in the array will be in a new column). If the array is larger
.  than the column count, excessive values will be ignored. If the array is smaller than the column
.  count, however, the trailing values in the newly added row will be 0. */
CLDISTAT cldiDomainAddRow(cldidomain_t *self, size_t row, size_t n, const cldifpm_t *values);
/* Add a row to the domain with each cell being equal to a given value. */
CLDISTAT cldiDomainAddRepeatRow(cldidomain_t *self, size_t row, cldifpm_t value);
/* Add a row (complete with domain type) to the matrix at a certain row number.
.  For each bit in `column_nature` that indicates a domain parameter (domain parameters are concurrent
.  values like `x`, `y`, `a`, `b`, etc. that change or don't change as a function traverses the domain,
.  and they each own their own individual columns in the domain's in-built matrix of values), create
.  a column for that parameter if is doesn't already exist, and set the domain type (finite, all natural
.  numbers, all prime numbers, etc.) of each specified column to the which is specified inside of the
.  domain-type indicator bits inside of `column_nature`. */
CLDISTAT cldiDomainAddColumn(cldidomain_t *self, int column_nature);
/* For each parameter specified by bit in `column_spec`, set values to a repetition of one particular
.  value. */
CLDISTAT cldiDomainAddRepeatColumn(cldidomain_t *self, int column_spec, cldifpm_t val);
/* For each parameter specified by bit in `column_spec`, set values to a repetition of one particular
.  value. */
CLDISTAT cldiDomainAddRepeatColumn(cldidomain_t *self, int column_spec, cldifpm_t val);

/* Add a value into the domain just after a given row, in a given column. */
CLDISTAT cldiDomainSetValue(cldidomain_t *self, size_t row, size_t col, cldifpm_t value);
/* Add multiple values, equaling one given value, starting at a certain row, to a given column. */
CLDISTAT cldiDomainSetRepeatVals(cldidomain_t *self, size_t row, size_t col, size_t n, cldifpm_t value);
/* Set multiple values in the domain inside of a given column, starting at a
.  given row, to a given set of values of n length. */
CLDISTAT cldiDomainSetValues(cldidomain_t *self, size_t row, size_t col, size_t n, const cldifpm_t *value);
/* Set the values in a row in the domain (each value in the array will be in a new column). If the
.  array is larger than the column count, excessive values will be ignored. If the array is smaller than the column
.  count, however, values after the end will not be modified. */
CLDISTAT cldiDomainSetRow(cldidomain_t *self, size_t row, size_t n, const cldifpm_t *value);
/* Set each cell in a row in the domain equal to a given value. */
CLDISTAT cldiDomainSetRepeatRow(cldidomain_t *self, size_t row, cldifpm_t value);
/* Clear the whole domain. */
CLDISTAT cldiDomainClearAll(cldidomain_t *self);

/* Execute a graphing function within the domain, returns all points in a matrix,
.  columns act as different parameters to each point, and different rows act as
.  seperate points. */
// - 2-Dimensional
cldimatrix_t cldiFuncInDomain2D(const cldidomain_t *domain, cldigfunc2d_t func);
// - 3-Dimensional
cldimatrix_t cldiFuncInDomain3D(const cldidomain_t *domain, cldigfunc3d_t func);
// - 4-Dimensional
cldimatrix_t cldiFuncInDomain4D(const cldidomain_t *domain, cldigfunc4d_t func);



#ifdef __cplusplus
}
#endif

#endif // _cldi_head__math_DOMAIN_H
