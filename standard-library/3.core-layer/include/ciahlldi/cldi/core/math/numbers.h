
#ifndef _cldi_core__math_NUMBERS_H
#define _cldi_core__math_NUMBERS_H 1

/* Setup CLDI module "core" */
#include "../setup.h"

/* Requires: cldi-portable: types */
#include <ciahlldi/cldi/portable/types.h>

#ifdef __cplusplus
extern "C" {
#endif



/* ----------------------------------- */
/* Number Type (`CLDI_NUMTYPE`) */

	typedef enum _CLDI_NUMTYPE_T
	{
		/* Null, no value */
		CLDI_NUMTYPE_NONE               = (char) 0,
		CLDI_NUMTYPE_NULL               = CLDI_NUMTYPE_NONE,
		CLDI_NUMTYPE_NO_VALUE           = CLDI_NUMTYPE_NONE,
		CLDI_NUMTYPE_BLANK              = CLDI_NUMTYPE_NONE,
		CLDI_NUMTYPE_EMPTY              = CLDI_NUMTYPE_NONE,

		/* Not a number (NaN). */
		CLDI_NUMTYPE_NAN                = (char) -1,
		CLDI_NUMTYPE_NaN                = CLDI_NUMTYPE_NAN,
		CLDI_NUMTYPE_Nan                = CLDI_NUMTYPE_NAN, /* in case you mess up! :) */
		CLDI_NUMTYPE_INVALID            = CLDI_NUMTYPE_NAN,

		/* Whole number, rational integer. */
		CLDI_NUMTYPE_WHOLE              = (char) 1,
		CLDI_NUMTYPE_INT                = CLDI_NUMTYPE_WHOLE,
		CLDI_NUMTYPE_INTEGER            = CLDI_NUMTYPE_WHOLE,
		/* Size value amount. */
		CLDI_NUMTYPE_SIZE               = 4,
		CLDI_NUMTYPE_SIZE_T             = CLDI_NUMTYPE_SIZE,
		/* Floating-point number (coefficient+fractional amount) */
		CLDI_NUMTYPE_FLOAT              = (char) 2,
		CLDI_NUMTYPE_RATIONAL           = CLDI_NUMTYPE_FLOAT,

		/* Number is irrational. */
		CLDI_NUMTYPE_IRRATIONAL         = (char) -2,

		/* Number is uncountably infinite. */
		CLDI_NUMTYPE_INF                = (char) -3,
		CLDI_NUMTYPE_INFINITE           = CLDI_NUMTYPE_INF,
		CLDI_NUMTYPE_INFINITY           = CLDI_NUMTYPE_INF,
	} CLDI_NUMTYPE, CLDI_NUMTYPE_T;

	/* Sign type */
	typedef enum _CLDI_NUMSIGN_T
	{
		/* Signed number with a negative sign. */
		CLDI_NUMSIGN_NEG      = (char) 0,
		CLDI_NUMSIGN_NEGATIVE = CLDI_NUMSIGN_NEG,

		/* Signed number with a positive sign (or signed zero). */
		CLDI_NUMSIGN_POS      = (char) 1,
		CLDI_NUMSIGN_POSITIVE = CLDI_NUMSIGN_POS,

		/* Specify number as an unsigned value. */
		CLDI_NUM_UNSIGNED     = (char) 2,
		CLDI_NUMSIGN_UNSIGNED = CLDI_NUM_UNSIGNED,
		CLDI_NUMSIGN_NONE     = CLDI_NUM_UNSIGNED,
	} CLDI_NUMSIGN, CLDI_NUMSIGN_T;

	/* Division types to pass as a signal to division methods. */
	typedef enum _CLDI_DIVTYPE_T
	{
		/* Assume the division from the arguments that were passed. */
		CLDI_DIVTYPE_ASSUME,
		CLDI_DIVTYPE_DEFAULT = CLDI_DIVTYPE_ASSUME,

		/* Discard the remainder, leaving a floored result. */
		CLDI_DIVTYPE_FLOOR,

		/* Compensate for the remainder by adding one to the result. */
		CLDI_DIVTYPE_CEIL,
		CLDI_DIVTYPE_CEILING = CLDI_DIVTYPE_CEIL,

		/* Round up or down based on the arguments. */
		CLDI_DIVTYPE_ROUND,
	} CLDI_DIVTYPE, CLDI_DIVTYPE_T;

	/* Maximum size floating-point type (either double or extended). */
	typedef double cldifloatmax_t;


/* ----------------------------------- */
/* Number Value (`cldiNum`) */

	typedef struct _cldiNum_t
	{
		cldishalf type;
		cldishalf sign;

		unsigned long long higher_bits;
		unsigned long long raw_value;
	} cldiNum, cldiNum_t;

	/* Various cldiNum Constants */

	extern const cldiNum CLDINUM_NULL;
		/* Null state for cldiNum */
	extern const cldiNum CLDINUM_NAN;
	#define CLDINUM_NaN  CLDINUM_NAN
	#define CLDINUM_Nan  CLDINUM_NAN
		/* NaN value */
	extern const cldiNum     CLDINUM_INF;
	#define CLDINUM_INFINITE CLDINUM_INF
	#define CLDINUM_INFINITY CLDINUM_INF
		/* Infinity value ('upper limit has been surpassed' state) */
	extern const cldiNum     CLDINUM_ZERO;
	extern const cldiNum     CLDINUM_ZERO_UNSIGNED;
	#define   CLDINUM_ZERO_U CLDINUM_ZERO_UNSIGNED
		/* Absolute zero in signed and positive form, or in unsigned form. */
	extern const cldiNum CLDINUM_PI;
		/* Pi in cldiNum form. */
	extern const cldiNum CLDINUM_E;
	#define CLDINUM_EULER CLDINUM_E
		/* Euler's constant (e) in cldiNum form. */

	/* Make (unsigned) from an unsigned size value. */
	cldiNum cldiNum_MakeSize  (size_t value);
	/* Make from a signed size value. */
	cldiNum cldiNum_MakeSSize (ssize_t value);
	/* Make from a whole number (unsigned). */
	cldiNum cldiNum_MakeWholeUnsigned(uintmax_t value);
	/* Make from a whole number (signed). */
	cldiNum cldiNum_MakeWhole (intmax_t value);
	/* Make from a long. */
	cldiNum cldiNum_MakeLong  (long value);
	/* Make from an int. */
	cldiNum cldiNum_MakeInt   (int value);
	/* Make from a short. */
	cldiNum cldiNum_MakeShort (short value);
	/* Make from a single-byte `char`. */
	cldiNum cldiNum_MakeByte  (char value);
	/* Make from a float. */
	cldiNum cldiNum_MakeFloat (float value);
	/* Make from a double-precision float. */
	cldiNum cldiNum_MakeDouble(double value);
	/* Make from a maximum-size floating-point number. */
	cldiNum cldiNum_MakeExtended(cldifloatmax_t value);

	/* Make as an irrational number, storing all bits that CAN be represented
	.  as double-precision float. */
	cldiNum cldiNum_MakeIrrational(double representable_bits);
	cldiNum cldiNum_MakeExtendedIrrational(cldifloatmax_t representable_bits);


	/* --- Mathematical Operations --- */

	/* Math operations for `long` */
	/* Get the addition result using a long. */
	long    cldiNumPlusLong          (const cldiNum * self, long long  plus, bool is_unsigned);
	/* Get the addtion result using a long, but return as cldiNum. */
	cldiNum cldiGetNumPlusLong       (const cldiNum * self, long long  plus, bool is_unsigned);
	/* Add a long to this number (and return result). */
	long    cldiNumAddLong           (      cldiNum * self, long long   add, bool is_unsigned);

	/* Get the subtraction result using a long. */
	long    cldiNumMinusLong         (const cldiNum * self, long long minus, bool is_unsigned);
	/* Get the subtraction result using a long, but return as cldiNum. */
	cldiNum cldiGetNumMinusLong      (const cldiNum * self, long long minus, bool is_unsigned);
	/* Subtract a long from this number (and return result). */
	long    cldiNumSubLong           (      cldiNum * self, long long   sub, bool is_unsigned);

	/* Get the multiplication result using an long. */
	long    cldiNumTimesLong         (const cldiNum * self, long long  mult, bool is_unsigned);
	/* Get the multiplication result using an long, but return as cldiNum. */
	cldiNum cldiGetNumTimesLong      (const cldiNum * self, long long  mult, bool is_unsigned);
	/* Multiply a long with this number (and return result). */
	long    cldiNumMultLong          (      cldiNum * self, long long  mult, bool is_unsigned);

	/* Get the division result using an long. */
	long    cldiNumDivLong           (const cldiNum * self, long long   div);
	/* Get the division result using an long, but return as cldiNum. */
	cldiNum cldiGetNumDivLong        (const cldiNum * self, long long   div);
	/* Divide a long by this number (and return result). */
	long    cldiNumDivByLong         (      cldiNum * self, long long   div);

	/* Get the division result using a float and using a rounding type. */
	float   cldiNumAutoDivLong       (const cldiNum * self, long long   div, CLDI_DIVTYPE rounding_type);
	/* Get the division result using a float, but return as cldiNum, using a rounding type. */
	cldiNum cldiGetNumAutoDivLong    (const cldiNum * self, long long   div, CLDI_DIVTYPE rounding_type);
	/* Divide a float by this number using a rounding type, return result. */
	float   cldiNumAutoDivideByLong  (      cldiNum * self, long long   div, CLDI_DIVTYPE rounding_type);

	/* Math operations for `int` */
	/* Get the addition result using an int. */
	int     cldiNumPlusInt           (const cldiNum * self, int  plus, bool is_unsigned);
	/* Get the addtion result using an int, but return as cldiNum. */
	cldiNum cldiGetNumPlusInt        (const cldiNum * self, int  plus, bool is_unsigned);
	/* Add an int to this number (and return result). */
	int     cldiNumAddInt            (      cldiNum * self, int   add, bool is_unsigned);

	/* Get the subtraction result using an int. */
	int     cldiNumMinusInt          (const cldiNum * self, int minus, bool is_unsigned);
	/* Get the subtraction result using an int, but return as cldiNum. */
	cldiNum cldiGetNumMinusInt       (const cldiNum * self, int minus, bool is_unsigned);
	/* Subtract an int from this number (and return result). */
	int     cldiNumSubInt            (      cldiNum * self, int   sub, bool is_unsigned);

	/* Get the multiplication result using an int. */
	int     cldiNumTimesInt          (const cldiNum * self, int  mult, bool is_unsigned);
	/* Get the multiplication result using an int, but return as cldiNum. */
	cldiNum cldiGetNumTimesInt       (const cldiNum * self, int  mult, bool is_unsigned);
	/* Multiply an int with this number (and return result). */
	int     cldiNumMultInt           (      cldiNum * self, int  mult, bool is_unsigned);

	/* Get the division result using an int. */
	int     cldiNumDivInt            (const cldiNum * self, int   div);
	/* Get the division result using an int, but return as cldiNum. */
	cldiNum cldiGetNumDivInt         (const cldiNum * self, int   div);
	/* Divide an int by this number (and return result). */
	int     cldiNumDivideByInt       (      cldiNum * self, int   div);

	/* Get the division result using a float and using a rounding type. */
	float   cldiNumAutoDivInt        (const cldiNum * self, int   div, CLDI_DIVTYPE rounding_type);
	/* Get the division result using a float, but return as cldiNum, using a rounding type. */
	cldiNum cldiGetNumAutoDivInt     (const cldiNum * self, int   div, CLDI_DIVTYPE rounding_type);
	/* Divide a float by this number using a rounding type, return result. */
	float   cldiNumAutoDivideByInt   (      cldiNum * self, int   div, CLDI_DIVTYPE rounding_type);

	/* Math operations for `short` */
	/* Get the addition result using an short. */
	short   cldiNumPlusShort         (const cldiNum * self, short int  plus, bool is_unsigned);
	/* Get the addtion result using an short, but return as cldiNum. */
	cldiNum cldiGetNumPlusShort      (const cldiNum * self, short int  plus, bool is_unsigned);
	/* Add a short to this number, return result. */
	short   cldiNumAddShort          (      cldiNum * self, short int   add, bool is_unsigned);

	/* Get the subtraction result using an short. */
	short   cldiNumMinusShort        (const cldiNum * self, short int minus, bool is_unsigned);
	/* Get the subtraction result using an short, but return as cldiNum. */
	cldiNum cldiGetNumMinusShort     (const cldiNum * self, short int minus, bool is_unsigned);
	/* Subtract a short from this number, return result. */
	short   cldiNumSubShort          (      cldiNum * self, short int   sub, bool is_unsigned);

	/* Get the multiplication result using an short. */
	short   cldiNumTimesShort        (const cldiNum * self, short int  mult, bool is_unsigned);
	/* Get the multiplication result using an short, but return as cldiNum. */
	cldiNum cldiGetNumTimesShort     (const cldiNum * self, short int  mult, bool is_unsigned);
	/* Multiply a short with this number, return result. */
	short   cldiNumMultShort         (      cldiNum * self, short int  mult, bool is_unsigned);

	/* Get the division result using an short. */
	short   cldiNumDivShort          (const cldiNum * self, short int   div);
	/* Get the division result using an short, but return as cldiNum. */
	cldiNum cldiGetNumDivShort       (const cldiNum * self, short int   div);
	/* Divide a short by this number, return result. */
	short   cldiNumDivideByShort     (      cldiNum * self, short int   div);

	/* Get the division result using a float and using a rounding type. */
	float   cldiNumAutoDivShort      (const cldiNum * self, short int   div, CLDI_DIVTYPE rounding_type);
	/* Get the division result using a float, but return as cldiNum, using a rounding type. */
	cldiNum cldiGetNumAutoDivShort   (const cldiNum * self, short int   div, CLDI_DIVTYPE rounding_type);
	/* Divide a float by this number using a rounding type, return result. */
	float   cldiNumAutoDivideByShort (      cldiNum * self, short int   div, CLDI_DIVTYPE rounding_type);

	/* Math operations for `char` */
	/* Get the addition result using a single-byte char. */
	char    cldiNumPlusByte          (const cldiNum * self, char  plus, bool is_unsigned);
	/* Get the addtion result using a char, but return as cldiNum. */
	cldiNum cldiGetNumPlusByte       (const cldiNum * self, char  plus, bool is_unsigned);
	/* Add a char to this number, return result. */
	char    cldiNumAddByte           (      cldiNum * self, char   add, bool is_unsigned);

	/* Get the subtraction result using a single-byte char. */
	char    cldiNumMinusByte         (const cldiNum * self, char minus, bool is_unsigned);
	/* Get the subtraction result using a char, but return as cldiNum. */
	cldiNum cldiGetNumMinusByte      (const cldiNum * self, char minus, bool is_unsigned);
	/* Subtract a char from this number, return result. */
	char    cldiNumSubByte           (      cldiNum * self, char   sub, bool is_unsigned);

	/* Get the multiplication result using a single-byte char. */
	char    cldiNumTimesByte         (const cldiNum * self, char  mult, bool is_unsigned);
	/* Get the multiplication result using a char, but return as cldiNum. */
	cldiNum cldiGetNumTimesByte      (const cldiNum * self, char  mult, bool is_unsigned);
	/* Multiply a char with this number, return result. */
	char    cldiNumMultByte          (      cldiNum * self, char  mult, bool is_unsigned);

	/* Get the division result using a single-byte char. */
	char    cldiNumDivByte           (const cldiNum * self, char   div);
	/* Get the division result using a char, but return as cldiNum. */
	cldiNum cldiGetNumDivByte        (const cldiNum * self, char   div);
	/* Divide a char by this number, return result. */
	char    cldiNumDivideByByte      (      cldiNum * self, char   div);

	/* Get the division result using a float and using a rounding type. */
	float   cldiNumAutoDivByte       (const cldiNum * self, char   div, CLDI_DIVTYPE rounding_type);
	/* Get the division result using a float, but return as cldiNum, using a rounding type. */
	cldiNum cldiGetNumAutoDivByte    (const cldiNum * self, char   div, CLDI_DIVTYPE rounding_type);
	/* Divide a float by this number using a rounding type, return result. */
	float   cldiNumAutoDivideByByte  (      cldiNum * self, char   div, CLDI_DIVTYPE rounding_type);

	/* Math operations for `float` */
	/* Get the addition result using a float. */
	float   cldiNumPlusFloat              (const cldiNum * self, float  plus);
	/* Get the addtion result using a float, but return as cldiNum. */
	cldiNum cldiGetNumPlusFloat           (const cldiNum * self, float  plus);
	/* Add a float to this number, return result. */
	float   cldiNumAddFloat               (      cldiNum * self, float   add);

	/* Get the subtraction result using a float. */
	float   cldiNumMinusFloat             (const cldiNum * self, float minus);
	/* Get the subtraction result using a float, but return as cldiNum. */
	cldiNum cldiGetNumMinusFloat          (const cldiNum * self, float minus);
	/* Subtract a float from this number, return result. */
	float   cldiNumSubFloat               (      cldiNum * self, float   sub);

	/* Get the multiplication result using a float. */
	float   cldiNumTimesFloat             (const cldiNum * self, float   mult);
	/* Get the multiplication result using a float, but return as cldiNum. */
	cldiNum cldiGetNumTimesFloat          (const cldiNum * self, float   mult);
	/* Multiply a float with this number, return result. */
	float   cldiNumMultFloat              (      cldiNum * self, float   mult);

	/* Get the division result using a float. */
	float   cldiNumDivFloat               (const cldiNum * self, float   mult);
	/* Get the division result using a float, but return as cldiNum. */
	cldiNum cldiGetNumDivFloat            (const cldiNum * self, float   mult);
	/* Divide a float by this number, return result. */
	float   cldiNumDivideByFloat          (      cldiNum * self, float   mult);

	/* Get the division result using a float and using a rounding type. */
	float   cldiNumAutoDivFloat           (const cldiNum * self, float div, CLDI_DIVTYPE rounding_type);
	/* Get the division result using a float, but return as cldiNum, using a rounding type. */
	cldiNum cldiGetNumAutoDivFloat        (const cldiNum * self, float div, CLDI_DIVTYPE rounding_type);
	/* Divide a float by this number using a rounding type, return result. */
	float   cldiNumAutoDivideByFloat      (      cldiNum * self, float div, CLDI_DIVTYPE rounding_type);

	/* Math operations for `double` */
	/* Get the addition result using a double-precision float. */
	double  cldiNumPlusDouble             (const cldiNum * self, double  plus);
	/* Get the addtion result using a double, but return as cldiNum. */
	cldiNum cldiGetNumPlusDouble          (const cldiNum * self, double  plus);
	/* Add a double to this number, return result. */
	double  cldiNumAddDouble              (      cldiNum * self, double   add);

	/* Get the subtraction result using a double-precision float. */
	double  cldiNumMinusDouble            (const cldiNum * self, double minus);
	/* Get the subtraction result using a double, but return as cldiNum. */
	cldiNum cldiGetNumMinusDouble         (const cldiNum * self, double minus);
	/* Subtract a double from this number, return result. */
	double  cldiNumSubDouble              (      cldiNum * self, double   sub);

	/* Get the multiplication result using a double-precision float. */
	double  cldiNumTimesDouble            (const cldiNum * self, double  mult);
	/* Get the multiplication result using a double, but return as cldiNum. */
	cldiNum cldiGetNumTimesDouble         (const cldiNum * self, double  mult);
	/* Multiply a double with this number, return result. */
	double  cldiNumMultDouble             (      cldiNum * self, double  mult);

	/* Get the division result using a double-precision float. */
	double  cldiNumDivDouble              (const cldiNum * self, double   div);
	/* Get the division result using a double, but return as cldiNum. */
	cldiNum cldiGetNumDivDouble           (const cldiNum * self, double   div);
	/* Divide a double by this number, return result. */
	double  cldiNumDivideByDouble         (      cldiNum * self, double   div);

	/* Get the division result using a double-precision float and using a rounding type. */
	double  cldiNumAutoDivDouble          (const cldiNum * self, double div, CLDI_DIVTYPE rounding_type);
	/* Get the division result using a double, but return as cldiNum, using a rounding type. */
	cldiNum cldiGetNumAutoDivDouble       (const cldiNum * self, double div, CLDI_DIVTYPE rounding_type);
	/* Divide a double by this number using a rounding type, return result. */
	double  cldiNumAutoDivideByDouble     (      cldiNum * self, double div, CLDI_DIVTYPE rounding_type);

	/* Math operations for `cldifloatmax_t` ("extended float" or double) */
	/* Get the addition result using a double-precision float. */
	cldifloatmax_t cldiNumPlusExtended    (const cldiNum * self, cldifloatmax_t  plus);
	/* Get the addtion result using a double, but return as cldiNum. */
	cldiNum        cldiGetNumPlusExtended (const cldiNum * self, cldifloatmax_t  plus);
	/* Add a double to this number, return result. */
	cldifloatmax_t cldiNumAddExtended     (      cldiNum * self, cldifloatmax_t   add);

	/* Get the subtraction result using a double-precision float. */
	cldifloatmax_t cldiNumMinusExtended   (const cldiNum * self, cldifloatmax_t minus);
	/* Get the subtraction result using a double, but return as cldiNum. */
	cldiNum        cldiGetNumMinusExtended(const cldiNum * self, cldifloatmax_t minus);
	/* Subtract a double from this number, return result. */
	cldifloatmax_t cldiNumSubExtended     (      cldiNum * self, cldifloatmax_t   sub);

	/* Get the multiplication result using a double-precision float. */
	cldifloatmax_t cldiNumTimesExtended   (const cldiNum * self, cldifloatmax_t  mult);
	/* Get the multiplication result using a double, but return as cldiNum. */
	cldiNum        cldiGetNumTimesExtended(const cldiNum * self, cldifloatmax_t  mult);
	/* Multiply a double with this number, return result. */
	cldifloatmax_t cldiNumMultExtended    (      cldiNum * self, cldifloatmax_t  mult);

	/* Get the division result using a double-precision float. */
	cldifloatmax_t cldiNumDivExtended     (const cldiNum * self, cldifloatmax_t   div);
	/* Get the division result using a double, but return as cldiNum. */
	cldiNum        cldiGetNumDivExtended  (const cldiNum * self, cldifloatmax_t   div);
	/* Divide a double by this number, return result. */
	cldifloatmax_t cldiNumDivByExtended   (      cldiNum * self, cldifloatmax_t   div);

/* Number Pair Type (cldiNumPair) */

	typedef struct _cldiNumPair_t
	{
		cldiNum x, y;
	}
	cldiNumPair, cldiNumPair_t;


	/* Null value for cldiNum */
	extern const cldiNumPair CLDINUMPAIR_NULL;
	/* Default double-zero origin point */
	extern const cldiNumPair CLDINUMPAIR_DEFAULT_ORIGIN;


/* ----------------------------------- */
/* Number Set Data Bits (`CLDI_NUMSETDATA`) */

	typedef enum _CLDI_NUMSETDATA_T
	{
		/* Default data setting. */
		CLDI_NUMSETDATA_DEFAULT = (int) 0,

		/* Type structure itself is known to be heap allocated (specifically not by
		.  `new`, and will not be freed by `delete` awareness of when those keywords
		.  will be called and when they wont MUST be maintained or the type will not
		.  be safe). */
		CLDI_NUMSETDATA_HEAP_ALLOCATED = (int) 0x0001,
	}
	CLDI_NUMSET_DATA,
	CLDI_NUMSETDATA,
	CLDI_NUMSET_DATA_T,
	CLDI_NUMSETDATA_T;


/* Const Number Set (`cldiConstNumset`) */

	typedef struct _cldiConstNumset_t
	{
		/* Information to store about this type for later interactions, use
		.  bit values from CLDI_NUMSETDATA. */
		cldihalf data;

		/* The array of numbers to store as the address. */
		const cldiNum *const address;

		/* The total amount of values in the set. */
		const size_t     size;
	} cldiConstNumset, cldiConstNumset_t;

	/* Null value for this structure: */
	extern const cldiConstNumset CLDICONSTNUMSET_NULL;

	/* Drop and release this structure from use in the current context. */
	bool cldiConstNumset_Drop(cldiConstNumset * self);

	/* Initialize with a new set. */
	bool cldiConstNumset_InitNewSet(
		cldiConstNumset * self,
		size_t        set_size,
			/* The size of the set that to make a private copy of. */
		const cldiNum   * set
			/* The set to copy. */
	);
	/* Initialize shared with pre-existing state through it's address. */
	bool cldiConstNumset_InitShared(
		cldiConstNumset * self,
		const cldiNum   * set_state_address
			/* The address of the state to sign onto / reference. */
	);


/* Number Set (`cldiNumset`) */

	typedef struct _cldiNumset_t
	{
		const cldiConstNumset origin;

		cldiNum  * modifiable_address;

		size_t set_size;

		cldihalf   data;
	} cldiNumset, cldiNumset_t;

	/* Null value for this structure. */
	extern const cldiNumset CLDINUMSET_NULL;

	/* Drop and release this structure from use in the current context. */
	bool cldiNumset_Drop(cldiNumset * self);


	/* Initialize this structure from a raw array. */
	bool cldiNumset_InitFromArray(
		cldiNumset    * self,
		size_t      array_length,
			/* The amount of cldiNum structure values there are in the passed array. */
		const cldiNum * array
			/* The array of cldiNum structures to copy from. */
	);

	/* - Initialize from an array of `float`s. */
	bool cldiNumset_InitFromFloatArray(
		cldiNumset * self,
		size_t, const float *
			/* Same 2 arguments as from InitFromArray(), but float* instead
			.  of cldiNum*. */
	);
	/* - Initialize from an array of double-precision floats (`double`s). */
	bool cldiNumset_InitFromDoubleArray(
		cldiNumset * self,
		size_t, const double *
			/* Same 2 arguments as from InitFromArray(), but double* instead
			.  of cldiNum*. */
	);

	/* - Initialize from an array of size values (`size_t`). */
	bool cldiNumset_InitFromSizeArray(
		cldiNumset * self,
		size_t, const size_t *
			/* Same 2 arguments as from InitFromArray(), but size_t*
			.  instead of cldiNum*. */
	);
	/* - Initialize from an array of signed size values (`ssize_t`). */
	bool cldiNumset_InitFromSSizeArray(
		cldiNumset * self,
		size_t, const ssize_t *
			/* Same 2 arguments as from InitFromArray(), but ssize_t*
			.  instead of cldiNum*. */
	);
	/* - Initialize from an array of `long`s. */
	bool cldiNumset_InitFromLongArray(
		cldiNumset * self,
		size_t, const long *
			/* Same 2 arguments as from InitFromArray(), but long* instead
			.  of cldiNum*. */
	);
	/* - Initialize from an array of `int`s */
	bool cldiNumset_InitFromIntArray(
		cldiNumset * self,
		size_t, const int *
			/* Same 2 arguments as from InitFromArray(), but int* instead
			.  of cldiNum*. */
	);
	/* - Initialize from an array of `short`s */
	bool cldiNumset_InitFromShortArray(
		cldiNumset * self,
		size_t, const short *
			/* Same 2 arguments as from InitFromArray(), but short* instead
			.  of cldiNum*. */
	);
	/* - Initialize from array of single-byte `char`s. */
	bool cldiNumset_InitFromByteArray(
		cldiNumset * self,
		size_t, const char *
			/* Same 2 arguments as from InitFromArray(), but char* instead
			.  of cldiNum*. */
	);


/* ----------------------------------- */
/* 2D Numset type (cldiPairSet, cldiNumset2D) */

	/* Static PairSet type */
	typedef struct _cldiConstPairSet_t
	{
		const cldihalf data;

		const cldiNumPair *const address;
		const size_t         length;
	} cldiConstPairSet, cldiConstPairSet_t;

	typedef struct _cldiPairSet_t
	{
		cldiConstPairSet origin;

		cldiNumPair * modifiable_state_address;
		size_t    current_length;
	} cldiPairSet, cldiPairSet_t;


/* ----------------------------------- */
/* Vector Set or 2D Numset type (cldiVecSet, cldiVectorSet, cldiNumset2D) */

	/* Static VectorSet type */
	typedef struct _cldiConstVecSet_t
	{
		const cldihalf data;

		const cldiConstNumset *const address;
		const size_t             length;
	}
	cldiConstVecSet,    cldiConstVecSet_t,
	cldiConstVectorSet, cldiConstVectorSet_t,
	cldiConstNumset2D,  cldiConstNumset2D_t;

	typedef struct _cldiVecSet_t
	{
		cldiConstVecSet origin;

		cldiConstNumset * modifiable_state_address;
		size_t        current_length;
	}
	cldiVecSet,    cldiVecSet_t,
	cldiVectorSet, cldiVectorSet_t,
	cldiNumset2D,  cldiNumset2D_t;


/* ----------------------------------- */



#ifdef __cplusplus
}

