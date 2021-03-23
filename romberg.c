#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*
 * Integrates function f in range [a, b] using Romberg algorithm
 * up to step size (b - a) / 2^n.
 */
double romberg(double (*f)(double), double a, double b, int n)
{
	double *R = malloc(sizeof(double) * n * n);

	double h = (b - a) / 2.; // step size
	int jn = 1;
	
	R[0] = h * ((*f)(a) + (*f)(b)); // first trapezoid
	
	for (int i = 1; i < n; ++i) {
		double sum = 0.;
		for (int j = 0; j < jn; ++j)
			sum += (*f)(a + 2. * j * h); // accumulate values at every step

		R[i * n] = R[(i - 1) * n] / 2. + sum * h; // estimate

		for (int j = 1; j <= i; ++j) // refine estimate using Richardson extrapolation
			R[i * n + j] = R[i * n + j - 1] +
				(R[i * n + j - 1] - R[(i - 1) * n + j - 1]) /
				(pow(4, j) - 1.);
		
		jn *= 2; // double number of trapezoids
		h /= 2.; // halve step size
	}

	double result = R[(n - 1) * n + n - 1]; // last value
	
	free(R);

	return result;
}
