


/* Implementing: cldi-head: math/shapes2d.h */
#include <cldi/head/math/shapes2d.h>



const char CLDIERRMSG_GFUNC_NULL_POINT_AND_DOMAIN[] =
	"Arguments `domain` and `point` must not be null or 0.";
const char CLDIERRMSG_GFUNC_MISSING_XPARAM[] =
	"Missing `x` parameter inside of supplied domain.";



cldipoint2d_t* cldiLine(const cldidomain_t *domain, cldipoint2d_t* point, cldipoint2d_t* mirror)
{
	if (domain == NULL || point == NULL)
		return NULL;

	cldifpm_t x = cldiDomainGetXDefault(domain, 0.0);
	point->x = x;
	// y = ax + b
	point->y = (cldiDomainGetADefault(domain, 1.0) * x) + cldiDomainGetBDefault(domain, 0.0);

	return point;
}
cldipoint2d_t* cldiCircle(const cldidomain_t *domain, cldipoint2d_t* point, cldipoint2d_t* mirror)
{
	if (domain == NULL || point == NULL)
		return NULL;

	const cldifpm_t
		x = cldiDomainGetXDefault(domain, 0.0),
		c = cldiDomainGetCDefault(domain, 1.0),
		b     = cldiDomainGetBDefault(domain, 0.0),
		// Let a = h, b = k, and c = r
		// (x - a)^2 + (y - b)^2 = c^2
		// (y - b)^2 = c^2 - (x - a)^2
		xma   = x - cldiDomainGetADefault(domain, 0.0),
		S     = (c*c) - (xma*xma),
		sqrtS = cldifpmsqrt(S);

	point-> x = x;
	mirror->x = x;
	// reverse (y - b)^2:
	// Where S = c^2 - (x - a)^2,
	// y = sqrt(S) + b
	point-> y = sqrtS + b;
	mirror->y = sqrtS - b;

	return mirror;
}
cldipoint2d_t* cldiEllipse(const cldidomain_t *domain, cldipoint2d_t *point, cldipoint2d_t* mirror)
{
	if (domain == NULL || point == NULL)
		return NULL;

	
}
cldipoint2d_t* cldiParabola(const cldidomain_t *domain, cldipoint2d_t *point, cldipoint2d_t* mirror)
{
	if (domain == NULL || point == NULL)
		return NULL;

	const cldifpm_t
		x = cldiDomainGetDefaultX(domain, 0.0),
		// y = x^2 + a
		y = (x*x) + cldiDomainGetADefault(domain, 0.0);

	point-> x = x;
	mirror->x = x;
	point-> y = y;
	mirror->y = y;

	return mirror;
}