namespace ciahlldi
{
	namespace cldi
	{
		namespace core
		{
			namespace types
			{
				/* Maximum size floating-point type (either double or extended). */
				typedef cldifloatmax_t floatmax_t;

				/* Importing division types to the C++ namespace. */
				using DIVTYPE = CLDI_DIVTYPE;

				/* For assuming the division type based on the arguments passed. */
				constexpr DIVTYPE DIVTYPE_ASSUME = CLDI_DIVTYPE_ASSUME;
				/* Division type for 'flooring' the remainder. */
				constexpr DIVTYPE DIVTYPE_FLOOR  = CLDI_DIVTYPE_FLOOR;
				/* Division type for rounding the result. */
				constexpr DIVTYPE DIVTYPE_ROUND  = CLDI_DIVTYPE_ROUND;
				/* Division type for expanding the result to account for existence
				.  of a remainder. */
				constexpr DIVTYPE DIVTYPE_CEIL   = CLDI_DIVTYPE_CEIL;
				/* Division type for fully incorporating the remainder in exact quantity
				.  by returning/converting the number to a floating-point type that can
				.  store the remainder by fraction. */
				constexpr DIVTYPE DIVTYPE_FULL   = CLDI_DIVTYPE_FULL;


				class num: protected cldiNum
				{
				public:
					/* --- Handling CLDI_NUMTYPE --- */
					using TypeFlag = CLDI_NUMTYPE;

