
#ifndef _cldi_head_
#define _cldi_head_ 1
#define __cldi__    1



/* Header Load Order:
 * 
 *   settings.h
 *    |
 *   setup.h --- setup/platform.h
 *    |           |
 *    |          setup/includes.h
 *    |           |
 *    |          setup/stat.h
 *    |           |
 *    |          setup/types.h
 *    +-----------+
 *    |
 *   functypes.h
 * 
 *  The last header may be included alone, as it will include all other headers
 *  in chain.
 */

#include "head/functypes.h"




#endif /* _cldi_head__ */
