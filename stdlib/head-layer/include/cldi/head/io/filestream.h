
#ifndef _cldi_head__io_FILE_H
#define _cldi_head__io_FILE_H 1

#ifndef _cldi_head__MEMORY_H
#	include "path.h"
#endif



/* File Buffer Flags enum;
.  - 'rwx' (bits 0-2, 3-5, & 6-8): These are permission bits for the public,
.                                  group, and owner domains respectively.
.  - 'O' (bit 9): This bit corresponds to whether the buffer or stream is open.
.  - 'E' (bit 10): This is the EOF bit, it is marked as 1 once the stream or
.                  buffer has reached the end of the file. */
typedef enum _CLDIFBUFFLAGS //          ownr: grp: all:
{ //                                    E O rwx rwx rwx
	CLDI_FBUFFLAGS_NULL = 0,     // 000 0 0 000 000 000

	CLDI_FBUF_PREAD     = 04,    // 000 0 0 000 000 100
	CLDI_FBUF_PWRTE     = 02,    // 000 0 0 000 000 010
	CLDI_FBUF_PEXEC     = 01,    // 000 0 0 000 000 001
	CLDI_FBUF_PPERMS    = 07,    // 000 0 0 000 000 111

	CLDI_FBUF_GREAD     = 040,   // 000 0 0 000 100 000
	CLDI_FBUF_GWRTE     = 020,   // 000 0 0 000 010 000
	CLDI_FBUF_GEXEC     = 010,   // 000 0 0 000 001 000
	CLDI_FBUF_GPERMS    = 070,   // 000 0 0 000 111 000

	CLDI_FBUF_OREAD     = 0400,  // 000 0 0 100 000 000
	CLDI_FBUF_OWRTE     = 0200,  // 000 0 0 010 000 000
	CLDI_FBUF_OEXEC     = 0100,  // 000 0 0 001 000 000
	CLDI_FBUF_OPERMS    = 0700,  // 000 0 0 111 000 000

	CLDI_FBUF_OPEN      = 01000, // 000 0 1 000 000 000

	CLDI_FBUF_EOF       = 02000, // 000 1 0 000 000 000

	/* Defaults */
	// Read/Write file buffer
	CLDI_DEFAULT_FBUF  = 0666,   // 000 0 0 110 110 110
	// Input file buffer
	CLDI_DEFAULT_IFBUF = 0444,   // 000 0 0 100 100 100
	// Output file buffer
	CLDI_DEFAULT_OFBUF = 0222,   // 000 0 0 010 010 010
	// Library file buffer (executable)
	CLDI_DEFAULT_LFBUF = 0555,   // 000 0 0 101 101 101
} CLDI_FBUF_FLAG;

