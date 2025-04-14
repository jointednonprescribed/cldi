
#ifndef _cldi_head__MEMORY_HPP
#define _cldi_head__MEMORY_HPP 1

#ifndef _cldi_head__MEMORY_H
#	include "../memory.h"
#endif

#if CLDI_C_ONLY == false



namespace cldi
{
	/* Alias for CLDIHEAPFLAG enum type */
	using HEAPFLAG      = ::CLDIHEAPFLAG;
	/* Enum values from _CLDIHEAPFLAGS: */
	constexpr HEAPFLAG NULL_HEAPFLAGS = ::CLDI_NULL_HEAPFLAGS;
	constexpr HEAPFLAG HEAP_ACTIVE = ::CLDI_HEAP_ACTIVE;
	constexpr HEAPFLAG HEAP_INACTIVE = ::CLDI_HEAP_INACTIVE;
	constexpr HEAPFLAG ENVHEAP = ::CLDI_ENVHEAP;
	constexpr HEAPFLAG SYSHEAP = ::CLDI_SYSHEAP;
	constexpr HEAPFLAG LOWFRAG_HEAP = ::CLDI_LOWFRAG_HEAP;
	constexpr HEAPFLAG DEFAULT_SYSHEAP = ::CLDI_DEFAULT_SYSHEAP;
	constexpr HEAPFLAG DEFAULT_ENVHEAP = ::CLDI_DEFAULT_ENVHEAP;

	inline int (&ConvToSysHeapPerms)(int) = ::cldiConvToSysHeapPerms;
	inline int (&ConvToSysHeapFlags)(int) = ::cldiConvToSysHeapFlags;

	/* Alias for CLDIMBLKFLAG enum type */
	using MBLK_FLAG = CLDIMBLKFLAG;
	/* Enum values from _CLDIMBLKPERMS: */
	condtexpr MBLK_FLAG MBLK_OREAD = ::CLDI_MBLK_OREAD;
	condtexpr MBLK_FLAG MBLK_OWRTE = ::CLDI_MBLK_OWRTE;
	condtexpr MBLK_FLAG MBLK_OEXEC = ::CLDI_MBLK_OEXEC;
	condtexpr MBLK_FLAG MBLK_GREAD = ::CLDI_MBLK_GREAD;
	condtexpr MBLK_FLAG MBLK_GWRTE = ::CLDI_MBLK_GWRTE;
	condtexpr MBLK_FLAG MBLK_GEXEC = ::CLDI_MBLK_GEXEC;
	condtexpr MBLK_FLAG MBLK_PREAD = ::CLDI_MBLK_PREAD;
	condtexpr MBLK_FLAG MBLK_PWRTE = ::CLDI_MBLK_PWRTE;
	condtexpr MBLK_FLAG MBLK_PEXEC = ::CLDI_MBLK_PEXEC;
	condtexpr MBLK_FLAG MBLK_NO_AUTH = ::CLDI_MBLK_NO_AUTH;
	condtexpr MBLK_FLAG MBLK_PAUTH = ::CLDI_MBLK_PAUTH;
	condtexpr MBLK_FLAG MBLK_GAUTH = ::CLDI_MBLK_GAUTH;
	condtexpr MBLK_FLAG MBLK_OAUTH = ::CLDI_MBLK_OAUTH;
	condtexpr MBLK_FLAG MBLK_ACTIVEOWNER = ::CLDI_MBLK_ACTIVEOWNER;
	/* Defaults */
	contexpr MBLK_FLAG MBLK_DEFAULT_AUTH  = ::CLDI_DEFAULT_MBLK_AUTH;
	contexpr MBLK_FLAG MBLK_DEFAULT_PERMS = ::CLDI_DEFAULT_MBLK_PERMS;
	contexpr MBLK_FLAG MBLK_PRIVATE_PERMS = ::CLDI_PRIVATE_MBLK_PERMS;
	/* Aliases */
	contexpr MBLK_FLAG MBLK_READ          = ::CLDI_MBLK_READ;
	contexpr MBLK_FLAG MBLK_WRITE         = ::CLDI_MBLK_WRITE;
	contexpr MBLK_FLAG MBLK_EXEC          = ::CLDI_MBLK_EXEC;
	contexpr MBLK_FLAG MBLK_OWNER_PERMS   = ::CLDI_MBLK_OWNER_PERMS;
	contexpr MBLK_FLAG MBLK_GROUP_PERMS   = ::CLDI_MBLK_GROUP_PERMS;
	contexpr MBLK_FLAG MBLK_PUBLIC_PERMS  = ::CLDI_MBLK_PUBLIC_PERMS;

