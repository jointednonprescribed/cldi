
#ifndef _cldi_portable__types_functypes_IMPL_QUADFUNCTION_H
#define _cldi_portable__types_functypes_IMPL_QUADFUNCTION_H 1

#include "../../../setup.h"



#define cldiQuadFunction(rtype, name, type1, type2, type3, type4)   rtype name(type1 a0, type2 a1, type3 a2, type4 a3)
#define cldiQuadFunction_t(rtype, name, type1, type2, type3, type4) rtype (*name)(type1,type2,type3,type4)



#endif /* _cldi_portable__types_functypes_IMPL_QUADFUNCTION_H */
