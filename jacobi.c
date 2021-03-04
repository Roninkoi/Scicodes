#include <stdlib.h>
#include <stdio.h>
#include <math.h>
 
// sign of floating point number
#define sign(x) (x >= 0.0 ? 1.0 : -1.0)
 
// random floating point number
#define randf() (((double) rand() / (double) RAND_MAX - 0.5) * 2.0)
 
/*
 * Construct diagonal n x n matrix a with value d.
 */
void constructDiag(double *a, int n, double d)
{
    for (int ij = 0; ij < n * n; ++ij) // go through entire matrix
        a[ij] = (double) (ij % n == ij / n) * d; // and check if at diagonal
}
 
/*
 * Construct n x n Givens rotation matrix Qpq with row p and column q.
 * Diagonal value c (cos) and off-diagonal value s (sin).
 */
void constructQpq(double *Qpq, int n, int p, int q, double c, double s)
{
    constructDiag(Qpq, n, 1.0); // identity matrix
 
    Qpq[p * n + p] = c;
    Qpq[q * n + q] = c;
    Qpq[p * n + q] = -s;
    Qpq[q * n + p] = s;
}
 
/*
 * Computes value of n x n matrix expression Qpq^T B Qpq and places it into B.
 */
void computeQTBQ(double *Qpq, double *B, int n)
{
    double *Bn = (double *) malloc(n * n * sizeof(double));
 
    for (int i = 0; i < n; ++i) { // Bn = Qpq^T B
        for (int j = 0; j < n; ++j) {
            Bn[i * n + j] = 0.0;
            for (int k = 0; k < n; ++k)
                Bn[i * n + j] += Qpq[k * n + i] * B[k * n + j];
        }
    }
    
    for (int i = 0; i < n; ++i) { // B = Bn Qpq
        for (int j = 0; j < n; ++j) {
            B[i * n + j] = 0.0;
            for (int k = 0; k < n; ++k)
                B[i * n + j] += Bn[i * n + k] * Qpq[k * n + j];
        }
    }
    
    free(Bn);
}
 
#define MAXIT 10000 // maximum iterations
#define EPSILON 0.001 // maximum residual
 
/*
 * Solve eigenvalues of n x n matrix Q using Jacobi method.
 */
void jacobi(double *Q, int n)
{
    double *B = (double *) malloc(n * n * sizeof(double));
    double *Qpq = (double *) malloc(n * n * sizeof(double));
 
    for (int ij = 0; ij < n * n; ++ij) // initial value of b
        B[ij] = Q[ij];
 
    double res; // residual
    
    for (int i = 0; i < MAXIT; ++i) {
        for (int p = 0; p < n - 1; ++p) { // row
            for (int q = p + 1; q < n; ++q) { // column
                double appqq = Q[p * n + p] - Q[q * n + q];
                double apq = Q[p * n + q];
 
                if (appqq * appqq + 4.0 * apq * apq <= 0.0) {// NaN
                    printf("Jacobi error: Bad matrix!\n");
                    continue;
                }
                
                double C = appqq / sqrt(appqq * appqq + 4.0 * apq * apq);
                
                double c = sqrt((1.0 + C) / 2.0); // cos
                double s = sign(apq) * sqrt((1.0 - C) / 2.0); // sin
 
                constructQpq(Qpq, n, p, q, c, s); // construct rotation matrix
 
                computeQTBQ(Qpq, B, n); // get new value of B
            }
        }
 
        res = 0.0;
        for (int ij = 0; ij < n * n; ++ij) { // next iteration value of Q
            res += fabs(Q[ij] - B[ij]); // accumulate residual
            
            Q[ij] = B[ij];
        }
 
        if (res < EPSILON) // if converged, stop iterating
            break;
    }
 
    if (res >= EPSILON)
        printf("Jacobi error: Didn't converge!\n");
    
    free(Qpq);
    free(B);
}
