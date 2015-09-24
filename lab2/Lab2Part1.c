/* 
 * File:   Lab2part1.c
 * Author: Shizhang Yin (shizhang.yin@mail.utoronto.ca)
 * Date: September 22, 2015
 * Course: APS105
 * 
 * Summary of File:
 * 
 * This is a program that calculates pobability of having hard attck. It collects
 * user inputs of age, doctor estimate, and BNTP value.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) 
{
    static const double DOC_EST = 1.5;
    static const int PATIENT_AGE = 10;
    static const double BNTP_DIV = 125.0;
    static const int BNTP_MUL = 20;
    
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
    
    hfProbability = (doctorEstimate/DOC_EST) + (patientAge/PATIENT_AGE) + (bntpValue/BNTP_DIV) * BNTP_MUL; // Calculation of the probability
    printf("Computed likelihood of heart failure is %.1f%%",hfProbability); // Output answer
    
    return (EXIT_SUCCESS);
}

