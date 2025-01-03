
#ifndef _cldi_core_namespace_
#	include "setup.h"
#	if !defined(__cplusplus) || __CLDI_no_cpp > false
#		define _cldi_core_namespace_ 0
#	else
#		define _cldi_core_namespace_ 1

#include "version.h"

#include <ciahlldi/cldi/head/NS_DECL.hpp>
#include <ciahlldi/cldi/portable/NS_DECL.hpp>


namespace cldi {
	namespace core {
		constexpr unsigned long long VERSION = CLDI_CORE_VERSION;
	}
}


#	endif
#endif /* _cldi_core_namespace_ */
