#include <stdio.h>
#include "plot_x11.h"
#include "metod_1.h"
#include "main.h"
#include "metod_2.h"
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <float.h>
const double inf = DBL_MAX - 100;
const double eps = 0.0000000000000000001;
double begin,end,c;
double *x, *f_x, *d;
bool fromFile;
int n;
double accuracy;
double f_file(int i, double t);
#define h 0.00000001
void drawAxes(double left, double right, double up, double down,double height, double width);
/* ������� ��������� ������� */
static int variant = 1;

/* ���������� ���������� ���� */
double f(double x)
{
    return fabs(sin(x));
}
double f_first(double x)
{
	return 0.5 * (f(x + h) - f(x - h))/h;
}
double f_file(int i, double t)
{
    return f_x[i - 1] + t*(f_x[i] - f_x[i - 1]);
}
static void
DrawWindowContent (void)
{
    double up,down;
    char tmp[32];
    int width = nWWidth;		/* ������� ������ ������ */
    int height = nWHeight;	/* ������� ������ ������ */
    double absHeight;
    double absWidth ;
    WSetColor (DARKGRAY);
    WFillRectangle (0, 0, width, height);
    up = -inf;
    down = inf;
    if(fromFile)
    {
        for(int i = 1; i < n - 1; i++)
        {
            if(variant == 1 || variant == 4 || variant == 8 || variant == 9 )
            {
                if(x[i] >= begin && x[i] <= end)
                {
                    double l = f_x[i] - f_x[i - 1];
                    for(double t = 0; t < 1; t += 0.01)
                    {
                        if(up < f_x[i - 1] + t*l)
                            up = f_x[i - 1] + t*l;
                        if(down > f_x[i - 1] + t*l)
                            down = f_x[i - 1] + t*l;
                    }
                }
            }
            if(variant == 5 || variant == 7)
            {
                if(x[i] >= begin && x[i] <= end)
                {
                    double l = f_x[i] - f_x[i - 1];
                    for(double t = 0; t < 1; t += 0.01)
                    {
                        if(down > f_x[i - 1] + t*l - f_1(x[i - 1] + t*(x[i] - x[i - 1])))
                            down = f_x[i - 1] + t*l - f_1(x[i - 1] + t*(x[i] - x[i - 1]));
                        if(up < f_x[i - 1] + t*l - f_1(x[i - 1] + t*(x[i] - x[i - 1])))
                            up = f_x[i - 1] + t*l - f_1(x[i - 1] + t*(x[i] - x[i - 1]));
                    }
                }
            }
            if(variant == 6 || variant == 7)
            {
                if(x[i] >= begin && x[i] <= end)
                {
                    double l = f_x[i] - f_x[i - 1];
                    for(double t = 0; t < 1; t += 0.01)
                    {
                        if(down > f_x[i - 1] + t*l - f_2(x[i - 1] + t*(x[i] - x[i - 1])))
                            down = f_x[i - 1] + t*l - f_2(x[i - 1] + t*(x[i] - x[i - 1]));
                        if(up < f_x[i - 1] + t*l - f_2(x[i - 1] + t*(x[i] - x[i - 1])))
                            up = f_x[i - 1] + t*l - f_2(x[i - 1] + t*(x[i] - x[i - 1]));

                    }
                }
            }
        }
    }
    if(!fromFile)
    {
        for(double i = begin; i < end; i+= accuracy)
        {
            if(variant == 1 || variant == 4 || variant == 8 || variant == 9)
            {
                if(up < f(i))
                    up = f(i);
                if(down > f(i))
                    down = f(i);
            }
            if(variant == 5 || variant == 7 )
            {
                if(down > f(i) - f_1(i))
                    down = f(i) - f_1(i);
                if(up < f(i) - f_1(i))
                    up = f(i) - f_1(i);
            }
            if(variant == 6 || variant == 7 )
            {
                if(down > f(i) - f_2(i))
                    down = f(i) - f_2(i);
                if(up < f(i) - f_2(i))
                    up = f(i) - f_2(i);
            }
        }
    }
    for(double i = begin; i < end; i+= accuracy)
    {
        if(variant == 2 || variant == 4 || variant == 8)
        {
            if(up < f_1(i))
                up = f_1(i);
            if(down > f_1(i))
                down = f_1(i);
        }
        if(variant == 3 || variant == 4 || variant == 9)
        {
            if(down > f_2(i))
                down = f_2(i);
            if(up < f_2(i))
                up = f_2(i);
        }
    }
    printf("%lf up \n" , up);
    absHeight = up - down;
    absWidth = end - begin;
    WSetColor(RED);
    WDrawString("AbsHeight",10,10);
    sprintf(tmp,"%lf",absHeight);
    WDrawString(tmp,10,20);
    drawAxes(begin,end,up, down,height,width);
    if((variant == 1 || variant == 4 || variant == 9 || variant == 8) && !fromFile)
    {
        WSetColor (BLUE);
        for(double i = begin; i < end; i += accuracy)
        {
            WDrawLine(width*fabs(begin - i)/absWidth,height*fabs(f(i) - up)/absHeight,width*fabs(begin - i - accuracy)/absWidth,height*fabs(f(i + accuracy) - up)/absHeight);
        }
    }
    if(variant == 2 || variant == 4 || variant == 8)
    {
         WSetColor (YELLOW);
        for(double i = begin; i < end; i += accuracy)
        {
            WDrawLine(width*fabs(begin - i)/absWidth,height*fabs(f_1(i) - up)/absHeight,width*fabs(begin - i - accuracy)/absWidth,height*fabs(f_1(i + accuracy) - up)/absHeight);
        }
    }
    if(variant == 3 || variant == 4 || variant == 9)
    {
         WSetColor (BLACK);
        for(double i = begin; i < end; i += accuracy)
        {
            WDrawLine(width*fabs(begin - i)/absWidth,height*fabs(f_2(i) - up)/absHeight,width*fabs(begin - i - accuracy)/absWidth,height*fabs(f_2(i + accuracy) - up)/absHeight);
        }
    }
    if((variant == 5 || variant == 7 )&& !fromFile)
    {
        WSetColor(BLUE);
        for(double i = begin; i < end; i += accuracy)
        {
            WDrawLine(width*fabs(begin - i)/absWidth,height*fabs((f(i) - f_1(i)) - up)/absHeight,width*fabs(begin - i - accuracy)/absWidth,height*fabs((f(i + accuracy) - f_1(i + accuracy)) - up)/absHeight);
        }
    }
    if((variant == 6 || variant == 7 )&& !fromFile)
    {
        WSetColor(YELLOW);
        for(double i = begin; i < end; i += accuracy)
        {
            WDrawLine(width*fabs(begin - i)/absWidth,height*fabs((f(i) - f_2(i)) - up)/absHeight,width*fabs(begin - i - accuracy)/absWidth,height*fabs((f(i + accuracy) - f_2(i + accuracy)) - up)/absHeight);
        }
    }
    if((variant == 5 || variant == 7) && fromFile)
    {
        WSetColor(BLUE);
        for(int i =  1; i < n; i ++)
        {
            double delta = x[i] - x[i - 1];
            for(double t = 0; t < 1; t += 0.01)
            {
                if(x[i - 1] >= begin && x[i] <= end)
                    WDrawLine(width*fabs(begin - (x[i - 1] + t*delta))/absWidth,height*fabs((f_file(i,t) - f_1(x[i - 1] + t*delta)) - up)/absHeight,width*fabs(begin - (x[i - 1] + (t + 0.01)*delta))/absWidth,height*fabs((f_file(i,t + 0.01) - f_1(x[i - 1] + (t + 0.01)*delta )) - up)/absHeight);
            }
        }
    }
    if((variant == 6 || variant == 7 )&& fromFile)
    {
        WSetColor(YELLOW);
        for(int i = 1; i < n; i ++)
        {
            double delta = x[i] - x[i - 1];
            for(double t = 0; t < 1; t += 0.01)
            {
                if(x[i - 1] >= begin && x[i] <= end)
                    WDrawLine(width*fabs(begin - (x[i - 1] + t*delta))/absWidth,height*fabs((f_file(i,t) - f_2(x[i - 1] + t*delta)) - up)/absHeight,width*fabs(begin - (x[i - 1] + (t + 0.01)*delta))/absWidth,height*fabs((f_file(i,t + 0.01) - f_2(x[i - 1] + (t + 0.01)*delta )) - up)/absHeight);
            }
        }
    }
    if((variant == 1 || variant == 4 || variant == 8 || variant == 9) && fromFile)
    {
        WSetColor (BLUE);
        for(int i = 1; i < n; i ++)
        {
            double delta = x[i] - x[i - 1];
            for(double t = 0; t < 1; t += 0.01)
            {
                if(x[i - 1] >= begin && x[i] <= end)
                    WDrawLine(width*fabs(begin - (x[i - 1] + t*delta))/absWidth,height*fabs(f_file(i,t) - up)/absHeight,width*fabs(begin - (x[i - 1] + (t + 0.01)*delta))/absWidth,height*fabs(f_file(i,t + 0.01) - up)/absHeight);
            }
        }
    }

}
void drawAxes(double left, double right, double up, double down,double height, double width)
{
    if(up*down < 0)
    {
        WSetColor(GREEN);
        WDrawLine(0,height*(fabs(up))/(fabs(up) + fabs(down)),width,height*(fabs(up)/(fabs(up) + fabs(down))));
    }
    if(left*right < 0)
    {
        WSetColor(GREEN);
        WDrawLine(width*fabs(left)/(fabs(left)+ fabs(right)),0,width*fabs(left)/(fabs(left) + fabs(right)),height);
    }
}
static int
KeyPressFunction (int nKeySym)
{
    switch (nKeySym)
    {
    case XK_Q:
    case XK_q:
        return KEY_PRESS_QUIT;

    case XK_1:
        variant = 1;
        WSetTitle ("Function");
        break;
    case XK_2:
        variant = 2;
        WSetTitle ("Metod 1");
        break;
    case XK_3:
        variant = 3;
        WSetTitle ("Metod 2");
        break;
    case XK_4:
        variant = 4;
        WSetTitle ("All functions");
        break;
    case XK_5:
        variant = 5;
        WSetTitle("Pogreshnost1");
        break;
    case XK_6:
        variant = 6;
        WSetTitle("Pogreshnost2");
        break;
    case XK_7:
        variant = 7;
        WSetTitle("Pogreshnost");
        break;
    case XK_8:
        variant = 8;
        WSetTitle("First and func");
        break;
    case XK_9:
        variant = 9;
        WSetTitle("Second and func");
        break;
    case XK_F1:
        Delta_1();
        Calc_1();
        break;
    case XK_F2:
        Delta_2();
        Calc_2();
        break;
    case XK_N:
    case XK_n:
        n*=2;
        Finalize_1();
        Finalize_2();
        Init_1(n,begin,end);
        Init_2(n,begin,end);
        Input_1();
        Input_2();
        Calc_1();
        Calc_2();
        break;
    case XK_P:
    case XK_p:
        begin += (end - begin)/10;
        end -= (end - begin)/10;
        break;
    case XK_O:
    case XK_o:
        begin -= (end - begin)/10;
        end += (end - begin)/10;
        break;
    case XK_a:
    case XK_A:
        begin -= 1;
        end -= 1;
        break;
    case XK_d:
    case XK_D:
        begin += 1;
        end += 1;
        break;

    default:
        return KEY_PRESS_NOTHING;
    }
    //up = -inf;
    //down = inf;
    /* ������������ ���� */
    return KEY_PRESS_EXPOSE;
}