/* Printing Format Flags enum;
.  - 'W' (bits 0-7): The maximum width to fit the string into, default: 255 (max).
.  - 'P' (bits 8-12): The maximum precision to fit the string into, if the value
.                     is negative (bit 12 is set), the precision is default based
.                     on the type entered.
.  - 'X' (bits 13 & 14): The numerary format to print in (decimal (default), octal,
.                        binary, hexadecimal).
.  - 'E' (bits 15 & 16): The rules adopted regarding exponential notation,
.                        00 = disabled, 01 = allowed, 10 = forced, 11 = forced and
.                        decimal-only.
.  - 'U' (bit 17): This bit forces number types to be presented as unsigned, floating-
.                  point types are not affected.
.  - 'I' (bit 18): This bit forces number types to be presented as 2's-compliment,
.                  signed integers, if this bit as well as the "unsigned" bit are set,
.                  the number will be interpreted as an "Offset Binary" signed integer,
.                  floating-point types will not be affected.
.  - '+' (bit 19): This bit forces positive numbers to be presented with the positive
.                  sign.
.  - 'S' (bit 20): This bit indicates to truncate the end of any text that doesn't
.                  fit inside a specified width.
.  - 'C' (bits 22 & 23): Bit 22 indicates a 'clear' maximum width, allowing the up
.                        to the full limit of characters indexed by a 64-bit unsigned
.                        integer, while bit 23 indicates a clear maximum precision,
.                        the maximum relevant precision allowed by a given data type. */
typedef enum _CLDIPRFLAGS // requires size: long long
{ //                                       C  p S + I U E  X  P     W
	CLDI_PRFLAGS_NULL      = 0,         // 00 0 0 0 0 0 00 00 00000 00000000

	CLDI_PRWIDTH_BIAS      = 0,         // flags |= (width&CLDI_PRWIDTH_MASK) + 0 // integrate into flags
	CLDI_PRWIDTH_MASK      = 255,       // 00 0 0 0 0 0 00 00 00000 11111111
	CLDI_PRWIDTH_BSHFT     = 0, // Value place offset of these bits

	CLDI_PRPRECISION_BIAS  = 255,       // flags |= (precision+255) & CLDI_PRPRECISION_MASK // integrate into flags
	CLDI_PRPRECISION_MASK  = 0x1f00,    // 00 0 0 0 0 0 00 00 11111 00000000
	CLDI_PRPRECISION_BSHFT = 8,

	CLDI_PRDEC             = 0x0000,    // 00 0 0 0 0 0 00 00 00000 00000000
	CLDI_PRHEX             = 0x2000,    // 00 0 0 0 0 0 00 01 00000 00000000
	CLDI_PROCT             = 0x4000,    // 00 0 0 0 0 0 00 10 00000 00000000
	CLDI_PRBIN             = 0x6000,    // 00 0 0 0 0 0 00 11 00000 00000000
	CLDI_PRNUMFMT_MASK     = 0x6000,    // 00 0 0 0 0 0 00 11 00000 00000000
	CLDI_PRNUMFMT_BSHFT    = 13,        // 00 0 0 0 0 0 00 11 00000 00000000

	/* Disable exponential notation. */
	CLDI_PRNOXPN           = 0x00000,   // 00 0 0 0 0 0 00 00 00000 00000000
	/* Allow exponential notation for large numbers. */
	CLDI_PRALLOWXPN        = 0x08000,   // 00 0 0 0 0 0 01 00 00000 00000000
	/* Force exponential notation in current number format. */
	CLDI_PRFORCEXPN        = 0x10000,   // 00 0 0 0 0 0 10 00 00000 00000000
	/* Force decimal-only exponential notation. */
	CLDI_PRDECXPN          = 0x18000,   // 00 0 0 0 0 0 11 00 00000 00000000
	CLDI_PRXPN_BSHFT       = 15,

	/* Unsigned and Signed mode */
	CLDI_PRUNSIGNED        = 0x20000,   // 00 0 0 0 0 1 00 00 00000 00000000
	CLDI_PRSIGNED          = 0x40000,   // 00 0 0 0 1 0 00 00 00000 00000000

	/* Show positive sign */
	CLDI_PRSHOWPOS         = 0x80000,   // 00 0 0 1 0 0 00 00 00000 00000000

	/* Strict width and precision */
	CLDI_PRSTRICTW         = 0x100000,  // 00 0 1 0 0 0 00 00 00000 00000000
	CLDI_PRSTRICTP         = 0x200000,  // 00 1 0 0 0 0 00 00 00000 00000000

	/* Clear bits */
	CLDI_PRCLEARW          = 0x400000,  // 01 0 0 0 0 0 00 00 00000 00000000
	CLDI_PRCLEARP          = 0x800000,  // 10 0 0 0 0 0 00 00 00000 00000000
	CLDI_PRCLEAR_MASK      = 0xc00000,  // 11 0 0 0 0 0 00 00 00000 00000000
	CLDI_PRCLEAR_BSHFT     = 22,
} CLDI_PRFLAGS, CLDI_PRINT_FLAGS;
/* Scan/Print Format codes:
.  - All printf() codes are valid in this format
.  - All options that take an argument do so from the variadic set of arguments
.    passed to the ScanF() or PrintF() method that was called.
.  - '%-y?' and '%-n?': Where '?' is one of the TOGGLABLE options below, y sets
.                       to true, where n sets to false.
.  - '%-c?': Where '?' is one of the CLEARABLE options below, c clears that
.            option to default
.  - '%-sw': Set width as strict (truncate data that doesn't fit).
.  - '%-sp': Restrict precision to right-hand side of a decimal point for
.            floating-point numbers.
.  - '%-x': Set number format to hexidecimal (togglable, clearable)
.  - '%-d': Set number format to decimal (togglable, clearable)
.  - '%-o': Set number format to octal (togglable, clearable)
.  - '%-b': Set number format to binary (togglable, clearable)
.  - '%-u': Set to unsigned mode (togglable, clearable)
.  - '%-i': Set to signed mode (togglable, clearable)
.  - '%-e': Toggle 'allow' exponential notation bit (when paired with 'force',
.           decimal-only exp. notation will be enforced) (togglable, clearable)
.  - '%-E': Toggle 'force' exponential notation (togglable, clearable)
.  - '%-+': Toggle the 'Show Positive Sign' bit (togglable, clearable)
.  - '%-w': Set width to next argument (takes int argument, clearable)
.  - '%-p': Set precision to next argument (takes int argument, clearable)
.  - '%ws': Format code for wchar_t string
.  - '%wc': Format code for wchar_t
.*/

