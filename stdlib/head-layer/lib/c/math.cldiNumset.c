


/* Implementing: cldi-head: math.h */
#include <cldi/head/math.h>



#define cldiMakeNumset_IMPL(constructor, ...) \
	cldinumset_t r; \
	constructor (&r, __VA_ARGS__); \
	return r
// END cldiMakeNumset_IMPL
#define cldiNewNumset_IMPL(constructor, ...) \
	CLDI_ERRNO = CLDI_SUCCESS; \
\
	cldimemref r; \
	int e = cldiInitMemrefNewBlock( \
		&r, \
		(clditypeinfo_t){ \
			.size=sizeof(cldinumset_t), \
			.templ=CLDI_STRUCT_TYPE \
		}, \
		CLDI_DEFAULT_MBLK_PERMS \
	); \
\
	if (e != CLDI_SUCCESS) \
		return r; \
\
	constructor (cldiMemrefGetAddress(&r), __VA_ARGS__); \
\
	return r
// END cldiNewNumset_IMPL
CLDISTAT     cldiInitNumset(cldinumset_t *self)
{
	CLDI_ERRNO = CLDI_SUCCESS;

	cldiInitMemref(&self->set);

	return CLDI_SUCCESS;
}
cldinumset_t cldiMakeNumset()
{
	cldinumset_t r;
	cldiInitNumset(&r);
	return r;
}
cldimemref   cldiNewNumset()
{
	CLDI_ERRNO = CLDI_SUCCESS;

	cldimemref r;
	int e = cldiInitMemrefNewBlock(
		&r,
		(clditypeinfo_t){
			.size=sizeof(cldinumset_t),
			.templ=CLDI_STRUCT_TYPE
		},
		CLDI_DEFAULT_MBLK_PERMS
	);

	if (e != CLDI_SUCCESS)
		return r;

	cldiInitNumset(cldiMemrefGetAddress(&r));

	return r;
}

#define cldiInitNumsetAs_IMPL(type, self, typetempl, set_size, set) \
	if (set_size == 0 || set == NULL) \
		return cldiInitMemref(&self->set); \
\
	CLDI_ERRNO = CLDI_SUCCESS; \
\
	if (cldiInitMemrefNewBlock( \
		&self->set, \
		(clditypeinfo_t) {.size=sizeof(type), .templ=typetempl}, \
		CLDI_DEFAULT_MBLK_PERMS \
	) != CLDI_SUCCESS) \
		return CLDI_ERRNO; \
\
	type *a = cldiMemrefGetAddress(&self->set); \
	if (a == NULL || CLDI_ERRNO != CLDI_SUCCESS) \
		return CLDI_ERRNO; \
	for (size_t i = 0; i < set_size; a[i] = set[i], i++); \
\
	return CLDI_SUCCESS
// END cldiInitNumsetAs_IMPL()
CLDISTAT     cldiInitNumsetAs(const cldinumset_t *self, size_t set_size, const cldifpm_t *set)
{
	cldiInitNumsetAs_IMPL(cldifpm_t, self, CLDI_FLOAT_TYPE, set_size, set);
}
CLDISTAT     cldiInitNumsetAsLF(const cldinumset_t *self, size_t set_size, const double *set)
{
	cldiInitNumsetAs_IMPL(double, self, CLDI_FLOAT_TYPE, set_size, set);
}
CLDISTAT     cldiInitNumsetAsF(const cldinumset_t *self, size_t set_size, const float *set)
{
	cldiInitNumsetAs_IMPL(float, self, CLDI_FLOAT_TYPE, set_size, set);
}
cldinumset_t cldiMakeNumsetAs(size_t set_size, const cldifpm_t *set)
{
	cldiMakeNumset_IMPL(cldiInitNumsetAs, set_size, set);
}
cldinumset_t cldiMakeNumsetAsLF(size_t set_size, const double *set)
{
	cldiMakeNumset_IMPL(cldiInitNumsetAsLF, set_size, set);
}
cldinumset_t cldiMakeNumsetAsF(size_t set_size, const float *set)
{
	cldiMakeNumset_IMPL(cldiInitNumsetAsF, set_size, set);
}
cldimemref   cldiNewNumsetAs(size_t set_size, const cldifpm_t *set)
{
	cldiNewNumset_IMPL(cldiInitNumsetAs, set_size, set);
}
cldimemref   cldiNewNumsetAsLF(size_t set_size, const double *set)
{
	cldiNewNumset_IMPL(cldiInitNumsetAsLF, set_size, set);
}
cldimemref   cldiNewNumsetAsF(size_t set_size, const float *set)
{
	cldiNewNumset_IMPL(cldiInitNumsetAsF, set_size, set);
}

