
#ifndef _cldi_portable__types_functypes_IMPL_CALLABLE_HPP
#	include "../../../setup/cpp-check.hpp"
#	if _cldi_cpp_check == 0
#		define _cldi_portable__types_functypes_IMPL_CALLABLE_HPP 0
#	else
#		define _cldi_portable__types_functypes_IMPL_CALLABLE_HPP 1

#include "../../../setup.h"
#include "../../../NS_DECL.hpp"



namespace cldi
{
	template <typename _RTyp, typename... _A>
	class iCallable
	{
	public:
		iCallable() = delete;
		iCallable(const iCallable&) = delete;
		~iCallable() = delete;

		constexpr _RTyp operator ()(_A... args)
		{
			this->Call(args...);
		}

		virtual _RTyp Call(_A...) =0;
	};
}



#	endif
#endif /* _cldi_portable__types_functypes_IMPL_CALLABLE_HPP */
