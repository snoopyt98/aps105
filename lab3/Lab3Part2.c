/* 
 * File:   Lab3part2.c
 * Author: yinshizh
 *
 * Created on October 1, 2015, 12:26 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void) 
{
    int randomSeed, numberToguess, inputNumber;
    bool processState=true;
    printf("Enter seed: ");
    scanf("%d",&randomSeed);
    srand(randomSeed);
    while(processState==true)
    {
        numberToguess=(rand()%7)+1;
        printf("Guess a number from 1 to 7 (<=0 to quit): ");
        scanf("%d",&inputNumber);
        printf("Number picked: %d\n",numberToguess);
        if(inputNumber<=0)
        {
            printf("Goodbye");
            processState=false;
        }
        else if(inputNumber>7)
            printf("Number too high, guess again!\n");
        else if(inputNumber==numberToguess)
            printf("Good guess!\n");
        else
            printf("Sorry, try again!\n");
    }
    return (EXIT_SUCCESS);
}