	inline int (&ConvToSysMemPerms)(int) = ::cldiConvToSysMemPerms;
	inline int (&ConvToSysMemFlags)(int) = ::cldiConvToSysMemFlags;

	/* Alias for cldimblkstat_t enum type */
	using mblkstat_t    = ::cldimblkstat_t;
	/* Enum values for cldimblkstat_t: */
	constexpr mblkstat_t MBLK_UNAVAILABLE = ::CLDI_MBLK_UNAVAILABLE;
	constexpr mblkstat_t MBLK_NONEXISTENT = ::CLDI_MBLK_NONEXISTENT;
	constexpr mblkstat_t MBLK_ACTIVE      = ::CLDI_MBLK_ACTIVE;
	constexpr mblkstat_t MBLK_PENDING     = ::CLDI_MBLK_PENDING;
	constexpr mblkstat_t MBLK_HOLE        = ::CLDI_MBLK_HOLE;

	/* Alias for CLDI_MBLK_HEADER (memory block header) */
	using mblkheader_t  = ::CLDI_MBLK_HEADER;
	/* Alias for CLDI_HEAP_HEADER (heap header) */
	using heapheader_t  = ::CLDI_HEAP_HEADER;
	/* Alias for cldisysheap_t (system heap reference) */
	using sysheap_t     = ::cldisysheap_t;
	// - Predefined values for sysheap_t
	constexpr sysheap_t SYSHEAP_NULL = CLDISYSHEAP_NULL;
	constexpr sysheap_t SYSHEAP_CURRENT = CLDISYSHEAP_CURRENT;
	/* Alias for cldimblkid_t (memory block ID) */
	using mblkid_t      = ::cldimblkid_t;

	/* Alias for cldiheap_t (heap type) */
	using _gheap_t      = ::cldiheap_t;

	/* Alias and type-safe wrapper for cldimemref */
	using _gmemref      = ::cldimemref;
	template <typename _T>
	class memref;
	/* Type-safe allocator function. */
	template <typename _T>
	using mblkallocator = supplier<memref<_T>>;
	/* Type-safe destructor function. */
	template <typename _T>
	using mblkdestructor = consumer<memref<_T>*>;

	/* Type-safe wrapper type for cldiheap_t: */
	class heap_t: private _gheap_t
	{
	public:

		static constexpr size_t DEFAULT_MBLK_BUFSIZE = CLDI_DEFAULT_MBLK_BUFSIZE;

		heap_t();
		heap_t(size_t heapsize, int flags);
		heap_t(size_t heapsize, size_t bufsize=DEFAULT_MBLK_BUFSIZE, int flags=MBLK_);
		heap_t(sysheap_t sysheap, size_t bufsize=DEFAULT_MBLK_BUFSIZE);
		heap_t(const _gheap_t &conv);
		heap_t(const heap_t &rhv);
		~heap_t();

		STAT Drop();

		operator _gheap_t() const;

		static heap_t MakeHeapFromCurrent();
		STAT SetAsCurrentHeap();
		STAT AdoptCurrentHeap();

		size_t          TotalSize() const;
		size_t          Size() const;
		size_t          MemoryUsage() const;
		double          MemoryUsagePercent() const;
		size_t          MemoryRemaining() const;
		const char*     GetName() const;
		memref<wchar_t> GetNameW();
		STAT            SetName(const char *name);
		STAT            SetName(const wchar_t *name);

