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
