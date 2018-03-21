#include <math.h>
#include "main.h"
#include "metod_1.h"
void Coeff_1(int n, double *x, double *f_x, double *c);
double Value_1(double t, int n, double *c, double *x);
void Coeff_1(int n, double *x, double *f_x, double *c)
{
	int i, j;

    for (i = 0; i < n - 3; i++)
        c[i * (3 + 1)] = f_x[i];

    for (i = 0; i < 3 + 1; i++)
        c[(n - 3 - 1) * (3 + 1) + i] = f_x[i + n - 3 - 1];

    for (i = 1; i < 3 + 1; i++)
        for (j = 3; j > i - 1; j--)
            c[(n - 3 - 1) * (3 + 1) + j] =
(c[(n - 3 - 1) * (3 + 1) + j] - c[(n - 3 - 1) * (3 + 1) + j - 1]) / (x[n - 3 + j - 1] - x[n - 3 - 1 + j - i]);

    for (i = 1; i < 3 + 1; i++)
        for (j = 0; j < n - 3 - 1; j++)
            c[j * (3 + 1) + i] = (c[(j + 1) * (3 + 1) + i - 1] - c[j * (3 + 1) + i - 1]) / (x[j + i] - x[j]);
}

double Value_1(double t, int n, double *c, double *x)
{
	int i, j;
	double fx;

	for (i = 0; i < n - 2; i++)
		if (t <= x[i + 1]) break;

    if (i > n - 3 - 1) i = n - 3 - 1;

    fx = c[i * (3 + 1) + 3];

    for (j = 3 - 1; j >= 0; j--)
	{
		fx *= (t - x[i + j]);
        fx += c[i * (3 + 1) + j];
	}

	return fx;
}
