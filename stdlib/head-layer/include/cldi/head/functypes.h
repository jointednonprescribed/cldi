
#pragma cldic module head:functypes
#ifndef _cldi_head__FUNCTYPES_H
#define _cldi_head__FUNCTYPES_H 1

#include "setup.h"
#pragma cldic require head:setup



/* C-Compatible Function type templates (they required a 'name' parameter, to
.  ensure all usages go into a typedef declaration). */
#define cldiTemplFunction(rtype, name, ...) typedef rtype (*name)(__VA_ARGS__)
#define cldiTemplConsumer(name, ...)        typedef void  (*name)(__VA_ARGS__)
#define cldiTemplSupplier(rtype, name)      typedef rtype (*name)()
typedef void (*cldisubroutine_t)();


/* C++ bindings for this file: */
#include "icxx/functypes.hpp"



#endif // _cldi_head__FUNCTYPES_H
