


/* Implementing: cldi-head: math.h */
#include <cldi/head/math.h>



const char CLDIERRMSG_MATH_OVERFLOW_SIZE[] = "Size is too large.";
const char CLDIERRMSG_MATH_NULL_COUNT_ARR[] = "Arguments `count` and `array` must be non-zero.";


cldifpm_t cldisum(size_t count, const cldifpm_t *array)
{
	if (count < 1 || array == NULL) {
		CLDI_ERRNO = CLDI_ENULL_ARG;
		return CLDIFPM_NAN;
	}

	cldifpm_t v, a;
	for (int i = 0; i < count; i++) {
		a = array[i];
		if (a == CLDIFPM_NAN || a == CLDIFPM_INFINITY)
			continue;
		else
			v += a;
	}

	return v;
}
double cldisumd(size_t count, const double *array)
{
	if (count < 1 || array == NULL) {
		CLDI_ERRNO = CLDI_ENULL_ARG;
		return NAN;
	}

	double v, a;
	for (int i = 0; i < count; i++) {
		a = array[i];
		if (a == NAN || a == INFINITY)
			continue;
		else
			v += a;
	}

	return v;
}
float cldisumf(size_t count, const float *array)
{
	if (count < 1 || array == NULL) {
		CLDI_ERRNO = CLDI_ENULL_ARG;
		return NAN;
	}

	float v, a;
	for (int i = 0; i < count; i++) {
		a = array[i];
		if (a == ((float)NAN) || a == ((float)INFINITY))
			continue;
		else
			v += a;
	}

	return v;
}
signed int cldisumi(size_t count, const int *array)
{
	if (count < 1 || array == NULL) {
		CLDI_ERRNO = CLDI_ENULL_ARG;
		return 0;
	}

	signed int v;
	for (int i = 0; i < count; i++, v += array[i]);

	return v;
}
unsigned int cldisumui(size_t count, const unsigned int *array)
{
	if (count < 1 || array == NULL) {
		CLDI_ERRNO = CLDI_ENULL_ARG;
		return 0;
	}

	unsigned int v;
	for (int i = 0; i < count; i++, v += array[i]);

	return v;
}
signed long cldisuml(size_t count, const long *array)
{
	if (count < 1 || array == NULL) {
		CLDI_ERRNO = CLDI_ENULL_ARG;
		return 0;
	}

	signed long v;
	for (int i = 0; i < count; i++, v += array[i]);

	return v;
}
unsigned long cldisumul(size_t count, const unsigned long *array)
{
	if (count < 1 || array == NULL) {
		CLDI_ERRNO = CLDI_ENULL_ARG;
		return 0;
	}

	unsigned long v;
	for (int i = 0; i < count; i++, v += array[i]);

	return v;
}
signed long long cldisumll(size_t count, const long long *array)
{
	if (count < 1 || array == NULL) {
		CLDI_ERRNO = CLDI_ENULL_ARG;
		return 0;
	}

	signed long long v;
	for (int i = 0; i < count; i++, v += array[i]);

	return v;
}
unsigned long long cldisumull(size_t count, const unsigned long long *array)
{
	if (count < 1 || array == NULL) {
		CLDI_ERRNO = CLDI_ENULL_ARG;
		return 0;
	}

	unsigned long long v;
	for (int i = 0; i < count; i++, v += array[i]);

	return v;
}