/* File Seek Positioning enum; */
typedef enum _CLDIFSEEKPOS
{
	CLDI_FSEEK_CURRENT = 0,
	
	CLDI_FSEEK_END,
	CLDI_FSEEK_BEG,
	CLDI_FREL_CURRENT  = CLDI_FSEEK_CURRENT,
	CLDI_FREL_END      = CLDI_FSEEK_END,
	CLDI_FREL_BEG      = CLDI_FSEEK_BEG
} CLDI_FSEEK_POS, CLDI_FREL_POS;

/* File Buffer type :
.  For writing to and reading from files in a multithreaded environment. */
typedef struct _CLDIFILEBUF
{
	cldipath_t         path;
	FILE              *stream;
	unsigned long long flags, errserial;
	CLDISTAT           errno;
} cldifilebuf_t;

/* Methods associated with cldifilebuf_t: */

/* Construct as blank (null) instance. */
cldifilebuf_t* cldiInitFileBuf(cldifilebuf_t *self);
/* Construct from a FILE*. */
cldifilebuf_t* cldiInitFileBufStream(cldifilebuf_t *self, FILE *stream, long long flags);
/* Construct from a file descriptor. */
cldifilebuf_t* cldiInitFileBufFD(cldifilebuf_t *self, int fd, long long flags);
/* Construct with stream to stdin pipe. */
cldifilebuf_t* cldiInitFileBufStdin(cldifilebuf_t *self);
/* Construct with stream to stdout pipe. */
cldifilebuf_t* cldiInitFileBufStdout(cldifilebuf_t *self);
/* Construct with stream to stderr pipe. */
cldifilebuf_t* cldiInitFileBufStderr(cldifilebuf_t *self);
/* Allocate a new instance in the heap. */
cldimemref cldiNewFileBuf();
cldimemref cldiNewFileBufStream(FILE *stream, long long flags);
cldimemref cldiNewFileBufFD(int fd, long long flags);
cldimemref cldiNewFileBufStdin();
cldimemref cldiNewFileBufStdout();
cldimemref cldiNewFileBufStderr();

/* Get stream flags. */
cldifilebuf_t*    cldiFileBufFlags(const cldifilebuf_t *self);
/* Get path. */
const cldipath_t* cldiFileBufPath(const cldifilebuf_t *self);
/* Get stream (FILE*). */
const FILE*       cldiFileBufStream(const cldifilebuf_t *self);
/* Get error state. */
CLDISTAT          cldiFileBufErrno(const cldifilebuf_t *self);

