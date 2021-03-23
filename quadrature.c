#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <complex.h>

/*
 * Calculates roots of nth degree real polynomial p using
 * the eigenvalue method. 
 * Roots returned as a complex array, which is allocated.
 */
complex *eigenroots(int n, double *p)
{
	int n1 = n + 1;
	complex *A = (complex *) calloc(sizeof(complex), n1 * n1);
	for (int ii = 0; ii < n - 1; ++ii)
		A[(ii + 1) + ii * n] = 1.0; // transpose

	for (int i = 0; i < n; ++i) { // assign polynomial coefficients to top row
		A[i * n] = -p[n1 - i - 2] / p[n1 - 1]; // transpose
	}

	complex *roots = (complex *) malloc(sizeof(complex) * n); // eigenvalues
	complex *work = (complex *) malloc(sizeof(complex) * 2 * n);

	char jn = 'N'; // no eigenvectors
	int ok;
	int n2 = 2 * n;
	// use LAPACK to compute complex eigenvalues
	zgeev_(&jn, &jn, &n, A, &n, roots, NULL, &n, NULL, &n, work, &n2, work, &ok);

	free(work);
	free(A);

	return roots;
}

/*
 * Generate next Laguerre polynomial j + 1.
 */
double laguerre(double x, int j)
{
	if (j == 0)
		return 1.;

	if (j == 1)
		return 1. - x;

	return ((2. * j - 1. - x) * laguerre(x, j - 1) - (j - 1.) * laguerre(x, j - 2)
			) / (j);
}

/*
 * Coefficient of x^j term in nth degree Laguerre polynomial
 */
double laguerre_coeff(int j, int n)
{
	double nfjf = 1.; // n! / j!
	for (int i = j + 1; i <= n; ++i) {
		nfjf *= i;
	}
	
	double jf = 1.; // j!
	for (int i = 2; i <= j; ++i)
		jf *= i;
	
	double njf = 1.; // (n - j)!
	for (int i = 2; i <= n - j; ++i)
		njf *= i;

	return (1. - 2. * (j % 2)) * nfjf / jf / njf;
}

/*
 * Gauss-Laguerre quadrature integration of function exp(-x) f(x) in
 * range [0, INFINITY] with number of points n.
 */
double gl_quadrature(double (*f)(double), int n)
{
	double *coeffs = malloc(sizeof(double) * (n + 1));

	// calculate coefficients of nth degree Laguerre polynomial
	for (int i = 0; i <= n; ++i)
		coeffs[i] = laguerre_coeff(i, n);

	complex *x = eigenroots(n, coeffs); // solve n roots of polynomial
	double sum = 0.;
	
	double n1 = n + 1;
	double n12 = n1 * n1;

	for (int i = 0; i < n; ++i) {
		double xi = creal(x[i]); // all roots real
		double ln1 = laguerre(xi, n + 1); // evaluate (n + 1) degree polynomial at xi
		
		double wi = xi / n12 / ln1 / ln1; // weights

		sum += wi * (*f)(xi); // accumulate contributions
	}
	
	free(coeffs);
	free(x);
	
	return sum;
}
