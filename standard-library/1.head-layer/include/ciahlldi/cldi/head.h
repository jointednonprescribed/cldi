
#ifndef _cldi_head_
#define _cldi_head_ 1
#define __cldi__    1



/* Header Load Order:
 * 
 *   settings.h
 *    |
 *   setup.h --- platform.h
 *    |           |
 *    |          includes.h
 *    |           |
 *    |          stat.h
 *    |           |
 *    |          types.h
 *    +-----------+
 * 
 *  The last header may be included alone, as it will include all other headers
 *  in chain.
 */

#include "head/setup.h"




#endif /* _cldi_head__ */
