/* 
 * File:   Lab1.c
 * Author: Shizhang Yin (shizhang.yin@mail.utoronto.ca)
 * Date: September 17, 2015
 * Course: APS105
 * 
 * Summary of File:
 * 
 *  This file contains code which ask for two user input numbers. It calculates
 *  sum, difference and division of two numbers. Also, the program output the 
 *  two squares of the two input numbers.
 */

#include <stdio.h>// Include standard input/output header 
#include <stdlib.h>// Include standard library header

int main(void) // Main function with a integer return and no input
{
    int inputNumber1; //Declare variable inputNumber1 and inputNumber2
    int inputNumber2; 
    
    printf("Enter First Number: ");
    scanf("%d",&inputNumber1);
    printf("Enter Second Number: ");
    scanf("%d",&inputNumber2); // Get input from user
    // All calculations are within prinf() function because they are simple
    printf("Sum: %d\n",inputNumber1+inputNumber2); // Print result of calculations
    printf("Difference: %d\n",inputNumber1-inputNumber2);
    printf("Square of Number 1: %d\n",inputNumber1*inputNumber1);
    printf("Square of Number 2: %d\n",inputNumber2*inputNumber2);
    printf("Division: %d\n",inputNumber2/inputNumber1);
    
    return (EXIT_SUCCESS); // Executed successfully
}

