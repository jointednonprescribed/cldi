
#ifndef _cldi_portable__types_functypes_IMPL_suppliers_LONGSUPPLIER_H
#define _cldi_portable__types_functypes_IMPL_suppliers_LONGSUPPLIER_H 1

#include "../../../../setup.h"

#include "../supplier.h"



#define cldiLongSupplier(name) long int name(void)
typedef long int (*cldiLongSupplier_t) (void);


#if defined(__cplusplus) && __CLDI_no_cpp < true
namespace cldi
{
	class longsupplier_t : public supplier_t<long int>
	{
	public:

		constexpr longsupplier_t(const supplier_t<long int>& other):
			supplier_t(other.function)
		{}

		constexpr longsupplier_t(long int (*func)(void)):
			supplier_t(func)
		{}
	};
}
#endif



#endif /* _cldi_portable__types_functypes_IMPL_suppliers_LONGSUPPLIER_H */
