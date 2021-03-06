/*
 * Solve equation A x = b using guess x = g
 */
void GaussSeidel(mat *a, mat *b, mat *g, int maxIt, double epsilon)
{
	int n = a->r;

	double delta = 0.0;

	int conv = 0;

	for (int k = 0; k < maxIt; ++k) {
		delta = 0.0;

		for (int i = 0; i < n; ++i) {
			double x = 1.0 / a->m[i][i];

			double s0 = 0.0;

			for (int j = a->rmin[i]; j <= i - 1; ++j) {
				s0 += a->m[i][j] * g->m[j][0];
			}

			double s1 = 0.0;

			for (int j = i + 1; j <= a->rmax[i]; ++j) {
				s1 += a->m[i][j] * g->m[j][0];
			}

			x *= (b->m[i][0] - s0 - s1);

			if (x != x) {
				return;
			}

			double d = fabs(g->m[i][0] - x);

			if (d > epsilon)
				delta = d;

			g->m[i][0] = x;
		}

		if (fabs(delta) < epsilon) { // has converged
			conv = 1;

			break;
		}
	}
}
