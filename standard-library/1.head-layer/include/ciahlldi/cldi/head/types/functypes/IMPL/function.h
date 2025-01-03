
#ifndef _cldi_portable__types_functypes_IMPL_FUNCTION_H
#define _cldi_portable__types_functypes_IMPL_FUNCTION_H 1

#include "../../../setup.h"
#include "../../../NS_DECL.hpp"

#include "callable.hpp"



#define cldiFunction(rtype, name, ...)   rtype   name (__VA_ARGS__)
#define cldiFunction_t(rtype, name, ...) rtype (*name)(__VA_ARGS__)


#if defined(__cplusplus) && __CLDI_no_cpp < true
namespace cldi
{
	template <typename _RTyp, typename... _A>
	class function_t : public iCallable<_RTyp, _A...>
	{
	protected:
		_RTyp (*const function)(_A...);

	public:
		constexpr function_t():
			function(NULL)
		{}
		constexpr function_t(const function_t& other):
			function(other.function)
		{}

		constexpr function_t(void (*function)(_A...)):
			function(function)
		{}

		constexpr _RTyp operator ()(_A... args)
		{
			this->Call(args...);
		}

		_RTyp Call(_A... args)
		{
			function(args...);
		}
	};
}
#endif



#endif /* _cldi_portable__types_functypes_IMPL_FUNCTION_H */
