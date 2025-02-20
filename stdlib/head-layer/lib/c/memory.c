


/* Implementing: cldi-head: memory.h */
#include <cldi/head/memory.h>



cldiheap_t CLDI_CURRENT_HEAP;

cldiheap_t* cldiGetCurrentHeap()
{
	CLDI_ERRNO = CLDI_SUCCESS;
	// If CLDI_CURRENT_HEAP is uninitialized,
	if (cldiHeapIsNull(&CLDI_CURRENT_HEAP))
		// Initialize as current thread's default heap
		if (!cldiStatPermissible(cldiInitHeapCurrent(&CLDI_CURRENT_HEAP)))
			// If non-permissible error, return with error
			return NULL;
	// else return current heap
	return &CLDI_CURRENT_HEAP;
}
cldisysheap_t cldiGetCurrentSysheap()
{
	CLDI_ERRNO = CLDI_SUCCESS;
	// If CLDI_CURRENT_HEAP is uninitialized,
	if (cldiHeapIsNull(&CLDI_CURRENT_HEAP))
		// Initialize as current thread's default heap
		if (!cldiStatPermissible(cldiInitHeapCurrent(&CLDI_CURRENT_HEAP)))
			// If non-permissible error, return with error
			return NULL;
	// else/after return current system heap
#if CLDI_PLATFORM == CLDI_WINDOWS
	return (cldisysheap_t) GetCurrentHeap();
#elif CLDI_PLATFORM_UNIXLIKE == true
	return CLDISYSHEAP_NULL;
#else
#	error "cldi-head: cldiGetCurrentSysheap() has no implementation for this platform, report to the developer(s)."
#endif
}

