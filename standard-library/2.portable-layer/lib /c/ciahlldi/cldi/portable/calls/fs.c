
/* Implementing: cldi-portable: calls/fs */
#include <ciahlldi/cldi/portable/calls/fs.h>

/* Requires: calls/memory */
#include <ciahlldi/cldi/portable/calls/memory.h>
/*           types/basic-types */
#include <ciahlldi/cldi/portable/types/basictypes.h>
/*           text/str */
#include <ciahlldi/cldi/portable/text/str.h>



bool cldiPathnameExists(const char * __path)
{
#if __CLDI_PLATFORM == CLDI_PLATFORM_WINDOWS
#elif __CLDI_PLATFORM_UNIX_BASED > false

#else
	const char *pathname = cldiGetCleanPathnameString(__path);

	FILE *f = fopen(pathname, "r");
	if (f == NULL) {
		cldiDropMemory(pathname);
		return errno != ENOENT;
	} else {
		fclose(f);
		cldiDropMemory(pathname);
		return true;
	}
#endif
}
bool cldiPathnameIsFile(const char * __path)
{
#if __CLDI_PLATFORM_UNIX_BASED > false
	struct stat path_stat;

	const char * pathname = cldiGetCleanPathnameString(__path);

	long e = stat(pathname, &path_stat);
	cldiDropMemory(pathname);

	if (e != 0)
		return false;
	else
		return !S_ISDIR(path_stat.st_mode);
#endif
}
bool cldiPathnameIsRegularFile(const char * __path)
{
#if __CLDI_PLATFORM_UNIX_BASED > false
	struct stat path_stat;

	const char * pathname = cldiGetCleanPathnameString(__path);

	long e = stat(pathname, &path_stat);
	cldiDropMemory(pathname);

	if (e != 0)
		return false;
	else
		return S_ISREG(path_stat.st_mode);
#endif
}
bool cldiPathnameIsDir(const char * __path)
{
#if __CLDI_PLATFORM_UNIX_BASED > false
	struct stat path_stat;

	const char * pathname = cldiGetCleanPathnameString(__path);

	long e = stat(pathname, &path_stat);
	cldiDropMemory(pathname);

	if (e != 0)
		return false;
	else
		return S_ISDIR(path_stat.st_mode);
#endif
}
bool cldiPathnameIsLink(const char * __path)
{
#if __CLDI_PLATFORM_UNIX_BASED > false
	struct stat path_stat;

	const char * pathname = cldiGetCleanPathnameString(__path);

	long e = stat(pathname, &path_stat);
	cldiDropMemory(pathname);

	if (e != 0)
		return false;
	else
		return S_ISLNK(path_stat.st_mode);
#endif
}
bool cldiPathnameIsPipe(const char * __path)
{
#if __CLDI_PLATFORM_UNIX_BASED > false
	struct stat path_stat;

	const char * pathname = cldiGetCleanPathnameString(__path);

	long e = stat(pathname, &path_stat);
	cldiDropMemory(pathname);

	if (e != 0)
		return false;
	else
		return S_ISFIFO(path_stat.st_mode);
#endif
}
bool cldiPathnameIsCharSpec(const char * __path)
{
#if __CLDI_PLATFORM_UNIX_BASED > false
	struct stat path_stat;

	const char * pathname = cldiGetCleanPathnameString(__path);

	long e = stat(pathname, &path_stat);
	cldiDropMemory(pathname);

	if (e != 0)
		return false;
	else
		return S_ISCHR(path_stat.st_mode);
#endif
}
bool cldiPathnameIsBlockSpec(const char * __path)
{
#if __CLDI_PLATFORM_UNIX_BASED > false
	struct stat path_stat;

	const char * pathname = cldiGetCleanPathnameString(__path);

	long e = stat(pathname, &path_stat);
	cldiDropMemory(pathname);

	if (e != 0)
		return false;
	else
		return S_ISBLK(path_stat.st_mode);
#endif
}

bool cldiPathnameIsRel(const char * __path)
{
	const char * pathname = cldiGetCleanPathnameString(__path);



	return false;
}
bool cldiPathnameIsAbs(const char * __path)
{
	if (__path == NULL)
		/* Null argument is unusable. */
		return false;

	const char * pathname = cldiGetCleanPathnameString(__path);
	if (pathname == NULL)
		/* If this functions fails and returns NULL, the path itself might be invalid. */
		return false;



	return false;
}

