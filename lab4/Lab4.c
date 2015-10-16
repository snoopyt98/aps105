#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const CONST_E=2.71828182845904524;
double gaussFunc(double x, double spread);

int main(void)
{
    double spreadNum, limitA, limitB, midX, outResult=0;
    int inputN, i;
    do
    {
        printf("Enter the spread value (must be >0): ");
        scanf("%lf",&spreadNum);
    }
    while(spreadNum<=0);
    do
    {
        do
        printf("Please enter the number of rectangles (n): ");
        scanf("%d", &inputN);  
        if(inputN<1)
        {
            printf("exit.");
            return 0;
        }
        printf("Enter the interval of integration (a b): ");
        scanf("%lf %lf", &limitA, &limitB);
        midX=limitA;
        for(i=0;i<inputN;i++)
        {
            midX=((limitB-limitA)/inputN)+midX;
            outResult=outResult+gaussFunc(midX,spreadNum)*((limitB-limitA)/inputN);
        }
        printf("Integral of Gaussian with spread %.3f on [%.3f, %.3f] with n = %d is: %.3f\n", spreadNum, limitA, limitB, inputN, outResult);
        outResult=0;
    }
    while(true);
}

double gaussFunc(double x, double spread)
{
    double outArea;
    outArea=pow(CONST_E, -(x*x)/spread);
    return outArea;
}
