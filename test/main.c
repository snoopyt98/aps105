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
    while( true )
    {
        printf("\nCommand?: ");
        getStringFromUserInput(input, MAX_LENGTH);
        response = toupper(input[0]);
        if ( response == 'I' )
        {
            //Insert a new song
            insert(library);
        }
        else if ( response == 'P' )
        {
            // Print the music library.
            print(library);
        }
        else if ( response == 'S' )
        {
            // Search for a song by its name.
            cocktailSort(library, songNum(library));
        }
        else if ( response == 'Q' )
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
    while(library[i].songName[0]!='\0')
        i++;
    printf("Song name: ");
    getStringFromUserInput(library[i].songName, MAX_LENGTH-1);
    printf("Artist: ");
    getStringFromUserInput(library[i].artist, MAX_LENGTH-1);
}

void print(Song library[])
{
    int i=0;
    if(library[0].songName[0]=='\0')
    {
        printf("\nThe music library is empty.\n");
        return;
    }
    printf("\nMy Personal Music Library:\n");
    while(library[i].songName[0]!='\0')
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
    while(( location < (size - 1) ) && (sortFinished==false))
    {
        sortFinished = true;
        printf("%d",current);
        //current=location;
        while(current < (size - 1 - location))
        {
            if( strcmp(library[current].artist, library[current + 1].artist) > 0 )
            {
                char tempS[MAX_LENGTH],tempA[MAX_LENGTH];
                strcpy(tempS,library[current].songName);
                strcpy(tempA,library[current].artist);
                strcpy(library[current].songName,library[current + 1].songName);
                strcpy(library[current].artist,library[current + 1].artist);
                strcpy(library[current + 1].songName,tempS);
                strcpy(library[current + 1].artist,tempA);
                sortFinished=false;
            }
            current++;
        }
        current--;
        while( current > location)
        {
            if( strcmp(library[current-1].artist, library[current].artist) > 0 )
            {
                char tempS[MAX_LENGTH],tempA[MAX_LENGTH];
                strcpy(tempS,library[current-1].songName);
                strcpy(tempA,library[current-1].artist);
                strcpy(library[current-1].songName,library[current].songName);
                strcpy(library[current-1].artist,library[current].artist);
                strcpy(library[current].songName,tempS);
                strcpy(library[current].artist,tempA);
                sortFinished=false;
            }
            current--;
        }
        current++;
        location++;
    }
    print(library);
}

void getStringFromUserInput(char s[], int maxStrLength)
{
    int i = 0;
    char c;
    while ( i < maxStrLength && ( c = getchar()) != '\n' )
        s[i++] = c;
    s[i] = '\0';
}

void initLib(Song library[])
{
    int i;
    for(i=0;i<MAX_LIBRARY_SIZE;i++)
    {
        library[i].songName[0]='\0';
    }
}

int songNum(Song library[])
{
    int i=0;
    while(library[i].songName[0]!='\0')
        i++;
    return i;
}