CLDISTAT cldiInitHeap(cldiheap_t *self)
{
	CLDI_ERRNO = CLDI_SUCCESS;

	self->sysheap    = CLDISYSHEAP_NULL;
	self->envheap    = NULL;
	self->blocks     = NULL;
	self->blockcount = 0;

	return CLDI_SUCCESS;
}
CLDISTAT cldiInitHeapCurrentBuf(cldiheap_t *self, size_t bufsize)
{
	CLDI_ERRNO = CLDI_SUCCESS;

	const cldipid_t pid = cldiGetCurrentPID();

	void *addr = NULL;
	CLDI_MBLK_HEADER  *header  = NULL;
	CLDI_MBLK_HEADER **buf     = NULL;
#if CLDI_PLATFORM == CLDI_WINDOWS
	HANDLE hHeap = GetCurrentHeap();

	if (bufsize > 0) {
		header = (CLDI_MBLK_HEADER*) HeapAlloc(
			hHeap,
			cldiConvToSysMemPerms(CLDI_DEFAULT_MBLK_PERMS),
			sizeof(CLDI_MBLK_HEADER) + sizeof(CLDI_MBLK_HEADER*) * bufsize
		);

		addr = &header[1];
		buf  = (CLDI_MBLK_HEADER**) addr;

		header->block_type = cldiPtrTypeInfo;
		header->array_size = bufsize;
		header->perms      = CLDI_DEFAULT_MBLK_PERMS | CLDI_MBLK_ACTIVEOWNER;
		header->refc       = 1;
		header->status     = CLDI_MBLK_ACTIVE;
		header->owner      = cldiGetCurrentPID();
	}

	self->sysheap    = hHeap;
	self->envheap    = NULL;
	self->blocks     = buf;
	self->blockcount = 0;

	return CLDI_SUCCESS;
#elif CLDI_PLATFORM_UNIXLIKE == true

	// only if requested buffer size is greater than 0,
	if (bufsize > 0) {
		// allocate memory for block header and reference bank
		header = (CLDI_MBLK_HEADER*) mmap(
			// no minimum address
			NULL,
			// allocate space for a heap header, block buffer (with its own memory
			// block header), and a reference bank for allocated blocks
			sizeof(CLDI_HEAP_HEADER) + sizeof(CLDI_MBLK_HEADER) + sizeof(CLDI_MBLK_HEADER*) * bufsize,
			// adapt permissions for system API
			cldiConvToSysMemPerms(CLDI_DEFAULT_MBLK_PERMS),
			// adapt flags for system API
			cldiConvToSysHeapFlags(CLDI_DEFAULT_MBLK_PERMS),
			// demand zero in heap (no file descriptor from expanded CLDISYSHEAP_CURRENT)
			CLDISYSHEAP_CURRENT,
			// no offset required
			0
		);
		// move ptr to end of header (beginning of block) and remove type qualification
		// with void*.
		addr = &header[1];
		// recast to void** to store void* references in the bank.
		buf  = (void**) addr;

		// Fill header info
		header->block_type  = cldiPtrTypeInfo;
		header->array_size  = bufsize;
		header->perms       = CLDI_DEFAULT_MBLK_PERMS | CLDI_MBLK_ACTIVEOWNER;
		header->refc        = 1;
		header->status      = CLDI_MBLK_ACTIVE;
		header->owner       = pid;
	}

	// Fill heap info (including `buf`)
	self->sysheap    = CLDISYSHEAP_CURRENT; // use the system-provided heap.
	self->envheap    = NULL;
	self->blocks     = buf;
	self->blockcount = 0;

	// return success
	return CLDI_SUCCESS;
#else
#	error "cldi-head: cldiInitHeapCurrent() has no implementation for this platform, report to the developer(s)."
#endif
}
CLDISTAT cldiInitHeapCurrent(cldiheap_t *self)
{
	return cldiInitHeapCurrentBuf(self, CLDI_DEFAULT_MBLK_BUFSIZE);
}
CLDISTAT cldiInitEnvHeapBuf(cldiheap_t *self, size_t heap_size, size_t bufsize, int flags)
{
	CLDI_ERRNO = CLDI_SUCCESS;

	const cldisysheap_t sysheap = CLDISYSHEAP_CURRENT;
	const cldipid_t     pid     = cldiGetCurrentPID();

	// ptr container with deleted type
	void             *addr      = NULL,
	// ptr container for reference bank "blocks"
	/*............*/**buf       = NULL,
	// ptr container for reference bank "holes"
	/*............*/**holbuf    = NULL;
	// ptr container for header of reference bank "blocks"
	CLDI_MBLK_HEADER *header    = NULL,
	// ptr container for header of reference bank "holes"
	/*............*/ *holheader = NULL;
	// ptr container for heap header
	CLDI_HEAP_HEADER *hheader   = NULL;

	// check if the LOWFRAG_HEAP flag is enabled
	bool lowfrag = flags & CLDI_LOWFRAG_HEAP == CLDI_LOWFRAG_HEAP;

	// store total heap size,
	// start with default buffer size if buffer size is set to 0, and the total
	// size of a reference bank (mem block header and the array itself) otherwise.
	if (bufsize == 0)
		bufsize = CLDI_DEFAULT_MBLK_BUFSIZE;
	// include, in bufsize and heap_size, the number of blocks and bytes to
	// allocate as arrays to keep track of blocks and holes
	if (lowfrag) {
		bufsize += 2;
		heap_size += bufsize * 2;
	} else {
		bufsize++;
		heap_size += bufsize;
	}
	size_t total_heapsize = sizeof(CLDI_MBLK_HEADER) + (sizeof(void*) * bufsize);
	// If LOWFRAG_HEAP is enabled, multiply heapsize by 2, as another buffer will
	// be needed to record holes in the heap.
	if (lowfrag)
		total_heapsize *= 2;
	// Add the size of the required heap header, and the heap itself, for a total
	// including:
	//   - The heap header
	//   - A reference bank for allocated blocks (+ header)
	//   - A reference bank for deleted blocks (+ header) (if LOWFRAG_HEAP is enabled)
	//   - The entire heap with requested size
	total_heapsize += sizeof(CLDI_HEAP_HEADER) + heap_size;

	// allocate the heap as one entire memory block with system-specific function
	hheader =
#if CLDI_PLATFORM == CLDI_WINDOWS
	(CLDI_HEAP_HEADER*) HeapAlloc(
		// pass in sysheap handle
		sysheap,
		// convert to system memory perms/flags
		cldiConvToSysMemFlags(flags),
		// use predecided buffer size
		total_heapsize
	);
#elif CLDI_PLATFORM_UNIXLIKE == true
	(CLDI_HEAP_HEADER*) mmap(
		// no minimum address
		NULL,
		// use predecided buffer size
		total_heapsize,
		// pass in mem permissions flags, and memory allocation/info flags
		cldiConvToMemPerms(CLDI_DEFAULT_MBLK_PERMS),
		cldiConvToMemFlags(CLDI_DEFAULT_MBLK_PERMS),
		// pass sysheap value as file descriptor
		sysheap,
		// no offset
		0
	);
#else
#	error "cldi-head: cldiInitEnvHeapBuf() has no implementation for this platform, report to the developer(s)."
#endif
	// move ptr past the end of the heap header
	addr      = &hheader[1];
	// cast/store address as "blocks" reference bank header
	header    = (CLDI_MBLK_HEADER*) addr;
	// move ptr past the end of the header item
	addr      = &header[1];
	// cast/store address as "blocks" reference bank
	buf       = (void**) addr;
	// append ref bank "blocks" to itself (`header` is its memory block header),
	// to track it as a memory block
	buf[0]    = header;
	// move ptr to the end of "blocks"
	addr      = &buf[bufsize];
	// only if LOWFRAG_HEAP flag is enabled,
	if (lowfrag) {
		// cast/store address as the second reference bank header
		holheader = (CLDI_MBLK_HEADER*) addr;
		// add ref bank "holes" to ref bank "blocks", to track it as a memory
		// block
		buf[1]    = holheader;
		// move ptr past the end of the second header
		addr      = &holheader[1];
		// cast/store address as the second reference bank
		holbuf    = (void**) addr;
		// 
		// move ptr to the end of the second reference bank
		// and store as the beginning of the heap.
		addr      = &holbuf[bufsize];
	}
	// else, current address (end of first reference bank) will be the
	// beginning of the heap.

	hheader->name       = NULL;
	hheader->base       = header;
	hheader->top        = addr;
	hheader->bounds     = heap_size;
	hheader->blocks     = buf;
	hheader->blockcount = lowfrag? 2 : 1;

	header->block_type    = cldiPtrTypeInfo;
	header->array_size    = bufsize;
	header->perms         = CLDI_DEFAULT_MBLK_PERMS | CLDI_MBLK_ACTIVE;
	header->refc          = 1;
	header->status        = CLDI_MBLK_ACTIVE;
	header->owner         = cldiGetCurrentPID();

	holheader->block_type = cldiPtrTypeInfo;
	holheader->array_size = bufsize;
	holheader->perms      = CLDI_DEFAULT_MBLK_PERMS | CLDI_MBLK_ACTIVE;
	holheader->refc       = 1;
	holheader->status     = CLDI_MBLK_ACTIVE;
	holheader->owner      = cldiGetCurrentPID();
}
CLDISTAT cldiInitEnvHeap(cldiheap_t *self, size_t heap_size, int flags)
{
	return cldiInitEnvHeapBuf(self, heap_size, CLDI_DEFAULT_MBLK_BUFSIZE, flags);
}
CLDISTAT cldiInitSysheapBuf(cldiheap_t *self, cldisysheap_t sysheap, size_t bufsize)
{
	CLDI_ERRNO = CLDI_SUCCESS;

	cldipid_t pid = cldiGetCurrentPID();

	void *addr = NULL, **buf = NULL;
	CLDI_MBLK_HEADER *header = NULL; 

	// only if requested buffer size is greater than 0,
	if (bufsize > 0) {
		// allocate memory for block header and reference bank
		header = (CLDI_MBLK_HEADER*)
	#if CLDI_PLATFORM == CLDI_WINDOWS
		HeapAlloc(
			sysheap,
			cldiConvToSysMemPerms(CLDI_DEFAULT_MBLK_PERMS),
			sizeof(CLDI_MBLK_HEADER) + sizeof(void*) * bufsize
		);
	#elif CLDI_PLATFORM_UNIXLIKE == true
		mmap(
			// no minimum address
			NULL,
			// allocate space for two buffers (of equal size), and one header for
			// each, (two total)
			sizeof(CLDI_MBLK_HEADER) + sizeof(void*) * bufsize,
			// adapt permissions for system API
			cldiConvToSysMemPerms(CLDI_DEFAULT_MBLK_PERMS),
			// adapt flags for system API
			cldiConvToSysHeapFlags(CLDI_DEFAULT_MBLK_PERMS),
			// On unix, sysheap becomes file descriptor
			sysheap,
			// no offset required
			0
		);
	#else
	#	error "cldi-head: cldiInitSysheapBuf() has no implementation on this platform, report to the developer(s)."
	#endif
		// move ptr to end of header (beginning of block) and remove type qualification
		// with void*.
		addr = &header[1];
		// recast to void** to store void* references in the bank.
		buf  = (void**) addr;

		// Fill header info
		header->block_type  = cldiPtrTypeInfo;
		header->array_size  = bufsize;
		header->perms       = CLDI_DEFAULT_MBLK_PERMS | CLDI_MBLK_ACTIVEOWNER;
		header->refc        = 1;
		header->status      = CLDI_MBLK_ACTIVE;
		header->owner       = pid;
	}

	self->sysheap    = sysheap;
	self->envheap    = NULL;
	self->blocks     = buf;
	self->blockcount = 0;
}
CLDISTAT cldiInitSysheap(cldiheap_t *self, cldisysheap_t sysheap)
{
	return cldiInitSysheapBuf(self, sysheap, CLDI_DEFAULT_MBLK_BUFSIZE);
}


