


/* Implementing: cldi-head: memory.h */
#include <cldi/head/memory.h>



cldiheap_t CLDI_CURRENT_HEAP;

cldiheap_t* cldiGetCurrentHeap()
{
	// If CLDI_CURRENT_HEAP is uninitialized,
	if (cldiHeapIsNull(&CLDI_CURRENT_HEAP)) {
		// Initialize as current thread's default heap
		cldiInitHeapCurrent(&CLDI_CURRENT_HEAP);
		// If non-permissible error, return with error
		if (!cldiIsPermissible())
			return NULL;
	}
	// else return current heap
	return &CLDI_CURRENT_HEAP;
}

CLDISTAT cldiInitHeap(cldiheap_t *self)
{
	CLDI_ERRNO = CLDI_SUCCESS;
	self->base       = NULL;
	self->top        = NULL;
	self->bounds     = 0;
	self->holes      = NULL;
	self->holesizes  = NULL;
	self->holecount  = 0;
	self->_holecap   = 0;
	self->blocks     = NULL;
	self->blockcount = 0;
	self->_blockcap  = 0;
	self->sysheap    = CLDISYSHEAP_NULL;
	self->info       = 0;
	self->owner      = cldiGetCurrentPID();
	return CLDI_SUCCESS;
}
CLDISTAT cldiInitHeapCurrent(cldiheap_t *self)
{
	CLDI_ERRNO = CLDI_SUCCESS;
#if CLDI_PLATFORM == CLDI_WINDOWS
	return CLDI_ENO_IMPL;
#elif CLDI_PLATFORM_UNIXLIKE == true
	CLDI_MBLK_HEADER *bufh = (CLDI_MBLK_HEADER*) mmap(
		NULL,
		sizeof(CLDI_MBLK_HEADER) + sizeof(void*) * CLDI_DEFAULT_MBLK_BUFSIZE,
		cldiConvToSysMemPerms(CLDI_MBLK_PERM_DFLT),
		cldiConvToSysHeapFlags(CLDI_DEFAULT_SYSHEAP),
		0, 0
	);
	void *addr = (void*) &bufh[1];
	void **buf = (void**) addr;

	bufh->block_type = cldiPtrTypeInfo;

	self->base       = NULL;
	self->top        = NULL;
	self->bounds     = 0;
	self->holes      = NULL;
	self->holesizes  = NULL;
	self->holecount  = 0;
	self->_holecap   = 0;
	self->blocks     = NULL;
	self->blockcount = 0;
	self->_blockcap  = 0;
	self->sysheap    = CLDISYSHEAP_NULL;
	self->info       = CLDI_DEFAULT_SYSHEAP;
	self->owner      = cldiGetCurrentPID();
#else
	return CLDI_ENO_IMPL;
#	error "cldi-head: cldiInitHeapCurrent() has no implementation for this platform, report to the developer(s)."
#endif
}
CLDISTAT cldiInitEnvHeap(cldiheap_t *self, size_t heap_size)
{
	self->owner = cldiGetCurrentPID();
	return CLDI_ENO_IMPL;
}