int
main (void)
{
    int ret_code;
    char answer;
    FILE * file;
    accuracy = 0.001;  /* ����� �� ����� X11. */
    printf("Do you want to read data from file? \n");
    if(scanf("%c",&answer)!= 1)
        return 0;
    if(answer == 'y' || answer == 'Y')
    {
        fromFile = true;
        file = fopen("data.dat","r");
        if(!file)
        {
            printf("Fail to open file");
            return 0;
        }
        if(fscanf(file,"%i",&n) != 1)
            printf("cannot read from file");

        x = (double*)malloc(n * sizeof(double));
        f_x = (double*)malloc(n * sizeof(double));
        d = (double*)malloc(n * sizeof(double));
        for(int i = 0; i < n; i++)
        {
            if(fscanf(file,"%lf",x + i) != 1)
                printf("cannot read from file");
            if(fscanf(file,"%lf",f_x + i) != 1)
                printf("cannot read from file");
            if(fscanf(file,"%lf",d + i) != 1)
                printf("cannot read from file");
        }
        fclose(file);
        for(int i = 0; i < n; i++)
        {
            if(i == 0)
            {
                begin = x[i];
                end = x[i];
            }
            if(begin > x[i])
                begin = x[i];
            if(end < x[i])
                end = x[i];
        }
        Init_1(n,begin,end);
        Init_2(n,begin,end);
        Input1_1(x,f_x);
        Input1_2(x,f_x,d);
        Calc_1();
        Calc_2();
    }
    else
    {
        fromFile = false;
        n = 10;

        printf("Enter begin, end, n: \n");
        if(scanf("%lf %lf %i",&begin, &end, &n) != 3)
        {
            printf("Error");
            return 0;
        }
        Init_1(n,begin,end);
        Input_1();
        Calc_1();
        Init_2(n,begin,end);
        Input_2();
        Calc_2();
    }
    printf("%lf\n",(end - begin)/accuracy);
    if((end - begin)/accuracy > 1000000)
        accuracy = (end - begin)/1000000;
    ret_code = DrawWindow (DrawWindowContent, KeyPressFunction);
    if (ret_code)
    {
        switch (ret_code)
        {
        case PLOT_X11_ERR_1:
            printf ("%s\n", PLOT_X11_ERR_MSG_1);
            break;
        case PLOT_X11_ERR_2:
            printf ("%s\n", PLOT_X11_ERR_MSG_2);
            break;
        case PLOT_X11_ERR_3:
            printf ("%s\n", PLOT_X11_ERR_MSG_3);
            break;
        case PLOT_X11_ERR_4:
            printf ("%s\n", PLOT_X11_ERR_MSG_4);
            break;
        case PLOT_X11_ERR_5:
            printf ("%s\n", PLOT_X11_ERR_MSG_5);
            break;
        default:
            printf ("%s\n", PLOT_X11_ERR_MSG_DEF);
            break;
        }
        return ret_code;
    }

    return 0;
}