/* Set stream flags. */
cldifilebuf_t*    cldiFileBufSetFlags(cldifilebuf_t *self, long long strmflags);
/* Set path and open a stream to the file at that path. */
cldifilebuf_t*    cldiFileBufSetPath(cldifilebuf_t *self, const cldipath_t *path);
/* Set path to null and open to stream. */
cldifilebuf_t*    cldiFileBufSetStream(cldifilebuf_t *self, FILE *path);
/* Clear error state. */
CLDISTAT          cldiFileBufClearErr(cldifilebuf_t *self);
/* Check if the file has a path. */
bool              cldiFileBufHasPath(const cldifilebuf_t *self);

/* Write to the file. */
size_t cldiFileBufWrite(cldifilebuf_t *self, size_t len, size_t nmemb, const void *array);
/* Write a c-style string to the file. */
size_t cldiFileBufWriteCStr(cldifilebuf_t *self, const char *str);
// - Supply a specified length
size_t cldiFileBufWriteNCStr(cldifilebuf_t *self, size_t len, const char *str);
/* Write a wchar string to the file. */
size_t cldiFileBufWriteWStr(cldifilebuf_t *self, const wchar_t *str);
// - Supply a specified length
size_t cldiFileBufWriteNWStr(cldifilebuf_t *self, size_t len, const wchar_t *str);
/* Write a cldistring_t to the file. */
size_t cldiFileBufWriteStr(cldifilebuf_t *self, const cldistr_t *str);


/* Basic File Stream tyoe */
typedef struct _CLDIFSTREAM
{
	cldifilebuf_t stream;
	long long     prflags;
} cldifstream_t;

/* Methods associated with cldifstream_t: */

// For all InitFStream() and NewFStream() methods that construct from an object
// that have already-initialized flags/permissions (such as FILE* or cldifilebuf_t*),
// the flags that may or may not be passed in will be gated by the flags that are
// already present in the given file interaction object that contains those
// already-initialized flags. These functions will not have a form containing the 'M'
// suffix, which refers to FStream and FileBuf objects being initialized with a
// text-based file-mode operand, such as "r+", "wb", etc., instead the default isomorph
// of each of these methods takes in only the already-initialized file interaction
// object, and an 'Ex' suffixed isomorph for each will take in additional stream
// flags that may be merged with the object. -- This applies to InitFileBuf() and
//                                              NewFileBuf() functions as well.

// For all InitFStream(), InitFileBuf(), NewFStream(), and NewFileBuf() functions
// that do not take in an object that is already-initialized as a file interaction
// medium (such as const char* and cldipath_t as a sole file reference, no cldifilebuf_t
// included), two isomorphs total are included: the default isomorph (InitFStreamPath(),
// InitFileBufPathS(), etc.) which take in only the file interaction object and
// stream flags identifying permissions/flags for the file interactions, and the
// 'M' suffixed isomorph for taking in the file mode as a text-based operand (such
// as "rw", "wx", etc.)

