#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

const int MAX_LENGTH = 1024;
const int MAX_LIBRARY_SIZE = 100;

typedef struct song
{
    char songName[MAX_LENGTH];
    char artist[MAX_LENGTH];
} Song;

void getStringFromUserInput(char s[], int arraySize);
void insert(Song library[]);
void print(Song library[]);
void cocktailSort(Song library[], int size);

int main(void)
{
    Song Library[MAX_LIBRARY_SIZE];
    char response;
    printf("%s", "Personal Music Library.\n\n");
    printf("%s", "Commands are I (insert), D (delete), S (search by song name),\n"
           "P (print), Q (quit).\n");
    while( true )
    {
        printf("\nCommand?: ");
        getStringFromUserInput(input, 1);
        response = toupper(input[0]);
        if ( response == 'I' )
        {
            //Insert a new song
            insert(Library);
        }
        else if ( response == 'P' )
        {
            // Print the music library.
            print(Library);
        }
        else if ( response == 'S' )
        {
            // Search for a song by its name.
            char input[MAX_LENGTH + 1];
            printf("\nEnter the name of the song to search for: ");
            getStringFromUserInput(input, MAX_LENGTH);
            sort(root, input);
        }
        else
        {
            printf("\nInvalid command.\n");
        }
    }
    return 0;
}

void insert()
{
    printf("Song name: ");
    getStringFromUserInput(songNamein, MAX_LENGTH);
    printf("Artist: ");
    getStringFromUserInput(artistin, MAX_LENGTH);
}

void cocktailSort(Song library[], int size)
{
    int location = 0, currentF,currentB;
    bool ftbf = true; // Frontward true Backward false
    bool sortFinished = false;
    while( location < size - 1 && sortFinished = false )
    {
        current=0;
        while( currentF < size - 2 - location && ftbf)
        {
            if( strcmp(library[currentF].artist, library[currentF + 1].artist) > 0 )
            {
                char temp[] = library[currentF].artist;
                library[currentF].artist = library[currentF + 1].artist;
                library[currentF + 1].artist = temp;
            }
            current++;
        }
        currentB=size-1;
        while( currentB > location && !ftbf)
        {
            if( strcmp(library[currentB-1].artist, library[currentB].artist) > 0 )
            {
                char temp[] = library[current-1].artist;
                library[currentB-1].artist = library[currentB].artist;
                library[currentB].artist = temp;
            }
            currentB--;
        }
        location++;
    }
}

void getStringFromUserInput(char s[], int maxStrLength)
{
    int i = 0;
    char c;
    while ( i < maxStrLength && ( c = getchar()) != '\n' )
        s[i++] = c;
    s[i] = '\0';
}