		template <typename _T>
		mblkid_t   NewBlock(int flags)
		{
			return cldiHeapNewBlock(this, typeinfo_t<_T>(), flags);
		}
		template <typename _T>
		mblkid_t   NewArray(size_t array_size, int flags)
		{
			return cldiHeapNewArray(this, typeinfo_t<_T>(), array_size, flags);
		}
		template <typename _T>
		mblkid_t   NewPendingBlock(int flags)
		{
			return cldiHeapNewPendingBlock(this, typeinfo_t<_T>(), flags);
		}
		template <typename _T>
		mblkid_t   NewPendingArray(size_t array_size, int flags)
		{
			return cldiHeapNewPendingArray(this, typeinfo_t<_T>(), array_size, flags);
		}
		template <typename _T>
		memref<_T> NewBlockRef(int flags, mblkdestructor<_T> destr = NULL)
		{
			return memref<_T>(this, cldiHeapNewPendingBlock(this, typeinfo_t<_T>(), flags), destr);
		}
		template <typename _T>
		memref<_T> NewArrayRef(size_t array_size, int flags, mblkdestructor<_T> destr = NULL)
		{
			return memref<_T>(this, cldiHeapNewPendingArray(this, typeinfo_t<_T>(), array_size, flags), destr);
		}
		STAT BorrowBlock(mblkid_t blkid) const;
		STAT ClaimBlock(mblkid_t blkid) const;
		STAT DropBlock(mblkid_t blkid);

		void *const       GetBlockAddr(mblkid_t blkid);
		const void *const GetBlockConstAddr(mblkid_t blkid)        const;
		STAT              GetBlockStatus(mblkid_t blkid)           const;
		int               GetBlockPerms(mblkid_t blkid)            const;
		oid_t             GetBlockOwner(mblkid_t blkid)            const;
		pid_t             GetBlockOwnerThread(mblkid_t blkid)            const;
		gid_t             GetBlockOwnerGroup(mblkid_t blkid)            const;
		int               GetBlockRefCount(mblkid_t blkid)         const;
		size_t            GetBlockSize(mblkid_t blkid)             const;
		size_t            GetBlockCapacity(mblkid_t blkid)         const;

		int      GetBlockPerms(const cldiheap_t *self, cldimblkid_t blk);
		CLDISTAT SetBlockPerms(const cldiheap_t *self, cldimblkid_t blk, int perms);
		CLDISTAT AddBlockPerms(const cldiheap_t *self, cldimblkid_t blk, int perms);
		CLDISTAT RemoveBlockPerms(const cldiheap_t *self, cldimblkid_t blk, int perms);
		CLDISTAT ClearBlockPerms(const cldiheap_t *self, cldimblkid_t blk);
		
		bool BlockStatusEq(cldimblkid_t blk, cldimblkstat_t check_stat);
		bool IsBlockActive(const cldiheap_t *self, cldimblkid_t blk);
		bool IsBlockPending(const cldiheap_t *self, cldimblkid_t blk);
		bool IsBlockHole(const cldiheap_t *self, cldimblkid_t blk);
		bool IsBlockWritable(const cldiheap_t *self, cldimblkid_t blk);
		bool IsBlockReadable(const cldiheap_t *self, cldimblkid_t blk);
		bool IsBlockExecutable(const cldiheap_t *self, cldimblkid_t blk);
		bool IsBlockWritableOnThread(const cldiheap_t *self, cldimblkid_t blk, cldipid_t thr);
		bool IsBlockReadableOnThread(const cldiheap_t *self, cldimblkid_t blk, cldipid_t thr);
		bool IsBlockExecutableOnThread(const cldiheap_t *self, cldimblkid_t blk, cldipid_t thr);
		
		bool IsNull() const;
		bool IsActive() const;
		bool IsSysheap() const;
		bool IsEnvHeap() const;
		bool IsLowFrag() const;

		template <typename _T>
		memref<_T> CallAllocator(mblkallocator<_T> allocator)
		{
			_gheap_t *const true_heap = ::CLDI_CURRENT_HEAP;

			::CLDI_CURRENT_HEAP = this;

			memref<_T> ref = allocator();

			::CLDI_CURRENT_HEAP = true_heap;

			return ref;
		}
	};
	/* Current Heap reference. */
	inline _gheap_t* (&__CURRENT_HEAP) = ::CLDI_CURRENT_HEAP;
	/* Get current heap. */
	heap_t&            GetCurrentHeap();
	inline sysheap_t (&GetCurrentSysheap)() = ::cldiGetCurrentSysheap;

