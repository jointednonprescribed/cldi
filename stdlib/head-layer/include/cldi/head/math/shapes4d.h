
#ifndef _cldi_head__math_SHAPES4D_H
#define _cldi_head__math_SHAPES4D_H 1

/* Subheader of head/math.h */
#ifndef _cldi_head__MATH_H
#	include "../math.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif



// 4-Dimensional point
typedef struct _CLDITENSOR4D
{
	cldifpm_t w, x, y, z;
} cldipoint4d_t, clditensor4d_t;
// 4-Dimension Point Function
cldiTemplFunction(cldipoint4d_t*, cldigfunc4d_t, const cldidomain_t*, cldipoint4d_t*, cldipoint4d_t*);
// 4-Dimensional Shape (collection of points)
typedef struct _CLDISHAPE4D
{
	cldimemref points;
	size_t     len;
	bool      _composite;
} cldishape4d_t;
// 4-Dimensional Graph (collection of shapes)
typedef struct _CLDIGRAPH4D
{
	cldimemref shapes;
	size_t     len;
} cldigraph4d_t;



#ifdef __cplusplus
}
#endif

#endif // _cldi_head__math_SHAPES4D_H