/* Construct as blank (null) instance. */
cldifstream_t* cldiInitFStream(cldifstream_t *self) CLDINOEXCEPT;
/* Construct with a FILE*. */
cldifstream_t* cldiInitFStreamFile(cldifstream_t *self, FILE *buf);
/* Construct with a FILE* and specified stream flags. */
cldifstream_t* cldiInitFStreamFileEx(cldifstream_t *self, FILE *buf, long long flags);
/* Construct with a path object. */
cldifstream_t* cldiInitFStreamPath(cldifstream_t *self, cldipath_t *path, long long flags);
/* Construct with a path object and file mode. */
cldifstream_t* cldiInitFStreamPathM(cldifstream_t *self, cldipath_t *path, const char *mode);
/* Construct with a path string. */
cldifstream_t* cldiInitFStreamPathS(cldifstream_t *self, const char *path, long long flags);
/* Construct with a path string and file mode. */
cldifstream_t* cldiInitFStreamPathSM(cldifstream_t *self, const char *path, const char *mode);
#define cldiInitFStreamPathMS cldiInitFStreamPathSM
/* Construct with a file buffer. */
cldifstream_t* cldiInitFStreamFileBuf(cldifstream_t *self, cldifilebuf_t *buf);
/* Construct with a file buffer and specified stream flags. */
cldifstream_t* cldiInitFStreamFileBufEx(cldifstream_t *self, cldifilebuf_t *buf, long long flags);
/* Allocate a new instance in the heap: */
cldimemref cldiNewFStream();
cldimemref cldiNewFStreamFile(FILE *buf);
cldimemref cldiNewFStreamFileEx(FILE *buf, long long flags);
cldimemref cldiNewFStreamPath(cldipath_t *path, long long flags);
cldimemref cldiNewFStreamPathM(cldipath_t *path, const char *mode);
cldimemref cldiNewFStreamPathS(const char *path, long long flags);
cldimemref cldiNewFStreamPathSM(const char *path, const char *mode);
#define    cldiNewFStreamPathMS cldiNewFStreamPathSM
cldimemref cldiNewFStreamFileBuf(cldifilebuf_t *buf);
cldimemref cldiNewFStreamFileBufEx(cldifilebuf_t *buf, long long flags);

/* Wrap an already-initialized FILE* object. */
cldifstream_t* cldiFStreamOpenFile(cldifstream_t *self, FILE *buf);
/* Wrap an already-initialized FILE* object and attempt to merge specified stream flags. */
cldifstream_t* cldiFStreamOpenFileEx(cldifstream_t *self, FILE *buf, long long flags);
/* Open stream to file path. */
cldifstream_t* cldiFStreamOpenPath(cldifstream_t *self, const cldipath_t *path, const char *mode);
/* Open stream to file path string. */
cldifstream_t* cldiFStreamOpenPathS(cldifstream_t *self, const char *path, const char *mode);
/* Open stream to file path with stream flags. */
cldifstream_t* cldiFStreamOpenPathM(cldifstream_t *self, const cldipath_t *path, long long flags);
/* Open stream to file path string with stream flags. */
cldifstream_t* cldiFStreamOpenPathSM(cldifstream_t *self, const char *path, long long flags);
#define cldiFStreamOpenPathMS cldiFStreamOpenPathSM
#define cldiFStreamOpen       cldiFStreamOpenPathS
#define cldiOpenFile          cldiFStreamOpenPathS
/* Open an already-initialized cldifilebuf_t object. */
cldifstream_t* cldiFStreamOpenFileBuf(cldifstream_t *self, cldifilebuf_t *buf);
/* Open an already-initialized cldifilebuf_t object and attempt to merge specified stream flags. */
cldifstream_t* cldiFStreamOpenFileBufEx(cldifstream_t *self, cldifilebuf_t *buf, long long flags);

/* Close file stream. */
CLDISTAT       cldiCloseFStream(cldifstream_t *self);
/* Close file stream in the heap. */
CLDISTAT       cldiCloseFStreamInstance(cldimemref *self);
#define cldiCloseFile cldiCloseFStream

const cldipath_t*    cldiFStreamPath(const cldifstream_t *self);
long long            cldiFStreamPrintFlags(const cldifstream_t *self);
long long            cldiFStreamStreamFlags(const cldifstream_t *self);
const cldifilebuf_t* cldiFStreamGetBuf(const cldifstream_t *self);

/* Clear the current error state. */
CLDISTAT             cldiFStreamClearErr(cldifstream_t *self);

bool cldiFSreamIsOpen(const cldifstream_t *self);
bool cldiFSreamIsFile(const cldifstream_t *self);
bool cldiFSreamIsDir(const cldifstream_t *self);
bool cldiFSreamIsFIFO(const cldifstream_t *self);
bool cldiFSreamIsLink(const cldifstream_t *self);
bool cldiFSreamPathExists(const cldifstream_t *self);
bool cldiFSreamCanCreatePath(const cldifstream_t *self);
bool cldiFSreamHasPath(const cldifstream_t *self);
bool cldiFSreamAtEOF(const cldifstream_t *self);

