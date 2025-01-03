
#ifndef _cldi_portable__types_functypes_IMPL_BIFUNCTION_H
#define _cldi_portable__types_functypes_IMPL_BIFUNCTION_H 1

#include "../../../setup.h"



#define cldiBiFunction(rtype, name, type1, type2)   rtype name(type1 a0, type2 a1)
#define cldiBiFunction_t(rtype, name, type1, type2) rtype (*name)(type1,type2)



#endif /* _cldi_portable__types_functypes_IMPL_BIFUNCTION_H */
