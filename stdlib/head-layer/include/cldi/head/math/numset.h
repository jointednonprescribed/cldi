
#ifndef _cldi_head__math_NUMSET_H
#define _cldi_head__math_NUMSET_H 1

/* Subheader of head/math.h */
#ifndef _cldi_head__MATH_H
#	include "../math.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif



CLDISTAT     cldiInitNumset(cldinumset_t *self);
cldinumset_t cldiMakeNumset();
cldimemref   cldiNewNumset();

CLDISTAT     cldiInitNumsetAs(cldinumset_t *self, size_t set_size, const cldifpm_t *set);
CLDISTAT     cldiInitNumsetAsLF(cldinumset_t *self, size_t set_size, const double *set);
CLDISTAT     cldiInitNumsetAsF(cldinumset_t *self, size_t set_size, const float *set);
cldinumset_t cldiMakeNumsetAs(size_t set_size, const cldifpm_t *set);
cldinumset_t cldiMakeNumsetAsLF(size_t set_size, const double *set);
cldinumset_t cldiMakeNumsetAsF(size_t set_size, const float *set);
cldimemref   cldiNewNumsetAs(size_t set_size, const cldifpm_t *set);
cldimemref   cldiNewNumsetAsLF(size_t set_size, const double *set);
cldimemref   cldiNewNumsetAsF(size_t set_size, const float *set);

CLDISTAT     cldiInitNumsetAsUHH(cldinumset_t *self, size_t set_size, const unsigned char *set);
CLDISTAT     cldiInitNumsetAsHH(cldinumset_t *self, size_t set_size, const signed char *set);
CLDISTAT     cldiInitNumsetAsUH(cldinumset_t *self, size_t set_size, const unsigned short *set);
CLDISTAT     cldiInitNumsetAsH(cldinumset_t *self, size_t set_size, const signed short *set);
CLDISTAT     cldiInitNumsetAsUI(cldinumset_t *self, size_t set_size, const unsigned int *set);
CLDISTAT     cldiInitNumsetAsI(cldinumset_t *self, size_t set_size, const signed int *set);
CLDISTAT     cldiInitNumsetAsUL(cldinumset_t *self, size_t set_size, const unsigned long int *set);
CLDISTAT     cldiInitNumsetAsL(cldinumset_t *self, size_t set_size, const signed long int *set);
CLDISTAT     cldiInitNumsetAsULL(cldinumset_t *self, size_t set_size, const unsigned long long *set);
CLDISTAT     cldiInitNumsetAsLL(cldinumset_t *self, size_t set_size, const signed long long *set);
cldinumset_t cldiMakeNumsetAsUHH(size_t set_size, const unsigned char *set);
cldinumset_t cldiMakeNumsetAsHH(size_t set_size, const signed char *set);
cldinumset_t cldiMakeNumsetAsUH(size_t set_size, const unsigned short *set);
cldinumset_t cldiMakeNumsetAsH(size_t set_size, const signed short *set);
cldinumset_t cldiMakeNumsetAsUI(size_t set_size, const unsigned int *set);
cldinumset_t cldiMakeNumsetAsI(size_t set_size, const signed int *set);
cldinumset_t cldiMakeNumsetAsUL(size_t set_size, const unsigned long int *set);
cldinumset_t cldiMakeNumsetAsL(size_t set_size, const signed long int *set);
cldinumset_t cldiMakeNumsetAsULL(size_t set_size, const unsigned long long *set);
cldinumset_t cldiMakeNumsetAsLL(size_t set_size, const signed long long *set);
cldimemref   cldiNewNumsetAsUHH(size_t set_size, const unsigned char *set);
cldimemref   cldiNewNumsetAsHH(size_t set_size, const signed char *set);
cldimemref   cldiNewNumsetAsUH(size_t set_size, const unsigned short *set);
cldimemref   cldiNewNumsetAsH(size_t set_size, const signed short *set);
cldimemref   cldiNewNumsetAsUI(size_t set_size, const unsigned int *set);
cldimemref   cldiNewNumsetAsI(size_t set_size, const signed int *set);
cldimemref   cldiNewNumsetAsUL(size_t set_size, const unsigned long int *set);
cldimemref   cldiNewNumsetAsL(size_t set_size, const signed long int *set);
cldimemref   cldiNewNumsetAsULL(size_t set_size, const unsigned long long *set);
cldimemref   cldiNewNumsetAsLL(size_t set_size, const signed long long *set);

