


/* Implementing: cldi-head: setup/types.h */
#include <ciahlldi/cldi/head/setup/types.h>



cldipid_t cldiGetCurrentPID()
{
#if CLDI_PLATFORM_UNIXLIKE == true
	return getpid();
#elif CLDI_PLATFORM == CLDI_WINDOWS
	return GetCurrentPID();
#else
#   error "cldi-head: GetCurrentPID() has no implementation on this system, report this problem to the developer."
#endif
}