CLDISTAT     cldiInitNumsetAsUHH(const cldinumset_t *self, size_t set_size, const unsigned char *set)
{
	cldiInitNumsetAs_IMPL(unsigned char, self, CLDI_INT_TYPE, set_size, set);
}
CLDISTAT     cldiInitNumsetAsHH(const cldinumset_t *self, size_t set_size, const signed char *set)
{
	cldiInitNumsetAs_IMPL(signed char, self, CLDI_INT_TYPE, set_size, set);
}
CLDISTAT     cldiInitNumsetAsUH(const cldinumset_t *self, size_t set_size, const unsigned short *set)
{
	cldiInitNumsetAs_IMPL(unsigned short, self, CLDI_INT_TYPE, set_size, set);
}
CLDISTAT     cldiInitNumsetAsH(const cldinumset_t *self, size_t set_size, const signed short *set)
{
	cldiInitNumsetAs_IMPL(signed short, self, CLDI_INT_TYPE, set_size, set);
}
CLDISTAT     cldiInitNumsetAsUI(const cldinumset_t *self, size_t set_size, const unsigned int *set)
{
	cldiInitNumsetAs_IMPL(unsigned int, self, CLDI_INT_TYPE, set_size, set);
}
CLDISTAT     cldiInitNumsetAsI(const cldinumset_t *self, size_t set_size, const signed int *set)
{
	cldiInitNumsetAs_IMPL(signed int, self, CLDI_INT_TYPE, set_size, set);
}
CLDISTAT     cldiInitNumsetAsUL(const cldinumset_t *self, size_t set_size, const unsigned long int *set)
{
	cldiInitNumsetAs_IMPL(unsigned long int, self, CLDI_INT_TYPE, set_size, set);
}
CLDISTAT     cldiInitNumsetAsL(const cldinumset_t *self, size_t set_size, const signed long int *set)
{
	cldiInitNumsetAs_IMPL(signed long int, self, CLDI_INT_TYPE, set_size, set);
}
CLDISTAT     cldiInitNumsetAsULL(const cldinumset_t *self, size_t set_size, const unsigned long long *set)
{
	cldiInitNumsetAs_IMPL(unsigned long long, self, CLDI_INT_TYPE, set_size, set);
}
CLDISTAT     cldiInitNumsetAsLL(const cldinumset_t *self, size_t set_size, const signed long long *set)
{
	cldiInitNumsetAs_IMPL(signed long long, self, CLDI_INT_TYPE, set_size, set);
}
cldinumset_t cldiMakeNumsetAsUHH(size_t set_size, const unsigned char *set)
{
	cldiMakeNumset_IMPL(cldiInitNumsetAsUHH, set_size, set);
}
cldinumset_t cldiMakeNumsetAsHH(size_t set_size, const signed char *set)
{
	cldiMakeNumset_IMPL(cldiInitNumsetAsHH, set_size, set);
}
cldinumset_t cldiMakeNumsetAsUH(size_t set_size, const unsigned short *set)
{
	cldiMakeNumset_IMPL(cldiInitNumsetAsUH, set_size, set);
}
cldinumset_t cldiMakeNumsetAsH(size_t set_size, const signed short *set)
{
	cldiMakeNumset_IMPL(cldiInitNumsetAsH, set_size, set);
}
cldinumset_t cldiMakeNumsetAsUI(size_t set_size, const unsigned int *set)
{
	cldiMakeNumset_IMPL(cldiInitNumsetAsUI, set_size, set);
}
cldinumset_t cldiMakeNumsetAsI(size_t set_size, const signed int *set)
{
	cldiMakeNumset_IMPL(cldiInitNumsetAsI, set_size, set);
}
cldinumset_t cldiMakeNumsetAsUL(size_t set_size, const unsigned long int *set)
{
	cldiMakeNumset_IMPL(cldiInitNumsetAsUL, set_size, set);
}
cldinumset_t cldiMakeNumsetAsL(size_t set_size, const signed long int *set)
{
	cldiMakeNumset_IMPL(cldiInitNumsetAsL, set_size, set);
}
cldinumset_t cldiMakeNumsetAsULL(size_t set_size, const unsigned long long *set)
{
	cldiMakeNumset_IMPL(cldiInitNumsetAsULL, set_size, set);
}
cldinumset_t cldiMakeNumsetAsLL(size_t set_size, const signed long long *set)
{
	cldiMakeNumset_IMPL(cldiInitNumsetAsLL, set_size, set);
}
cldimemref   cldiNewNumsetAsUHH(size_t set_size, const unsigned char *set)
{
	cldiNewNumset_IMPL(cldiInitNumsetAsUHH, set_size, set);
}
cldimemref   cldiNewNumsetAsHH(size_t set_size, const signed char *set)
{
	cldiNewNumset_IMPL(cldiInitNumsetAsHH, set_size, set);
}
cldimemref   cldiNewNumsetAsUH(size_t set_size, const unsigned short *set)
{
	cldiNewNumset_IMPL(cldiInitNumsetAsUH, set_size, set);
}
cldimemref   cldiNewNumsetAsH(size_t set_size, const signed short *set)
{
	cldiNewNumset_IMPL(cldiInitNumsetAsH, set_size, set);
}
cldimemref   cldiNewNumsetAsUI(size_t set_size, const unsigned int *set)
{
	cldiNewNumset_IMPL(cldiInitNumsetAsUI, set_size, set);
}
cldimemref   cldiNewNumsetAsI(size_t set_size, const signed int *set)
{
	cldiNewNumset_IMPL(cldiInitNumsetAsI, set_size, set);
}
cldimemref   cldiNewNumsetAsUL(size_t set_size, const unsigned long int *set)
{
	cldiNewNumset_IMPL(cldiInitNumsetAsUL, set_size, set);
}
cldimemref   cldiNewNumsetAsL(size_t set_size, const signed long int *set)
{
	cldiNewNumset_IMPL(cldiInitNumsetAsL, set_size, set);
}
cldimemref   cldiNewNumsetAsULL(size_t set_size, const unsigned long long *set)
{
	cldiNewNumset_IMPL(cldiInitNumsetAsULL, set_size, set);
}
cldimemref   cldiNewNumsetAsLL(size_t set_size, const signed long long *set)
{
	cldiNewNumset_IMPL(cldiInitNumsetAsLL, set_size, set);
}
#undef cldiInitNumsetAs_IMPL

