
#ifndef _cldi_head__MEMORY_HPP
#define _cldi_head__MEMORY_HPP 1

#ifndef _cldi_head__MEMORY_H
#	include "../memory.h"
#endif

#if CLDI_C_ONLY == false



namespace cldi
{
	/* Alias for CLDIHEAPFLAG enum type */
	using HEAPFLAG = CLDIHEAPFLAG;
	/* Enum values from _CLDIHEAPFLAGS: */
	constexpr HEAPFLAG HF_SYSHEAP = CLDI_SYSHEAP;
	constexpr HEAPFLAG HF_FREE_HEAP = CLDI_FREE_HEAP;
	constexpr HEAPFLAG HF_DEFAULT_SYSHEAP = CLDI_DEFAULT_SYSHEAP;
	constexpr HEAPFLAG HF_DEFAULT_VHEAP = CLDI_DEFAULT_VHEAP;

	/* Alias for CLDIMBLKPERM enum type */
	using MBLKPERM = CLDIMBLKPERM;
	/* Enum values from _CLDIMBLKPERMS: */
	constexpr MBLKPERM MBLK_OREAD = CLDI_MBLK_OREAD;
	constexpr MBLKPERM MBLK_OWRTE = CLDI_MBLK_OWRTE;
	constexpr MBLKPERM MBLK_OEXEC = CLDI_MBLK_OEXEC;
	constexpr MBLKPERM MBLK_GREAD = CLDI_MBLK_GREAD;
	constexpr MBLKPERM MBLK_GWRTE = CLDI_MBLK_GWRTE;
	constexpr MBLKPERM MBLK_GEXEC = CLDI_MBLK_GEXEC;
	constexpr MBLKPERM MBLK_AREAD = CLDI_MBLK_AREAD;
	constexpr MBLKPERM MBLK_AWRTE = CLDI_MBLK_AWRTE;
	constexpr MBLKPERM MBLK_AEXEC = CLDI_MBLK_AEXEC;
	constexpr MBLKPERM MBLK_READ  = CLDI_MBLK_READ;
	constexpr MBLKPERM MBLK_WRITE = CLDI_MBLK_WRITE;
	constexpr MBLKPERM MBLK_EXEC  = CLDI_MBLK_EXEC;

	/* Alias for cldimblkstat_t enum type */
	using mblkstat_t  = cldimblkstat_t;
	/* Enum values for cldimblkstat_t: */
	constexpr mblkstat_t MBLK_UNAVAILABLE = CLDI_MBLK_UNAVAILABLE;
	constexpr mblkstat_t MBLK_NONEXISTENT = CLDI_MBLK_NONEXISTENT;
	constexpr mblkstat_t MBLK_ACTIVE = CLDI_MBLK_ACTIVE;
	constexpr mblkstat_t MBLK_PENDING = CLDI_MBLK_PENDING;
	constexpr mblkstat_t MBLK_HOLE = CLDI_MBLK_HOLE;

	/* Alias for cldisysheap_t (system heap reference) */
	using sysheap_t   = cldisysheap_t;
	/* Alias for cldimblkid_t (memory block ID) */
	using mblkid_t    = cldimblkid_t;
	/* Alias for cldimblkdestr_t (memory block destructor) */
	using mblkdestr_t = cldimblkdestr_t;
	/* Alias for cldiallocator_t (memory block allocator) */
	using allocator_t = cldiallocator_t;

	/* Alias for cldiheap_t (heap type) */
	using heap_t = cldiheap_t;

	/* cldimemref */
	using _gmemref = cldimemref;

	/* Type-safe wrapper type for cldimemref: */
	template <typename _T>
	class memref: private _gmemref
	{
	private:

		memref(_T *ref, size_t item_count=1, mblkdestr_t destr=NULL):
			destructor(destr), ptr(ref), heap(GetCurrentHeap()), id(0),
			objcount(item_count). objtype(TYPE_INFO), owner(GetCurrentPID()),
			active(ref != NULL), activeid(false), shared(true)
		{}

	public:

		bool MatchTypeInfo(_gtypeinfo_t info)
		{
			return info.size == sizeof(_T) && info.templ == typeinfo_t<_T>::TEMPLATE;
		}
		bool MatchBlockType(memblkid_t blkid, const heap_t &heap)
		{
			_gtypeinfo_t info = heap->GetBlockTypeInfo(blkid);
			return info.size == sizeof(_T) && info.templ == typeinfo_t<_T>::TEMPLATE;
		}
		bool MatchBlockType(memblkid_t blkid)
		{
			return MatchBlockType(blkid, *(this->heap))
		}
		bool MatchBlockType(const memref<_T> &ref)
		{
			return MatchBlockType(ref.id, ref.heap);
		}

