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
    bool processState = true;
    bool reRandom=true; // Declare variables
    
    printf("Enter seed: ");
    scanf("%d", &randomSeed); // Get the seed for rand() from user
    srand(randomSeed); // Set the seed with srand()
    while (processState == true) // Determain if the program should exit
    {
        if(reRandom==true) // Determain if the program needs a new random number
        {
        numberToguess = (rand() % 7) + 1; // Get a random number from 1 to 7
        }
        
	reRandom=true; // Ask for a new random number next loop
        printf("Guess a number from 1 to 7 (<=0 to quit): ");
        scanf("%d", &inputNumber); // Ask for user input
       
	 if (inputNumber <= 0)
        {
            printf("Goodbye");
            processState = false; // Exit the loop
        } 
        else if (inputNumber > 7)
        {
            printf("Number too high, guess again!\n");
            reRandom=false; // Stop regenarate a new random number
        }
        else if (inputNumber == numberToguess) 
        {
            printf("Number picked: %d\n", numberToguess);
            printf("Good guess!\n"); // The user guessed the right number
        } 
        else 
        {
            printf("Number picked: %d\n", numberToguess);
            printf("Sorry, try again!\n"); // The user guessed the wrong number
        }
    }
    return (EXIT_SUCCESS);
}

