
#ifndef _cldi_portable__calls_FS_H
#define _cldi_portable__calls_FS_H 1

#include "../setup.h"

/* Requires: cldi-portable: types/basic_types */
#include "../types/basictypes.h"
/*                          text/chartypes */
#include "../text/chartypes.h"
/*                          handles/text */
#include "../handles/text.h"



/* Path Name Seperator Charactor */
#if __CLDI_PLATFORM == CLDI_PLATFORM_WINDOWS
#define CLDI_PATH_SEP_CHAR  '\\'
#define CLDI_PATH_SEPERATOR "\\"
#else
#define CLDI_PATH_SEP_CHAR  '/'
#define CLDI_PATH_SEPERATOR "/"
#endif


/* ----------------------------------- */
/* --- File Operations --- */

	/* Include File Opening Options */
	#include "fs/IMPL/FILE_OPTIONS.h"
	/* Include File Status Markers */
	#include "fs/IMPL/FILE_STATUS.h"

	#ifdef __cplusplus
	extern "C" {
	#endif

	/* Check if a path exists on the filesystem. */
	bool cldiPathnameExists(const char * pathname);
	/* Checking if a path is that of a file or a directory. */
		/* On all but the following platforms, PathnameIsFile() will
		.  only ever return true, and PathnameIsDir() and PathnameIsLink()
		.  will only ever return false:
		.   - Windows
		.   - MacOS, Linux, and other Unix-based platforms */
	bool cldiPathnameIsFile(const char * pathname);
	bool cldiPathnameIsRegularFile(const char * pathname);
	bool cldiPathnameIsDir(const char * pathname);
	bool cldiPathnameIsLink(const char * pathname);
	bool cldiPathnameIsPipe(const char * pathname);
	bool cldiPathnameIsCharSpec(const char * pathname);
	bool cldiPathnameIsBlockSpec(const char * pathname);
	/* Alias for PathnameIsRegularFile(): */
	#define cldiPathnameIsRegFile cldiPathnameIsRegularFile

	/* Check path syntax to tell whether the pathname is a relative
	.  or absolute position. */
	bool cldiPathnameIsRel(const char * pathname);
	bool cldiPathnameIsAbs(const char * pathname);
	/* Calculate a relative path to the given pathname, or find the absolute
	.  designation of a relative path reference. */
	CLDISTRHANDLE cldiRelPathname(const char * pathname);
	CLDISTRHANDLE cldiAbsPathname(const char * pathname);
	const char *_cldi_objspawn_ cldiRelPathnameString(const char * pathname);
	const char *_cldi_objspawn_ cldiAbsPathnameString(const char * pathname);
	/* If the path is of a link rather than a physical file or directory, get
	.  get the absolute designation of the path that the link actually points to. */
	CLDISTRHANDLE cldiRealPathname(const char * pathname);
	const char *_cldi_objspawn_ cldiRealPathnameString(const char * pathname);
	/* Format the given path to be correct and readable. */
	CLDISTRHANDLE cldiGetCleanPathname(const char * pathname);
	const char *_cldi_objspawn_ cldiGetCleanPathnameString(const char * pathname);

	/* If a given pathname does not exist, create as a new file or directory. */
	cldifilestat_t cldiCreateNewFile(const char * pathname, long long permissions);
	cldifilestat_t cldiCreateNewDirectory(const char * pathname, long long permissions);
	#define          cldiCreateNewDir cldiCreateNewDirectory
	cldistat_t     cldiCreateNewFileD(const char * pathname);
	cldistat_t     cldiCreateNewDirectoryD(const char * pathname);
	#define          cldiCreateNewDirD cldiCreateNewDirectoryD
	/* If a given pathname does not exist, create as a new file or directory,
	.  and create parent directories if need be. */
	cldifilestat_t cldiCreateNewFileAndParent(const char * pathname);
	cldifilestat_t cldiCreateNewDirAndParent(const char * pathname);
	/* Rename a file or directory (without moving). */
	cldifilestat_t cldiRenamePathname(const char * pathname, const char * new_name);
	/* Move/rename a file or directory. */
	cldifilestat_t cldiMoveFile(const char * pathname, const char * new_location);
	cldifilestat_t cldiMoveDir(const char * pathname, const char * new_location);
	/* Move a file or directory to a new place with a new name. */
	cldifilestat_t cldiEditPathname(const char * pathname, const char * rename_to);
	/* Delete a file or directory. */
	cldifilestat_t cldiRemoveFile(const char * pathname); /* file, don't otherwise */
	cldifilestat_t cldiRemoveDir(const char * pathname);  /* dir, don't otherwise  */
	cldifilestat_t cldiRemovePathname(const char * pathname); /* either */

	/* Checking file permissions. */
	long long     cldiGetPathnamePermissions(const char * pathname);
	/* Get the name of the owner of the file or directory. */
	CLDISTRHANDLE cldiGetPathnameOwner(const char * pathname);
	const char *_cldi_objspawn_ cldiGetPathnameOwnerString(const char * pathname);
	/* Get the name of the owner group of the file or directory,
	.  if no groups, or groups do not exist on the current system,
	.  return the owner's name. */

	CLDISTRHANDLE cldiGetPathnameGroup(const char * pathname);
	const char *_cldi_objspawn_ cldiGetPathnameGroupString(const char * pathname);

	#ifdef __cplusplus
	}
	#	if __CLDI_no_cpp > false
	namespace cldi
	{
		constexpr auto PathnameExists         = cldiPathnameExists;
		constexpr auto PathnameIsFile         = cldiPathnameIsFile;
		constexpr auto PathnameIsDir          = cldiPathnameIsDir;
		constexpr auto PathnameIsLink         = cldiPathnameIsLink;
		constexpr auto PathnameIsRel          = cldiPathnameIsRel;
		constexpr auto PathnameIsAbs          = cldiPathnameIsAbs;
		constexpr auto RelPathname            = cldiRelPathname;
		constexpr auto AbsPathname            = cldiAbsPathname;
		constexpr auto RealPathname           = cldiRealPathname;
		constexpr auto GetCleanPathname       = cldiGetCleanPathname;

		constexpr auto CreateNewFile          = cldiCreateNewFile;
		constexpr auto CreateNewDir           = cldiCreateNewDir;
		constexpr auto CreateNewFileAndParent = cldiCreateNewFileAndParent;
		constexpr auto CreateNewDirAndParent  = cldiCreateNewDirAndParent;
		constexpr auto RenameFile             = cldiRenameFile;
		constexpr auto MoveFile               = cldiMoveFile;
		constexpr auto MoveDir                = cldiMoveDir;
		constexpr auto RenamePathname         = cldiRenamePathname;
		constexpr auto RemoveFile             = cldiRemoveFile;
		constexpr auto RemoveDir              = cldiRemoveDir;
		constexpr auto RemovePathname         = cldiRemovePathname;

		constexpr auto GetPathnamePermissions = cldiGetPathnamePermissions;
		constexpr auto GetPathnameOwner       = cldiGetPathnameOwner;
		constexpr auto GetPathnameGroup       = cldiGetPathnameGroup;
	}
	#	endif
	#endif


