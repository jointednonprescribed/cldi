
#ifndef _cldi_portable__types_functypes_IMPL_CONSUMER_H
#define _cldi_portable__types_functypes_IMPL_CONSUMER_H 1

#include "../../../setup.h"
#include "../../../NS_DECL.hpp"

#include "callable.hpp"



#define cldiConsumer(name, ...)   void   name (__VA_ARGS__)
#define cldiConsumer_t(name, ...) void (*name)(__VA_ARGS__)


#if defined(__cplusplus) && __CLDI_no_cpp < true
namespace cldi
{
	template <typename... _A>
	class consumer_t : public iCallable<void, _A...>
	{
	protected:
		void (*const function)(_A...);

	public:
		constexpr consumer_t():
			function(NULL)
		{}
		constexpr consumer_t(const consumer_t& other):
			function(other.function)
		{}

		constexpr consumer_t(void (*function)(_A...)):
			function(function)
		{}

		constexpr void operator ()(_A... args)
		{
			this->Call(args...);
		}

		void Call(_A... args)
		{
			function(args...);
		}
	};
}
#endif



#endif /* _cldi_portable__types_functypes_IMPL_CONSUMER_H */
