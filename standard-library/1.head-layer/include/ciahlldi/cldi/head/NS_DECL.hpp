
#ifndef _cldi_head_namespace_
#	include "setup.h"
#	if !defined(__cplusplus) || __CLDI_no_cpp > false
#		define _cldi_head_namespace_ 0
#	else
#		define _cldi_head_namespace_ 1

#include "version.h"


namespace cldi
{
	constexpr unsigned long long VERSION = CLDI_VERSION;

	namespace head
	{
		constexpr unsigned long long VERSION = CLDI_HEAD_VERSION;
	}
}


#	endif
#endif
