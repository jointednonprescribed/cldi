
#ifndef _cldi_portable__calls_FILEOPT_H
#define _cldi_portable__calls_FILEOPT_H 1



#ifdef __cplusplus
extern "C" {
#endif
typedef enum _CLDI_FILE_OPTIONS
{
	CLDI_FILE_READ         = 1UL,
	CLDI_FILE_WRITE        = 2UL,
	CLDI_FILE_APPEND       = 4UL,
	CLDI_FILE_APPEND_READ  = 5UL,
	CLDI_FILE_APPEND_WRITE = 6UL,

	CLDI_FILE_UPDATE_MODE  = 0x8,

	CLDI_FILE_BINARY_MODE  = 0x10,

	CLDI_NO_FILE_OVERWRITE = 0x20,
	CLDI_CREATE_NEW_FILE   = CLDI_NO_FILE_OVERWRITE,

	CLDI_PUBLIC_FILE_PERMS = 0x40,
} CLDI_FILE_OPTIONS;
#ifdef __cplusplus
}
#	if __CLDI_no_cpp > false
namespace cldi
{
	using FILE_OPTIONS = cldifileopt_t;
	using fileopt_t    = cldifileopt_t;
}
#	endif
#endif



#endif /* _cldi_portable__calls_FILEOPT_H */
