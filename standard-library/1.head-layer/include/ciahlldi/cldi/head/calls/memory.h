
#ifndef _cldi_head__calls_MEMORY_H
#define _cldi_head__calls_MEMORY_H 1

/* Setup CLDI module "head" */
#include "../setup.h"

/* Requires: cldi-head: types/basic-types */
#include "../types/basictypes.h"

#ifdef __cplusplus
extern "C" {
#endif



/* Type Definitions */

/* `Heap` type */
#ifdef _WIN32
	typedef HANDLE cldiheap_t;
#else
	typedef void *const cldiheap_t;
#endif

cldiheap_t cldiGetCurrentHeap();


/* Memory Management Options/Flags */

/* Allocation Options */
typedef enum CLDIMEMOPT
{
	CLDI_MEM_DEFAULT  = 0x8,

	CLDI_MEM_READ     = 0x1,
	CLDI_MEM_WRITE    = 0x2,
	CLDI_MEM_EXEC     = 0x4,

	CLDI_MEM_SET_ZERO = 0x8,
} cldimemopt_t;

/* Memory Block Header, and Block Pointer */
typedef struct CLDIMEMHEADER cldimemheader_t;
typedef struct CLDIMEMBLK    cldimemblk_t;


/* Memory Management Operations */

/* Generic heap memory request functions, optional args: `output` */
void*    cldiReqMemory(size_t amount_of_bytes, int options);
void*    cldiReqMemoryEc(size_t amount_of_bytes, int options, void **const output);
void*    cldiHeapReqMem(cldiheap_t heap, size_t amount_of_bytes, int options);
CLDISTAT cldiHeapReqMemEc(void **const var_to_output_ref, cldiheap_t*, size_t, int);

/* Request memory from a FILE*, optional args: `output`. */
void*    cldiReqFileView(FILE *file, size_t amount_of_bytes, int options);
CLDISTAT cldiReqFileViewEc(void **const var_to_output_ref, FILE*, size_t, int);

/* Share a memory block with another scope (object or function), drop shared copy with
.  cldiDropMemory(), optional args: `output`. */
void*    cldiShareMemory(void *const address);
CLDISTAT cldiShareMemoryEc(void *const address, void **const output);

/* Set ownership of memory to another thread, only works if executed as the
.  current owner thread. */
CLDISTAT cldiSetMemoryOwner(void *const address, cldipid_t new_owner);

/* Unmap memory from the page table or reliquish share in a certain memory
.  block. */
CLDISTAT cldiDropMemory(void *const address);


/* Storage Class Definitions */
struct CLDIMEMHEADER
{
#if __CLDI_PLATFORM_UNIXLIKE > false
	const size_t    _mBlkSize; /* The size of the memory block ahead. */
#endif
	const cldipid_t _mOwner;   /* The process ID of the thread that owns this memory block. */
	const int       _mFlags;   /* Access and permissions flags for this memory. */

#if defined(__cplusplus) && __CLDI_no_cpp < true

	CLDIMEMHEADER(size_t size, cldipid_t owner, int flags=CLDI_MEM_DEFAULT);
	CLDIMEMHEADER(size_t size, int flags=CLDI_MEM_DEFAULT);

	~CLDIMEMHEADER();

	size_t    GetSize()  const;
	cldipid_t GetOwner() const;
	int       GetFlags() const;

#endif
};

struct CLDIMEMBLK
{
	cldiheap_t             _heap; /* The heap this block is allocated inside of. */
	cldimemheader_t *const _blk;  /* Ptr to the memory header. */

#if defined(__cplusplus) && __CLDI_no_cpp < true

	CLDIMEMBLK(const cldimemheader_t* header);

	~CLDIMEMBLK();

	cldimemblk_t  NewBlock(size_t size, cldiheap_t heap=cldiGetCurrentHeap(), int flags=CLDI_MEM_DEFAULT);
	cldimemblk_t  NewBlock(size_t size, cldipid_t owner, cldiheap_t heap=cldiGetCurrentHeap(), int flags=CLDI_MEM_DEFAULT);
	cldimemblk_t* New(const cldimemheader_t* header);

	const cldimemheader_t* GetHeader() const;
	const void* GetBlock() const;

#endif
};


/* Copy data from one place to another. */
CLDISTAT cldiCopyBytes(size_t amount, const void *const src, void *const destination);
char*    cldiNewCopyBytes(size_t amount, const void *const src);
CLDISTAT cldiNewCopyBytesEc(size_t amount, const void *const src, char **output);



#ifdef __cplusplus
}
#	if __CLDI_no_cpp > false
namespace cldi
{
	/* C++ extensions for this module. */
	using heap_t = cldiheap_t;
	using memopt_t = cldimemopt_t;
	using memheader_t = cldimemheader_t;

	/* Memory Operations */
	using HeapAlloc = cldiHeapAlloc;
	using HeapAllocEc = cldiHeapAllocEc;
	using MapFileView = cldiMapFileView;
	using MapFileViewEc = cldiMapFileViewEc;
	using MapFileViewOnHeap = cldiMapFileViewOnHeap;
	using MapFileViewOnHeapEc = cldiMapFileViewOnHeapEc;
	using DropMemory = cldiDropMemory;
}
#	endif
#endif

#endif /* _cldi_head__calls_MEMORY_H */
