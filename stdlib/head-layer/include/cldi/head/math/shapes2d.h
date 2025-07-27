
#ifndef _cldi_head__math_SHAPES2D_H
#define _cldi_head__math_SHAPES2D_H 1

/* Subheader of head/math.h */
#ifndef _cldi_head__math_DOMAIN_H
#	include "domain.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif



/* 2-Dimensional point */
typedef struct _CLDITENSOR2D
{
	cldifpm_t x, y;
} cldipoint2d_t, clditensor2d_t;
/* 2-Dimension Point Function */
cldiTemplFunction(
	/* Return Type           */ cldipoint2d_t*, // This should be referencing the \
	.                                              same object that was passed as \
	.                                              Argument 2.
	/* Name of Function Type */ cldigfunc2d_t,
	// Arguments:
		const cldidomain_t*, /*  Argument 1: The domain to run with that will
		.                                    supply the arguments for any given
		.                                    iteration. */
		cldipoint2d_t*, /*       Argument 2: The tensor object to use as an output
		.                                    object for. */
		cldipoint2d_t* /*        Argument 3: The tensor object to use as an output
		.                                    template for any generated mirrored
		.                                    version of the returned point. */
);
/* 2-Dimensional Shape (collection of points) */
typedef struct _CLDISHAPE2D
{
	cldimemref points;
	size_t     len;
	bool      _composite;
} cldishape2d_t;
/* 2-Dimensional Graph (collection of shapes) */
typedef struct _CLDIGRAPH2D
{
	cldimemref shapes;
	size_t     len;
} cldigraph2d_t;

/* Built-in Shape Functions */
// If the address returns is equal to the reference passed in for the first
// point, than only one point was returned, else, if the return value is equal
// the second point reference that was passed in, the function modified both
// objects, and two points, one being a "mirrored" version of the other, were
// returned.
cldipoint2d_t* cldiLine(const cldidomain_t*, cldipoint2d_t*, cldipoint2d_t*);
cldipoint2d_t* cldiCircle(const cldidomain_t*, cldipoint2d_t*, cldipoint2d_t*);
cldipoint2d_t* cldiEllipse(const cldidomain_t*, cldipoint2d_t*, cldipoint2d_t*);
cldipoint2d_t* cldiParabola(const cldidomain_t*, cldipoint2d_t*, cldipoint2d_t*);
cldipoint2d_t* cldiSquare(const cldidomain_t*, cldipoint2d_t*, cldipoint2d_t*);
cldipoint2d_t* cldiRect(const cldidomain_t*, cldipoint2d_t*, cldipoint2d_t*);
cldipoint2d_t* cldiPolygon(const cldidomain_t*, cldipoint2d_t*, cldipoint2d_t*);

/* Domain Template Functions */
cldidomain_t* cldiLineDomain(cldidomain_t*, cldifpm_t slope);
cldidomain_t* cldiLineDomainPos(cldidomain_t*, cldifpm_t slope, cldifpm_t posx, cldifpm_t posy);
cldidomain_t* cldiCircleDomain(cldidomain_t*, cldifpm_t size);
cldidomain_t* cldiCircleDomainPos(cldidomain_t*, cldifpm_t size, cldifpm_t posx, cldifpm_t posy);
cldidomain_t* cldiEllipseDomain(cldidomain_t*, cldifpm_t height, cldifpm_t width);
cldidomain_t* cldiEllipseDomainPos(cldidomain_t*, cldifpm_t height, cldifpm_t width, cldifpm_t posx, cldifpm_t posy);
cldidomain_t* cldiParabolaDomain(cldidomain_t*, cldifpm_t height, cldifpm_t width);
cldidomain_t* cldiParabolaDomainPos(cldidomain_t*, cldifpm_t height, cldifpm_t width, cldifpm_t posy);
cldidomain_t* cldiSquareDomain(cldidomain_t*, cldifpm_t size);
cldidomain_t* cldiSquareDomainPos(cldidomain_t*, cldifpm_t size, cldifpm_t posx, cldifpm_t posy);
cldidomain_t* cldiRectDomain(cldidomain_t*, cldifpm_t height, cldifpm_t width);
cldidomain_t* cldiRectDomainPos(cldidomain_t*, cldifpm_t height, cldifpm_t width, cldifpm_t posx, cldifpm_t posy);
cldidomain_t* cldiPolygonDomain(cldidomain_t*, cldifpm_t size, cldifpm_t sides);
cldidomain_t* cldiPolygonDomainPos(cldidomain_t*, cldifpm_t size, cldifpm_t sides, cldifpm_t posx, cldifpm_t posy);

