#include <stdlib.h>
#include <stdio.h>
#include <math.h>
 
// sign of floating point number
#define sign(x) (x >= 0.0 ? 1.0 : -1.0)
 
// function f
#define f(x) (sin(3.0 * M_PI * (x) * (x) * (x) / ((x) * (x) - 1.0)) + 0.5)
// derivative f'
#define fp(x) (cos(3.0 * M_PI * (x) * (x) * (x)) / ((x) * (x) - 1.0) * \
		(9.0 * M_PI * (x) * (x) - 6.0 * M_PI * (x) * (x) * (x) * (x) / \
		 ((x) * (x) - 1.0)) / ((x) * (x) - 1.0))
 
// Bisection method tolerance
#define BISECT_TOL 1.0e-7
// Bisection method maximum iterations
#define BISECT_MAXIT 10000
 
/*
 * Calculates root of equation f(x) using bisection method
 * in the interval [a, b].
 */
double bisect_f(double a, double b)
{
    double c; // solution to f(c) == 0
    double aa = a; // current interval
    double bb = b;
 
    int conv = 0;
    
    for (int i = 0; i < BISECT_MAXIT; ++i) {
        c = (aa + bb) / 2.0; // midpoint of current interval
 
        double fc = f(c);
 
        if (fc == 0.0 || (b - a) / 2.0 < BISECT_TOL) {
            conv = 1; // found root!
            break;
        }
 
        if (sign(fc) == sign(f(aa))) // pick which side to advance
            aa = c;
        else
            bb = c;
    }
 
    if (!conv)
        fprintf(stderr, "Bisect error: Didn't find root!\n");
 
    return c;
}
 
// Newton's method maximum iterations
#define NEWTON_MAXIT 10000
// Newton's method tolerance
#define NEWTON_TOL 1.0e-7
// Newton's method smallest value
#define NEWTON_EPS 1.0e-10
 
/*
 * Calculates root of f(x) using Newton's method
 * based on initial guess x0.
 */
double newton_f(double x0)
{
    double x = x0;
 
    int conv = 0;
    for (int i = 0; i < NEWTON_MAXIT; ++i) {
        double y = f(x);
        double dy = fp(x);
 
        if (fabs(dy) <= NEWTON_EPS) {
            fprintf(stderr, "Newton error: Small f'(x)!\n");
            break;
        }
 
        double x1 = x - y / dy; // advance
 
        if (fabs(x1 - x) <= NEWTON_TOL) {
            conv = 1; // converged
            break;
        }
 
        x = x1; // new value of x
    }
 
    if (!conv)
        fprintf(stderr, "Newton error: Didn't converge!\n");
 
    return x;
}
 
