
#pragma cldic module head:memory
#ifndef _cldi_head__MEMORY_H
#define _cldi_head__MEMORY_H 1

#include "functypes.h"
#pragma cldic require head:functypes

#ifdef __cplusplus
extern "C" {
#endif



/* This enum contains bit settings for flags that modify heap initialization and
.  maintenance. */
typedef enum _CLDIHEAPFLAGS
{
	CLDI_NULL_HEAPFLAGS = 0x0, // 0000 0000 0000 0 0 0 0

	CLDI_HEAP_ACTIVE    = 0x1, // 0000 0000 0000 0 0 0 1
	CLDI_HEAP_INACTIVE  = 0x1, // 0000 0000 0000 0 0 0 0

	CLDI_ENVHEAP        = 0x2, // 0000 0000 0000 0 0 1 0
	CLDI_SYSHEAP        = 0x0, // 0000 0000 0000 0 0 0 0

	CLDI_LOWFRAG_HEAP   = 0x4, // 0000 0000 0000 0 1 0 0

	CLDI_DEFAULT_SYSHEAP=CLDI_SYSHEAP,
	CLDI_DEFAULT_ENVHEAP=CLDI_ENVHEAP | CLDI_LOWFRAG_HEAP,
} CLDIHEAPFLAG;
// Convert CLDI heap permissions and flags to system-specific ones
int cldiConvToSysHeapPerms(int flags);
// Convert CLDI heap flags to system-specific flags (exclude permissions)
int cldiConvToSysHeapFlags(int flags);

/* This enum contains bit settings for setting, establishing, and detecting
.  memory permissions. */
// r: read permissions
// w: write permissions
// x: execute permissions
// A: author status; which threads can change permissions
// O: owner participation; whether the owner is still using the block.
//                                        0000 0000 0000 0000
typedef enum _CLDIMBLKFLAGS //                  ownr: grp: all:
{ //                                         O A-- rwx rwx rwx
	CLDI_MBLK_OREAD         = 0x100,  // 000 0 000 100 000 000
	CLDI_MBLK_OWRTE         = 0x80,   // 000 0 000 010 000 000
	CLDI_MBLK_OEXEC         = 0x40,   // 000 0 000 001 000 000
	CLDI_MBLK_GREAD         = 0x20,   // 000 0 000 000 100 000
	CLDI_MBLK_GWRTE         = 0x10,   // 000 0 000 000 010 000
	CLDI_MBLK_GEXEC         = 0x8,    // 000 0 000 000 001 000
	CLDI_MBLK_PREAD         = 0x4,    // 000 0 000 000 000 100
	CLDI_MBLK_PWRTE         = 0x2,    // 000 0 000 000 000 010
	CLDI_MBLK_PEXEC         = 0x1,    // 000 0 000 000 000 001
	// No threads can change permissions (author priviledges) (0x000)
	CLDI_MBLK_NO_AUTH       = 0x000,  // 000 0 000 000 000 000
	// No threads can change permissions (author priviledges) (0x000)
	CLDI_MBLK_PAUTH         = 0x200,  // 000 0 001 000 000 000
	// Thread in the same group as owner can change permissions (author priviledges) (0x010)
	CLDI_MBLK_GAUTH         = 0x400,  // 000 0 010 000 000 000
	// Owner thread can change permissions (author priviledges, this by itself is default) (0x100)
	CLDI_MBLK_OAUTH         = 0x800,  // 000 0 100 000 000 000
	// Owner is still using the block (this bit is usually added when the block
	// is claimed).
	CLDI_MBLK_ACTIVEOWNER   = 0x1000, // 000 1 000 000 000 000

	/* Defaults */
	CLDI_DEFAULT_MBLK_AUTH  = CLDI_MBLK_OAUTH,

	CLDI_DEFAULT_MBLK_PERMS = CLDI_DEFAULT_MBLK_AUTH | CLDI_MBLK_OREAD | CLDI_MBLK_OWRTE | CLDI_MBLK_GREAD | CLDI_MBLK_PREAD,
	CLDI_PRIVATE_MBLK_PERMS = CLDI_MBLK_OAUTH | CLDI_MBLK_OREAD | CLDI_MBLK_OWRTE,

	/* Aliases */
	CLDI_MBLK_READ          = CLDI_MBLK_OREAD,
	CLDI_MBLK_WRITE         = CLDI_MBLK_OWRTE,
	CLDI_MBLK_EXEC          = CLDI_MBLK_OEXEC,

	CLDI_MBLK_OWNER_PERMS   = CLDI_MBLK_OREAD | CLDI_MBLK_OWRTE | CLDI_MBLK_OEXEC,
	CLDI_MBLK_GROUP_PERMS   = CLDI_MBLK_GREAD | CLDI_MBLK_GWRTE | CLDI_MBLK_GEXEC,
	CLDI_MBLK_PUBLIC_PERMS  = CLDI_MBLK_PREAD | CLDI_MBLK_PWRTE | CLDI_MBLK_PEXEC,
} CLDIMBLKFLAG;
// Convert CLDI memory block permissions flags to system-specific ones (only include
// permissions-related flags).
int cldiConvToSysMemPerms(int flags);
// Convert CLDI memory block flags to system-specific flags
int cldiConvToSysMemFlags(int flags);

/* Memory Block Status enum */
typedef enum _CLDIMBLKSTATUS
{
	CLDI_MBLK_UNAVAILABLE=-1,
	CLDI_MBLK_NONEXISTENT=0,
	CLDI_MBLK_ACTIVE,
	CLDI_MBLK_PENDING,
	CLDI_MBLK_HOLE,
} cldimblkstat_t;    

/* Memory Block ID type (should always be defined as the type used as an
.  index/counter for the array of valid memory blocks in a heap associated
.  with a `heap` object, usually, this is size_t). */
typedef CLDI_MBLKID_INTSIZE cldimblkid_t;
/* Memory Reference type */
typedef struct _CLDIMEMREF cldimemref;
/* Memory Block Destructor type */
typedef void (*cldimblkdestr_t)(cldimemref*);

/* System-Recognized Heap Specifier type (set to 0 or NULL equivalent to
.  specify "current heap"). */
#if CLDI_PLATFORM_UNIXLIKE == true
typedef int cldisysheap_t;
#	define CLDISYSHEAP_NULL    (-1)
#	define CLDISYSHEAP_CURRENT 0
#elif CLDI_PLATFORM == CLDI_WINDOWS
typedef HANDLE cldisysheap_t;
#	define CLDISYSHEAP_NULL    NULL
#	define CLDISYSHEAP_CURRENT (GetCurrentHeap())
#else
typedef int cldisysheap_t;
#	define CLDISYSHEAP_NULL    (-1)
#	define CLDISYSHEAP_CURRENT 0
#endif

/* Memory Block Header type; this type is placed in the offset of an allocated
.  memory block to encode metadata for freeing that memory block and checking
.  its permissions, size, status, and owner. */
typedef struct _CLDIMBLKH
{
	// Block type (size and template)
	clditypeinfo_t block_type;
	// Array size (number of potential items in the entire block, usually 1)
	size_t         array_size;
	// Permissions applied to the memory block
	int            perms;
	// Reference count for the block, so that be kept alive to be shared between multiple threads.
	int            refc;
	// The current status of the block.
	cldimblkstat_t status;
	// The owner thread of the block.
	cldioid_t      owner;
} CLDI_MBLK_HEADER;

/* Heap Header type; this type is placed in the offset of an allocated heap to
.  encode metadata about that heap for managing it in system memory, identifying
.  it, and tracking its permissions and owner. */
typedef struct _CLDIHEAPH
{
	/* The identifyable name given to this heap, NULL by default. */
	const char        *name;
	/* The bottom (start) and current top of the heap on the current thread's
	.  page table. */
	void              *base, *top;
	/* The max size of the heap (SIZE_MAX if system heap). */
	cldimblkid_t       bounds;
	/* An array containing all known holes in the heap (areas between fragments). */
	void             **holes;
	/* The amount of holes and associated hole sizes. */
	size_t             holecount;
	/* An array of known active blocks. */
	CLDI_MBLK_HEADER **blocks;
	/* The amount of known active blocks. */
	cldimblkid_t       blockcount;
	/* Heap permissions. */
	int                perms;
	/* The owner thread of the heap. */
	cldioid_t          owner;
} CLDI_HEAP_HEADER;

/* Memory Reference type */
struct _CLDIMEMREF
{
	clditypeinfo_t  objtype;
	cldimblkdestr_t destructor;
	void           *ptr;
	cldiheap_t     *heap;
	cldimblkid_t    id;
	cldioid_t       owner;
	bool active, activeid, shared;
};

/* Heap type */
typedef struct _CLDIHEAP
{
	/* The system-managed heap that this object refers to (if any). */
	cldisysheap_t      sysheap;
	/* The managed-environment heap that the object refers to (if any). */
	CLDI_HEAP_HEADER  *envheap;
	/* An array of known active blocks (if not stored in heap header). */
	CLDI_MBLK_HEADER **blocks;
	/* The amount of known active blocks. */
	cldimblkid_t       blockcount;
} cldiheap_t;


/* Methods associated with cldimemref objects: */

/* Construct a cldimemref as blank (null). */
CLDISTAT cldiInitMemref(cldimemref *self) CLDINOEXCEPT;
/* Construct a cldimemref from an existing block using its ID. */
CLDISTAT cldiInitMemrefExistingID(cldimemref *self, cldimblkid_t blkid);
/* Construct a cldimemref with a copy of an existing block using its ID. */
CLDISTAT cldiInitMemrefCopyID(cldimemref *self, cldimblkid_t blkid);
/* Construct a cldimemref from an existing block on a particular heap, using its ID. */
CLDISTAT cldiInitMemrefOnHeap(cldimemref *self, cldiheap_t *heap, cldimblkid_t blkid);
/* Construct a cldimemref with a copy of an existing block on a particular heap, using its ID. */
CLDISTAT cldiInitMemrefCopyOnHeap(cldimemref *self, cldiheap_t *heap, cldimblkid_t blkid);
/* Construct a cldimemref from an already existing block (share block). */
CLDISTAT cldiInitMemrefBorrowed(cldimemref *self, const cldimemref *borrow);
/* Construct a cldimemref with a copy of another memory block. */
CLDISTAT cldiInitMemrefCopy(cldimemref *self, const cldimemref *copy);
/* Construct a cldimemref as a new block. */
CLDISTAT cldiInitMemrefNewBlock(cldimemref *self, clditypeinfo_t block_type, int flags);
CLDISTAT cldiInitMemrefNewBlockEx(cldimemref *self, clditypeinfo_t block_type, int flags, cldimblkdestr_t destructor);
/* Construct a cldimemref as a new array block. */
CLDISTAT cldiInitMemrefNewArray(cldimemref *self, clditypeinfo_t block_type, size_t array_size, int flags);
CLDISTAT cldiInitMemrefNewArrayEx(cldimemref *self, clditypeinfo_t block_type, size_t array_size, int flags, cldimblkdestr_t destructor);
/* Construct a cldimemref as a new block on a particular heap. */
CLDISTAT cldiInitMemrefNewBlockOnHeap(cldimemref *self, cldiheap_t *heap, clditypeinfo_t block_type, int flags);
CLDISTAT cldiInitMemrefNewBlockOnHeapEx(cldimemref *self, cldiheap_t *heap, clditypeinfo_t block_type, int flags, cldimblkdestr_t destructor);
/* Construct a cldimemref as a new array block on a particular heap. */
CLDISTAT cldiInitMemrefNewArrayOnHeap(cldimemref *self, cldiheap_t *heap, clditypeinfo_t block_type, size_t array_size, int flags);
CLDISTAT cldiInitMemrefNewArrayOnHeapEx(cldimemref *self, cldiheap_t *heap, clditypeinfo_t block_type, size_t array_size, int flags, cldimblkdestr_t destructor);
/* Make a new instance and pass it over the stack -- Corresponding to constructors. */
cldimemref cldiMakeMemref() CLDINOEXCEPT;
cldimemref cldiMakeMemrefExistingID(cldimblkid_t blkid);
cldimemref cldiMakeMemrefCopyID(cldimblkid_t blkid);
cldimemref cldiMakeMemrefOnHeap(cldiheap_t *heap, cldimblkid_t blkid);
cldimemref cldiMakeMemrefCopyOnHeap(cldiheap_t *heap, cldimblkid_t blkid);
cldimemref cldiMakeMemrefBorrowed(const cldimemref *borrow);
cldimemref cldiMakeMemrefCopy(const cldimemref *copy);
cldimemref cldiMakeMemrefNewBlock(clditypeinfo_t block_type, int flags);
cldimemref cldiMakeMemrefNewArray(clditypeinfo_t block_type, size_t array_size, int flags);
cldimemref cldiMakeMemrefNewBlockOnHeap(cldiheap_t *heap, clditypeinfo_t block_type, int flags);
cldimemref cldiMakeMemrefNewArrayOnHeap(cldiheap_t *heap, clditypeinfo_t block_type, size_t array_size, int flags);
#define    cldiMemrefBorrow cldiMakeMemrefBorrowed

/* Drop the memory block and memref object (set to blank state to be written over
.  again or deleted). */
CLDISTAT              cldiDropMemref(cldimemref *drop);

/* Get the cldimemref's heap. */
cldiheap_t*           cldiMemrefGetHeap(const cldimemref *self);
/* Return the address of a cldimemref object, if the current thread is missing
.  either read or write priviledges, this function returns null and passes a
.  READONLY error (missing only write privs) or NO_ACCESS error (missing ALL
.  privs) to CLDI_ERRNO. */
void*                 cldiMemrefGetAddress(const cldimemref *self);
/* Return the address of a cldimemref object in const (readonly) mode, if the
.  current thread is missing read priviledges, this function returns null and
.  passes a NO_ACCESS error to CLDI_ERRNO. */
const void*           cldiMemrefGetConstAddress(const cldimemref *self);
/* Get the cldimemref's block ID. */
cldimblkid_t          cldiMemrefGetBlockID(const cldimemref *self);
/* Get the cldimemref's block type info. */
const clditypeinfo_t* cldiMemrefGetBlockType(const cldimemref *self);
/* Get the permissions and flags of the memory block. */
int                   cldiMemrefGetBlockFlags(const cldimemref *self);
/* Get the owner ID of the cldimemref object's memory block (may not be the current
.  thread). */
cldioid_t             cldiMemrefGetBlockOwner(const cldimemref *self);
/* Get the owner of the cldimemref object's memory block's process ID (may not be
.  the current thread). */
cldipid_t             cldiMemrefGetBlockOwnerThread(const cldimemref *self);
/* Get the owner of the cldimemref object's memory block's group ID (may not be
.  the same as the current thread). */
cldigid_t             cldiMemrefGetBlockOwnerGroup(const cldimemref *self);
/* Get the owner ID of the cldimemref object itself. */
cldioid_t             cldiMemrefGetOwner(const cldimemref *self);
/* Get the owner of the cldimemref object's process ID. */
cldipid_t             cldiMemrefGetOwnerThread(const cldimemref *self);
/* Get the owner of the cldimemref object's group ID'. */
cldigid_t             cldiMemrefGetOwnerGroup(const cldimemref *self);

/* Check if the cldimemref is null. */
bool                  cldiMemrefIsNull(const cldimemref *self) CLDINOEXCEPT;
/* Check if the cldimemref is non-null. */
bool                  cldiMemrefIsNonNull(const cldimemref *self) CLDINOEXCEPT;
/* Check if the cldimemref is active. */
bool                  cldiMemrefIsActive(const cldimemref *self) CLDINOEXCEPT;
/* Check if the cldimemref is inactive. */
bool                  cldiMemrefIsInactive(const cldimemref *self) CLDINOEXCEPT;
/* Check if the cldimemref is active by an ID, as opposed to a raw pointer. */
bool                  cldiMemrefHasActiveID(const cldimemref *self) CLDINOEXCEPT;
/* Check if the cldimemref is not active by an ID, instead it is active by a raw
.  pointer. */
bool                  cldiMemrefHasRawPtr(const cldimemref *self) CLDINOEXCEPT;
/* Check if the cldimemref is borrowing its reference. */
bool                  cldiMemrefIsBorrowing(const cldimemref *self) CLDINOEXCEPT;
/* Check if the cldimemref is non-null. */
bool                  cldiMemrefIsBlockOwner(const cldimemref *self) CLDINOEXCEPT;
/* Check if the block is currently shared between multiple blocks. */
bool                  cldiMemrefBlockIsShared(const cldimemref *self) CLDINOEXCEPT;


/* Methods associated with heap objects: */

// Function type alias that allocates a memory block and returns a cldimemref
// for said block over the stack.
cldiTemplSupplier(cldimemref, cldiallocator_t);   // cldimemref  <method-name>()

/* Executes a memory block allocator function (that returns its cldimemref over
.  the stack) under the context of a specified heap. */
cldimemref  cldiHeapCallAllocator(cldiheap_t *heap, cldiallocator_t allocator);

// The default amount of blocks that a heap will track before its capacity is
// manually altered.
#define CLDI_DEFAULT_MBLK_BUFSIZE 25

// A reference to the current thread's default heap.
extern cldiheap_t *CLDI_CURRENT_HEAP;
// Reservation for a heap to initialize after program start and link to
// CLDI_CURRENT_HEAP until modified (or unless modified first).
extern cldiheap_t _CLDI_ENTRY_HEAP;

cldiheap_t*    cldiGetCurrentHeap();
CLDISTAT       cldiSetCurrentHeap(cldiheap_t *set_to);
cldisysheap_t  cldiGetCurrentSysheap();

CLDISTAT       cldiInitHeap(cldiheap_t *self) CLDINOEXCEPT;
CLDISTAT       cldiInitHeapCurrent(cldiheap_t *self);
CLDISTAT       cldiInitHeapCurrentBuf(cldiheap_t *self, size_t bufsize);
CLDISTAT       cldiInitEnvHeap(cldiheap_t *self, size_t heap_size, int flags);
CLDISTAT       cldiInitEnvHeapBuf(cldiheap_t *self, size_t heap_size, size_t bufsize, int flags);
CLDISTAT       cldiInitSysheap(cldiheap_t *self, cldisysheap_t sysheap);
CLDISTAT       cldiInitSysheapBuf(cldiheap_t *self, cldisysheap_t sysheap, size_t bufsize);

cldiheap_t     cldiMakeHeap();
cldiheap_t     cldiMakeHeapCurrent();
cldiheap_t     cldiMakeHeapCurrentBuf(size_t bufsize);
cldiheap_t     cldiMakeEnvHeap(size_t heap_size, int flags);
cldiheap_t     cldiMakeEnvHeapBuf(size_t heap_size, size_t bufsize, int flags);
cldiheap_t     cldiMakeSysheap(cldisysheap_t sysheap);
cldiheap_t     cldiMakeSysheapBuf(cldisysheap_t sysheap, size_t bufsize);

cldiheap_t*    cldiNewHeap();
cldiheap_t*    cldiNewHeapCurrent();
cldiheap_t*    cldiNewHeapCurrentBuf(size_t bufsize);
cldiheap_t*    cldiNewEnvHeap(size_t heap_size, int flags);
cldiheap_t*    cldiNewEnvHeapBuf(size_t heap_size, size_t bufsize, int flags);
cldiheap_t*    cldiNewSysheap(cldisysheap_t sysheap);
cldiheap_t*    cldiNewSysheapBuf(cldisysheap_t sysheap, size_t bufsize);

size_t         cldiHeapGetTotalSize(const cldiheap_t *self);
size_t         cldiHeapGetSize(const cldiheap_t *self);
size_t         cldiHeapMemoryUsage(const cldiheap_t *self);
double         cldiHeapMemoryUsagePercent(const cldiheap_t *self);
size_t         cldiHeapMemoryRemaining(const cldiheap_t *self);
const char*    cldiGetHeapName(const cldiheap_t *self);
cldimemref     cldiGetHeapNameW(const cldiheap_t *self);
CLDISTAT       cldiSetHeapName(cldiheap_t *self, const char *name);
CLDISTAT       cldiSetHeapNameW(cldiheap_t *self, const wchar_t *name);

cldimblkid_t   cldiHeapNewBlock(cldiheap_t *self, clditypeinfo_t type, int flags);
cldimblkid_t   cldiHeapNewArray(cldiheap_t *self, clditypeinfo_t type, size_t array_size, int flags);
cldimblkid_t   cldiHeapNewPendingBlock(cldiheap_t *self, clditypeinfo_t type, int flags);
cldimblkid_t   cldiHeapNewPendingArray(cldiheap_t *self, clditypeinfo_t type, size_t array_size, int flags);
CLDISTAT       cldiHeapBorrowBlock(const cldiheap_t *self, cldimblkid_t blk);
CLDISTAT       cldiHeapClaimBlock(const cldiheap_t *self, cldimblkid_t blk);
CLDISTAT       cldiHeapDropBlock(cldiheap_t *self, cldimblkid_t blk);

void*          cldiHeapGetBlockAddr(const cldiheap_t *self, cldimblkid_t blk)
	CLDITHROWEX(CLDI_ENOT_WRITABLE, CLDI_ENO_ACCESS);
const void*    cldiHeapGetBlockConstAddr(const cldiheap_t *self, cldimblkid_t blk);
cldimblkstat_t cldiHeapGetBlockStatus(const cldiheap_t *self, cldimblkid_t blk);
int            cldiHeapGetBlockRefCount(const cldiheap_t *self, cldimblkid_t blk);
size_t         cldiHeapGetBlockSize(const cldiheap_t *self, cldimblkid_t blk);
size_t         cldiHeapGetBlockCapacity(const cldiheap_t *self, cldimblkid_t blk);
cldioid_t      cldiHeapGetBlockOwner(const cldiheap_t *self, cldimblkid_t blk);
pid_t          cldiHeapGetBlockOwnerThread(const cldiheap_t *self, cldimblkid_t blkid);
gid_t          cldiHeapGetBlockOwnerGroup(const cldiheap_t *self, cldimblkid_t blkid);
int            cldiHeapGetBlockPerms(const cldiheap_t *self, cldimblkid_t blk);
CLDISTAT       cldiHeapSetBlockPerms(const cldiheap_t *self, cldimblkid_t blk, int perms)
	CLDITHROWEX(CLDI_ENO_ACCESS);
CLDISTAT       cldiHeapAddBlockPerms(const cldiheap_t *self, cldimblkid_t blk, int perms)
	CLDITHROWEX(CLDI_ENO_ACCESS);
CLDISTAT       cldiHeapRemoveBlockPerms(const cldiheap_t *self, cldimblkid_t blk, int perms)
	CLDITHROWEX(CLDI_ENO_ACCESS);
CLDISTAT       cldiHeapClearBlockPerms(const cldiheap_t *self, cldimblkid_t blk)
	CLDITHROWEX(CLDI_ENO_ACCESS);

bool           cldiBlockStatEq(cldimblkid_t blk, cldimblkstat_t check_stat) CLDINOEXCEPT;
bool           cldiBlockStatOnHeapEq(const cldiheap_t *self, cldimblkid_t blk, cldimblkstat_t stat) CLDINOEXCEPT;
bool           cldiHeapIsBlockActive(const cldiheap_t *self, cldimblkid_t blk) CLDINOEXCEPT;
bool           cldiHeapIsBlockPending(const cldiheap_t *self, cldimblkid_t blk) CLDINOEXCEPT;
bool           cldiHeapIsBlockHole(const cldiheap_t *self, cldimblkid_t blk) CLDINOEXCEPT;
bool           cldiHeapIsBlockWritable(const cldiheap_t *self, cldimblkid_t blk) CLDINOEXCEPT;
bool           cldiHeapIsBlockReadable(const cldiheap_t *self, cldimblkid_t blk) CLDINOEXCEPT;
bool           cldiHeapIsBlockExecutable(const cldiheap_t *self, cldimblkid_t blk) CLDINOEXCEPT;
bool           cldiHeapIsBlockWritableOnThread(const cldiheap_t *self, cldimblkid_t blk, cldipid_t thr) CLDINOEXCEPT;
bool           cldiHeapIsBlockReadableOnThread(const cldiheap_t *self, cldimblkid_t blk, cldipid_t thr) CLDINOEXCEPT;
bool           cldiHeapIsBlockExecutableOnThread(const cldiheap_t *self, cldimblkid_t blk, cldipid_t thr) CLDINOEXCEPT;

bool           cldiHeapIsNull(const cldiheap_t *self) CLDINOEXCEPT;
bool           cldiHeapIsActive(const cldiheap_t *self) CLDINOEXCEPT;
bool           cldiIsSysheap(const cldiheap_t *self) CLDINOEXCEPT;
bool           cldiIsEnvHeap(const cldiheap_t *self) CLDINOEXCEPT;
bool           cldiIsLowFragHeap(const cldiheap_t *self) CLDINOEXCEPT;



#ifdef __cplusplus
}
#endif
/* C++ bindings for this file: */
#include "icxx/memory.hpp"

#endif // _cldi_head__MEMORY_H
