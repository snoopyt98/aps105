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
Node *insert(Node* root);
Node *delete(Node* root, char input[]);
Node *search(Node* root, char input[]);
Node *print(Node* root);
void *exitClean(Node* root);

// Declarations of support functions
// See below the main function for descriptions of what these functions do

void getStringFromUserInput(char s[], int arraySize);
Node *newNode(char songNamein[], char artistin[], char genrein[], Node *link);

const int MAX_LENGTH = 1024;

int main(void)
{
    Node *root = NULL;
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
        getStringFromUserInput(input, 1);

        // Response is the first character entered by user.
        // Convert to uppercase to simplify later comparisons.
        response = toupper(input[0]);

        if ( response == 'I' )
        {
            root = insert(root);
        }
        else if ( response == 'D' )
        {
            // Delete a song from the list.
            char input[MAX_LENGTH + 1];
            printf("\nEnter the name of the song to be deleted: ");
            getStringFromUserInput(input, MAX_LENGTH);
            root = delete(root, input);
        }
        else if ( response == 'S' )
        {
            // Search for a song by its name.
            char input[MAX_LENGTH + 1];
            printf("\nEnter the name of the song to search for: ");
            getStringFromUserInput(input, MAX_LENGTH);
            search(root, input);
        }
        else if ( response == 'P' )
        {
            // Print the music library.
            print(root);
        }
        else if ( response == 'Q' )
        {
            ; // do nothing, we'll catch this below
        }
        else
        {
            // do this if no command matched ...
            printf("\nInvalid command.\n");
        }
    }
    while ( response != 'Q' );
    if ( root != NULL )
        exitClean(root);
    printf("\nThe music library is empty.\n");
    return 0;
}

// Support Function Definitions

// Prompt the user for a string safely, without buffer overflow

void getStringFromUserInput(char s[], int maxStrLength)
{
    int i = 0;
    char c;

    while ( i < maxStrLength && ( c = getchar()) != '\n' )
        s[i++] = c;

    s[i] = '\0';
}

Node *insert(Node* root)
{
    // Insert a song into the linked list.
    // Maintain the list in alphabetical order by song name.
    //   ADD STATEMENT(S) HERE

    // USE THE FOLLOWING PRINTF STATEMENTS WHEN PROMPTING FOR DATA:
    Node* temp = root;
    char songNamein[MAX_LENGTH + 1];
    char artistin[MAX_LENGTH + 1];
    char genrein[MAX_LENGTH + 1];
    printf("Song name: ");
    getStringFromUserInput(songNamein, MAX_LENGTH);
    printf("Artist: ");
    getStringFromUserInput(artistin, MAX_LENGTH);
    printf("Genre: ");
    getStringFromUserInput(genrein, MAX_LENGTH);
    if ( root == NULL )
    {
        root = newNode(songNamein, artistin, genrein, NULL);
        return root;
    }
    else
    {
        int counter = 0;
        Node* temp1 = root;
        Node* temp2 = root->link;
        while ( temp != NULL )
        {
            if ( strcmp(temp->songName, songNamein) == 0 )
            {
                printf("A song with the name ’%s’ is already in the music library. No new song entered.\n", songNamein);
                return root;
            }
            temp = temp->link;
        }
        while ( temp1 != NULL )
        {
            if (( strcmp(temp1->songName, songNamein) > 0 ) && ( counter == 0 ))
            {
                root = newNode(songNamein, artistin, genrein, temp1);
                return root;
            }
            else if (( strcmp(temp1->songName, songNamein) < 0 ) && ( temp1->link == NULL || ( strcmp(temp1->link->songName, songNamein) > 0 )))//place after
            {
                temp1->link = newNode(songNamein, artistin, genrein, temp2);
                return root;
            }
            counter++;
            temp1 = temp1->link;
            if ( temp2 != NULL )
                temp2 = temp2->link;
            else
                temp2 = NULL;
        }
    }
    return root;
}

Node *delete(Node* root, char input[])
{
    if ( root == NULL )
    {
        printf("\nThe music library is empty.\n");
        return root;
    }
    else if ( strcmp(root->songName, input) == 0 )
    {
        Node* temp = root->link;
        free(root->songName);
        free(root->artist);
        free(root->genre);
        free(root);
        printf("\nDeleting a song with name ’%s’ from the music library.\n", input);
        return temp;
    }
    Node* previous = root;
    Node* current = root->link;
    while ( current != NULL )
    {
        if ( strcmp(current->songName, input) == 0 )
        {
            previous->link = current->link;
            free(current->songName);
            free(current->artist);
            free(current->genre);
            free(current);
            printf("\nDeleting a song with name ’%s’ from the music library.\n", input);
            return root;
        }
        previous = previous->link;
        current = current->link;
    }
    printf("\nThe song name ’%s’ was not found in the music library.\n", input);
    return root;
}

Node *newNode(char songNamein[], char artistin[], char genrein[], Node* link)
{
    Node *t = (Node *) malloc(sizeof ( Node ));
    t->songName = (char *) malloc(( MAX_LENGTH + 1 ) * sizeof ( char ));
    t->artist = (char *) malloc(( MAX_LENGTH + 1 ) * sizeof ( char ));
    t->genre = (char *) malloc(( MAX_LENGTH + 1 ) * sizeof ( char ));
    strncpy(t->songName, songNamein, MAX_LENGTH + 1);
    strncpy(t->artist, artistin, MAX_LENGTH + 1);
    strncpy(t->genre, genrein, MAX_LENGTH + 1);
    t->link = NULL;
    if ( link != NULL )
        t->link = link;
    return t;
}

Node *search(Node* root, char input[])
{
    Node *temp = root;
    while ( temp != NULL )
    {
        if ( strcmp(temp->songName, input) == 0 )
        {
            printf("\nThe song name ’%s’ was found in the music library.\n\n", input);
            printf("%s\n", temp->songName);
            printf("%s\n", temp->artist);
            printf("%s\n", temp->genre);
            return root;
        }

        temp = temp->link;
    }
    printf("\nThe song name '%s' was not found in the music library.\n", input);
    return root;
}

Node *print(Node* root)
{
    printf("\n");
    printf("My Personal Music Library: \n");
    Node* temp = root;
    if ( temp == NULL )
    {
        printf("\nThe music library is empty.\n");
        return root;
    }
    while ( temp != NULL )
    {
        printf("\n");
        printf("%s\n", temp->songName);
        printf("%s\n", temp->artist);
        printf("%s\n", temp->genre);
        temp = temp->link;
    }
    return root;
}

void *exitClean(Node* root)
{
    if ( root != NULL )
    {
        printf("\nDeleting a song with name ’%s’ from the music library.\n", root->songName);
        exitClean(root->link);
        free(root->songName);
        free(root->artist);
        free(root->genre);
        free(root);
    }
}
