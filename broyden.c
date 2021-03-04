#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// sign of floating point number
#define sign(x) (x >= 0.0 ? 1.0 : -1.0)

/*
 * Invert 2 x 2 matrix A.
 */
void mat2_inverse(double *A)
{
	double a, b, c, d;
	a = A[0];
	b = A[1];
	c = A[2];
	d = A[3];

	A[0] = d / (a * d - b * c);
	A[1] = -b / (a * d - b * c);
	A[2] = -c / (a * d - b * c);
	A[3] = a / (a * d - b * c);
}

// Broyden maximum iterations
#define BMAXIT 10000
// Broyden epsilon
#define BEPSILON 1.0e-15

// functions for Broyden
#define f1(x1, x2) (exp(-(x1) * (x1) - (x2) * (x2)) - 1.0 / 8.0)
#define f2(x1, x2) (sin(x1) - cos(x2))

// Jacobian for functions f1 and f2
#define Jf(x1, x2) {										\
		-2.0 * (x1) * exp(-(x1) * (x1) - (x2) * (x2)),		\
			-2.0 * (x2) * exp(-(x1) * (x1) - (x2) * (x2)),	\
			cos(x1) - cos(x2),								\
			sin(x1) + sin(x2)								\
			}

/*
 * Solves root vector of f1(x1, x2) = f2(x1, x2) = 0
 * for initial guess vector x_init of size 2.
 * Allocates and returns root vector of size 2.
 */
double *broyden(double *x_init)
{
	double *root = malloc(sizeof(double) * 2);
	root[0] = x_init[0];
	root[1] = x_init[1];

	double B[4] = Jf(x_init[0], x_init[1]); // Jacobian
	mat2_inverse(&B[0]); // inverse Jacobian

	for (int i = 0; i < BMAXIT; ++i) {
		double f1r = f1(root[0], root[1]); // f_(i-1)
		double f2r = f2(root[0], root[1]);

		// new values of x
		double x1 = root[0] - B[0] * f1r - B[1] * f2r; // x - B f
		double x2 = root[1] - B[2] * f1r - B[3] * f2r;

		double s1 = x1 - root[0]; // x_i - x_(i-1)
		double s2 = x2 - root[1];
		
		double y1 = f1(x1, x2) - f1r;
		double y2 = f2(x1, x2) - f2r;

		// s^T B
		double sTB1 = s1 * B[0] + s2 * B[2];
		double sTB2 = s1 * B[1] + s2 * B[3];
		
		// s^T B y = s1 a y1 + s1 b y2 + s2 c y1 + s2 d y2
		double dot = sTB1 * y1 + sTB2 * y2;

		if (dot < BEPSILON)
			break;

		// s - B y
		double d1 = s1 - (B[0] * y1 + B[1] * y2);
		double d2 = s2 - (B[2] * y1 + B[3] * y2);

		// update B = ((a, b), (c, d))
		B[0] += d1 * sTB1 / dot;
		B[1] += d1 * sTB2 / dot;
		B[2] += d2 * sTB1 / dot;
		B[3] += d2 * sTB2 / dot;

		// update x
		root[0] = x1;
		root[1] = x2;
	}

	return root;
}