cldifpm_t cldisub(size_t count, const cldifpm_t *array)
{
	if (count < 1 || array == NULL) {
		CLDI_ERRNO = CLDI_ENULL_ARG;
		return CLDIFPM_NAN;
	}

	cldifpm_t v, a;
	for (int i = 0; i < count; i++) {
		a = array[i];
		if (a == CLDIFPM_NAN || a == CLDIFPM_INFINITY)
			continue;
		else
			v -= a;
	}

	return v;
}
double cldisubd(size_t count, const double *array)
{
	if (count < 1 || array == NULL) {
		CLDI_ERRNO = CLDI_ENULL_ARG;
		return NAN;
	}

	double v, a;
	for (int i = 0; i < count; i++) {
		a = array[i];
		if (a == NAN || a == INFINITY)
			continue;
		else
			v -= a;
	}

	return v;
}
float cldisubf(size_t count, const float *array)
{
	if (count < 1 || array == NULL) {
		CLDI_ERRNO = CLDI_ENULL_ARG;
		return NAN;
	}

	float v, a;
	for (int i = 0; i < count; i++) {
		a = array[i];
		if (a == ((float)NAN) || a == ((float)INFINITY))
			continue;
		else
			v -= a;
	}

	return v;
}
signed int cldisubi(size_t count, const int *array)
{
	if (count < 1 || array == NULL) {
		CLDI_ERRNO = CLDI_ENULL_ARG;
		return 0;
	}

	signed int v;
	for (int i = 0; i < count; i++, v -= array[i]);

	return v;
}
unsigned int cldisubui(size_t count, const unsigned int *array)
{
	if (count < 1 || array == NULL) {
		CLDI_ERRNO = CLDI_ENULL_ARG;
		return 0;
	}

	unsigned int v;
	for (int i = 0; i < count; i++, v -= array[i]);

	return v;
}
signed long cldisubl(size_t count, const long *array)
{
	if (count < 1 || array == NULL) {
		CLDI_ERRNO = CLDI_ENULL_ARG;
		return 0;
	}

	signed long v;
	for (int i = 0; i < count; i++, v -= array[i]);

	return v;
}
unsigned long cldisubul(size_t count, const unsigned  long *array)
{
	if (count < 1 || array == NULL) {
		CLDI_ERRNO = CLDI_ENULL_ARG;
		return 0;
	}

	unsigned long v;
	for (int i = 0; i < count; i++, v -= array[i]);

	return v;
}
signed long long cldisubll(size_t count, const long long *array)
{
	if (count < 1 || array == NULL) {
		CLDI_ERRNO = CLDI_ENULL_ARG;
		return 0;
	}

	signed long long v;
	for (int i = 0; i < count; i++, v -= array[i]);

	return v;
}
unsigned long long cldisubull(size_t count, const unsigned long long *array)
{
	if (count < 1 || array == NULL) {
		CLDI_ERRNO = CLDI_ENULL_ARG;
		return 0;
	}

	unsigned long long v;
	for (int i = 0; i < count; i++, v -= array[i]);

	return v;
}

cldifpm_t cldialt(size_t count, const cldifpm_t *array)
{
	if (count < 1 || array == NULL) {
		CLDI_ERRNO = CLDI_ENULL_ARG;
		return CLDIFPM_NAN;
	}

	cldifpm_t v, a;
	bool op = true;
	for (int i = 0; i < count; i++, op = !op) {
		a = array[i];
		if (a == CLDIFPM_NAN || a == CLDIFPM_INFINITY)
			continue;
		else if (op)
			v += a;
		else
			v -= a;
	}

	return v;
}
double cldialtd(size_t count, const double *array)
{
	if (count < 1 || array == NULL) {
		CLDI_ERRNO = CLDI_ENULL_ARG;
		return NAN;
	}

	double v, a;
	bool op = true;
	for (int i = 0; i < count; i++, op = !op) {
		a = array[i];
		if (a == NAN || a == INFINITY)
			continue;
		else if (op)
			v += a;
		else
			v -= a;
	}

	return v;
}
float cldialtf(size_t count, const float *array)
{
	if (count < 1 || array == NULL) {
		CLDI_ERRNO = CLDI_ENULL_ARG;
		return NAN;
	}

	float v, a;
	bool op = true;
	for (int i = 0; i < count; i++, op = !op) {
		a = array[i];
		if (a == ((float)NAN) || a == ((float)INFINITY))
			continue;
		else if (op)
			v += a;
		else
			v -= a;
	}

	return v;
}
signed int cldialti(size_t count, const int *array)
{
	if (count < 1 || array == NULL) {
		CLDI_ERRNO = CLDI_ENULL_ARG;
		return 0;
	}

	signed int v;
	bool op = true;
	for (int i = 0; i < count; i++, op = !op) {
		if (op)
			v += array[i];
		else
			v -= array[i];
	}

	return v;
}
unsigned int cldialtui(size_t count, const unsigned int *array)
{
	if (count < 1 || array == NULL) {
		CLDI_ERRNO = CLDI_ENULL_ARG;
		return 0;
	}

	unsigned int v;
	bool op = true;
	for (int i = 0; i < count; i++, op = !op) {
		if (op)
			v += array[i];
		else
			v -= array[i];
	}

	return v;
}
signed long cldialtl(size_t count, const long *array)
{
	if (count < 1 || array == NULL) {
		CLDI_ERRNO = CLDI_ENULL_ARG;
		return 0;
	}

	signed long v;
	bool op = true;
	for (int i = 0; i < count; i++, op = !op) {
		if (op)
			v += array[i];
		else
			v -= array[i];
	}

	return v;
}
unsigned long cldialtul(size_t count, const unsigned long *array)
{
	if (count < 1 || array == NULL) {
		CLDI_ERRNO = CLDI_ENULL_ARG;
		return 0;
	}

	unsigned long v;
	bool op = true;
	for (int i = 0; i < count; i++, op = !op) {
		if (op)
			v += array[i];
		else
			v -= array[i];
	}

	return v;
}
signed long long cldialtll(size_t count, const long long *array)
{
	if (count < 1 || array == NULL) {
		CLDI_ERRNO = CLDI_ENULL_ARG;
		return 0;
	}

	signed long long v;
	bool op = true;
	for (int i = 0; i < count; i++, op = !op) {
		if (op)
			v += array[i];
		else
			v -= array[i];
	}

	return v;
}
unsigned long long cldialtull(size_t count, const unsigned long long *array)
{
	if (count < 1 || array == NULL) {
		CLDI_ERRNO = CLDI_ENULL_ARG;
		return 0;
	}

	unsigned long long v;
	bool op = true;
	for (int i = 0; i < count; i++, op = !op) {
		if (op)
			v += array[i];
		else
			v -= array[i];
	}

	return v;
}

