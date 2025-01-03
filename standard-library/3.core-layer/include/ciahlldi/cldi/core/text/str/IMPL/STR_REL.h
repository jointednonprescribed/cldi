
#ifndef _cldi_core__text_IMPL_STR_REL_H
#define _cldi_core__text_IMPL_STR_REL_H 1

#include "../../../setup.h"



#if defined(__cplusplus) && __CLDI_no_cpp > false
extern "C" {
#endif
enum _CLDISTRREL
{
	CLDISTR_REL_ERR         = -6,
	CLDISTR_REL_UNKNOWN     = -5,
	CLDISTR_REL_PPARENT     = -4,
	CLDISTR_REL_PCHILD      = -3,
	CLDISTR_REL_PSIBLING    = -2,
	CLDISTR_REL_PARTNER     = -1,
	CLDISTR_NO_RELATIONSHIP = 0,
	CLDISTR_REL_SIBLING     = 1,
	CLDISTR_REL_CHILD       = 2,
	CLDISTR_REL_PARENT      = 3,
	CLDISTR_REL_COPY        = 4,
};

#if defined(__cplusplus) && __CLDI_no_cpp > false
}
#endif
/* Aliases for this enum: */
typedef enum _CLDISTRREL CLDISTRREL, CLDI_STR_REL;

#if defined(__cplusplus) && __CLDI_no_cpp < true
namespace cldi {
	namespace core {
		using STR_REL = CLDISTRREL;
		using STRING_RELATIONSHIP = CLDISTRREL;
	}
	using core::STR_REL, core::STRING_RELATIONSHIP;
}
#endif


/* Check if any given string relationship shows a partnership. */
bool cldiStrRelIsPartnership(CLDISTRREL relationship);
#if defined(__cplusplus) && __CLDI_no_cpp < true
namespace cldi
{
	namespace core
	{
		using STR_REL = CLDISTRREL;
		using STRING_RELATIONSHIP = CLDISTRREL;

		constexpr bool StrRelIsPartnership(STR_REL relationship)
		{
			return relationship < 0;
		}
	}
	using core::STR_REL, core::STRING_RELATIONSHIP;
}
#endif



#endif /* _cldi_core__text_IMPL_STR_REL_H */