/* ----------------------------------- */
/* --- File IO --- */

	#ifdef __cplusplus
	extern "C" {
	#endif

	/* Open file from `filename` path in `file_options` mode/options. */
	FILE * cldiOpenFile(
		const char * pathname,
			/* A filesystem path to the file to
			.  open (in string form). */
		long long    options
			/* Bitwise combination of options from
			.  the enum `CLDI_FILE_OPTIONS`. */
	);
	/* OpenFile(), but takes more arguments on how to run, and provides an error code. */
	cldifilestat_t cldiOpenFileEx(
		FILE      ** file_return,
			/* An output reference for a FILE* return value. */
		const char * pathname, long file_options
			/* Same 2 arguments as from OpenFile(). */
	);
	/* fopen() surrogate */
	#define cldiOpenFile_s fopen

	/* Close a file. */
	cldifilestat_t cldiCloseFile(FILE * file);

	/* Flush the writing buffer of a file. */
	cldifilestat_t cldiFlushFileBuffer(FILE * file);
	/* Clears all buffers of `file`. */
	cldifilestat_t cldiClearFileBuffers(FILE * file);
	/* Clears the file's reading buffer. */
	cldifilestat_t cldiClearFileRBuffer(FILE * file);
	/* Clears the file's writing buffer. */
	cldifilestat_t cldiClearFileWBuffer(FILE * file);

	/* Write zero-terminated, c-style string to `file`. */
	cldifilestat_t cldiFilePrint(
		FILE            * file,
		const char      * string
	);
	/* Write zero-terminated, c-style string to `file`, takes more command on how
	.  exactly to do so. */
	cldifilestat_t cldiFilePrintEx(
		FILE            * file,
		const char      * string,
		bool              single_line
	);
	/* Writes zero-terminated, c-style string to buffer of `file` without flushing. */
	cldifilestat_t cldiFileWrite(
		FILE            * file,
		const char      * string
	);
	/* Writes zero-terminated, c-style string to buffer of `file` without flushing,
	.  takes more command on how exactly to do so. */
	cldifilestat_t cldiFileWriteEx(
		FILE            * file,
		const char      * string,
		bool              single_line
	);

	/* Write a echar_t string to a file. */
	cldifilestat_t cldiFilePrintWC(
		FILE            * file,
		const wchar_t   * string
	);
	/* Write a wchar_t string to a file, takes more command on how exactly
	.  to do so. */
	cldifilestat_t cldiFilePrintExWC(
		FILE            * file,
		const wchar_t   * string,
		bool              single_line
	);
	/* Write a wchar_t string to the buffer of `file` without flushing. */
	cldifilestat_t cldiFileWriteWC(
		FILE            * file,
		const wchar_t   * string
	);
	/* Write a wchar_t string to the buffer of `file` without flushing,
	.  takes more command on how exactly to do so. */
	cldifilestat_t cldiFileWriteExWC(
		FILE            * file,
		const wchar_t   * string,
		bool              single_line
	);

	/* Write a string of some encoding to a file. */
	cldifilestat_t cldiFilePrintEncoded(
		CLDI_CHARTYPE     string_encoding,
		FILE            * file,
		cldifnamemax_t    string_length,
		const void *const string
	);
	/* Write a string of some encoding to a file, takes more command on how exactly
	.  to do so. */
	cldifilestat_t cldiFilePrintEncodedEx(
		CLDI_CHARTYPE     string_encoding,
		FILE            * file,
		cldifnamemax_t    string_length,
		const void *const string,
		bool              single_line
	);
	/* Write a string of some encoding to the buffer of `file` without flushing. */
	cldifilestat_t cldiFileWriteEncoded(
		CLDI_CHARTYPE     string_encoding,
		FILE            * file,
		cldifnamemax_t    string_length,
		const void *const string
	);
	/* Write a string of some encoding to the buffer of `file` without flushing,
	.  takes more command on how exactly to do so. */
	cldifilestat_t cldiFileWriteEncodedEx(
		CLDI_CHARTYPE     string_encoding,
		FILE            * file,
		cldifnamemax_t    string_length,
		const void *const string,
		bool              single_line
	);

	/* Write array to `file`. */
	cldifilestat_t cldiFilePrintArray(
		FILE            * file,
		cldifnamemax_t    array_size,
		size_t        array_member_size,
		const void *const array
	);
	/* Write string to `file`, takes more command
	.  on how exactly to do so. */
	cldifilestat_t cldiFilePrintArrayEx(
		FILE            * file,
		cldifnamemax_t    array_size,
		size_t        array_member_size,
		const void *const array,
		bool              single_line
	);
	/* Writes array to buffer of `file` without flushing. */
	cldifilestat_t cldiFileWriteArray(
		FILE            * file,
		cldifnamemax_t    array_size,
		size_t        array_member_size,
		const void *const array
	);
	/* Writes zero-terminated, c-style string to buffer of `file` without flushing,
	.  takes more command on how exactly to do so. */
	cldifilestat_t cldiFileWriteArrayEx(
		FILE            * file,
		cldifnamemax_t    array_size,
		size_t        array_member_size,
		const void *const array,
		bool              single_line
	);

	/* Write formatted output to the file specified, using a zero-terminated, c-style
	.  string to represent the format pattern to write. */
	cldifilestat_t cldiFilePrintf(FILE * file, const char * format_string, ...);
	/* Write formatted output to the file specified, using a zero-terminated, c-style
	.  string to represent the format pattern to write. */
	cldifilestat_t cldiFilePrintfWC(FILE * file, const wchar_t * format_string, ...);

	/* Reads file contents and copies them to an output array. */
	cldifilestat_t cldiFileRead(
		FILE       * file,
		void const * output,
		size_t   max_chars
	);
	/* Reads file contents and copies them to an output array,
	.  takes more command on how exactly to do so (other encoding types, etc.). */
	cldifilestat_t cldiFileReadEx(
		FILE       * file,
		void const * output,
		size_t   max_chars,
		bool         single_line
	);
	/* Reads buffer data into passed array (data already found in the buffer). */
	cldifilestat_t cldiFileReadBuff(
		FILE       * file,
		void const * output,
		size_t   max_chars
	);
	/* Reads buffer data into passed array (data already found in the buffer),
	.  takes more command on how exactly to do so (other encoding types, etc.). */
	cldifilestat_t cldiFileReadBuffEx(
		FILE       * file,
		void const * output,
		size_t   max_chars,
		bool         single_line
	);

	/* Reads file contents and copies them to an output array. */
	cldifilestat_t cldiFileReadWC(
		FILE     * file,
		wchar_t  * output,
		size_t max_chars
	);
	/* Reads file contents and copies them to an output array,
	.  takes more command on how exactly to do so (other encoding types, etc.). */
	cldifilestat_t cldiFileReadExWC(
		FILE     * file,
		wchar_t  * output,
		size_t max_chars,
		bool       single_line
	);
	/* Reads buffer data into passed array (data already found in the buffer). */
	cldifilestat_t cldiFileReadBufferWC(
		FILE     * file,
		wchar_t  * output,
		size_t max_chars
	);
	/* Reads buffer data into passed array (data already found in the buffer),
	.  takes more command on how exactly to do so (other encoding types, etc.). */
	cldifilestat_t cldiFileReadBufferExWC(
		FILE     * file,
		wchar_t  * output,
		size_t max_chars,
		bool       single_line
	);

	/* Reads file contents and copies them to an output array. */
	cldifilestat_t cldiFileReadEncoded(
		FILE       * file,
		void const * output,
		size_t   max_chars
	);
	/* Reads file contents and copies them to an output array,
	.  takes more command on how exactly to do so (other encoding types, etc.). */
	cldifilestat_t cldiFileReadEncodedEx(
		FILE       * file,
		void const * output,
		size_t   max_chars,
		bool         single_line
	);
	/* Reads buffer data into passed array (data already found in the buffer). */
	cldifilestat_t cldiFileReadBufferEncoded(
		FILE       * file,
		void const * output,
		size_t   max_chars
	);
	/* Reads buffer data into passed array (data already found in the buffer),
	.  takes more command on how exactly to do so (other encoding types, etc.). */
	cldifilestat_t cldiFileReadBufferEncodedEx(
		FILE       * file,
		void const * output,
		size_t   max_chars,
		bool         single_line
	);

	/* Read file text, scanning with a given format regex, format arguments will
	.  provide output. */
	cldifilestat_t cldiFileScanf(FILE * file, const char * format, ...);
	/* Read file text, scanning with a given format regex, provided in some encoding format,
	.  format arguments will provide output. */
	cldifilestat_t cldiFileScanfWC(FILE * file, const wchar_t * format, ...);

	#ifdef __cplusplus
	}
	#	if __CLDI_no_cpp > false
	namespace cldi
	{
		constexpr auto OpenFile                = cldiOpenFile;
		constexpr auto OpenFileEx              = cldiOpenFileEx;
		constexpr auto OpenFile_s              = fopen;

		constexpr auto CloseFile               = cldiCloseFile;

		constexpr auto FlushFileBuffer         = cldiFlushFileBuffer;
		constexpr auto ReadFileToBuffer        = cldiReadFileToBuffer;

		constexpr auto ClearFileBuffers        = cldiClearFileBuffers;
		constexpr auto ClearFileBuffer         = cldiClearFileBuffer;

		constexpr auto FilePrint               = cldiFilePrint;
		constexpr auto FilePrintEx             = cldiFilePrintEx;
		constexpr auto FileWrite               = cldiFileWrite;
		constexpr auto FileWriteEx             = cldiFileWriteEx;

		constexpr auto FilePrintWC             = cldiFilePrintWC;
		constexpr auto FilePrintExWC           = cldiFilePrintExWC;
		constexpr auto FileWriteWC             = cldiFileWriteWC;
		constexpr auto FileWriteExWC           = cldiFileWriteExWC;

		constexpr auto FilePrintEncoded        = cldiFilePrintEncoded;
		constexpr auto FilePrintEncodedEx      = cldiFilePrintEncodedEx;
		constexpr auto FileWriteEncoded        = cldiFileWriteEncoded;
		constexpr auto FileWriteEncodedEx      = cldiFileWriteEncodedEx;

		constexpr auto FilePrintArray          = cldiFilePrintArray;
		constexpr auto FilePrintArrayEx        = cldiFilePrintArrayEx;
		constexpr auto FileWriteArray          = cldiFileWriteArray;
		constexpr auto FileWriteArrayEx        = cldiFileWriteArrayEx;

		constexpr auto FilePrintf              = cldiFilePrintf;
		constexpr auto FilePrintfWC            = cldiFilePrintfWC;

		constexpr auto FileRead                = cldiFileRead;
		constexpr auto FileReadEx              = cldiFileReadEx;
		constexpr auto FileReadBuffer          = cldiFileReadBuffer;
		constexpr auto FileReadBufferEx        = cldiFileReadBufferEx;

		constexpr auto FileReadWC              = cldiFileReadWC;
		constexpr auto FileReadExWC            = cldiFileReadExWC;
		constexpr auto FileReadBufferWC        = cldiFileReadBufferWC;
		constexpr auto FileReadBufferExWC      = cldiFileReadBufferExWC;

		constexpr auto FileReadEncoded         = cldiFileReadEncoded;
		constexpr auto FileReadEncodedEx       = cldiFileReadEncodedEx;
		constexpr auto FileReadBufferEncoded   = cldiFileReadBufferEncoded;
		constexpr auto FileReadBufferEncodedEx = cldiFileReadBufferEncodedEx;

		constexpr auto FileScanf               = cldiFileScanf;
		constexpr auto FileScanfWC             = cldiFileScanfWC;
	}
	#	endif
	#endif


