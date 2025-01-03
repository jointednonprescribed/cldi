
#ifndef _cldi_portable__types_functypes_IMPL_TRIFUNCTION_H
#define _cldi_portable__types_functypes_IMPL_TRIFUNCTION_H 1

#include "../../../setup.h"



#define cldiTriFunction(rtype, name, type1, type2, type3)   rtype name(type1 a0, type2 a1, type3 a2)
#define cldiTriFunction_t(rtype, name, type1, type2, type3) rtype (*name)(type1,type2)



#endif /* _cldi_portable__types_functypes_IMPL_TRIFUNCTION_H */
