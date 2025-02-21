
#ifndef _cldi_head__MEMORY_H
#define _cldi_head__MEMORY_H 1

#include "functypes.h"



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
// O: owner participation; whether the owner is still
// using the block                        0000 0000 0000 0000
typedef enum _CLDIMBLKFLAGS //                 ownr: grp: all:
{ //                                         O A-- rwx rwx rwx
	CLDI_MBLK_OREAD         = 0x100,  // 000 0 000 100 000 000
	CLDI_MBLK_OWRTE         = 0x80,   // 000 0 000 010 000 000
	CLDI_MBLK_OEXEC         = 0x40,   // 000 0 000 001 000 000
	CLDI_MBLK_GREAD         = 0x20,   // 000 0 000 000 100 000
	CLDI_MBLK_GWRTE         = 0x10,   // 000 0 000 000 010 000
	CLDI_MBLK_GEXEC         = 0x8,    // 000 0 000 000 001 000
	CLDI_MBLK_AREAD         = 0x4,    // 000 0 000 000 000 100
	CLDI_MBLK_AWRTE         = 0x2,    // 000 0 000 000 000 010
	CLDI_MBLK_AEXEC         = 0x1,    // 000 0 000 000 000 001
	// No threads can change permissions (author priviledges) (0x000)
	CLDI_MBLK_NO_AUTH       = 0x000,  // 000 0 000 000 000 000
	// No threads can change permissions (author priviledges) (0x000)
	CLDI_MBLK_AAUTH         = 0x200,  // 000 0 001 000 000 000
	// Thread in the same group as owner can change permissions (author priviledges) (0x010)
	CLDI_MBLK_GAUTH         = 0x400,  // 000 0 010 000 000 000
	// Owner thread can change permissions (author priviledges, this by itself is default) (0x100)
	CLDI_MBLK_OAUTH         = 0x800,  // 000 0 100 000 000 000

	// Owner is still using the block (this bit is usually added when the block is claimed).
	CLDI_MBLK_ACTIVEOWNER   = 0x1000, // 000 1 000 000 000 000

	CLDI_DEFAULT_MBLK_AUTH  = CLDI_MBLK_OAUTH,

	CLDI_DEFAULT_MBLK_PERMS = CLDI_DEFAULT_MBLK_AUTH | CLDI_MBLK_OREAD | CLDI_MBLK_OWRTE | CLDI_MBLK_GREAD | CLDI_MBLK_AREAD,
	CLDI_PRIVATE_MBLK_PERMS = CLDI_MBLK_OAUTH | CLDI_MBLK_OREAD | CLDI_MBLK_OWRTE,

	CLDI_MBLK_READ          = CLDI_MBLK_OREAD,
	CLDI_MBLK_WRITE         = CLDI_MBLK_OWRTE,
	CLDI_MBLK_EXEC          = CLDI_MBLK_OEXEC,
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
#define CLDISYSHEAP_NULL    (-1)
#define CLDISYSHEAP_CURRENT 0
#elif CLDI_PLATFORM == CLDI_WINDOWS
typedef HANDLE cldisysheap_t;
#define CLDISYSHEAP_NULL    NULL
#define CLDISYSHEAP_CURRENT (GetCurrentHeap())
#else
typedef int cldisysheap_t;
#define CLDISYSHEAP_NULL    (-1)
#define CLDISYSHEAP_CURRENT 0
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
	cldipid_t      owner;
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
	cldipid_t          owner;
} CLDI_HEAP_HEADER;

/* Heap type */
typedef struct _CLDIHEAP
{
	/* The system-managed heap that this object refers to (if any). */
	cldisysheap_t      sysheap;
	/* The managed-environment heap that the object refers to (if any). */
	CLDI_HEAP_HEADER  *envheap;
	/* An array of known active blocks. */
	CLDI_MBLK_HEADER **blocks;
	/* The amount of known active blocks. */
	cldimblkid_t       blockcount;
} cldiheap_t;

/* Methods associated with heap objects: */

// The default amount of blocks that a heap will track before its capacity is
// manually altered.
#define CLDI_DEFAULT_MBLK_BUFSIZE 25

// A container for the current thread's main heap.
extern cldiheap_t CLDI_CURRENT_HEAP;

cldiheap_t*    cldiGetCurrentHeap();
cldisysheap_t  cldiGetCurrentSysheap();

CLDISTAT       cldiInitHeap(cldiheap_t *self);
CLDISTAT       cldiInitHeapCurrent(cldiheap_t *self);
CLDISTAT       cldiInitHeapCurrentBuf(cldiheap_t *self, size_t bufsize);
CLDISTAT       cldiInitEnvHeap(cldiheap_t *self, size_t heap_size, int flags);
CLDISTAT       cldiInitEnvHeapBuf(cldiheap_t *self, size_t heap_size, size_t bufsize, int flags);
CLDISTAT       cldiInitSysheap(cldiheap_t *self, cldisysheap_t sysheap);
CLDISTAT       cldiInitSysheapBuf(cldiheap_t *self, cldisysheap_t sysheap, size_t bufsize);