	/* Type-safe wrapper type for cldimemref: */
	template <typename _T>
	class memref: private _gmemref
	{
	private:

		memref(_T *ref, size_t item_count=1, mblkdestr_t destr=NULL):
			objtype(TYPE_INFO), destructor(destr), ptr(ref),
			heap(GetCurrentHeap()), id(0),  owner(GetCurrentPID()),
			active(ref != NULL), activeid(false), shared(true)
		{}

	public:

		TYPE_COMPAT MatchTypeInfo(const _gtypeinfo_t &info)
		{
			return info.size == sizeof(_T) && info.templ == typeinfo_t<_T>::TEMPLATE;
		}
		TYPE_COMPAT MatchBlockType(const heap_t &heap, memblkid_t blkid)
		{
			_gtypeinfo_t info = heap->GetBlockType(blkid);
			return info.size == sizeof(_T) && info.templ == typeinfo_t<_T>::TEMPLATE;
		}
		TYPE_COMPAT MatchBlockType(mblkid_t blkid)
		{
			return MatchBlockType(*(this->heap), blkid);
		}
		TYPE_COMPAT MatchBlockType(const memref<_T> &ref)
		{
			return MatchBlockType(ref.id, ref.heap);
		}

		STAT Borrow(const memref<_T> &rhv)
		{
			errno = SUCCESS;

			if (rhv.active) {
				if (active)
					Drop();

				if (rhv.activeid) {
					::cldiHeapBorrowBlock(rhv.heap, rhv.id);
					if (!cldiIsPermissible()) {
						return errno;
					}
				}
				objtype    = rhv.objtype;
				destructor = rhv.destructor;
				ptr        = rhv.ptr;
				heap       = rhv.heap;
				id         = rhv.id;
				active     = rhv.active;
				activeid   = rhv.activeid;
				shared     = true;
			}

			return errno;
		}
		STAT Borrow(const _gmemref &rhv)
		{
			errno = SUCCESS;

			if (MatchTypeInfo(rhv.objtype) != TYPE_COMPAT_FULL) {
				errno = EINCOMPATIBLE_TYPE;
				return EINCOMPATIBLE_TYPE;
			}

			if (rhv.active) {
				if (active)
					Drop();

				::cldiMemrefBorrow(this, &rhv);
				if (!IsPermissible()) {
					return errno;
				}
			}

			return errno;
		}
		STAT Borrow(heap_t &heap, mblkid_t blkid, mblkdestr_t destr = NULL)
		{
			errno = SUCCESS;
			if (!MatchTypeInfo(heap, blkid)) {
				errno = EINCOMPATIBLE_TYPE;
				return;
			}

			if (heap.IsBlockActive(blkid)) {
				if (active)
					Drop();

				heap.BorrowBlock(blkid);
				if (!IsPermissible()) {
					return errno;
				} else {
					destructor = destr;
					objtype    = heap.GetBlockType();
					ptr        = NULL;
					heap       = heap;
					id         = blkid;
					active     = true;
					activeid   = true;
					shared     = true;
				}
			}

			return errno;
		}
		STAT Borrow(mblkid_t blkid)
		{
			return Borrow(GetCurrentHeap(), blkid);
		}