/* Methods associated with 2D Shape objects: */

CLDISTAT cldiInitShape2D(cldishape2d_t *self);
CLDISTAT cldiInitShape2DFunc(cldishape2d_t *self, cldidomain_t *domain, cldigfunc2d_t func);
CLDISTAT cldiInitShape2DPoints(cldishape2d_t *self, size_t n, cldipoint2d_t *points);
CLDISTAT cldiInitShape2DCopy(cldishape2d_t *self, const cldishape2d_t *copy_of);
CLDISTAT cldiInitShape2DBorrowed(cldishape2d_t *self, const cldishape2d_t *borrow);

CLDISTAT cldiRefactorShape2D(cldishape2d_t *self);
CLDISTAT cldiRefactorShape2DFunc(cldishape2d_t *self, cldidomain_t *domain, cldigfunc2d_t func);
CLDISTAT cldiRefactorShape2DPoints(cldishape2d_t *self, size_t n, cldipoint2d_t *points);
CLDISTAT cldiRefactorShape2DCopy(cldishape2d_t *self, const cldishape2d_t *copy_of);
CLDISTAT cldiRefactorShape2DBorrowed(cldishape2d_t *self, const cldishape2d_t *borrow);

cldishape2d_t cldiMakeShape2D();
cldishape2d_t cldiMakeShape2DFunc(cldidomain_t *domain, cldigfunc2d_t func);
cldishape2d_t cldiMakeShape2DPoints(size_t n, cldipoint2d_t *points);
cldishape2d_t cldiMakeShape2DCopy(const cldishape2d_t *copy_of);
cldishape2d_t cldiMakeShape2DBorrowed(const cldishape2d_t *borrow);

cldimemref cldiNewShape2D();
cldimemref cldiNewShape2DFunc(cldidomain_t *domain, cldigfunc2d_t func);
cldimemref cldiNewShape2DPoints(size_t n, cldipoint2d_t *points);
cldimemref cldiNewShape2DCopy(const cldishape2d_t *copy_of);
cldimemref cldiNewShape2DBorrowed(const cldishape2d_t *borrow);

CLDISTAT cldiShape2DDropBlock(cldimemref *drop);
CLDISTAT cldiDropShape2D(cldishape2d_t *drop);

CLDISTAT cldiShape2DAddPoint(cldishape2d_t *self, cldipoint2d_t point);
CLDISTAT cldiShape2DAddPoints(cldishape2d_t *self, size_t n, cldipoint2d_t *points);
CLDISTAT cldiShape2DAddPointBeg(cldishape2d_t *self, cldipoint2d_t point);
CLDISTAT cldiShape2DAddPointsBeg(cldishape2d_t *self, size_t n, cldipoint2d_t *points);
CLDISTAT cldiShape2DAddPointAt(cldishape2d_t *self, ssize_t idx, cldipoint2d_t point);
CLDISTAT cldiShape2DAddPointsAt(cldishape2d_t *self, ssize_t idx, size_t n, cldipoint2d_t *points);
CLDISTAT cldiShape2DRemovePoint(cldishape2d_t *self, ssize_t idx);
CLDISTAT cldiShape2DRemovePoints(cldishape2d_t *self, ssize_t start_at, size_t amount_to_remove);
CLDISTAT cldiShape2DClearAll(cldishape2d_t *self);



#ifdef __cplusplus
}
#endif

#endif // _cldi_head__math_SHAPES2D_H
