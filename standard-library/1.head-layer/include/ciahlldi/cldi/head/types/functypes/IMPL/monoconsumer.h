
#ifndef _cldi_portable__types_functypes_IMPL_MONOCONSUMER_H
#define _cldi_portable__types_functypes_IMPL_MONOCONSUMER_H 1

#include "../../../setup.h"



#define cldiMonoConsumer(name, type1) void(name)(type1 a)
#define cldiMonoConsumer_t(name, type1) void(*name)(type1, type2)



#endif /* _cldi_portable__types_functypes_IMPL_MONOCONSUMER_H */