cldiheap_t*    cldiNewHeap(cldiheap_t *self);
cldiheap_t*    cldiNewHeapCurrent(cldiheap_t *self);
cldiheap_t*    cldiNewHeapCurrentBuf(cldiheap_t *self, size_t bufsize);
cldiheap_t*    cldiNewEnvHeap(cldiheap_t *self, size_t heap_size, int flags);
cldiheap_t*    cldiNewEnvHeapBuf(cldiheap_t *self, size_t heap_size, size_t bufsize, int flags);
cldiheap_t*    cldiNewSysheap(cldiheap_t *self, cldisysheap_t sysheap);
cldiheap_t*    cldiNewSysheapBuf(cldiheap_t *self, cldisysheap_t sysheap, size_t bufsize);

const char*    cldiGetHeapName(const cldiheap_t *self);

CLDISTAT       cldiSetHeapName(cldiheap_t *self, const char *name);
CLDISTAT       cldiSetHeapNameW(cldiheap_t *self, const wchar_t *name);

cldimblkid_t   cldiHeapNewBlock(cldiheap_t *self, size_t total_size, int flags);
CLDISTAT       cldiHeapShareBlock(const cldiheap_t *self, cldimblkid_t blk);
CLDISTAT       cldiHeapClaimBlock(const cldiheap_t *self, cldimblkid_t blk);
CLDISTAT       cldiHeapDropBlock(cldiheap_t *self, cldimblkid_t blk);

void*          cldiHeapGetBlockAddr(const cldiheap_t *self, cldimblkid_t blk);
const void*    cldiHeapGetBlockConstAddr(const cldiheap_t *self, cldimblkid_t blk);
cldimblkstat_t cldiHeapGetBlockStatus(const cldiheap_t *self, cldimblkid_t blk);
size_t         cldiHeapGetBlockSize(const cldiheap_t *self, cldimblkid_t blk);
int            cldiHeapGetBlockPerms(const cldiheap_t *self, cldimblkid_t blk);

CLDISTAT       cldiHeapSetBlockPerms(const cldiheap_t *self, cldimblkid_t blk, int perms);
CLDISTAT       cldiHeapAddBlockPerms(const cldiheap_t *self, cldimblkid_t blk, int perms);
CLDISTAT       cldiHeapRemoveBlockPerms(const cldiheap_t *self, cldimblkid_t blk, int perms);
CLDISTAT       cldiHeapClearBlockPerms(const cldiheap_t *self, cldimblkid_t blk);

bool           cldiBlockStatusCheck(const cldiheap_t *self, cldimblkid_t blk, cldimblkstat_t stat);
bool           cldiHeapIsBlockActive(const cldiheap_t *self, cldimblkid_t blk);
bool           cldiHeapIsBlockPending(const cldiheap_t *self, cldimblkid_t blk);
bool           cldiHeapIsBlockHole(const cldiheap_t *self, cldimblkid_t blk);
bool           cldiHeapIsBlockWritable(const cldiheap_t *self, cldimblkid_t blk);
bool           cldiHeapIsBlockReadable(const cldiheap_t *self, cldimblkid_t blk);
bool           cldiHeapIsBlockExecutable(const cldiheap_t *self, cldimblkid_t blk);
bool           cldiHeapIsBlockWritableOnThread(const cldiheap_t *self, cldimblkid_t blk, cldipid_t thr);
bool           cldiHeapIsBlockReadableOnThread(const cldiheap_t *self, cldimblkid_t blk, cldipid_t thr);
bool           cldiHeapIsBlockExecutableOnThread(const cldiheap_t *self, cldimblkid_t blk, cldipid_t thr);

bool           cldiHeapIsNull(const cldiheap_t *self);
bool           cldiHeapIsActive(const cldiheap_t *self);
bool           cldiIsSysheap(const cldiheap_t *self);
bool           cldiIsEnvHeap(const cldiheap_t *self);
bool           cldiIsLowFragHeap(const cldiheap_t *self);


/* Methods associated with memref objects: */

cldiTemplSupplier(cldimemref, cldiallocator_t);   // cldimemref  <method-name>()

/* Executes a memory block allocator function (that returns its memref over the
.  stack) under the context of a specified heap. */
cldimemref  RunAllocator(cldiheap_t *heap, cldiallocator_t allocator);

#if defined(__cplusplus) && CLDI_C_ONLY == false
}
#endif
struct _CLDIMEMREF
{
	clditypeinfo_t  objtype;
	size_t          objcount;
	cldimblkdestr_t destructor;
	void           *ptr;
	cldiheap_t     *heap;
	cldimblkid_t    id;
	cldipid_t       owner;
	bool active, activeid, shared;
};
#if defined(__cplusplus) && CLDI_C_ONLY == true
}
#endif


/* C++ bindings for this file: */
#include "icxx/memory.hpp"



#endif // _cldi_head__MEMORY_H
