/* 
 * File:   Lab3part1.c
 * Author: yinshizh
 *
 * Created on September 30, 2015, 11:40 AM
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
int main(void) 
{
    double firstNum, secondNum;
    char inputChar;
    printf("Enter first number:");
    scanf("%lf", &firstNum);
    printf("Enter second number:");
    scanf("%lf", &secondNum);
    printf("Enter calculation command (one of a, s, m, or d):");
    scanf(" %c", &inputChar);
    if (inputChar == 'a')
        printf("Sum of %.2f and %.2f is %.2f", firstNum, secondNum, firstNum + secondNum);
    else if (inputChar == 's')
        printf("Difference of %.2f and %.2f is %.2f", firstNum, secondNum, firstNum - secondNum);
    else if (inputChar == 'm')
        printf("Product of %.2f and %.2f is %.2f", firstNum, secondNum, firstNum * secondNum);
    else if (inputChar == 'd') 
    {
        if (secondNum != 0)
            printf("Product of %.2f and %.2f is %.2f", firstNum, secondNum, firstNum / secondNum);
        else
            printf("Error, trying to divide by zero");
    } else
        printf("Error, unknown calculation command given");
    return (EXIT_SUCCESS);
}

