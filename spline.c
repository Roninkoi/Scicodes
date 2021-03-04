#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*
 * Does cubic spline interpolation for n points (x, y) with
 * the boundary condition bc at x0 and xn. Returns coeffients z.
 */
void cubic_spline(double *x, double *y, double bc, int n, double *z)
{
	double *h = malloc(sizeof(double) * n);
	double *b = malloc(sizeof(double) * n);
	
	double *u = malloc(sizeof(double) * n);
	double *v = malloc(sizeof(double) * n);
	
	 // solve system of equations
	for (int i = 0; i < n - 1; ++i) {
		h[i] = x[i+1] - x[i];
		b[i] = (y[i+1] - y[i]) / h[i];
	}

	u[1] = 2.0 * (h[1] + h[0]);
	v[1] = 6.0 * (b[1] - b[0]);

	for (int i = 2; i < n - 1; ++i) {
		u[i] = 2.0 * (h[i] + h[i-1]) - h[i-1] * h[i-1] / u[i-1];
		v[i] = 6.0 * (b[i] - b[i-1]) - h[i-1] * v[i-1] / u[i-1];
	}

	z[0] = bc; // set boundary conditions
	z[n-1] = bc;

	for (int i = n - 2; i >= 1; --i) {
		z[i] = (v[i] - h[i] * z[i+1]) / u[i]; // calculate coefficients
	}

	free(h);
	free(b);
	
	free(u);
	free(v);
}

/*
 * Evaluates cubic spline interpolation for n points (xi, yi) at x
 * using coefficients z.
 */
double cubic_spline_eval(double *xi, double *yi, double x, double *z, int n)
{
	int i = n - 1;
	for (; i >= 0; --i) { // search for point
		if (xi[i] <= x)
			break;
	}

	double h = xi[i+1] - xi[i]; // coeffs
	double b = -h * z[i+1] / 6.0 - 
		h * z[i] / 3.0 + (yi[i+1] - yi[i]) / h;

	double xd = x - xi[i]; // x diff

	return yi[i] + xd * (b + xd * (z[i] / 2.0 +
							   xd * (z[i+1]-z[i]) / (6.0 * h)));
}