// FStreamWrite() and FileBufWrite() functions do not flush the buffer until it
// is full, FStreamPrint() and FileBufPrint() functions flush when the buffer
// is full, and after the last character is loaded into the buffer. Otherwise,
// data is not flushed into the buffer until the file is accessed in a different
// mode.

/* Write array to file stream. */
size_t   cldiFStreamWrite(cldifstream_t *self, size_t nmemb, size_t n, const void *array);
/* Write string of n length to file stream. */
size_t   cldiFStreamWriteNS(cldifstream_t *self, size_t n, const char *str);
/* Write string to file stream. */
size_t   cldiFStreamWriteS(cldifstream_t *self, const char *str);
/* Write char to file stream. */
size_t   cldiFStreamWriteC(cldifstream_t *self, char chr);
/* Write wstring of n length to file stream. */
size_t   cldiFStreamWriteNW(cldifstream_t *self, size_t n, const wchar_t *str);
/* Write wstring to file stream. */
size_t   cldiFStreamWriteW(cldifstream_t *self, const wchar_t *str);
/* Write wstring to file stream. */
size_t   cldiFStreamWriteWC(cldifstream_t *self, wchar_t wchr);
/* Formatted write to file stream. */
#if CLDI_PLATFORM == WINDOWS
__cdecl
#endif
size_t   cldiFStreamWriteF(cldifstream_t *self, const char *fmt, ...);

/* Print array to file stream. */
size_t   cldiFStreamPrint(cldifstream_t *self, size_t nmemb, size_t n, const void *array);
/* Print string of n length to file stream. */
size_t   cldiFStreamPrintNS(cldifstream_t *self, size_t n, const char *str);
/* Print string to file stream. */
size_t   cldiFStreamPrintS(cldifstream_t *self, const char *str);
/* Print char to file stream. */
size_t   cldiFStreamPrintC(cldifstream_t *self, char chr);
/* Print wstring of n length to file stream. */
size_t   cldiFStreamPrintNW(cldifstream_t *self, size_t n, const wchar_t *str);
/* Print wstring to file stream. */
size_t   cldiFStreamPrintW(cldifstream_t *self, const wchar_t *str);
/* Print wchar_t to file stream. */
size_t   cldiFStreamPrintWC(cldifstream_t *self, wchar_t wchr);
/* Formatted print to file stream. */
#if CLDI_PLATFORM == WINDOWS
__cdecl
#endif
size_t   cldiFStreamPrintF(cldifstream_t *self, const char *fmt, ...);

/* Read string of max length n from file stream. */
size_t   cldiFStreamRead(cldifstream_t *self, size_t n, char *str);
/* Read string of max length n from file stream until 'delimiter' is
.  found (delimiter is not included in function output). */
size_t   cldiFStreamReadD(cldifstream_t *self, char delimiter, size_t n, char *str);
/* Read char from file stream. */
size_t   cldiFStreamReadC(cldifstream_t *self);
/* Read wstring of max length n from file stream. */
size_t   cldiFStreamReadW(cldifstream_t *self, size_t n, wchar_t *str);
/* Read wstring of max length n from file stream until 'delimiter. is
.  found (delimiter is not included in function output). */
size_t   cldiFStreamReadWD(cldifstream_t *self, wchar_t delimiter, size_t n, wchar_t *str);
/* Read wchar_t from file stream. */
size_t   cldiFStreamReadWC(cldifstream_t *self);
/* Formatted scan from file stream. */
#if CLDI_PLATFORM == WINDOWS
__cdecl
#endif
size_t   cldiFStreamScanF(cldifstream_t *self, const char *fmt, size_t max, const char *output, ...);
/* Formatted scan from file stream. */
#if CLDI_PLATFORM == WINDOWS
__cdecl
#endif
size_t   cldiFStreamScanFW(cldifstream_t *self, const char *fmt, size_t max, const wchar_t *output, ...);