		memref():
			objtype(typeinfo_t<_T>()), destructor(NULL), ptr(NULL),
			heap(NULL), id(0), owner(GetCurrentPID()),
			active(false), activeid(false), shared(false)
		{}
		memref(const memref<_T> &borrow):
			owner(GetCurrentPID())
		{
			active   = false;
			activeid = false;
			Borrow(borrow);
		}
		memref(_gmemref &gborrow):
			owner(GetCurrentPID())
		{
			active   = false;
			activeid = false;
			Borrow(gborrow);
		}
		memref(heap_t &blkheap, mblkid_t blkid, mblkdestuctor<_T> destr=NULL):
			owner(GetCurrentPID())
		{
			errno = SUCCESS;

			const mblkheader_t *blkh = cldiHeapGetBlockHeader(&blkheap, blkid);

			// if the block does not exist, construct null and return
			if (!cldiIsPermissible()) {
			construct_null: // construct null and return
				objtype    = CLDITYPEINFO_NULL;
				destructor = NULL;
				ptr        = NULL;
				heap       = NULL;
				id         = 0;
				active     = false;
				activeid   = false;
				shared     = false;
				return;
			} else {
				// else, check type information of memory block
				if (!MatchTypeInfo(blkh->block_type)) {
					// if incompatible, construct null and return will error.
					errno = EINCOMPATIBLE_TYPE;
					goto construct_null;
				// else if the block is pending,
				} else if (blkh->status == MBLK_PENDING) {
					// claim block ownership
					cldiHeapClaimBlock(&blkheap, blkid);
					// if some error is returned,
					if (!IsPermissible())
						goto construct_null;
					// else, claiming the block was successful, so construct with \
					block and heap information and shared=false flag
					objtype    = blkh->block_type;
					destructor = destr;
					ptr        = NULL;
					heap       = &blkheap;
					id         = blkid;
					active     = true;
					activeid   = true;
					shared     = false;
					return;
				// else, if the block is active 
				} else if (blkh->status == MBLK_ACTIVE) {
					// attempt to share the block instead
					cldiHeapBorrowBlock(&blkheap, blkid);
					// if not successful, construct null and return with current \
					error.
					if (!IsPermissible()) {
						goto construct_null;
					}
					// if sharing was successful, construct with block and \
					heap information and shared=true flag.
					objtype    = blkh->block_type;
					destructor = destr;
					ptr        = NULL;
					heap       = &blkheap;
					id         = blkid;
					active     = true;
					activeid   = true;
					shared     = true;
					return;
				}cout << setw(22) << records[i].name << setw(5) << records[i].avg << endl
			}
		}

		auto operator =(const memref<_T> &rhv)
		{
			Borrow(rhv);
		}
		auto operator =(const _gmemref &rhv)
		{
			Borrow(rhv);
		}

		/* Must be called by the destructor. */
		CLDISTAT Drop()
		{
			if (active) {
				destructor(this);
				if (activeid) {
					heap.DropBlock(id);
				} else if (ptr != NULL) {
					DropAddress(ptr);
				}
				ptr        = NULL;
				destructor = NULL;
				heap       = NULL;
				id         = 0;
				objcount   = 0;
				active     = false;
				activeid   = false;
				shared     = false;
			}
		}
		~memref()
		{
			this->Drop();
		}

		mblkdestr_t GetDestructor() const
		{
			return destructor;
		}
		heap_t& GetHeap() const
		{
			return *heap;
		}
		mblkid_t GetID() const
		{
			return id;
		}
		size_t GetObjectCount() const
		{
			return objcount;
		}
		_gtypeinfo_t GetBlockTypeInfo() const
		{
			return heap.GetBlockTypeInfo(id);
		} 
		_gtypeinfo_t GetGenericTypeInfo() const
		{
			return objtype;
		}
		typeinfo_t<_T> GetTypeInfo() const
		{
			return typeinfo_t<_T>();
		}
		pid_t GetOwner() const
		{
			return owner;
		}

		_T* GetAddr() const
		{
			return heap.GetBlockAddr(id);
		}
		const _T* BorrowAddr() const
		{
			return heap.BorrowBlockAddr(id);
		}

		bool IsNull() const
		{
			return ptr == NULL && id == 0 && heap == NULL && objcount == 0 && !active;
		}
		bool IsActive() const
		{
			return active;
		}
		bool IsActiveByID() const
		{
			return active && activeid;
		}
		bool IsShared() const
		{
			return shared;
		}
		bool OwnsBlock() const
		{
			return !shared;
		}
	};
}



#endif // CLDI_C_ONLY == false

#endif // _cldi_head__MEMORY_HPP
