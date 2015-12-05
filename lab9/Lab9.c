/* 
 * File:   Lab9.c
 * Author: Shizhang Yin (shizhang.yin@mail.utoronto.ca)
 * Date: December 3, 2015
 * Course: APS105
 *     
 * Summary of File:
 * 
 * This this a program that takes user input and put them into a music library. It can also sort the
 * array of music library with cocktail sort.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LENGTH 1024

static const int MAX_LIBRARY_SIZE = 100;

typedef struct song
{
    char songName[MAX_LENGTH];
    char artist[MAX_LENGTH];
} Song;

int songNum(Song library[]);
void initLib(Song library[]);
void getStringFromUserInput(char s[], int arraySize);
void insert(Song library[]);
void print(Song library[]);
void cocktailSort(Song library[], int size);

int main(void)
{
    Song library[MAX_LIBRARY_SIZE];
    initLib(library);
    char response,input[2];
    printf("%s", "Personal Music Library.\n\n");
    printf("%s", "Commands are I (insert), S (sort by artist),\n"
           "P (print), Q (quit).\n");
    while( true )//get command input from user
    {
        printf("\nCommand?: ");
        getStringFromUserInput(input, MAX_LENGTH);
        response = toupper(input[0]);
        if ( response == 'I' )//insert a new songt to the library
        {
            //Insert a new song
            insert(library);
        }
        else if ( response == 'P' )//print the current library
        {
            // Print the music library.
            print(library);
        }
        else if ( response == 'S' )//Sort the music library
        {
            // Sort the music library.
            cocktailSort(library, songNum(library));
        }
        else if ( response == 'Q' )//exit program
        {
            return 0;
        }
        else
        {
            printf("\nInvalid command.\n");
        }
    }
    return 0;
}

void insert(Song library[])
{
    int i=0;
    while(library[i].songName[0]!='\0')//find the avaliable place for insert
        i++;
    printf("Song name: ");
    getStringFromUserInput(library[i].songName, MAX_LENGTH-1);
    printf("Artist: ");
    getStringFromUserInput(library[i].artist, MAX_LENGTH-1);
}

void print(Song library[])
{
    int i=0;
    if(library[0].songName[0]=='\0')//if the music library is empty
    {
        printf("\nThe music library is empty.\n");
        return;
    }
    printf("\nMy Personal Music Library:\n");
    while(library[i].songName[0]!='\0')//print music library to the end
    {
        printf("\n%s\n",library[i].songName);
        printf("%s\n",library[i].artist);
        i++;
    }
}

void cocktailSort(Song library[], int size)
{
    int location = 0, current=0;
    bool sortFinished = false;
    char tempS[MAX_LENGTH],tempA[MAX_LENGTH];
    while(( location < (size - 1) ) && (sortFinished==false))
    {
        sortFinished = true;
        while(current < (size - 1 - location))//forward bubble
        {
            if( strcmp(library[current].artist, library[current + 1].artist) > 0 )//when it should be swapped
            {
                strcpy(tempS,library[current].songName);
                strcpy(tempA,library[current].artist);
                strcpy(library[current].songName,library[current + 1].songName);
                strcpy(library[current].artist,library[current + 1].artist);
                strcpy(library[current + 1].songName,tempS);
                strcpy(library[current + 1].artist,tempA);
                sortFinished=false;
            }
            else if(strcmp(library[current].artist, library[current + 1].artist) == 0)//same artist
            {
                if(strcmp(library[current].songName, library[current + 1].songName) > 0)//look for song name
                {
                    strcpy(tempS,library[current].songName);
                    strcpy(tempA,library[current].artist);
                    strcpy(library[current].songName,library[current + 1].songName);
                    strcpy(library[current].artist,library[current + 1].artist);
                    strcpy(library[current + 1].songName,tempS);
                    strcpy(library[current + 1].artist,tempA);
                    sortFinished=false;
                }
            }
            current++;
        }
        current--;
        while( current > location)//backward bubble
        {
            if( strcmp(library[current-1].artist, library[current].artist) > 0 )//when it should be swapped
            {
                strcpy(tempS,library[current-1].songName);
                strcpy(tempA,library[current-1].artist);
                strcpy(library[current-1].songName,library[current].songName);
                strcpy(library[current-1].artist,library[current].artist);
                strcpy(library[current].songName,tempS);
                strcpy(library[current].artist,tempA);
                sortFinished=false;
            }
            else if(strcmp(library[current-1].artist, library[current].artist) == 0)//same artist
            {
                if(strcmp(library[current-1].songName, library[current].songName) > 0)//look for song name
                {
                    strcpy(tempS,library[current-1].songName);
                    strcpy(tempA,library[current-1].artist);
                    strcpy(library[current-1].songName,library[current].songName);
                    strcpy(library[current-1].artist,library[current].artist);
                    strcpy(library[current].songName,tempS);
                    strcpy(library[current].artist,tempA);
                    sortFinished=false;
                }
            }
            current--;
        }
        current++;
        location++;
    }
    print(library);
}

void getStringFromUserInput(char s[], int maxStrLength)//function from last lab
{
    int i = 0;
    char c;
    while ( i < maxStrLength && ( c = getchar()) != '\n' )
        s[i++] = c;
    s[i] = '\0';
}

void initLib(Song library[])//init and fill array with zero
{
    int i;
    for(i=0;i<MAX_LIBRARY_SIZE;i++)
    {
        library[i].songName[0]='\0';
    }
}

int songNum(Song library[])//find the first avaliable place
{
    int i=0;
    while(library[i].songName[0]!='\0')
        i++;
    return i;
}
