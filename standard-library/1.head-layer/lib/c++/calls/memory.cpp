
/* Implementing: cldi-head: calls/memory */
#include <ciahlldi/cldi/head/calls/memory.h>

/* Requires: cldi-head: calls/process */
#include <ciahlldi/cldi/head/calls/process.h>



/* struct cldimemheader_t */
CLDIMEMHEADER::CLDIMEMHEADER(size_t size, cldipid_t owner, int flags):
#if __CLDI_PLATFORM_UNIXLIKE > false
	_mBlkSize(size),
#endif
	_mFlags(flags), _mOwner(owner)
{}
CLDIMEMHEADER::CLDIMEMHEADER(size_t size, int flags):
#if __CLDI_PLATFORM_UNIXLIKE > false
	_mBlkSize(size),
#endif
	_mFlags(flags), _mOwner(cldiGetCurrentPID())
{}

CLDIMEMHEADER::~CLDIMEMHEADER()
{}