/* Flush the write (put) buffer of the file. */
CLDISTAT cldiFStreamFlushP(cldifstream_t *self);
/* Flush the read (get) buffer of the file. */
CLDISTAT cldiFStreamFlushG(cldifstream_t *self);
/* Flush all of the file's buffers. */
CLDISTAT cldiFStreamFlush(cldifstream_t *self);

/* Seek some point in the file (move only the write ptr). */
const void *const cldiFStreamSeekP(cldifstream_t *self, CLDI_FSEEK_POS seek_position);
// - Seek relative to some position in the file.
const void *const cldiFStreamSeekRelP(cldifstream_t *self, ssize_t rel, CLDI_FSEEK_POS seek_position);
// - Seek relative to some position in the file (line-by-line).
const void *const cldiFStreamSeekRelLnP(cldifstream_t *self, ssize_t rel, CLDI_FSEEK_POS seek_position);
/* Seek some point in the file (move only the read ptr). */
const void *const cldiFStreamSeekG(cldifstream_t *self, CLDI_FSEEK_POS seek_position);
// - Seek relative to some position in the file.
const void *const cldiFStreamSeekRelG(cldifstream_t *self, ssize_t rel, CLDI_FSEEK_POS seek_position);
// - Seek relative to some position in the file (line-by-line).
const void *const cldiFStreamSeekRelLnG(cldifstream_t *self, ssize_t rel, CLDI_FSEEK_POS seek_position);
/* Seek some point in the file (move both ptrs, read/write). */
const void *const cldiFStreamSeek(cldifstream_t *self, CLDI_FSEEK_POS seek_position);
// - Seek relative to some position in the file.
const void *const cldiFStreamSeekRel(cldifstream_t *self, ssize_t rel, CLDI_FSEEK_POS seek_position);
// - Seek relative to some position in the file (line-by-line).
const void *const cldiFStreamSeekRelLn(cldifstream_t *self, ssize_t rel, CLDI_FSEEK_POS seek_position);

/* Get the index within the file of a given ptr. */
size_t            cldiFStreamPtrIndex(cldifstream_t *self, const void *const ptr);
/* Get the index, relative to some position in the file, of a given ptr. */
ssize_t           cldiFStreamPtrRelIndex(cldifstream_t *self, const void *const ptr, CLDI_FREL_POS pos);
/* Get the index, relative to some position in the file, of a given absolute index. */
ssize_t           cldiFStreamIndexRel(cldifstream_t *self, size_t index, CLDI_FREL_POS pos);

/* Get write ptr of the file. */
const void *const cldiFStreamTellP(const cldifstream_t *self);
// - Get as absolute index rather than ptr.
size_t            cldiFStreamTellPI(const cldifstream_t *self);
// - Get as absolute index rather than ptr (line-by-line).
size_t            cldiFStreamTellLnP(const cldifstream_t *self);
// - Get relative position from a given position in the file.
ssize_t           cldiFStreamTellRelP(const cldifstream_t *self, CLDI_FSEEK_POS rel);
// - Get relative position from a given position in the file (line-by-line).
ssize_t           cldiFStreamTellRelLnP(const cldifstream_t *self, CLDI_FSEEK_POS rel);
/* Get read ptr of the file. */
const void *const cldiFStreamTellG(const cldifstream_t *self);
// - Get as absolute index rather than ptr.
size_t            cldiFStreamTellGI(const cldifstream_t *self);
// - Get as absolute index rather than ptr (line-by-line).
size_t            cldiFStreamTellLnG(const cldifstream_t *self);
// - Get relative position from a given position in the file.
ssize_t           cldiFStreamTellRelG(const cldifstream_t *self, CLDI_FSEEK_POS rel);
// - Get relative position from a given position in the file (line-by-line).
ssize_t           cldiFStreamTellRelLnG(const cldifstream_t *self, CLDI_FSEEK_POS rel);



#endif // _cldi_head__io_FILE_H
