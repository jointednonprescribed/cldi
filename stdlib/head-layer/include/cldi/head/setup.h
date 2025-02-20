
#ifndef _cldi_head__SETUP_H
#define _cldi_head__SETUP_H 1

#include "settings.h"



/* CLDI Version */
#define CLDI_VERSION 250000000UL
#if CLDI_C_ONLY == false
namespace cldi
{
	constexpr unsigned long VERSION = CLDI_VERSION;
}
#endif


/* Platform-awareness macros and code: */
#include "setup/platform.h"
/* All included C/C++ standard library modules, APIs, and external headers are
.  contained here: */
#include "setup/includes.h"

/* Include some setup code. */
#include "setup/stat.h"
#include "setup/types.h"



#endif // _cldi_head__SETUP_H