CLDISTRHANDLE cldiRelPathname(const char * __path)
{
	if (__path == NULL)
		return CLDISTRHANDLE_NULL;

	const char * pathname = cldiRelPathnameString(__path);
	if (pathname == NULL)
		return CLDISTRHANDLE_NULL;

	return (CLDISTRHANDLE){
		._valid=CLDISTRHANDLE_VALID_ID,
		._data=CLDISTRHANDLE_oDEFAULT,
		._init=true,
		.type=CLDI_CHARTYPE_CSTRING,
		.address=pathname,
		.char_count=cldiCStrlen(pathname),
	};
}
CLDISTRHANDLE cldiAbsPathname(const char * __path)
{
	if (__path == NULL)
		return CLDISTRHANDLE_NULL;

	const char * pathname = cldiAbsPathnameString(__path);
	if (pathname == NULL)
		return CLDISTRHANDLE_NULL;

	return (CLDISTRHANDLE){
		._valid=CLDISTRHANDLE_VALID_ID,
		._data=CLDISTRHANDLE_oDEFAULT,
		._init=true,
		.type=CLDI_CHARTYPE_CSTRING,
		.address=pathname,
		.char_count=cldiCStrlen(pathname),
	};
}
const char *_cldi_objspawn_ cldiRelPathnameString(const char * __path);
const char *_cldi_objspawn_ cldiAbsPathnameString(const char * __path);
CLDISTRHANDLE cldiRealPathname(const char * __path);
const char *_cldi_objspawn_ cldiRealPathnameString(const char * __path);
CLDISTRHANDLE cldiGetCleanPathname(const char * __path);
const char *_cldi_objspawn_ cldiGetCleanPathnameString(const char * __path);

cldifilestat_t cldiCreateNewFile(const char * __path, long long __perms)
{
	if (__path == NULL)
		return CLDI_FILE_NULL_ARG;

	const char * pathname = cldiGetCleanPathnameString(__path);
	if (pathname == NULL)
		return CLDI_FILE_INADEQUATE_ARG;

	FILE* f = fopen(pathname, "wx");
	if (f == NULL) {
		cldiDropMemory(pathname);
		return CLDI_FILE_ALREADY_EXISTS;
	}

	fclose(f);

	return CLDI_FILE_SUCCESS;
}
cldifilestat_t cldiCreateNewDirectory(const char * __path, long long __perms)
{
	if (__path == NULL)
		return CLDI_FILE_NULL_ARG;

	const char * pathname = cldiGetCleanPathnameString(__path);
	if (pathname == NULL)
		return CLDI_FILE_INADEQUATE_ARG;

	CLDI_FILE_STATUS e = CLDI_FILE_SUCCESS;

#if __CLDI_PLATFORM == CLDI_PLATFORM_WINDOWS
	SECURITY_DESCRIPTOR sDesc;
	if (InitializeSecurityDescriptor(&sDesc, 0) == 0)
		return CLDI_FILE_FAILED_SUBROUTINE;
#elif __CLDI_PLATFORM_UNIX_BASED > false
	struct stat st = [0];

	errno = 0;
	bool efStat = (stat(pathname, &st) == 0);
	if (!efStat && errno == ENOENT) {
		e = mkdir(pathname, __perms);
	}
	else if (efStat)
		return CLDI_FILE_ALREADY_EXISTS;
	else switch (errno) {
	case EACCES:       return CLDI_FILE_ACCESS_FAIL;
	case EBADF:        return CLDI_FILE_NONEXISTENT;
	case EINVAL:       return CLDI_FILE_INVALID_FLAGS;
	case ELOOP:        return CLDI_FILE_EXCESSIVE_LINKS;
	case ENAMETOOLONG: return CLDI_FILE_NAME_TOO_LONG;
	case ENOTDIR:      return CLDI_FILE_NOT_DIR;
	case ENOMEM:       return CLDI_FILE_NOMEM;
	default:           return CLDI_FILE_FAILED_SUBROUTINE;
	}

	return e;
#elif defined(__CLDI_IMPL_CreateNewDirectory)
	return __CLDI_IMPL_CreateNewDirectory();
#else
#pragma warn("CLDI: Function cldiCreateNewDirectory() didn't get a full implementation on this platform and with the current settings.")
	return CLDI_FILE_NO_IMPLEMENTATION;
#endif
}


