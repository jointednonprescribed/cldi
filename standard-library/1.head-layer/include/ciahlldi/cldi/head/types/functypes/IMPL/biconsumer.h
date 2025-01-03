
#ifndef _cldi_portable__types_functypes_IMPL_BICONSUMER_H
#define _cldi_portable__types_functypes_IMPL_BICONSUMER_H 1

#include "../../../setup.h"



#define cldiBiConsumer(name, type1, type2) void(name)(type1 arg0, type2 arg1)
#define cldiBiConsumer_t(name, type1, type2) void(*name)(type1,type2)



#endif /* _cldi_portable__types_functypes_IMPL_BICONSUMER_H */