					static constexpr TypeFlag TYPE_NONE       = CLDI_NUMTYPE_NONE;
						/* Null (imply nothing) type flag. */
					static constexpr TypeFlag TYPE_NAN        = CLDI_NUMTYPE_NAN;
						/* NaN (nonexistent value) type flag. */
					static constexpr TypeFlag TYPE_WHOLE      = CLDI_NUMTYPE_WHOLE;
						/* Whole number type flag. */
					static constexpr TypeFlag TYPE_SIZE       = CLDI_NUMTYPE_SIZE;
						/* Size (size_t or size_t) type flag. */
					static constexpr TypeFlag TYPE_RATIONAL   = CLDI_NUMTYPE_RATIONAL;
						/* Rational (fractional) number type flag. */
					static constexpr TypeFlag TYPE_IRRATIONAL = CLDI_NUMTYPE_IRRATIONAL;
						/* Irrational (repeating, endless fractional) number type flag. */
					static constexpr TypeFlag TYPE_INF        = CLDI_NUMTYPE_INF;
						/* Infinity (larger than value maximum) type flag. */

					/* And CLDI_NUMSIGN */
					using SignFlag = CLDI_NUMSIGN;

					static constexpr SignFlag POSITIVE = CLDI_NUMSIGN_POSITIVE;
						/* Positive sign flag */
					static constexpr SignFlag NEGATIVE = CLDI_NUMSIGN_NEGATIVE;
						/* Negative sign flag */
					static constexpr SignFlag UNSIGNED = CLDI_NUMSIGN_UNSIGNED;
						/* Unsigned (always positive) sign flag. */


