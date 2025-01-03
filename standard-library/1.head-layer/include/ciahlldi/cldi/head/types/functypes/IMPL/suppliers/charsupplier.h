
#ifndef _cldi_portable__types_functypes_IMPL_suppliers_CHARSUPPLIER_H
#define _cldi_portable__types_functypes_IMPL_suppliers_CHARSUPPLIER_H 1

#include "../../../../setup.h"

#include "../supplier.h"



#define cldiCharSupplier(name) int name(void)
typedef int (*cldiCharSupplier_t) (void);


#if defined(__cplusplus) && __CLDI_no_cpp < true
namespace cldi
{
	class charsupplier_t : public supplier_t<char>
	{
	public:

		constexpr charsupplier_t(const supplier_t<char>& other):
			supplier_t(other.function)
		{}

		constexpr charsupplier_t(char (*func)(void)):
			supplier_t(func)
		{}
	};
}
#endif



#endif /* _cldi_portable__types_functypes_IMPL_suppliers_CHARSUPPLIER_H */
