
#ifndef _cldi_portable__errhandling_THROWERS_H
#define _cldi_portable__errhandling_THROWERS_H 1

#include "../setup.h"



/* cldierr_t Structure Implementation */
#include "throwers/IMPL/cldierr_t.h"

/* USAGE: CLDITHROWV <method-name>(arguments) (replaces return type)
.         Throw an error using an integer value. */
typedef long long CLDITHROWV;
/* USAGE: CLDITHROW <method-name>(arguments) (replaces return type)
.         Throw an error with full detail. */
typedef cldierr_t CLDITHROW;



#endif /* _cldi_portable__errhandling_THROWERS_H */