				public:
					/* --- Constructors --- */

					num();

					static num From(num copy_value);
					static num From(cldiNum copy_value);
					static num From(const num& copy_from_ref);
					static num From(const cldiNum * copy_from_ref);

					num(size_t wrap);
					num(ssize_t wrap);
					num(long wrap,  bool is_unsigned=false);
					num(int wrap,   bool is_unsigned=false);
					num(short wrap, bool is_unsigned=false);
					num(char wrap,  bool is_unsigned=false);

					num(float wrap);
					num(double wrap);

					static num MakeIrrational(double representable_bits);

				public:
				/* --- Mathematical Operations --- */

					/* --- All Math Operations for normal integer types --- */
					long   Plus(long long plus)        const;
					int    Plus(int plus)              const;
					short  Plus(short int plus)        const;
					num    GetPlus(long long plus)     const;
					num    GetPlus(int plus)           const;
					num    GetPlus(short int plus);
					long   Add(long long add);
					int    Add(int add);
					short  Add(short int add)          const;
					long   operator +(long long plus)  const;
					int    operator +(int plus)        const;
					short  operator +(short int plus)  const;
					long   operator +=(long long add);
					int    operator +=(int add);
					short  operator +=(short int add);

					long   Minus      (long long minus) const;
					int    Minus      (int minus)       const;
					short  Minus      (short int minus) const;
					num    GetMinus   (long long minus) const;
					num    GetMinus   (int minus)       const;
					num    GetMinus   (short int minus) const;
					long   Sub        (long long sub);
					int    Sub        (int sub);
					short  Sub        (short int sub);
					long   operator - (long long minus) const;
					int    operator - (int minus)       const;
					short  operator - (short int minus) const;
					long   operator -=(long long sub);
					int    operator -=(int sub);
					short  operator -=(short int sub);