/* ----------------------------------- */
/* ----- Standard Pipe Operations ----- */

	#ifdef __cplusplus
	extern "C" {
	#endif

	/* Flush the stdout buffer (push buffer contents to pipe). */
	int cldiFlushStdout(void);
	/* Flush stderr. */
	int cldiFlushStderr(void);
	/* Take input (up to maximum character amount) from stdin, write to buffer without
	.  copying to an external output array, ending when a line feed, or other whitespace
	.  character is given. */
	int cldiGetStdin();
	/* Take input (up to maximum character amount) from stdin, write to buffer without copying
	.  to an external output array, ending when a line feed character is explicitly entered. */
	int cldiGetLnStdin();

	/* Write a c-style, zero-terminated string of `string_length` length to stdout. */
	int cldiPrint(const char * string);
	int cldiPrintln(const char*);
	/* Write a wchar_t array to stdout as UTF-16. */
	int cldiPrintWC(const wchar_t * string);
	int cldiPrintlnWC(const wchar_t*);
	/* Write a string of some encoding to stdout. */
	int cldiPrintEncoded(
		CLDI_CHARTYPE string_encoding,
		int           string_length,
		const char  * string
	);
	int cldiPrintlnEncoded(CLDI_CHARTYPE, int, const char*);

	/* Write a c-style, zero-terminated string of `string_length` length to stdout. */
	int cldiPrintf(const char * format_string, ...);
	/* Write a wchar_t string to stdout. */
	int cldiPrintfWC(const wchar_t * format_string, ...);
	/* Write a string of some encoding to stdout. */
	int cldiPrintfEncoded(
		CLDI_CHARTYPE     format_string_encoding,
		size_t        format_string_length,
		const void *const format_string,
		...
	);

	/* Write a c-style, zero-terminated string of `string_length` length to stderr. */
	int cldiPrintErr(const char * string);
	int cldiPrintlnErr(const char*);
	/* Write a c-style, zero-terminated string of `string_length` length to stderr. */
	int cldiPrintErrWC(const wchar_t * string);
	int cldiPrintlnErrWC(const wchar_t*);
	/* Write a string of some encoding to stderr. */
	int cldiPrintErrEncoded(
		CLDI_CHARTYPE string_encoding,
		int           string_length,
		const char  * string
	);
	int cldiPrintlnErrEncoded(CLDI_CHARTYPE, size_t, const char*);

	/* Extract character data from the stdin buffer, copying it to an output array. */
	int cldiReadBuff(char * output, int max_byte_capacity);
	int cldiReadBuffLn(char *      , int);
	/* Take input from stdin, then copy data from the buffer to an output array. */
	int cldiRead(char * output, int max_byte_capacity);
	int cldiReadLn(char *       , int);

	/* Read file text, scanning with a given format regex, format arguments will
	.  provide output. */
	int cldiScanf(const char * format, ...);
	/* Read file text, scanning with a given format regex, provided in some encoding format,
	.  format arguments will provide output. */
	int cldiScanfWC(const wchar_t * format, ...);

	#ifdef __cplusplus
	}
	#	if __CLDI_no_cpp > false
	namespace cldi
	{
		constexpr auto FlushStdout       = cldiFlushStdout;
		constexpr auto FlushStderr       = cldiFlushStderr;
		constexpr auto GetStdin          = cldiGetStdin;
		constexpr auto GetLnStdin        = cldiGetLnStdin;

		constexpr auto Print             = cldiPrint;
		constexpr auto Println           = cldiPrintln;
		constexpr auto PrintWC           = cldiPrintWC;
		constexpr auto PrintlnWC         = cldiPrintlnWC;
		constexpr auto PrintEncoded      = cldiPrintEncoded;
		constexpr auto PrintlnEncoded    = cldiPrintlnEncoded;

		constexpr auto Printf            = cldiPrintf;
		constexpr auto PrintfWC          = cldiPrintfWC;

		constexpr auto PrintErr          = cldiPrintErr;
		constexpr auto PrintlnErr        = cldiPrintlnErr;
		constexpr auto PrintErrWC        = cldiPrintErrWC;
		constexpr auto PrintlnErrWC      = cldiPrintlnErrWC;
		constexpr auto PrintErrEncoded   = cldiPrintErrEncoded;
		constexpr auto PrintlnErrEncoded = cldiPrintlnErrEncoded;

		constexpr auto PrintfErr         = cldiPrintfErr;
		constexpr auto PrintfErrWC       = cldiPrintfErrWC;

		constexpr auto ReadBuffer        = cldiReadBuffer;
		constexpr auto ReadLnBuffer      = cldiReadLnBuffer;
		constexpr auto Read              = cldiRead;
		constexpr auto ReadLn            = cldiReadLn;

		constexpr auto Scanf             = cldiScanf;
		constexpr auto ScanfWC           = cldiScanfWC;
	}
	#	endif
	#endif


/* ----------------------------------- */



#endif /* _cldi_portable__calls_FS_H */
