/* 
 * File:   Lab3part1.c
 * Author: yinshizh
 *
 * Created on September 30, 2015, 11:40 AM
 */

#include <stdio.h>
#include <stdlib.h>


int main(void) 
{
    double firstNum, secondNum;
    char inputChar; // Declare variables
    
    printf("Enter first number: "); // Ask for input numbers
    scanf("%lf", &firstNum);
    printf("Enter second number: ");
    scanf("%lf", &secondNum);
    printf("Enter calculation command (one of a, s, m, or d): "); // Ask for inputmode
    scanf(" %c", &inputChar); 
    
    if (inputChar == 'a') // Addition case
        printf("Sum of %.2f and %.2f is %.2f", firstNum, secondNum, firstNum + secondNum);
    else if (inputChar == 's') // Subtraction case
        printf("Difference of %.2f from %.2f is %.2f", firstNum, secondNum, firstNum - secondNum);
    else if (inputChar == 'm') // Multiplication case
        printf("Product of %.2f and %.2f is %.2f", firstNum, secondNum, firstNum * secondNum);
    else if (inputChar == 'd') // Division case
    {
        if (secondNum != 0) // The case  where denominator not equals to zero  
            printf("Division of %.2f by %.2f is %.2f", firstNum, secondNum, firstNum / secondNum);
        else // The case where denominator equals to zero
            printf("Error, trying to divide by zero");
    } else // The case where the input is unknown
        printf("Error, unknown calculation command given");
    return (EXIT_SUCCESS);
}

