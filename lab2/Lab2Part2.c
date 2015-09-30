/* 
 * File:   Lab2part2.c
 * Author: Shizhang Yin (shizhang.yin@mail.utoronto.ca)
 * Date: September 24, 2015
 * Course: APS105
 * 
 * Summary of File:
 * 
 * This is a program that takes a 4-bits binary input and turn it to a decimal
 * number.(I have made this program to adapt any digits of binary.) 
 */


#include <stdio.h>
#include <stdlib.h>

int main(void) 
{
    int decValue = 0;
    int inputBits;
    int bitDig[4] = {0}; // declare array for the input(can be changed)
    int i, j, k;
    int modAdd = 0;
    int bitDiglength = ((int) (sizeof (bitDig) / sizeof (bitDig[0]))); // get the length of  the array

    printf("Enter %d-bit binary number: ", bitDiglength);
    scanf("%d", &inputBits);

    for (i = 0; i < (bitDiglength - 1); i++) // put each number into array
    {
        bitDig[i] = (inputBits % (power(10, i + 1))) - modAdd;
        modAdd += bitDig[i];
    }
    bitDig[bitDiglength - 1] = inputBits - modAdd; // put last number into array

    for (j = 0; j < (bitDiglength); j++) // reduce the large # into single digits
    {
        bitDig[j] = bitDig[j] / (power(10, j));
    }

    for (k = 0; k < (bitDiglength); k++) // convert to base 10
    {
        decValue += bitDig[k] * power(2, k);
    }

    printf("%d in base 2 is %d in base 10", inputBits, decValue); // output result
    return (EXIT_SUCCESS);
}

int power(int base, unsigned int exp) // Function that solves powers
{
    int i, result = 1;
    for (i = 0; i < exp; i++)
        result *= base;
    return result;
}