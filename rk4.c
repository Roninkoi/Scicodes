#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// derivative
double f(double t, double y)
{
	return -y;
}

/*
 * One step of fourth-order Runge-Kutta method (RK4) at time t, step size h for
 * derivative y' = f(t, y)
 */
double rk4(double *k1, double *k2, double *k3, double *k4, double (*f)(double, double), double t, double h, double y)
{
	*k1 = f(t, y);
	*k2 = f(t + h / 2., y + *k1 * h / 2.);
	*k3 = f(t + h / 2., y + *k2 * h / 2.);
	*k4 = f(t + h, y + h * (*k3));
	
	return h / 6. * (*k1 + 2. * (*k2) + 2. * (*k3) + *k4);
}

/*
 * Runge-Kutta solver for equation y'' + y = 0 in range [a, b] with N steps
 * and initial conditions y(a) = y0, y'(a) = yp0
 */
double *runge_kutta_solver(double a, double b, int N, double y0, double yp0)
{
	double t = a;
	double h = (b - a) / (double) N; // step size
	double y = y0; // initial y(a)
	double yp = yp0; // y'(a)

	double k1, k2, k3, k4; // slopes

	double *ty = malloc(sizeof(double) * 2 * N); // solution (t, y) values
	
	for (int i = 0; i < N; ++i) {
		yp += rk4(&k1, &k2, &k3, &k4, &f, t, h, y);
		y += yp * h;
		t += h;
		
		ty[2 * i] = t;
		ty[2 * i + 1] = y;
	}

	return ty;
}