		auto operator =(const memref<_T> &rhv)
		{
			errno = SUCCESS;
			if (rhv.activeid || rhv.active) {
				memref<_T> sref = rhv.Share();
				if (!cldiIsPermissible()) {
					return;
				} else {
					ptr        = sref.ptr;
					destructor = sref.destructor;
					heap       = sref.heap;
					id         = sref.id;
					objcount   = sref.objcount;
					objtype    = sref.objtype;
					active     = sref.active;
					activeid   = sref.activeid;
					shared     = true;
				}
			} else {
				ptr        = rhv.ptr;
				destructor = rhv.destructor;
				heap       = rhv.heap;
				id         = rhv.id;
				objcount   = rhv.objcount;
				objtype    = rhv.objtype;
				active     = rhv.active;
				activeid   = rhv.activeid;
				shared     = rhv.shared;
			}
		}
		auto operator =(const _gmemref &rhv)
		{
			errno = SUCCESS;
			if (!MatchTypeInfo(rhv.objtype)) {
				errno = EINCOMPATIBLE_TYPE;
				return;
			}
			_gmemref sref;
			if (rhv.activeid || rhv.active) {
				cldiMemrefShare(&rhv, &sref);
				if (!cldiIsPermissible()) {
					return;
				} else {
					ptr        = sref.ptr;
					destructor = sref.destructor;
					heap       = sref.heap;
					id         = sref.id;
					objcount   = sref.objcount;
					objtype    = sref.objtype;
					active     = sref.active;
					activeid   = sref.activeid;
					shared     = true;
				}
			} else {
				ptr        = rhv.ptr;
				destructor = rhv.destructor;
				heap       = rhv.heap;
				id         = rhv.id;
				objcount   = rhv.objcount;
				objtype    = rhv.objtype;
				active     = rhv.active;
				activeid   = rhv.activeid;
				shared     = rhv.shared;
			}
		}