CLDISTAT     cldiInitNumsetEmpty(cldinumset_t *self, size_t num_capacity);
cldinumset_t cldiMakeNumsetEmpty(size_t num_capacity);
cldimemref   cldiNewNumsetEmpty(size_t num_capacity);

CLDISTAT     cldiInitNumsetCopy(cldinumset_t *self, const cldinumset_t *copy_of);
CLDISTAT     cldiInitNumsetCopyRef(cldinumset_t *self, const cldimemref *copy_of);
cldinumset_t cldiMakeNumsetCopy(const cldinumset_t *copy_of);
cldinumset_t cldiMakeNumsetCopyRef(const cldimemref *copy_of);
cldimemref   cldiNewNumsetCopy(const cldinumset_t *copy_of);
cldimemref   cldiNewNumsetCopyRef(const cldimemref *copy_of);

cldifpm_t    cldiNumsetSum(const cldinumset_t *self);
cldifpm_t    cldiNumsetAltSum(const cldinumset_t *self);
cldifpm_t    cldiNumsetDiff(const cldinumset_t *self);
cldifpm_t    cldiNumsetProduct(const cldinumset_t *self);
cldifpm_t    cldiNumsetQuotient(const cldinumset_t *self);

// Perform set operation, and store results in the current set (self)
CLDISTAT     cldiNumsetAddTo(cldinumset_t *self, const cldinumset_t *add);
CLDISTAT     cldiNumsetAltAddTo(cldinumset_t *self, const cldinumset_t *altadd);
CLDISTAT     cldiNumsetSubTo(cldinumset_t *self, const cldinumset_t *sub);
CLDISTAT     cldiNumsetMultTo(cldinumset_t *self, const cldinumset_t *mult);
CLDISTAT     cldiNumsetDivTo(cldinumset_t *self, const cldinumset_t *div);

cldinumset_t cldiNumsetAdd(const cldinumset_t *self, const cldinumset_t *add);
cldinumset_t cldiNumsetAltAdd(const cldinumset_t *self, const cldinumset_t *altadd);
cldinumset_t cldiNumsetSub(const cldinumset_t *self, const cldinumset_t *sub);
cldinumset_t cldiNumsetMult(const cldinumset_t *self, const cldinumset_t *mult);
cldinumset_t cldiNumsetDiv(const cldinumset_t *self, const cldinumset_t *div);

cldimemref   cldiNumsetAddNew(const cldinumset_t *add);
cldimemref   cldiNumsetAltAddNew(const cldinumset_t *altadd);
cldimemref   cldiNumsetSubNew(const cldinumset_t *sub);
cldimemref   cldiNumsetMultNew(const cldinumset_t *mult);
cldimemref   cldiNumsetDivNew(const cldinumset_t *div);

cldifpm_t    cldiNumsetMean(const cldinumset_t *self);
cldifpm_t    cldiNumsetMedian(const cldinumset_t *self);
cldifpm_t    cldiNumsetMode(const cldinumset_t *self);
cldifpm_t    cldiNumsetStandardDeviation(const cldinumset_t *self);
#define      cldiNumsetStdDev      cldiNumsetStandardDeviation
#define      cldiNumsetStandardDev cldiNumsetStandardDeviation



#ifdef __cplusplus
}
#endif

#endif // _cldi_head__math_NUMSET_H
