
#ifndef _cldi_portable__types_functypes_IMPL_suppliers_LLONGSUPPLIER_H
#define _cldi_portable__types_functypes_IMPL_suppliers_LLONGSUPPLIER_H 1

#include "../../../../setup.h"

#include "../supplier.h"



#define cldiLongSupplier(name) long long name(void)
typedef long long (*cldiLongSupplier_t) (void);


#if defined(__cplusplus) && __CLDI_no_cpp < true
namespace cldi
{
	class llongsupplier_t : public supplier_t<long long>
	{
	public:

		constexpr llongsupplier_t(const supplier_t<long long>& other):
			supplier_t(other.function)
		{}

		constexpr llongsupplier_t(long long (*func)(void)):
			supplier_t(func)
		{}
	};
}
#endif



#endif /* _cldi_portable__types_functypes_IMPL_suppliers_LLONGSUPPLIER_H */
