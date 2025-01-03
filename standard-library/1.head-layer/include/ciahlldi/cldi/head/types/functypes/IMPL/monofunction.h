
#ifndef _cldi_portable__types_functypes_IMPL_MONOFUNCTION_H
#define _cldi_portable__types_functypes_IMPL_MONOFUNCTION_H 1

#include "../../../setup.h"



#define cldiMonoFunction(rtype, name, type)   rtype name(type a)
#define cldiMonoFunction_t(rtype, name, type) rtype (*name)(type)



#endif /* _cldi_portable__types_functypes_IMPL_MONOFUNCTION_H */
