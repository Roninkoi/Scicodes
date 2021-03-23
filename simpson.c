#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*
 * Simpson's rule for numerical integration of interval [a, b]
 */
double simpson1(double (*f)(double), double a, double b)
{
	return (b - a) / 6. *
		((*f)(a) +
		 4. * (*f)((a + b) / 2.) +
		 (*f)(b)
		 );
}

/*
 * Simpson's rule for numerical integration of subdivided intervals
 * [a, c] and [c, b]
 */
double simpson2(double (*f)(double), double a, double b)
{
	return (b - a) / 12. *
		((*f)(a) +
		 4. * (*f)((3. * a + b) / 4.) +
		 2. * (*f)((a + b) / 2.) +
		 4. * (*f)((a + 3. * b) / 4.) +
		 (*f)(b)
		 );
}

// maximum splitting level
#define SIMPSON_MAX 20

/*
 * Recursive Simpson's method. Current recursion depth is rd.
 */
double rsimpson(double (*f)(double), double a, double b, double tol, int rd)
{
	double s1 = simpson1(f, a, b); // one Simpson's rule
	double s2 = simpson2(f, a, b); // two Simpson's rules

	if (rd >= SIMPSON_MAX) // max level reached?
		return s2;

	if (fabs(s2 - s1) < 15. * tol) // tolerance reached?
		return s2 + (s2 - s1) / 15.;

	// left division
	double left = rsimpson(f, a, (a + b) / 2., tol / 2., rd + 1);
	// right division
	double right = rsimpson(f, (a + b) / 2., b, tol / 2., rd + 1);

	return left + right;
}

/*
 * Adaptive Simpson's method integration of function f
 * in range [a, b]. Splitting is done up to tolerance tol.
 */
double simpson(double (*f)(double), double a, double b, double tol)
{
	return rsimpson(f, a, b, tol, 0);
}