cldifpm_t cldimult(size_t count, const cldifpm_t *array)
{
	if (count < 1 || array == NULL) {
		CLDI_ERRNO = CLDI_ENULL_ARG;
		return CLDIFPM_NAN;
	}

	cldifpm_t v, a;
	for (int i = 0; i < count; i++) {
		a = array[i];
		if (a == CLDIFPM_NAN || a == CLDIFPM_INFINITY)
			continue;
		else
			v *= a;
	}

	return v;
}
double cldimultd(size_t count, const double *array)
{
	if (count < 1 || array == NULL) {
		CLDI_ERRNO = CLDI_ENULL_ARG;
		return NAN;
	}

	double v, a;
	for (int i = 0; i < count; i++) {
		a = array[i];
		if (a == NAN || a == INFINITY)
			continue;
		else
			v *= a;
	}

	return v;
}
float cldimultf(size_t count, const float *array)
{
	if (count < 1 || array == NULL) {
		CLDI_ERRNO = CLDI_ENULL_ARG;
		return NAN;
	}

	float v, a;
	for (int i = 0; i < count; i++) {
		a = array[i];
		if (a == ((float)NAN) || a == ((float)INFINITY))
			continue;
		else
			v *= a;
	}

	return v;
}
signed int cldimulti(size_t count, const int *array)
{
	if (count < 1 || array == NULL) {
		CLDI_ERRNO = CLDI_ENULL_ARG;
		return 0;
	}

	signed int v;
	for (int i = 0; i < count; i++, v *= array[i]);

	return v;
}
unsigned int cldimultui(size_t count, const unsigned int *array)
{
	if (count < 1 || array == NULL) {
		CLDI_ERRNO = CLDI_ENULL_ARG;
		return 0;
	}

	unsigned int v;
	for (int i = 0; i < count; i++, v *= array[i]);

	return v;
}
signed long cldimultl(size_t count, const long *array)
{
	if (count < 1 || array == NULL) {
		CLDI_ERRNO = CLDI_ENULL_ARG;
		return 0;
	}

	signed long v;
	for (int i = 0; i < count; i++, v *= array[i]);

	return v;
}
unsigned long cldimultul(size_t count, const unsigned long *array)
{
	if (count < 1 || array == NULL) {
		CLDI_ERRNO = CLDI_ENULL_ARG;
		return 0;
	}

	unsigned long v;
	for (int i = 0; i < count; i++, v *= array[i]);

	return v;
}
signed long long cldimultll(size_t count, const long long *array)
{
	if (count < 1 || array == NULL) {
		CLDI_ERRNO = CLDI_ENULL_ARG;
		return 0;
	}

	signed long long v;
	for (int i = 0; i < count; i++, v *= array[i]);

	return v;
}
unsigned long long cldimultull(size_t count, const unsigned long long *array)
{
	if (count < 1 || array == NULL) {
		CLDI_ERRNO = CLDI_ENULL_ARG;
		return 0;
	}

	unsigned long long v;
	for (int i = 0; i < count; i++, v *= array[i]);

	return v;
}

