
#ifndef _cldi_head__io_PATH_H
#define _cldi_head__io_PATH_H 1

#ifndef _cldi_head__STRING_H
#	include "../string.h"
#endif



#if CLDI_PLATFORM_WINDOWS
const char CLDI_PATHSEP_S[]     = "\\";
const char CLDI_ALT_PATHSEP_S[] = "/";
#	define CLDI_PATHSEP     '\\'
#	define CLDI_ALT_PATHSEP '/'
#else
const char CLDI_PATHSEP_S[]     = "/";
const char CLDI_ALT_PATHSEP_S[] = "\\";
#	define CLDI_PATHSEP     '/'
#	define CLDI_ALT_PATHSEP '\\'
#endif

typedef struct _CLDIPATHEXPR
{
	cldimemref  path;

	size_t      disk, base;
#if CLDI_PLATFORM_UNIXLIKE == true
	struct stat fstat;
#endif
} cldipath_t;

bool cldiPathIsFile(const cldipath_t *self);
bool cldiPathIsDir(const cldipath_t *self);
bool cldiPathIsFIFO(const cldipath_t *self);
bool cldiPathIsLink(const cldipath_t *self);
bool cldiPathPathExists(const cldipath_t *self);



#endif // _cldi_head__io_PATH_H