					long   MultipliedBy(long long mult) const;
					int    MultipliedBy(int mult)       const;
					short  MultipliedBy(short int mult) const;
					num    GetMultBy   (long long mult) const;
					num    GetMultBy   (int mult)       const;
					num    GetMultBy   (short int mult) const;
					long   Mult        (long long mult);
					int    Mult        (int mult);
					short  Mult        (short int mult);
					long   operator *  (long long mult) const;
					int    operator *  (int mult)       const;
					short  operator *  (short int mult) const;
					long   operator *= (long long mult);
					int    operator *= (int mult);
					short  operator *= (short int mult);

					long   Divide     (long long div, DIVTYPE floor_or_full=DIVTYPE_ASSUME) const;
					int    Divide     (int div,       DIVTYPE floor_or_full=DIVTYPE_ASSUME) const;
					short  Divide     (short int div, DIVTYPE floor_or_full=DIVTYPE_ASSUME) const;
					num    GetDivBy   (long long div, DIVTYPE floor_or_full=DIVTYPE_ASSUME) const;
					num    GetDivBy   (int div,       DIVTYPE floor_or_full=DIVTYPE_ASSUME) const;
					num    GetDivBy   (short int div, DIVTYPE floor_or_full=DIVTYPE_ASSUME) const;
					long   DivideBy   (long long div, DIVTYPE floor_or_full=DIVTYPE_ASSUME);
					int    DivideBy   (int div,       DIVTYPE floor_or_full=DIVTYPE_ASSUME);
					short  DivideBy   (short int div, DIVTYPE floor_or_full=DIVTYPE_ASSUME);
					long   operator / (long long div) const;
					int    operator / (int div)       const;
					short  operator / (short int div) const;
					long   operator /=(long long div);
					int    operator /=(int div);
					short  operator /=(short int div);

