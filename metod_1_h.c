#include <stdlib.h>
#include "main.h"
#include "metod_1.h"

static int n;
static double a;
static double b;

static double *x = NULL;
static double *f_x = NULL;
static double *c = NULL;

void Coeff_1(int n, double *x, double *f_x, double *c);
double Value_1(double t, int n, double *c, double *x);

int Init_1(int n_, double a_, double b_)
{
	n = n_;
	a = a_;
    b = b_;

	x = (double*)malloc(n * sizeof(double));
	f_x = (double*)malloc(n * sizeof(double));
    c = (double*)malloc((n - 3) * (3 + 1) * sizeof(double));

	if (!(x && f_x && c)) return 0;

	return 1;
}
void Input1_1(double *x1, double *f_x1)
{
    for(int i = 0; i < n; i++)
    {
        x[i] = x1[i];
        f_x[i] = f_x1[i];
    }
}
void Finalize_1(void)
{
	if (x) free(x); x = NULL;
	if (f_x) free(f_x); f_x = NULL;
	if (c) free(c); c = NULL;
}

void Input_1(void)
{
	int i;
	double h;

	h = (b - a)/(n - 1);
	for (i = 0; i < n; i++)
	{
		x[i] = a + i * h;
		f_x[i] = f(x[i]);
	}
}

void Delta_1(void)
{
    f_x[n/2] += 0.1;
}

void Calc_1(void)
{
    Coeff_1(n, x, f_x, c);
}

double f_1(double t)
{
    return Value_1(t, n, c, x);
}
