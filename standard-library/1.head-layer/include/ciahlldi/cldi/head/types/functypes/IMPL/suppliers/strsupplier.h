
#ifndef _cldi_portable__types_functypes_IMPL_suppliers_STRSUPPLIER_H
#define _cldi_portable__types_functypes_IMPL_suppliers_STRSUPPLIER_H 1

#include "../../../../setup.h"

#include "../supplier.h"



#define cldiStrSupplier(name) const char* name(void)
typedef const char* (*cldiStrSupplier_t) (void);


#if defined(__cplusplus) && __CLDI_no_cpp < true
namespace cldi
{
	class strsupplier_t : public supplier_t<const char*>
	{
	public:

		constexpr strsupplier_t(const supplier_t<const char*>& other):
			supplier_t(other.function)
		{}

		constexpr strsupplier_t(const char* (*func)(void)):
			supplier_t(func)
		{}
	};
}
#endif



#endif /* _cldi_portable__types_functypes_IMPL_suppliers_STRSUPPLIER_H */
