
#ifndef _cldi_head__SETUP_H
#define _cldi_head__SETUP_H 1

#include "settings.h"



/* CLDI Version */
#define CLDI_VERSION 250000000UL
const unsigned long CLDI_LIB_VER  = CLDI_VERSION;
const unsigned long CLDI_HEAD_VER = CLDI_VERSION;
#if CLDI_C_ONLY == false
namespace cldi
{
	constexpr unsigned long VERSION      = CLDI_VERSION;
	constexpr unsigned long HEAD_VERSION = CLDI_VERSION;
}
#endif


/* Platform-awareness macros and code: */
#include "setup/platform.h"
/* All included APIs/external headers are contained here: */
#include "setup/includes.h"

/* Include some setup code. */
#include "setup/stat.h"
#include "setup/types.h"



#endif // _cldi_head__SETUP_H
