/* 
 * File:   main.c
 * Author: jonathanscottrose
 *
 * Created on October 13, 2014, 3:38 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * This program searches an array to find three even numbers in a row
 * and reports the index of the first element of the three
 */
int main(void) {
    
    const int SIZE = 10;
    int numFound = 0;
    int foundIndex;
    
    bool found = false;
    
    int A[  ] = { 3, 8, 4, 5, 2, 12, 20, 9, 7, 4 };
    int i;
    for (i = 0; i < SIZE && !found; i++) {
        
        if (A[i] % 2 == 0) {
            numFound++;
            if (numFound == 3) {
                found = true;
                foundIndex = i - 2;
            }
        }
        else numFound = 0;
    }
    
    if (found) printf("Found three even numbers in a row starting at index %d\n",foundIndex);

    return (EXIT_SUCCESS);
}
