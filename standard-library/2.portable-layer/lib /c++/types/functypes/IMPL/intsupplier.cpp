
/* Implementing: cldi-portable: types/functypes/IMPL/intsupplier */
#include <ciahlldi/cldi/portable/types/functypes/IMPL/intsupplier.h>



namespace cldi
{
	intsupplier_t::intsupplier_t(int (*__func)(void)):
		this->function(__func)
	{}
}


