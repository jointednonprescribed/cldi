
#ifndef _cldi_portable__types_functypes_IMPL_QUADCONSUMER_H
#define _cldi_portable__types_functypes_IMPL_QUADCONSUMER_H 1

#include "../../../setup.h"
#include "../../../NS_DECL.hpp"



#define cldiQuadConsumer(name, type1, type2, type3, type4)   void(name)(type1 a0, type2 a1, type3 a2, type4 a3)
#define cldiQuadConsumer_t(name, type1, type2, type3, type4) void(*name)(type1,type2,type3,type4)



#endif /* _cldi_portable__types_functypes_IMPL_QUADCONSUMER_H */