CLDISTAT     cldiInitNumsetEmpty(const cldinumset_t *self, size_t num_capacity)
{
	CLDI_ERRNO = CLDI_SUCCESS;

	if (num_capacity == 0)
		return cldiInitMemref(&self->set);
	else
		return cldiInitMemrefNewBlock(
			&self->set,
			(clditypeinfo_t){
				.size=sizeof(cldinumset_t),
				.templ=CLDI_STRUCT_TYPE
			}
		);
}
cldinumset_t cldiMakeNumsetEmpty(size_t num_capacity)
{
	cldiMakeNumset_IMPL(cldiInitNumsetEmpty, num_capacity);
}
cldimemref   cldiNewNumsetEmpty(size_t num_capacity)
{
	cldiNewNumset_IMPL(cldiInitNumsetEmpty, num_capacity);
}

CLDISTAT     cldiInitNumsetCopy(const cldinumset_t *self, const cldinumset_t *copy_of)
{
	
}
CLDISTAT     cldiInitNumsetCopyRef(const cldinumset_t *self, const cldimemref *copy_of);
cldinumset_t cldiMakeNumsetCopy(const cldinumset_t *copy_of)
{
	cldiMakeNumset_IMPL(cldiInitNumsetCopy, copy_of);
}
cldinumset_t cldiMakeNumsetCopyRef(const cldimemref *copy_of)
{
	cldiMakeNumset_IMPL(cldiInitNumsetCopyRef, copy_of);
}
cldimemref   cldiNewNumsetCopy(const cldinumset_t *copy_of)
{
	cldiNewNumset_IMPL(cldiInitNumsetCopy, copy_of);
}
cldimemref   cldiNewNumsetCopyRef(const cldimemref *copy_of)
{
	cldiNewNumset_IMPL(cldiInitNumsetCopyRef, copy_of);
}
#undef cldiMakeNumset_IMPL
#undef cldiNewNumset_IMPL

cldifpm_t    cldiNumsetSum(const cldinumset_t *self);
cldifpm_t    cldiNumsetAltSum(const cldinumset_t *self);
cldifpm_t    cldiNumsetDiff(const cldinumset_t *self);
cldifpm_t    cldiNumsetProduct(const cldinumset_t *self);
cldifpm_t    cldiNumsetQuotient(const cldinumset_t *self);

CLDISTAT     cldiNumsetAddTo(cldinumset_t *self, const cldinumset_t *add);
CLDISTAT     cldiNumsetAltAddTo(cldinumset_t *self, const cldinumset_t *altadd);
CLDISTAT     cldiNumsetSubTo(cldinumset_t *self, const cldinumset_t *sub);
CLDISTAT     cldiNumsetMultTo(cldinumset_t *self, const cldinumset_t *mult);
CLDISTAT     cldiNumsetDivTo(cldinumset_t *self, const cldinumset_t *div);

cldinumset_t cldiNumsetAdd(cldinumset_t *self, const cldinumset_t *add);
cldinumset_t cldiNumsetAltAdd(cldinumset_t *self, const cldinumset_t *altadd);
cldinumset_t cldiNumsetSub(cldinumset_t *self, const cldinumset_t *sub);
cldinumset_t cldiNumsetMult(cldinumset_t *self, const cldinumset_t *mult);
cldinumset_t cldiNumsetDiv(cldinumset_t *self, const cldinumset_t *div);

cldimemref   cldiNumsetAddNew(cldinumset_t *self, const cldinumset_t *add);
cldimemref   cldiNumsetAltAddNew(cldinumset_t *self, const cldinumset_t *altadd);
cldimemref   cldiNumsetSubNew(cldinumset_t *self, const cldinumset_t *sub);
cldimemref   cldiNumsetMultNew(cldinumset_t *self, const cldinumset_t *mult);
cldimemref   cldiNumsetDivNew(cldinumset_t *self, const cldinumset_t *div);

cldifpm_t    cldiNumsetMean(const cldinumset_t *self);
cldifpm_t    cldiNumsetMedian(const cldinumset_t *self);
cldifpm_t    cldiNumsetMode(const cldinumset_t *self);
cldifpm_t    cldiNumsetStandardDeviation(const cldinumset_t *self);


