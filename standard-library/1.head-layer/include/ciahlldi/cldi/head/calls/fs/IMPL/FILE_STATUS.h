
#ifndef _cldi_portable__calls_FILESTAT_H
#define _cldi_portable__calls_FILESTAT_H 1

#include "../../../setup.h"

#include "../../../types/basictypes.h"



#ifdef __cplusplus
extern "C" {
#endif
typedef enum _CLDI_FILE_STATUS
{
	CLDI_FILE_SUCCESS              = CLDI_SUCCESS,
	CLDI_FILE_NO_IMPLEMENTATION    = CLDI_NOIMPL,
	CLDI_FILE_NOMEM                = CLDI_NOMEM,

	CLDI_FILE_NULL_ARG             = CLDI_NULL_ARG,
	CLDI_FILE_FAILED_SUBROUTINE    = CLDI_FAILED_SUBROUTINE,
	CLDI_FILE_INADEQUATE_ARG       = CLDI_INADEQUATE_ARG,
	CLDI_FILE_INADEQUATE_ATTRIBUTE = CLDI_INADEQUATE_ATTRIBUTE,

	CLDI_FILE_ACCESS_FAIL,

	CLDI_FILE_OPEN_FAIL,
	CLDI_FILE_CLOSE_FAIL,
	CLDI_FILE_READ_FAIL,
	CLDI_FILE_WRITE_FAIL,

	CLDI_FILE_OVERFLOW,

	CLDI_FILE_NOT_DIR,
	CLDI_FILE_IS_DIR,
	CLDI_FILE_INVALID_FLAGS,
	CLDI_FILE_NONEXISTENT,
	CLDI_FILE_ALREADY_EXISTS,
	CLDI_FILE_NAME_TOO_LONG,
	CLDI_FILE_EXCESSIVE_LINKS,
} CLDI_FILE_STATUS, cldifilestat_t;
#ifdef __cplusplus
}
#	if __CLDI_no_cpp > false
namespace cldi
{
	using FILE_STATUS = cldifilestat_t;
	using filestat_t  = cldifilestat_t;

	constexpr auto FILE_SUCCESS              = CLDI_FILE_SUCCESS;

	constexpr auto FILE_NULL_ARG             = CLDI_FILE_NULL_ARG;
	constexpr auto FILE_FAILED_SUBROUTINE    = CLDI_FILE_FAILED_SUBROUTINE;
	constexpr auto FILE_INADEQUATE_ARG       = CLDI_FILE_INADEQUATE_ARG;
	constexpr auto FILE_INADEQUATE_ATTRIBUTE = CLDI_FILE_INADEQUATE_ATTRIBUTE;

	constexpr auto FILE_ACCESS_FAIL          = CLDI_FILE_ACCESS_FAIL;
	constexpr auto FILE_OPEN_FAIL            = CLDI_FILE_OPEN_FAIL;
	constexpr auto FILE_CLOSE_FAIL           = CLDI_FILE_CLOSE_FAIL;
	constexpr auto FILE_READ_FAIL            = CLDI_FILE_READ_FAIL;
	constexpr auto FILE_WRITE_FAIL           = CLDI_FILE_WRITE_FAIL;
}
#	endif
#endif



#endif /* _cldi_portable__calls_FILESTAT_H */
