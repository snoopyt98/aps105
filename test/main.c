//
// APS105-F15 Lab 8 Lab8.c
//
// This is a program written to maintain a personal music library, 
// using a linked list to hold the songs in the library.
//
// Author: <Shizhang Yin>
// Student Number: <1002428027>
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

// A node in the linked list

// Each string in the node is declared as a character pointer variable,
// so they need to be dynamically allocated using the malloc() function,
// and deallocated using the free() function after use.

typedef struct node
{
    char *songName;
    char *artist;
    char *genre;
    struct node *link;
} Node;


// Declarations of linked list functions
//
// Declare your own linked list functions here.
//
// ADD YOUR STATEMENT(S) HERE
void insert(Node** root);

// Declarations of support functions
// See below the main function for descriptions of what these functions do

void getStringFromUserInput(char s[], int arraySize);
void songNameDuplicate(char songName[]);
void songNameFound(char songName[]);
void songNameNotFound(char songName[]);
void songNameDeleted(char songName[]);
void artistFound(char artist[]);
void artistNotFound(char artist[]);
void printMusicLibraryEmpty(void);
void printMusicLibraryTitle(void);

const int MAX_LENGTH = 1024;

int main(void)
{
    Node *root = NULL;
    Node **passroot = &(root);
    // Declare the head of the linked list.

    //   ADD YOUR STATEMENT(S) HERE

    // Announce the start of the program
    printf("%s", "Personal Music Library.\n\n");
    printf("%s", "Commands are I (insert), D (delete), S (search by song name),\n"
            "P (print), Q (quit).\n");

    char response;
    char input[MAX_LENGTH + 1];
    do
    {
        printf("\nCommand?: ");
        getStringFromUserInput(input, MAX_LENGTH);

        // Response is the first character entered by user.
        // Convert to uppercase to simplify later comparisons.
        response = toupper(input[0]);

        if (response == 'I')
        {
            insert(passroot);
        }
        else if (response == 'D')
        {
            // Delete a song from the list.

            printf("\nEnter the name of the song to be deleted: ");

            //   ADD STATEMENT(S) HERE

        }
        else if (response == 'S')
        {
            // Search for a song by its name.

            printf("\nEnter the name of the song to search for: ");

            //   ADD STATEMENT(S) HERE

        }
        else if (response == 'P')
        {
            // Print the music library.

            //   ADD STATEMENT(S) HERE

        }
        else if (response == 'Q')
        {
            ; // do nothing, we'll catch this below
        }
        else
        {
            // do this if no command matched ...
            printf("\nInvalid command.\n");
        }
    }
    while (response != 'Q');

    // Delete the entire linked list.
    //   ADD STATEMENT(S) HERE

    // Print the linked list to confirm deletion.
    //   ADD STATEMENT(S) HERE

    return 0;
}

// Support Function Definitions

// Prompt the user for a string safely, without buffer overflow

void getStringFromUserInput(char s[], int maxStrLength)
{
    int i = 0;
    char c;

    while (i < maxStrLength && (c = getchar()) != '\n')
        s[i++] = c;

    s[i] = '\0';
}

// Function to call when the user is trying to insert a song name 
// that is already in the personal music library.

void songNameDuplicate(char songName[])
{
    printf("\nA song with the name '%s' is already in the music library.\n"
            "No new song entered.\n", songName);
}

// Function to call when a song name was found in the personal music library.

void songNameFound(char songName[])
{
    printf("\nThe song name '%s' was found in the music library.\n",
            songName);
}

// Function to call when a song name was not found in the personal music library.

void songNameNotFound(char songName[])
{
    printf("\nThe song name '%s' was not found in the music library.\n",
            songName);
}

// Function to call when a song name that is to be deleted
// was found in the personal music library.

void songNameDeleted(char songName[])
{
    printf("\nDeleting a song with name '%s' from the music library.\n",
            songName);
}

// Function to call when printing an empty music library.

void printMusicLibraryEmpty(void)
{
    printf("\nThe music library is empty.\n");
}

// Function to call to print a title when the entire music library is printed.

void printMusicLibraryTitle(void)
{
    printf("\nMy Personal Music Library: \n");
}

void insert(Node** root)
{
    // Insert a song into the linked list.
    // Maintain the list in alphabetical order by song name.
    //   ADD STATEMENT(S) HERE

    // USE THE FOLLOWING PRINTF STATEMENTS WHEN PROMPTING FOR DATA:
    Node* temp = *root;
    if (temp == NULL)
    {
        temp = (Node *) malloc(sizeof (Node));
        char songNameA[MAX_LENGTH];
        char artistA[MAX_LENGTH];
        char genreA[MAX_LENGTH];
        temp.songName=songNameA;
        temp.artist=artistA;
        temp.genre=genreA;
        printf("Song name: ");
        getStringFromUserInput(songNameA, MAX_LENGTH);
        printf("Artist: ");
        getStringFromUserInput(artistA, MAX_LENGTH);
        printf("Genre: ");
        getStringFromUserInput(genreA, MAX_LENGTH);
        temp->link = NULL;
        if (*root == NULL)
            *root = temp;
    }
    else
    {
        Node* newTemp=(Node *) malloc(sizeof (Node));;
        while (true)
        {

            if (temp->link == NULL)
            {
                temp->link = newTemp;
                break;
            }
            temp = temp->link;
        }
        char songNameB[MAX_LENGTH];
        char artistB[MAX_LENGTH];
        char genreB[MAX_LENGTH];
        newTemp.songName=songNameB;
        newTemp.artist=artistB;
        newTemp.genre=genreB;
        printf("Song name: ");
        getStringFromUserInput(songNameB, MAX_LENGTH);
        printf("Artist: ");
        getStringFromUserInput(artistB, MAX_LENGTH);
        printf("Genre: ");
        getStringFromUserInput(genreB, MAX_LENGTH);     
        newTemp->link = NULL;
    }

}
