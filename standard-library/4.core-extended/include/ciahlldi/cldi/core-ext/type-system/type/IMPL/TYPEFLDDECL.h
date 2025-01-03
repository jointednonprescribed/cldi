
#ifndef _cldi_core_ext__type_system_type_IMPL_TYPECLASS_H
#define _cldi_core_ext__type_system_type_IMPL_TYPECLASS_H 1

#include "../../../setup.h"
#include "../../../NS_DECL.hpp"



#if defined(__cplusplus) && __CLDI_no_cpp > false
extern "C" {
#endif
struct _CLDITYPEFLDDECL
{

};
#if __CLDI_no_cpp > false
#	ifdef __cplusplus
	}
#	endif
typedef const struct _CLDITYPEFLDDECL CLDITYPEFLDDECL, CLDI_TYPE_FIELD_DECL,
	CLDI_TYPE_FIELD_DECLARATIONS;
#else
typedef const _CLDITYPEFLDDECL CLDITYPEFLDDECL, CLDI_TYPE_FIELD_DECL,
	CLDI_TYPE_FIELD_DECLARATIONS;
namespace cldi
{
	namespace extended
	{
		using TYPEFLDDECL = CLDITYPEFLDDECL;
		using TYPE_FIELD_DECL = CLDITYPEFLDDECL;
		using TYPE_FIELD_DECLARATIONS = CLDITYPEFLDDECL;
	}
	using extended::TYPEFLDDECL, extended::TYPE_FIELD_DECL, extended::TYPE_FIELD_DECLARATIONS;
}
#endif



#endif /* _cldi_core_ext__type_system_type_IMPL_TYPECLASS_H */