cldifpm_t cldidiv(size_t count, const cldifpm_t *array)
{
	if (count < 1 || array == NULL) {
		CLDI_ERRNO = CLDI_ENULL_ARG;
		return NAN;
	}

	cldifpm_t v, a;
	for (int i = 0; i < count; i++)
		if (a == CLDIFPM_NAN || a == CLDIFPM_INFINITY)
			continue;
		else
			v /= array[i];

	return v;
}
double cldidivd(size_t count, const double *array)
{
	if (count < 1 || array == NULL) {
		CLDI_ERRNO = CLDI_ENULL_ARG;
		return CLDIFPM_NAN;
	}

	double v, a;
	for (int i = 0; i < count; i++)
		if (a == NAN || a == INFINITY)
			continue;
		else
			v /= array[i];

	return v;
}
float cldidivf(size_t count, const float *array)
{
	if (count < 1 || array == NULL) {
		CLDI_ERRNO = CLDI_ENULL_ARG;
		return NAN;
	}

	float v, a;
	for (int i = 0; i < count; i++)
		if (a == ((float)NAN) || a == ((float)INFINITY))
			continue;
		else
			v /= array[i];

	return v;
}

cldifpm_t cldimean(size_t count, const cldifpm_t *array)
{
	if (count < 1 || array == NULL) {
		cldithrowf(CLDI_ENULL_ARG, cldimeanf, CLDIERRMSG_MATH_NULL_COUNT_ARR);
		return (float)NAN;
	}

	const cldifpm_t c = (cldifpm_t) count;

	cldifpm_t v, a;
	for (int i = 0; i < count; i++)
		if (a == CLDIFPM_NAN || a == CLDIFPM_INF)
			continue;
		else
			v += array[i];

	return v / c;
}
double cldimeand(size_t count, const double *array)
{
	if (count < 1 || array == NULL) {
		cldithrowf(CLDI_ENULL_ARG, cldimeanf, CLDIERRMSG_MATH_NULL_COUNT_ARR);
		return NAN;
	}

	const double c = (double) count;

	double v, a;
	for (int i = 0; i < count; i++)
		if (a == NAN || a == INFINITY)
			continue;
		else
			v += array[i];

	return v / c;
}
float cldimeanf(size_t count, const float *array)
{
	if (count < 1 || array == NULL) {
		cldithrowf(CLDI_ENULL_ARG, cldimeanf, CLDIERRMSG_MATH_NULL_COUNT_ARR);
		return (float)NAN;
	}

	const float c = (float) count;

	double v, a;
	for (int i = 0; i < count; i++)
		if (a == NAN || a == INFINITY)
			continue;				
		else
			v += array[i];

	return v / c;
}
double cldimeani(size_t count, const int *array);
double cldimeanui(size_t count, const unsigned int *array);
double cldimeanl(size_t count, const long *array);
double cldimeanul(size_t count, const unsigned long *array);
double cldimeanll(size_t count, const long long *array);
double cldimeanull(size_t count, const unsigned long long *array);

cldifpm_t cldimedian(size_t count, const cldifpm_t *array);
double cldimediand(size_t count, const double *array);
float cldimedianf(size_t count, const float *array);
double cldimediani(size_t count, const int *array);
double cldimedianui(size_t count, const unsigned int *array);
double cldimedianl(size_t count, const long *array);
double cldimedianul(size_t count, const unsigned long *array);
double cldimedianll(size_t count, const long long *array);
double cldimedianull(size_t count, const unsigned long long *array);

cldifpm_t cldimode(size_t count, const cldifpm_t *array);
double cldimoded(size_t count, const double *array);
float cldimodef(size_t count, const float *array);
double cldimodei(size_t count, const int *array);
double cldimodeui(size_t count, const unsigned int *array);
double cldimodel(size_t count, const long *array);
double cldimodeul(size_t count, const unsigned long *array);
double cldimodell(size_t count, const long long *array);
double cldimodeull(size_t count, const unsigned long long *array);

cldifpm_t cldisdev(size_t count, const cldifpm_t *array);
double cldisdevd(size_t count, const double *array);
float cldisdevf(size_t count, const float *array);
double cldisdevi(size_t count, const int *array);
double cldisdevui(size_t count, const unsigned int *array);
double cldisdevl(size_t count, const long *array);
double cldisdevul(size_t count, const unsigned long *array);
double cldisdevll(size_t count, const long long *array);
double cldisdevull(size_t count, const unsigned long long *array);

