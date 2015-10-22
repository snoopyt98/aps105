/* 
 *  File:   Lab4.c
 *  Author: Shizhang Yin (shizhang.yin@mail.utoronto.ca)
 *  Date: October 22, 2015
 *  Course: APS105
 *     
 *  Summary of File:
 *       
 *  This program uses rectangular to approximate the area under an curve and therefore
 *  calculate the devivative of the graph.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double gaussFunc(double x, double spread);//declare function gaussFunc()

int main(void)
{
    
    double spreadNum, limitA, limitB, midX, outResult=0;//declare variable
    int inputN, i;
    
    do
    {
        printf("Enter the spread value (must be >0): ");//ask for spread value
        scanf("%lf",&spreadNum);
    }
    while(spreadNum<=0);
    
    for(;;)
    {
        printf("Please enter the number of rectangles (n): ");
        scanf("%d", &inputN);  
        
        if(inputN<1)//determine if the input is eligible for calculation)
        {
            printf("exiting.\n");
            return 0;//exit
        }
        
        do
        {
            printf("Enter the interval of integration (a b): ");//ask for the range of a closed integral
            scanf("%lf %lf", &limitA, &limitB);
            if(limitA>limitB)
                printf("Invalid interval!\n");
        }
        
        while(limitA>limitB);
            midX=limitA+((limitB-limitA)/(2*inputN));//find the first midX
        
        for(i=0;i<inputN;i++)
        {
            if(i!=0)
                midX=((limitB-limitA)/(inputN))+midX;//find each midX
            outResult=outResult+gaussFunc(midX,spreadNum)*((limitB-limitA)/inputN);//calculate area and add together
        }
        
        printf("Integral of Gaussian with spread %.3f on [%.3f, %.3f] with n = %d is: %.3f\n", spreadNum, limitA, limitB, inputN, outResult);//print result
        outResult=0;
    }
}

double gaussFunc(double x, double spread)//Find y value of given x
{
    double outY;
    outY=exp(-(x*x)/spread);//calculate y value at given x for the function
    return outY;
}
