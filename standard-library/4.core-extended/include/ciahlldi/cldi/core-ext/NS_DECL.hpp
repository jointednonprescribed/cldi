
#ifndef _cldi_core_ext__NS_DECL_HPP
#	include "setup.h"
#	if !defined(__cplusplus) || __CLDI_no_cpp > false
#		define _cldi_core_ext__NS_DECL_HPP 0
#	else
#		define _cldi_core_ext__NS_DECL_HPP 1
#	endif

#include "version.h"

#include <ciahlldi/cldi/head/NS_DECL.hpp>
#include <ciahlldi/cldi/portable/NS_DECL.hpp>
#include <ciahlldi/cldi/core/NS_DECL.hpp>


namespace cldi {
	namespace extended {
		constexpr unsigned long long VERSION = CLDI_CORE_EXT_VERSION;
	}
}


#	endif
#endif /* _cldi_core_ext__NS_DECL_H */
