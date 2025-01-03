
#ifndef _cldi_head__MACROS_H
#define _cldi_head__MACROS_H 1

#include "setup.h"



/* If C++, constexpr, else const. */
#if defined(__cplusplus) && __CLDI_no_cpp > false
#	define _cldi_constexpr_ constexpr
#else
#	define _cldi_constexpr_ const
#endif

/* Surrogate for CLDI Compiler's '_memory_spawn_' and '_ownership_transfer_' attributes. */
#ifdef __cldic
#	define _cldi_memspawn_ __attribute__(_memory_spawn_)
#	define _cldi_objspawn_ __attribute__(_memory_spawn_,_ownership_transfer_)
#	define _memspawn_ __attribute__(_memory_spawn_)
#	define _objspawn_ __attribute__(_memory_spawn_,_ownership_transfer_)
#else
#	define _cldi_memspawn_
#	define _cldi_objspawn_
#endif



#endif /* _cldi_head__MACROS_H */