					/* --- All Math Operations for single byte integer (`char`) --- */
					char   Plus       (char plus)   const;
					num    GetPlus    (char plus)   const;
					char   Add        (char add);
					char   operator + (char plus)   const;
					char   operator +=(char add)    const;

					char   Minus       (char minus) const;
					num    GetMinus    (char minus) const;
					char   Sub         (char sub);
					char   operator -  (char minus) const;
					char   operator -= (char sub);

					char   MultipliedBy(char mult)  const;
					num    GetMultBy   (char mult)  const;
					char   Mult        (char mult);
					char   operator *  (char mult)  const;
					char   operator *= (char mult);

					char   Divide      (char div, DIVTYPE floor_or_full=DIVTYPE_ASSUME) const;
					num    GetDivBy    (char div, DIVTYPE floor_or_full=DIVTYPE_ASSUME) const;
					char   DivideBy    (char div, DIVTYPE floor_or_full=DIVTYPE_ASSUME);
					char   operator /  (char div) const;
					char   operator /= (char div);

					/* --- All Math Operations for `num` class --- */
					num    Plus        (num plus)  const;
					num    GetPlus     (num plus)  const;
					num    Add         (num add);
					num    operator +  (num plus)  const;
					num    operator += (num add);

					num    Minus       (num minus) const;
					num    GetMinus    (num minus) const;
					num    Sub         (num sub);
					num    operator -  (num minus) const;
					num    operator -= (num sub);

