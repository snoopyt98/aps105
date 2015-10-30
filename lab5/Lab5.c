/* 
 * File:   Lab5.c
 * Author: Shizhang Yin (shizhang.yin@mail.utoronto.ca)
 * Date: October 22, 2015
 * Course: APS105
 *     
 * Summary of File:
 *       
 * The program ask for a user input DNA pattern, and the program search for a 
 * match in the const() DNA. The program will reported the position of all
 * matches to the user.
 */

#include <stdio.h>
#include <stdlib.h>

void askInput(char *inputPtr);
int findDNA(const char *setDNAPtr, char *patternDNAPtr, int *resultPtr, int n);
int findLength(const char *DNAPtr, char *inputArrPtr, int *inputIntPtr);

const char DNA[] = {'A', 'G', 'C', 'G', 'G', 'G', 'A', 'C', 'C', 'G', 'T', 'C',
    'C', 'C', 'G', 'A', 'C', 'A', 'T', 'T', 'G', 'A', 'T', 'G',
    'A', 'A', 'G', 'G', 'G', 'T', 'C', 'A', 'T', 'A', 'G', 'A',
    'C', 'C', 'C', 'A', 'A', 'T', 'A', 'C', 'G', 'C', 'C', 'A',
    'C', 'C', 'A', 'C', 'C', 'C', 'C', 'A', 'A', 'G', 'T', 'T',
    'T', 'T', 'C', 'C', 'T', 'G', 'T', 'G', 'T', 'C', 'T', 'T',
    'C', 'C', 'A', 'T', 'T', 'G', 'A', 'G', 'T', 'A', 'G', 'A',
    'T', 'T', 'G', 'A', 'C', 'A', 'C', 'T', 'C', 'C', 'C', 'A',
    'G', 'A', 'T', 'G', '\0'};

int main(void) 
{
    for (;;)
    {

        int i;
        char input[100] = {0};
        int result[100] = {0};

        askInput(input);//input func
        if (findDNA(&DNA[0], &input[0], result, 0)) 
        {
            for (i = 0; i < findLength(DNA, 0, 0); i++) 
            {
                if (result[i] == findLength(0, &input[0], 0))
                    printf("Match of search sequence found at element %d\n", i);//output result

            }
        }
    }
}

void askInput(char *inputPtr)//function that takes user input
{

    int lengthDNA, i, j, k;

    printf("Enter length of DNA sequence to match: ");
    scanf(" %d", &lengthDNA);

    if (lengthDNA <= 0) 
    {
        printf("Goodbye");
        exit(0); //exit
    }

    char inputPattern[lengthDNA];
    printf("Enter %d characters (one of AGTC*) as a search sequence: ", lengthDNA);
    for (i = 0; i < lengthDNA; i++)//scanf() user's input into an array
        scanf(" %c", &inputPattern[i]);
    inputPattern[i] = '\0';

    if (lengthDNA <= findLength(DNA, 0, 0)) 
    {
        for (j = 0; j < findLength(0, &inputPattern[0], 0); j++) 
        {
            if (inputPattern[j] != 'A' && inputPattern[j] != 'G' && inputPattern[j] != 'T' && inputPattern[j] != 'C' && inputPattern[j] != '*')//wrong input case 
            {
                printf("Erroneous character input '%c' exiting\n", inputPattern[j]);
                printf("Goodbye");
                exit(0); //exit
            }
        }
        for (k = 0; k < findLength(0, &inputPattern[0], 0); k++)//write input[] with pointer
            *(inputPtr + k) = inputPattern[k];
    }
}

int findDNA(const char *setDNAPtr, char *patternDNAPtr, int *resultPtr, int n)//function that output a find result array
{

    int j;

    for (j = 0; j < findLength(setDNAPtr, 0, 0);)//search all DNA[] for one element in patternDNA[] 
    {
        if (*(resultPtr + j) == n)//locate positions with largest n
        {

            if ((*(patternDNAPtr + n) == *(setDNAPtr + j + n)) || ((*(patternDNAPtr + n) == '*')&&*(setDNAPtr + j + n) != 0))
                *(resultPtr + j) = *(resultPtr + j) + 1;
        }
        j++;
    }
    n++;

    if (n == findLength(0, patternDNAPtr, 0))//exit function when all chars are found
        return 1;
    else
        findDNA(setDNAPtr, patternDNAPtr, resultPtr, n);//recursive
}

int findLength(const char *DNAPtr, char *inputArrPtr, int *inputIntPtr)//function that calculate the length of an array
{
    if (DNAPtr != 0 && inputArrPtr == 0 && inputIntPtr == 0)//const DNA
    {
        int i = 0;
        while (*(DNAPtr + i) != '\0')
            i++;
        return i;    
    }

    if (DNAPtr == 0 && inputArrPtr != 0 && inputIntPtr == 0) //user input
    {
        int j = 0;
        while (*(inputArrPtr + j) != '\0')
            j++;
        return j;
    }

    if (DNAPtr == 0 && inputArrPtr == 0 && inputIntPtr != 0) //output
    {
        int k = 0;
        while (*(inputIntPtr + k) != '\0')
            k++;
        return k;
    }
}
