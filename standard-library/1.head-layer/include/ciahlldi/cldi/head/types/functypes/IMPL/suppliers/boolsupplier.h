
#ifndef _cldi_portable__types_functypes_IMPL_suppliers_INTSUPPLIER_H
#define _cldi_portable__types_functypes_IMPL_suppliers_INTSUPPLIER_H 1

#include "../../../../setup.h"

#include "../supplier.h"



#define cldiBoolSupplier(name) bool name(void)
typedef bool (*cldiBoolSupplier_t) (void);


#if defined(__cplusplus) && __CLDI_no_cpp < true
namespace cldi
{
	class boolsupplier_t : public supplier_t<bool>
	{
	public:

		constexpr boolsupplier_t(const supplier_t<bool>& other):
			supplier_t(other.function)
		{}

		constexpr boolsupplier_t(bool (*func)(void)):
			supplier_t(func)
		{}
	};
}
#endif



#endif /* _cldi_portable__types_functypes_IMPL_suppliers_INTSUPPLIER_H */
