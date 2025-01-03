
#ifndef _cldi_core_
#define _cldi_core_ 1

/* Setup CLDI module "core" */
#include "core/setup.h"
#include "core/version.h"

/* Requires: cldi-portable: types */
#include <ciahlldi/cldi/portable/types.h>



/* Extensions to the C++ namespace scope (ciahlldi::cldi::core). */
#ifdef __cplusplus
extern "C++" {

namespace ciahlldi
{
	namespace cldi
	{
		namespace core
		{
			namespace types
			{
				using namespace ciahlldi::cldi::portable::types;
			}
		}
	}
}

}
#endif


/* Included Core Headers */

/* "types"       : Types for various other standard purposes. */
#include "core/types.h"

/* "text"        : Types and code all associated with the management and safety of text in all
.                  different acceptable forms. */
#include "core/text.h"

/* "math"        : Types and code all associated with mathematics processing and efficiency. */
#include "core/math.h"

/* "errhandling" : Code for common error handling and safe returning. */
#include "core/errhandling.h"




#endif /* __ciahlldi_core__ */
