
#ifndef _cldi_head__math_ARITHFUNCS_H
#define _cldi_head__math_ARITHFUNCS_H 1

#include "../setup.h"



/* Find the sum of all numbers in an array. */
unsigned char cldiUByteSum(const unsigned char *bytes, size_t n);
unsigned short cldiUShortSum(const unsigned short *shorts, size_t n);
unsigned int cldiUIntSum(const unsigned int *ints, size_t n);
unsigned long cldiULongSum(const unsigned long *longs, size_t n);
unsigned long long cldiULLongSum(const unsigned long long *llongs, size_t n);
signed   char cldiByteSum(const signed char *bytes, size_t n);
signed   short cldiShortSum(const signed short *shorts, size_t n);
signed   int cldiIntSum(const signed int *ints, size_t n);
signed   long cldiLongSum(const signed long *longs, size_t n);
signed   long long cldiLLongSum(const signed long long *llongs, size_t n);
#define cldiSum cldiIntSum
/* - For specific integer sizes. */
uint16_t cldiUInt16Sum(const uint16_t *a16, size_t n);
uint32_t cldiUInt32Sum(const uint32_t *a32, size_t n);
uint64_t cldiUInt64Sum(const uint64_t *a64, size_t n);
int16_t  cldiInt16Sum(const int16_t *a16, size_t n);
int32_t  cldiInt32Sum(const int32_t *a32, size_t n);
int64_t  cldiInt64Sum(const int64_t *a64, size_t n);

/* Find the product of all numbers multiplied together in an array. */
unsigned char cldiUBytesProduct(const unsigned char *bytes, size_t n);
unsigned short cldiUShortsProduct(const unsigned short *shorts, size_t n);
unsigned int cldiUIntsProduct(const unsigned int *ints, size_t n);
unsigned long cldiULongsProduct(const unsigned long *longs, size_t n);
unsigned long long cldiULLongsProduct(const unsigned long long *llongs, size_t n);
signed   char cldiBytesProduct(const signed char *bytes, size_t n);
signed   short cldiShortsProduct(const signed short *shorts, size_t n);
signed   int cldiIntsProduct(const signed int *ints, size_t n);
signed   long cldiLongsProduct(const signed long *longs, size_t n);
signed   long long cldiLLongsProduct(const signed long long *llongs, size_t n);
#define cldiProduct cldiIntsProduct
/* - For specific integer sizes. */
uint16_t cldiUInt16Product(const uint16_t *a16, size_t n);
uint32_t cldiUInt32Product(const uint32_t *a32, size_t n);
uint64_t cldiUInt64Product(const uint64_t *a64, size_t n);
int16_t  cldiInt16Product(const int16_t *a16, size_t n);
int32_t  cldiInt32Product(const int32_t *a32, size_t n);
int64_t  cldiInt64Product(const int64_t *a64, size_t n);



#endif
