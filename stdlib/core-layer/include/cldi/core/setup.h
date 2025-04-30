
#ifndef _cldi_core__SETUP_H
#define _cldi_core__SETUP_H 1

#include <cldi/head.h>



const unsigned long CLDI_CORE_VER = CLDI_VERSION;
#if CLDI_C_ONLY == false
namespace cldi
{
	constexpr unsigned long CORE_VERSION = CLDI_VERSION;
}
#endif



#endif // _cldi_core__SETUP_H
