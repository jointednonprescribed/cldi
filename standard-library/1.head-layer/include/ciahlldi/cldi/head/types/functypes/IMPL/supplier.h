
#ifndef _cldi_portable__types_functypes_IMPL_SUPPLIER_H
#define _cldi_portable__types_functypes_IMPL_SUPPLIER_H 1

#include "../../../setup.h"

#include "callable.hpp"



#define cldiSupplier(rtype, name)   rtype   name ()
#define cldiSupplier_t(rtype, name) rtype (*name)()

#if defined(__cplusplus) && __CLDI_no_cpp < true
namespace cldi
{
	template <typename _RTyp>
	class supplier_t : public iCallable<_RTyp>
	{
	public:
		typedef _RTyp (*specific_t)(void);

		const specific_t function;

	public:
		~supplier_t()
		{}

		constexpr supplier_t():
			function(NULL)
		{}
		constexpr supplier_t(const supplier_t& other):
			function(other.function)
		{}

		constexpr supplier_t(_RTyp (*func) ()):
			function(static_cast<_RTyp(*)(void)>(func))
		{}
		constexpr supplier_t(_RTyp (*func)(void)):
			function(func)
		{}


		constexpr operator _RTyp()
		{
			return function();
		}

		_RTyp Call()
		{
			return function();
		}
	};
}
#endif



#endif /* _cldi_portable__types_functypes_IMPL_SUPPLIER_H */
