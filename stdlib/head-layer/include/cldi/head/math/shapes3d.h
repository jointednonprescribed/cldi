
#ifndef _cldi_head__math_SHAPES3D_H
#define _cldi_head__math_SHAPES3D_H 1

/* Subheader of head/math.h */
#ifndef _cldi_head__MATH_H
#	include "../math.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif



// 3-Dimensional point
typedef struct _CLDITENSOR3D
{
	cldifpm_t x, y, z;
} cldipoint3d_t, clditensor3d_t;
// 3-Dimensional Graphing Function
cldiTemplFunction(cldipoint3d_t*, cldigfunc3d_t, const cldidomain_t*, cldipoint3d_t*, cldipoint3d_t*);
// 3-Dimensional Shape (collection of points)
typedef struct _CLDISHAPE3D
{
	cldimemref points;
	size_t     len;
	bool      _composite;
} cldishape3d_t;
// 3-Dimensional Graph (collection of shapes)
typedef struct _CLDIGRAPH3D
{
	cldimemref shapes;
	size_t     len;
} cldigraph3d_t;



#ifdef __cplusplus
}
#endif

#endif // _cldi_head__math_SHAPES3D_H