					num    MultipliedBy(num mult)  const;
					num    GetMultBy   (num mult)  const;
					num    Mult        (num mult);
					num    operator *  (num mult)  const;
					num    operator *= (num mult);

					num    Divide      (num div, DIVTYPE floor_or_full=DIVTYPE_ASSUME) const;
					num    GetDivBy    (num div, DIVTYPE floor_or_full=DIVTYPE_ASSUME) const;
					num    DivideBy    (num div, DIVTYPE floor_or_full=DIVTYPE_ASSUME);
					num    operator /  (num div) const;
					num    operator /= (num div);

					/* --- All Math Operation for `float` --- */
					float  Plus       (float plus)  const;
					num    GetPlus    (float plus)  const;
					float  Add        (float add);
					float  operator + (float plus)  const;
					float  operator +=(float add);

					float  Minus      (float minus) const;
					num    GetMinus   (float minus) const;
					float  Sub        (float sub);
					float  operator - (float minus) const;
					float  operator -=(float sub);

					float  MultipliedBy(float mult) const;
					num    GetMultBy   (float mult) const;
					float  Mult        (float mult);
					float  operator *  (float mult) const;
					float  operator *= (float mult);

					float  Divide     (float div, DIVTYPE floor_or_full=DIVTYPE_ASSUME) const;
					num    GetDivBy   (float div, DIVTYPE floor_or_full=DIVTYPE_ASSUME) const;
					float  DivideBy   (float div, DIVTYPE floor_or_full=DIVTYPE_ASSUME);
					float  operator / (float div) const;
					float  operator /=(float div);

					/* --- All Math Operations for `double` --- */
					double Plus       (double plus)  const;
					num    GetPlus    (double plus)  const;
					double Add        (double add);
					double operator + (double plus)  const;
					double operator +=(double add);

					double Minus      (double minus) const;
					num    GetMinus   (double minus) const;
					double Sub        (double sub);
					double operator - (double minus) const;
					double operator -=(double sub);

					double MultipliedBy(double mult) const;
					num    GetMultBy   (double mult) const;
					double Mult        (double mult);
					double operator *  (double mult) const;
					double operator *= (double mult);

					double Divide      (double div, DIVTYPE floor_or_full=DIVTYPE_ASSUME) const;
					num    GetDivBy    (double div, DIVTYPE floor_or_full=DIVTYPE_ASSUME) const;
					double DivideBy    (double div, DIVTYPE floor_or_full=DIVTYPE_ASSUME);
					double operator /  (double div) const;
					double operator /= (double div);
				};

				class numset: protected cldiNumset
				{
				protected:
					/* --- Constructors/Destuctors --- */

					numset();
					~numset();
				};
			}
		}

		using core::types::floatmax_t;

		using core::types::num;
		using core::types::numset;
	}
}

#endif

#endif /* _cldi_core__math_NUMBERS_H */
