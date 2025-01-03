
#ifndef _cldi_core_ext__type_system_type_IMPL_TYPECLASS_H
#define _cldi_core_ext__type_system_type_IMPL_TYPECLASS_H 1

#include "../../../setup.h"

#include "TYPEFLDDECL.h"

/* Requires: cldi-portable: types/basic-types */
#include <ciahlldi/cldi/portable/types/basictypes.h>



#if defined(__cplusplus) && __CLDI_no_cpp > false
extern "C" {
#endif
struct _CLDITYPECLASS
{
	const size_t type_size, ptr_offset;

	const CLDITYPEFLDDECL *const fields;

	const char type_name[30];
};
#if defined(__cplusplus) && __CLDI_no_cpp > false
}
#endif
typedef const struct _CLDITYPECLASS CLDITYPECLASS, CLDI_TYPECLASS;

#if __CLDI_no_cpp == false
namespace cldi
{
	namespace extended
	{
		using TYPECLASS = CLDITYPECLASS;
		using TYPE_CLASS = CLDITYPECLASS;
	}
}
#endif



#endif /* _cldi_core_ext__type_system_type_IMPL_TYPECLASS_H */
