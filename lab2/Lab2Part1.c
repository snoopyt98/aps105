/* 
 * File:   Lab2part1.c
 * Author: Shizhang Yin
 *
 * Created on September 22, 2015, 11:40 AM
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) 
{
    double patientAge;
    double doctorEstimate;
    int bntpValue;
    double hfProbability; // Declare variables
    printf("Enter patient age: ");
    scanf("%lf",&patientAge);
    printf("Enter doctor %% likelihood guess of heart failure: ");
    scanf("%lf",&doctorEstimate);
    printf("Enter patient BNPT value (between 0 and 1000 pg/ml): ");
    scanf("%d",&bntpValue); // Print questions and ask for information
    hfProbability = (doctorEstimate/1.5) + (patientAge/10) + (bntpValue/125.0) * 20; // Calculation of the probability
    printf("Computed likelihood of heart failure is %.1f%%",hfProbability); // Output answer
    return (EXIT_SUCCESS);
}

