#include <stdlib.h>
#include "main.h"
#include "metod_2.h"

static int n;
static double a;
static double b;

static double *x = NULL;
static double *f_x = NULL;
static double *c = NULL;
static double *d = NULL;

void Coeff_2(int n, double *x, double *f_x, double *c, double *d);
double Value_2(double t, int n, double *c, double *x);

int Init_2(int n_, double a_, double b_)
{
	n = n_;
	a = a_;
	b = b_;

	x = (double*)malloc(n * sizeof(double));
	f_x = (double*)malloc(n * sizeof(double));
	c = (double*)malloc(4 * (n - 1) * sizeof(double));
	d = (double*)malloc(n * sizeof(double));

	if (!(x && f_x && c && d)) return 0;

	return 1;
}

void Finalize_2(void)
{
	if (x) free(x); x = NULL;
	if (f_x) free(f_x); f_x = NULL;
	if (c) free(c); c = NULL;
	if (d) free(d); d = NULL;
}

void Input1_2(double *x1, double *f_x1,double * d1)
{
    for(int i = 0; i < n; i++)
    {
        x[i] = x1[i];
        f_x[i] = f_x1[i];
        d[i] = d1[i];
    }
}
void Input_2(void)
{
	int i;
	double h;

	h = (b - a)/(n - 1);
	for (i = 0; i < n; i++)
	{
		x[i] = a + i * h;
		f_x[i] = f(x[i]);
	}
    for (i = 1; i < n - 1; i++)
        d[i] = f_first(x[i]);

    d[0] = f_first(x[0]);
    d[n - 1] = f_first(x[n - 1]);
}

void Delta_2(void)
{
    f_x[n/2] += 0.1;
}

void Calc_2(void)
{
    Coeff_2(n, x, f_x, c, d);
}

double f_2(double t)
{
    return Value_2(t, n, c, x);
}
