
#pragma cldic module head:math
#ifndef _cldi_head__MATH_H
#define _cldi_head__MATH_H 1

#include "iter.h"
#pragma cldic require head:iter
#if CLDI_C_ONLY == true
#	include <math.h>
#else
#	include <cmath>
#endif



/* Float constants for math header */

#ifdef __cplusplus
#	define CLDIFPM_INF      std::numeric_limits<cldifpm_t>::infinity()
#	define CLDIFPM_INFINITY std::numeric_limits<cldifpm_t>::infinity()
#	define CLDIFPM_NAN      std::numeric_limits<cldifpm_t>::quiet_NaN()
#	define cldifpmsqrt      sqrtl
#	define cldifpmpow       powl
#else
#   define CLDIFPM_INF      (cldifpm_t)INFINITY
#	define CLDIFPM_INFINITY (cldifpm_t)INFINITY
#	define CLDIFPM_NAN      (cldifpm_t)NAN
#	define cldifpmsqrt      sqrt
#	define cldifpmpow       pow
#endif

#ifdef __cplusplus
extern "C" {
#endif


/* Enum for Special Value "Escape" Codes for Synthetic Numbers */
// 'I' (bit 0): Whether the number is considered infinity (ignores number value).
// 'N/s' (bits 1 & 2): Bit 2 (more significant) corresponds to the value being
//                     considered NaN, bit 1 (less significant, only considered
//                     when bit 2 is already 1) corresponds to that Nan value
//                     being a signaling NaN.
// 'R' (bit 3): The number's fractional portion repeats into infinity.
typedef enum _CLDINUMESC
{ //                                R N s I
	CLDI_NUMESC_NONE = 0,   // 0000 0 0 0 0
	CLDI_NUMESC_NULL = CLDI_NUMESC_NONE,

	CLDI_NUMESC_INF  = 0x1, // 0000 0 0 0 1
	CLDI_NUMESC_QNAN = 0x4, // 0000 0 1 0 0
	CLDI_NUMESC_QNaN     = CLDI_NUMESC_QNAN,
	CLDI_NUMESC_NAN      = CLDI_NUMESC_QNAN,
	CLDI_NUMESC_NaN      = CLDI_NUMESC_QNAN,
	CLDI_NUMESC_QUIETNAN = CLDI_NUMESC_QNAN,
	CLDI_NUMESC_QUIETNaN = CLDI_NUMESC_QNAN,

	CLDI_NUMESC_SNAN = 0x6, // 0000 0 1 1 0
	CLDI_NUMESC_SNaN      = CLDI_NUMESC_SNAN,
	CLDI_NUMESC_SIGNALNAN = CLDI_NUMESC_SNAN,
	CLDI_NUMESC_SIGNALNaN = CLDI_NUMESC_SNAN,

	CLDI_NUMESC_REP  = 0x8, // 0000 1 0 0 0
	CLDI_NUMESC_REPEAT = CLDI_NUMESC_REP,
} cldinumesc_t;


/* (Synthetic) Signed 128-bit Integer type */
typedef struct _CLDII28
{
	signed   long long a;
	unsigned long long b;
#if CLDI_PLATFORM32 == true
	unsigned long long c, d;
#endif
} cldii128_t, cldii128;
/* (Synthetic) Unsigned 128-bit Integer type */
typedef struct _CLDIU28
{
	unsigned long long a, b;
#if CLDI_PLATFORM32 == true
	unsigned long long c, d;
#endif
} cldiu128_t, cldiu128;
/* Methods associated with 128-bit Integers (Signed and Unsigned): */
#include "math/i128.h"


/* (Synthetic) Quadruple-Precision (128-bit) Floating Point type */
typedef struct _CLDIQUAD
{
	uint16_t exp, mantA;
	uint32_t mantB, mantC, mantD;
	int      esc;
} cldiquad_t, cldiquad;
/* Methods associated with quad-precision floats: */
#include "math/quad.h"


/* (Synthetic) Rational Number type */
typedef struct _CLDIRATIONAL
{
	signed long long num, den;
	int esc;
} cldirational_t, cldirational;

/* (Synthetic) Complex Number type */
typedef struct _CLDICOMPLEX
{
	cldifpm_t real, imag;
	int esc;
} cldicomplex_t, cldicomplex;


/* Basic Mathemical Set Functions */

// Get the sum of a set of numbers (of various types)
#define cldisum cldisumd
cldifpm_t          cldisumfm(size_t count, const cldifpm_t *array);
double             cldisumd(size_t count, const double *array);
float              cldisumf(size_t count, const float *array);
signed int         cldisumi(size_t count, const signed int *array);
unsigned int       cldisumui(size_t count, const unsigned int *array);
signed long        cldisuml(size_t count, const signed long int *array);
unsigned long      cldisumul(size_t count, const unsigned long *array);
signed long long   cldisumll(size_t count, const signed long long *array);
unsigned long long cldisumull(size_t count, const unsigned long long *array);

// Get the difference of a set of numbers (of various types)
#define cldisub cldisubd
cldifpm_t          cldisubfm(size_t count, const cldifpm_t *array);
double             cldisubd(size_t count, const double *array);
float              cldisubf(size_t count, const float *array);
signed int         cldisubi(size_t count, const signed int *array);
unsigned int       cldisubui(size_t count, const unsigned int *array);
signed long int    cldisubl(size_t count, const signed long int *array);
unsigned long      cldisubul(size_t count, const unsigned long *array);
signed long long   cldisubll(size_t count, const signed long long *array);
unsigned long long cldisubull(size_t count, const unsigned long long *array);

// Get the alternating sum of a set of numbers (of various types)
#define cldialt cldialtd
cldifpm_t          cldialtfm(size_t count, const cldifpm_t *array);
double             cldialtd(size_t count, const double *array);
float              cldialtf(size_t count, const float *array);
signed int         cldialti(size_t count, const signed int *array);
unsigned int       cldialtui(size_t count, const unsigned int *array);
signed long int    cldialtl(size_t count, const signed long int *array);
unsigned long      cldialtul(size_t count, const unsigned long *array);
signed long long   cldialtll(size_t count, const signed long long *array);
unsigned long long cldialtull(size_t count, const unsigned long long *array);

// Get the product of a set of numbers (of various types)
#define cldimul cldimuld
cldifpm_t          cldimulfm(size_t count, const cldifpm_t *array);
double             cldimuld(size_t count, const double *array);
float              cldimulf(size_t count, const float *array);
signed int         cldimuli(size_t count, const signed int *array);
unsigned int       cldimului(size_t count, const unsigned int *array);
signed long int    cldimull(size_t count, const signed long int *array);
unsigned long      cldimulul(size_t count, const unsigned long *array);
signed long long   cldimulll(size_t count, const signed long long *array);
unsigned long long cldimulull(size_t count, const unsigned long long *array);

// Get the quotient of a set of numbers (of various types)
#define cldidiv cldidivd
cldifpm_t          cldidivfm(size_t count, const cldifpm_t *array);
double             cldidivd(size_t count, const double *array);
float              cldidivf(size_t count, const float *array);

// Get the mean (average) of a set of numbers (of various types)
#define cldimean cldimeand
cldifpm_t          cldimeanfm(size_t count, const cldifpm_t *array);
double             cldimeand(size_t count, const double *array);
float              cldimeanf(size_t count, const float *array);
double             cldimeani(size_t count, const int *array);
double             cldimeanui(size_t count, const unsigned int *array);
double             cldimeanl(size_t count, const long *array);
double             cldimeanul(size_t count, const unsigned long *array);
double             cldimeanll(size_t count, const long long *array);
double             cldimeanull(size_t count, const unsigned long long *array);

// Get the median of a set of numbers (of various types)
#define cldimedian cldimediand
cldifpm_t          cldimedianfm(size_t count, const cldifpm_t *array);
double             cldimediand(size_t count, const double *array);
float              cldimedianf(size_t count, const float *array);
double             cldimediani(size_t count, const int *array);
double             cldimedianui(size_t count, const unsigned int *array);
double             cldimedianl(size_t count, const long *array);
double             cldimedianul(size_t count, const unsigned long *array);
double             cldimedianll(size_t count, const long long *array);
double             cldimedianull(size_t count, const unsigned long long *array);

// Get the mode of a set of numbers (of various types)
#define cldimode cldimoded
cldifpm_t          cldimodefm(size_t count, const cldifpm_t *array);
double             cldimoded(size_t count, const double *array);
float              cldimodef(size_t count, const float *array);
double             cldimodei(size_t count, const int *array);
double             cldimodeui(size_t count, const unsigned int *array);
double             cldimodel(size_t count, const long *array);
double             cldimodeul(size_t count, const unsigned long *array);
double             cldimodell(size_t count, const long long *array);
double             cldimodeull(size_t count, const unsigned long long *array);

// Get the standard deviation of a set of numbers (of various types)
#define cldisdev cldisdevd
cldifpm_t          cldisdevfm(size_t count, const cldifpm_t *array);
double             cldisdevd(size_t count, const double *array);
float              cldisdevf(size_t count, const float *array);
double             cldisdevi(size_t count, const int *array);
double             cldisdevui(size_t count, const unsigned int *array);
double             cldisdevl(size_t count, const long *array);
double             cldisdevul(size_t count, const unsigned long *array);
double             cldisdevll(size_t count, const long long *array);
double             cldisdevull(size_t count, const unsigned long long *array);

// Get the outliers of a set of numbers (of various types)
#define cldioutl cldioutld
ssize_t            cldioutlfm(
	size_t count, size_t max_outliers,
	const cldifpm_t *__restrict__ array,
	cldifpm_t       *__restrict__ output
);
ssize_t            cldioutld(
	size_t count, size_t max_outliers,
	const double *__restrict__ array,
	double       *__restrict__ output
);
ssize_t            cldioutlf(
	size_t count, size_t max_outliers,
	const float *__restrict__ array,
	float       *__restrict__ output
);
ssize_t            cldioutli(
	size_t count, size_t max_outliers,
	const int *__restrict__ array,
	int       *__restrict__ output
);
ssize_t            cldioutlui(
	size_t count, size_t max_outliers,
	const unsigned int *__restrict__ array,
	unsigned int       *__restrict__ output
);
ssize_t            cldioutll(
	size_t count, size_t max_outliers,
	const long *__restrict__ array,
	long       *__restrict__ output
);
ssize_t            cldioutlul(
	size_t count, size_t max_outliers,
	const unsigned long *__restrict__ array,
	unsigned long       *__restrict__ output
);
ssize_t            cldioutlll(
	size_t count, size_t max_outliers,
	const long long *__restrict__ array,
	long long       *__restrict__ output
);
ssize_t            cldioutlull(
	size_t count, size_t max_outliers,
	const unsigned long long *__restrict__ array,
	unsigned long long       *__restrict__ output
);

// Sort a set of numbers (least to greatest)
#define cldisort cldisortd
CLDISTAT           cldisortfm(size_t count, const cldifpm_t *array);
CLDISTAT           cldisortd(size_t count, const double *array);
CLDISTAT           cldisortf(size_t count, const float *array);
CLDISTAT           cldisorti(size_t count, const int *array);
CLDISTAT           cldisortui(size_t count, const unsigned int *array);
CLDISTAT           cldisortl(size_t count, const long *array);
CLDISTAT           cldisortul(size_t count, const unsigned long *array);
CLDISTAT           cldisortll(size_t count, const long long *array);
CLDISTAT           cldisortull(size_t count, const unsigned long long *array);
// Sort a set of numbers (greatest to least)
#define cldigsort cldigsortd
CLDISTAT           cldigsortfm(size_t count, const cldifpm_t *array);
CLDISTAT           cldigsortd(size_t count, const double *array);
CLDISTAT           cldigsortf(size_t count, const float *array);
CLDISTAT           cldigsorti(size_t count, const int *array);
CLDISTAT           cldigsortui(size_t count, const unsigned int *array);
CLDISTAT           cldigsortl(size_t count, const long *array);
CLDISTAT           cldigsortul(size_t count, const unsigned long *array);
CLDISTAT           cldigsortll(size_t count, const long long *array);
CLDISTAT           cldigsortull(size_t count, const unsigned long long *array);
// Reverse a set of numbers
#define cldisrev cldisrevd
CLDISTAT           cldisrevfm(size_t count, const cldifpm_t *array);
CLDISTAT           cldisrevd(size_t count, const double *array);
CLDISTAT           cldisrevf(size_t count, const float *array);
CLDISTAT           cldisrevi(size_t count, const int *array);
CLDISTAT           cldisrevui(size_t count, const unsigned int *array);
CLDISTAT           cldisrevl(size_t count, const long *array);
CLDISTAT           cldisrevul(size_t count, const unsigned long *array);
CLDISTAT           cldisrevll(size_t count, const long long *array);
CLDISTAT           cldisrevull(size_t count, const unsigned long long *array);

// Get a phase angle in radians (from degrees)
#define cldirad cldiradd
cldifpm_t cldiradfm(cldifpm_t r, cldifpm_t phase);
cldifpm_t cldiradd(cldifpm_t r, cldifpm_t phase);
cldifpm_t cldiradf(cldifpm_t r, cldifpm_t phase);
// Get a phase angle in degrees (from radians)
#define cldideg cldidegd
cldifpm_t cldidegfm(cldifpm_t r, cldifpm_t phase);
cldifpm_t cldidegd(cldifpm_t r, cldifpm_t phase);
cldifpm_t cldidegf(cldifpm_t r, cldifpm_t phase);

// Get circumference from diameter
#define cldicirc cldicircd
cldifpm_t cldicircfm(cldifpm_t d);
double    cldicircd(double d);
float     cldicircf(float d);
// Get circumference from radius
#define cldircirc cldircircd
cldifpm_t cldircircfm(cldifpm_t r);
double    cldircircd(double r);
float     cldircircf(float r);
// Get circumference from area
#define cldiacirc cldiacircd
cldifpm_t cldiacircfm(cldifpm_t a);
double    cldiacircd(double a);
float     cldiacircf(float a);

// Get diameter from circumference
#define cldidiam cldidiamd
cldifpm_t cldidiamfm(cldifpm_t c);
double    cldidiamd(double c);
float     cldidiamf(float c);
// Get diameter from area
#define cldiadiam cldidiamad
cldifpm_t cldiadiamfm(cldifpm_t a);
double    cldiadiamd(double a);
float     cldiadiamf(float a);

// Get radius from circumference
#define cldiradius cldiradiusd
cldifpm_t cldiradiusfm(cldifpm_t c);
double    cldiradiusd(double c);
float     cldiradiusf(float c);
// Get radius from area
#define cldiaradius cldiradiusad
cldifpm_t cldiaradiusfm(cldifpm_t a);
double    cldiaradiusd(double a);
float     cldiaradiusf(float a);

// Get area of a circle from radius
#define cldicircarea cldicircaread
cldifpm_t cldicircareafm(cldifpm_t r);
double    cldicircaread(double r);
float     cldicircareaf(float r);
// Get area of a circle from diameter
#define cldicircdarea cldicircdaread
cldifpm_t cldicircdareafm(cldifpm_t r);
double    cldicircdaread(double r);
float     cldicircdareaf(float r);
// Get area of a circle from circumference
#define cldicirccarea cldicirccaread
cldifpm_t cldicirccareafm(cldifpm_t r);
double    cldicirccaread(double r);
float     cldicirccareaf(float r);

// Get arc length in a circle from phase in radians
#define cldiarclen cldiarclend
cldifpm_t cldiarclenfm(cldifpm_t r, cldifpm_t rad);
double    cldiarclend(double r, double rad);
float     cldiarclenf(float r, float rad);
// Get arc length in a circle from phase in degrees
#define cldiarclendeg cldiarclendegd
cldifpm_t cldiarclendegfm(cldifpm_t r, cldifpm_t rad);
double    cldiarclendegd(double r, double rad);
float     cldiarclendegf(float r, float rad);


/* Number Set type */
typedef struct _CLDINUMSET
{
	cldimemref    set;
	size_t        len;
} cldinumset_t;
/* Methods associated with number sets: */
#include "math/numset.h"

/* Number Matrix type */
typedef struct _CLDIMATRIX
{
	cldimemref matrix;
	size_t     rows, cols;
} cldimatrix_t;
/* Methods associated with number matrices: */
#include "math/matrix.h"


// Evaluate a string as an equation, return error code if one is encountered.
cldifpm_t         cldieval(const char *equ);
// - Evaluate as quadruple-precision float
cldiquad          cldievalq(const char *equ);
// Evaluate a format string as an equation, return error code if one is encountered.
#if CLDI_PLATFORM == WINDOWS
	__cdecl
#endif
cldifpm_t cldifeval(const char *fmt, ...);
#if CLDI_PLATFORM == WINDOWS
	__cdecl
#endif
cldiquad  cldifevalq(const char *fmt, ...);


/* Include Math for Dimensional Shapes */
#include "math/domain.h"
#include "math/shapes2d.h"
#include "math/shapes3d.h"
#include "math/shapes4d.h"



#ifdef __cplusplus
}
#endif

#endif // _cldi_head__MATH_H