		memref():
			destructor(NULL), ptr(NULL), heap(NULL), id(0), objcount(0),
			objtype(TYPE_INFO), owner(GetCurrentPID()), active(false),
			activeid(false), shared(false)
		{}
		memref(const memref<_T> &ref):
			owner(GetCurrentPID())
		{
			*this = ref;
		}
		memref(_gmemref &gref):
		{
			*this = gref;
		}
		memref(heap_t &blkheap, mblkid_t blkid, mblkdestr_t destr=NULL):
			owner(GetCurrentPID())
		{
			errno = SUCCESS;
			// if the block does not exist, construct null and return
			if (!blkheap.BlockExists(blkid)) {
				errno = ENONEXISTENT;
				goto construct_null;
			} else {
				_gtypeinfo_t tinfo = blkheap.GetBlockTypeInfo(blkid);
				// else, check type information of memory block
				if (!MatchTypeInfo(tinfo)) {
					// if incompatible, construct null and return will error.
					errno = EINCOMPATIBLE_TYPE;
					goto construct_null;
				// else if the block is pending,
				} else if (blkheap.IsPendingBlock(blkid)) {
					// claim block ownership
					blkheap.ClaimBlock(blkid);
					// if some error is returned,
					if (!IsPermissible()) {
					construct_null: // construct null and return
						ptr        = NULL;
						destructor = NULL;
						heap       = NULL;
						id         = 0;
						objcount   = 0;
						objtype    = CLDITYPEINFO_NULL;
						active     = false;
						activeid   = false;
						shared     = false;
						return;
					}
					// else, claiming the block was successful, so construct with \
					block and heap information and shared=false flag
					ptr        = NULL;
					destructor = destr;
					heap       = &blkheap;
					id         = blkid;
					objcount   = blkheap.GetBlockObjectCount(blkid);
					objtype    = tinfo;
					active     = true;
					activeid   = true;
					shared     = false;
					return;
				// else, the block is active 
				} else {
					// attempt to share the block instead
					blkheap.ShareBlock(blkid);
					// if not successful, construct null and return with current \
					error.
					if (!IsPermissible()) {
						goto construct_null;
					}
					// if sharing was successful, construct with block and \
					heap information and shared=true flag.
					ptr        = NULL;
					destructor = destr;
					heap       = &blkheap;
					id         = blkid;
					objcount   = blkheap.GetBlockObjectCount(blkid);
					objtype    = tinfo;
					active     = true;
					activeid   = true;
					shared     = true;
					return;
				}
			}
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

		bool IsNull() constnamespace cldi
		{
			/* Alias for CLDIHEAPFLAG enum type */
			using HEAPFLAG = CLDIHEAPFLAG;
			/* Enum values from _CLDIHEAPFLAGS: */
			constexpr HEAPFLAG HF_SYSHEAP = CLDI_SYSHEAP;
			constexpr HEAPFLAG HF_FREE_HEAP = CLDI_FREE_HEAP;
			constexpr HEAPFLAG HF_DEFAULT_SYSHEAP = CLDI_DEFAULT_SYSHEAP;
			constexpr HEAPFLAG HF_DEFAULT_VHEAP = CLDI_DEFAULT_VHEAP;
		
			/* Alias for CLDIMBLKPERM enum type */
			using MBLKPERM = CLDIMBLKPERM;
			/* Enum values from _CLDIMBLKPERMS: */
			constexpr MBLKPERM MBLK_OREAD = CLDI_MBLK_OREAD;
			constexpr MBLKPERM MBLK_OWRTE = CLDI_MBLK_OWRTE;
			constexpr MBLKPERM MBLK_OEXEC = CLDI_MBLK_OEXEC;
			constexpr MBLKPERM MBLK_GREAD = CLDI_MBLK_GREAD;
			constexpr MBLKPERM MBLK_GWRTE = CLDI_MBLK_GWRTE;
			constexpr MBLKPERM MBLK_GEXEC = CLDI_MBLK_GEXEC;
			constexpr MBLKPERM MBLK_AREAD = CLDI_MBLK_AREAD;
			constexpr MBLKPERM MBLK_AWRTE = CLDI_MBLK_AWRTE;
			constexpr MBLKPERM MBLK_AEXEC = CLDI_MBLK_AEXEC;
			constexpr MBLKPERM MBLK_READ  = CLDI_MBLK_READ;
			constexpr MBLKPERM MBLK_WRITE = CLDI_MBLK_WRITE;
			constexpr MBLKPERM MBLK_EXEC  = CLDI_MBLK_EXEC;
		
			/* Alias for cldimblkstat_t enum type */
			using mblkstat_t  = cldimblkstat_t;
			/* Enum values for cldimblkstat_t: */
			constexpr mblkstat_t MBLK_UNAVAILABLE = CLDI_MBLK_UNAVAILABLE;
			constexpr mblkstat_t MBLK_NONEXISTENT = CLDI_MBLK_NONEXISTENT;
			constexpr mblkstat_t MBLK_ACTIVE = CLDI_MBLK_ACTIVE;
			constexpr mblkstat_t MBLK_PENDING = CLDI_MBLK_PENDING;
			constexpr mblkstat_t MBLK_HOLE = CLDI_MBLK_HOLE;
		
			/* Alias for cldisysheap_t (system heap reference) */
			using sysheap_t   = cldisysheap_t;
			/* Alias for cldimblkid_t (memory block ID) */
			using mblkid_t    = cldimblkid_t;
			/* Alias for cldimblkdestr_t (memory block destructor) */
			using mblkdestr_t = cldimblkdestr_t;
			/* Alias for cldiallocator_t (memory block allocator) */
			using allocator_t = cldiallocator_t;
		
			/* Alias for cldiheap_t (heap type) */
			using heap_t = cldiheap_t;
		
			/* cldimemref */
			using _gmemref = cldimemref;
		
			/* Type-safe wrapper type for cldimemref: */
			template <typename _T>
			class memref: private _gmemref
			{
			private:
		
				memref(_T *ref, size_t item_count=1, mblkdestr_t destr=NULL):
					destructor(destr), ptr(ref), heap(GetCurrentHeap()), id(0),
					objcount(item_count). objtype(TYPE_INFO), owner(GetCurrentPID()),
					active(ref != NULL), activeid(false), shared(true)
				{}
		
			public:
		
				bool MatchTypeInfo(_gtypeinfo_t info)
				{
					return info.size == sizeof(_T) && info.templ == typeinfo_t<_T>::TEMPLATE;
				}
				bool MatchBlockType(memblkid_t blkid, const heap_t &heap)
				{
					_gtypeinfo_t info = heap->GetBlockTypeInfo(blkid);
					return info.size == sizeof(_T) && info.templ == typeinfo_t<_T>::TEMPLATE;
				}
				bool MatchBlockType(memblkid_t blkid)
				{
					return MatchBlockType(blkid, *(this->heap))
				}
				bool MatchBlockType(const memref<_T> &ref)
				{
					return MatchBlockType(ref.id, ref.heap);
				}
		
				auto operator =(const memref<_T> &rhv)
				{
					errno = SUCCESS;
					if (rhv.activeid || rhv.active) {
						memref<_T> sref = rhv.Share();
						if (!cldiIsPermissible()) {
							return;
						} else {
							ptr        = sref.ptr;
							destructor = sref.destructor;
							heap       = sref.heap;
							id         = sref.id;
							objcount   = sref.objcount;
							objtype    = sref.objtype;
							active     = sref.active;
							activeid   = sref.activeid;
							shared     = true;
						}
					} else {
						ptr        = rhv.ptr;
						destructor = rhv.destructor;
						heap       = rhv.heap;
						id         = rhv.id;
						objcount   = rhv.objcount;
						objtype    = rhv.objtype;
						active     = rhv.active;
						activeid   = rhv.activeid;
						shared     = rhv.shared;
					}
				}
				auto operator =(const _gmemref &rhv)
				{
					errno = SUCCESS;
					if (!MatchTypeInfo(rhv.objtype)) {
						errno = EINCOMPATIBLE_TYPE;
						return;
					}
					_gmemref sref;
					if (rhv.activeid || rhv.active) {
						cldiMemrefShare(&rhv, &sref);
						if (!cldiIsPermissible()) {
							return;
						} else {
							ptr        = sref.ptr;
							destructor = sref.destructor;
							heap       = sref.heap;
							id         = sref.id;
							objcount   = sref.objcount;
							objtype    = sref.objtype;
							active     = sref.active;
							activeid   = sref.activeid;
							shared     = true;
						}
					} else {
						ptr        = rhv.ptr;
						destructor = rhv.destructor;
						heap       = rhv.heap;
						id         = rhv.id;
						objcount   = rhv.objcount;
						objtype    = rhv.objtype;
						active     = rhv.active;
						activeid   = rhv.activeid;
						shared     = rhv.shared;
					}
				}
		
				memref():
					destructor(NULL), ptr(NULL), heap(NULL), id(0), objcount(0),
					objtype(TYPE_INFO), owner(GetCurrentPID()), active(false),
					activeid(false), shared(false)
				{}
				memref(const memref<_T> &ref):
					owner(GetCurrentPID())
				{
					*this = ref;
				}
				memref(_gmemref &gref):
				{
					*this = gref;
				}
				memref(heap_t &blkheap, mblkid_t blkid, mblkdestr_t destr=NULL):
					owner(GetCurrentPID())
				{
					errno = SUCCESS;
					// if the block does not exist, construct null and return
					if (!blkheap.BlockExists(blkid)) {
						errno = ENONEXISTENT;
						goto construct_null;
					} else {
						_gtypeinfo_t tinfo = blkheap.GetBlockTypeInfo(blkid);
						// else, check type information of memory block
						if (!MatchTypeInfo(tinfo)) {
							// if incompatible, construct null and return will error.
							errno = EINCOMPATIBLE_TYPE;
							goto construct_null;
						// else if the block is pending,
						} else if (blkheap.IsPendingBlock(blkid)) {
							// claim block ownership
							blkheap.ClaimBlock(blkid);
							// if some error is returned,
							if (!IsPermissible()) {
							construct_null: // construct null and return
								ptr        = NULL;
								destructor = NULL;
								heap       = NULL;
								id         = 0;
								objcount   = 0;
								objtype    = CLDITYPEINFO_NULL;
								active     = false;
								activeid   = false;
								shared     = false;
								return;
							}
							// else, claiming the block was successful, so construct with \
							block and heap information and shared=false flag
							ptr        = NULL;
							destructor = destr;
							heap       = &blkheap;
							id         = blkid;
							objcount   = blkheap.GetBlockObjectCount(blkid);
							objtype    = tinfo;
							active     = true;
							activeid   = true;
							shared     = false;
							return;
						// else, the block is active 
						} else {
							// attempt to share the block instead
							blkheap.ShareBlock(blkid);
							// if not successful, construct null and return with current \
							error.
							if (!IsPermissible()) {
								goto construct_null;
							}
							// if sharing was successful, construct with block and \
							heap information and shared=true flag.
							ptr        = NULL;
							destructor = destr;
							heap       = &blkheap;
							id         = blkid;
							objcount   = blkheap.GetBlockObjectCount(blkid);
							objtype    = tinfo;
							active     = true;
							activeid   = true;
							shared     = true;
							return;
						}
					}
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