ssize_t cldioutl(
	size_t count, size_t max_outliers,
	const cldifpm_t *__restrict__ array,
	cldifpm_t       *__restrict__ output
);
ssize_t cldioutld(
	size_t count, size_t max_outliers,
	const double *__restrict__ array,
	double       *__restrict__ output
);
ssize_t cldioutlf(
	size_t count, size_t max_outliers,
	const float *__restrict__ array,
	float       *__restrict__ output
);
ssize_t cldioutli(
	size_t count, size_t max_outliers,
	const int *__restrict__ array,
	int       *__restrict__ output
);
ssize_t cldioutlui(
	size_t count, size_t max_outliers,
	const unsigned int *__restrict__ array,
	unsigned int       *__restrict__ output
);
ssize_t cldioutll(
	size_t count, size_t max_outliers,
	const long *__restrict__ array,
	long       *__restrict__ output
);
ssize_t cldioutlul(
	size_t count, size_t max_outliers,
	const unsigned long *__restrict__ array,
	unsigned long       *__restrict__ output
);
ssize_t cldioutlll(
	size_t count, size_t max_outliers,
	const long long *__restrict__ array,
	long long       *__restrict__ output
);
ssize_t cldioutlull(
	size_t count, size_t max_outliers,
	const unsigned long long *__restrict__ array,
	unsigned long long       *__restrict__ output
);

CLDISTAT cldisort(size_t count, const cldifpm_t *array);
CLDISTAT cldisortd(size_t count, const double *array);
CLDISTAT cldisortf(size_t count, const float *array);
CLDISTAT cldisorti(size_t count, const int *array);
CLDISTAT cldisortui(size_t count, const unsigned int *array);
CLDISTAT cldisortl(size_t count, const long *array);
CLDISTAT cldisortul(size_t count, const unsigned long *array);
CLDISTAT cldisortll(size_t count, const long long *array);
CLDISTAT cldisortull(size_t count, const unsigned long long *array);

CLDISTAT cldigsort(size_t count, const cldifpm_t *array);
CLDISTAT cldigsortd(size_t count, const double *array);
CLDISTAT cldigsortf(size_t count, const float *array);
CLDISTAT cldigsorti(size_t count, const int *array);
CLDISTAT cldigsortui(size_t count, const unsigned int *array);
CLDISTAT cldigsortl(size_t count, const long *array);
CLDISTAT cldigsortul(size_t count, const unsigned long *array);
CLDISTAT cldigsortll(size_t count, const long long *array);
CLDISTAT cldigsortull(size_t count, const unsigned long long *array);

CLDISTAT cldisrev(size_t count, const cldifpm_t *array);
CLDISTAT cldisrevd(size_t count, const double *array);
CLDISTAT cldisrevf(size_t count, const float *array);
CLDISTAT cldisrevi(size_t count, const int *array);
CLDISTAT cldisrevui(size_t count, const unsigned int *array);
CLDISTAT cldisrevl(size_t count, const long *array);
CLDISTAT cldisrevul(size_t count, const unsigned long *array);
CLDISTAT cldisrevll(size_t count, const long long *array);
CLDISTAT cldisrevull(size_t count, const unsigned long long *array);


cldiomni_t cldieval(const char *equ)
{
	CLDI_ERRNO = CLDI_ENO_IMPL;
	return CLDIOMNI_NAN;
}
cldiomni_t
#if CLDI_PLATFORM == CLDI_WINDOWS
	__cdecl
#endif
	cldifeval(const char *fequ, ...)
{
	// option 1 (the string is 200 characters or less): use this reserved character
	// buffer to store the formatted equation string.
	char buf[201] = {0};

	unsigned int vc = 0;

	char c = fequ[0];
	int  i = 0; 
	for (; c != 0; i++, c = fequ[i])
		if (c == '%' && fequ[i+1] != '%')
			vc++;

	if (vc > 0) {
		va_list va;
		va_start(va, vc);

		int perr = vsnprintf(buf, 200, fequ, va);
		
		if (perr > 0) {
			va_end(va);
			CLDI_ERRNO = CLDI_EOVERFLOW_ARG;
			return CLDIOMNI_NAN;
		} else if (perr < 0) {
			va_end(va);
			CLDI_ERRNO = cldiConvCStdlibError(CLDI_CSTDEC_VSNPRINTF, perr);
			return CLDIOMNI_NAN;
		} else {
			// if no errors or overflows occur, then end the va list and begin evaluation
			va_end(va);
			return cldieval(buf);
		}
	} else {
		CLDI_ERRNO = CLDI_ETOO_FEW_ARGS;
		return CLDIOMNI_NAN;
	}
}


