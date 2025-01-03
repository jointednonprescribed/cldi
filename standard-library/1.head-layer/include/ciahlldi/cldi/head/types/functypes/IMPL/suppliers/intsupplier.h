
#ifndef _cldi_portable__types_functypes_IMPL_suppliers_INTSUPPLIER_H
#define _cldi_portable__types_functypes_IMPL_suppliers_INTSUPPLIER_H 1

#include "../../../../setup.h"

#include "../supplier.h"



#define cldiIntSupplier(name) int name(void)
typedef int (*cldiIntSupplier_t) (void);


#if defined(__cplusplus) && __CLDI_no_cpp < true
namespace cldi
{
	class intsupplier_t : public supplier_t<int>
	{
	public:

		constexpr intsupplier_t(const supplier_t<int>& other):
			supplier_t(other.function)
		{}

		constexpr intsupplier_t(int (*func)(void)):
			supplier_t(func)
		{}
	};
}
#endif



#endif /* _cldi_portable__types_functypes_IMPL_suppliers_INTSUPPLIER_H */
