
#ifndef _cldi_portable__types_functypes_IMPL_suppliers_ADDRSUPPLIER_H
#define _cldi_portable__types_functypes_IMPL_suppliers_ADDRSUPPLIER_H 1

#include "../../../../setup.h"

#include "../supplier.h"



#define cldiAddrSupplier(name) void* name(void)
typedef void* (*cldiAddrSupplier_t) (void);


#if defined(__cplusplus) && __CLDI_no_cpp < true
namespace cldi
{
	class addrsupplier_t : public supplier_t<void*>
	{
	public:

		constexpr addrsupplier_t(const supplier_t<void*>& other):
			supplier_t(other.function)
		{}

		constexpr addrsupplier_t(void* (*func)(void)):
			supplier_t(func)
		{}
	};
}
#endif



#endif /* _cldi_portable__types_functypes_IMPL_suppliers_ADDRSUPPLIER_H */
