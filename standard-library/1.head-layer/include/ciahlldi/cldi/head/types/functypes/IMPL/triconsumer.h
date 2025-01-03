
#ifndef _cldi_portable__types_functypes_IMPL_TRICONSUMER_H
#define _cldi_portable__types_functypes_IMPL_TRICONSUMER_H 1

#include "../../../setup.h"



#define cldiTriConsumer(name, type1, type2, type3)   void(name)(type1 a0, type2 a1, type3 a2)
#define cldiTriConsumer_t(name, type1, type2, type3) void(*name)(type1,type2,type3)



#endif /* _cldi_portable__types_functypes_IMPL_TRICONSUMER_H */
