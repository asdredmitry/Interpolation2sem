#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define h 0.00000001
double func(double x)
{
    return fabs(sin(x));
}
double funcFirst(double x)
{
    return 0.5 * (func(x + h) - func(x - h))/h;
}
int main()
{
    int n;
    scanf("%i",&n);
    FILE * file = fopen("data.dat","w");
    if(!file)
        return 0;
    double begin,end;
    scanf("%lf %lf",&begin,&end);
    fprintf(file,"%i \n",n);
    for(double i = begin; i <= end; i += (end - begin)/(n - 1))
    {
        fprintf(file,"%f %f %f \n",i,func(i),funcFirst(i));
    }
}
