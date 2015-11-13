#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>

static const int MAX_BOARD_SIZE = 26;
static const int DELTA[8][2] = {-1, -1, -1, 0, -1, 1, 0, -1, 0, 1, 1, -1, 1, 0, 1, 1};

//static const int INFINITY = 1000000;//for alpha beta
/*
     a b c d e f g h
   1 - C B A A B C -
   2 C X D E E D X C
   3 B D - - - - D B
   4 A E - - - - E A
   5 A E - - - - E A
   6 B D - - - - D B
   7 C X D E E D X C
   8 - C B A A B C -
 */
static const int COMMON_SCORE_DEFAULT = 2;
static const double COMMON_SCORE_RATIO = 1;
static const int CORNER_SCORE_DEFAULT = 20;
static const double CORNER_SCORE_RATIO = 1;
static const int X_SCORE_DEFAULT = -7;
static const double X_SCORE_RATIO = 1;
static const int C_SCORE_DEFAULT = -3;
static const double C_SCORE_RATIO = 1;
static const int CENTER_SCORE_DEFAULT = -3;
static const double CENTER_SCORE_RATIO = 1;
static const int A_SCORE_DEFAULT = 8;
static const double A_SCORE_RATIO = 1;
static const int B_SCORE_DEFAULT = -4;
static const double B_SCORE_RATIO = 1;
static const int D_SCORE_DEFAULT = 11;
static const double D_SCORE_RATIO = 1;
static const int E_SCORE_DEFAULT = 1;
static const double E_SCORE_RATIO = 1;


static const double BOARD_SCORE_CONSTANT = 10;//to be changed
static const double CORNER_CONSTANT = 10;
static const double CONRER_STABILITY_CONSTANT = 10;
static const double MOBILITY_CONSTANT = 10;

void boardInitialize(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n);
void printBoard(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n);
char opColour(char colour);
int legalCases(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], char i, char j, char opColour, int n);
void userMove(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n, char colour);
void moveFlip(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n, char row, char col, char colour);
void flip(char tempBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int movePosition[8][3], int n, char row, char col, char colour);
void unflip(char tempBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int movePosition[8][3], int n, char row, char col, char colour);
bool positionInBounds(int N, char row, char col);
int checkLegalInDirection(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int N, char row, char col, char colour, int deltaRow, int deltaCol);
char computerColour(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n);
void gameProcess(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n, char colour);
void computerMove(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n, char colour);
bool checkWin(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n, char colour);
void reduceMove(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n, char colour, int* minCase);
double gameStage(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n);
bool cornerCase(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n, char row, char col, char colour);
int availableMoves(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n, char colour, int moveList[676][2], bool outputList);
void boardCount(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n, char colour, int* boardNum);
void generateScoreboard(int scoreBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n);
double heuristicScoreevaluation(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int scoreBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n, char colour);
double alphaBeta(char tempBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int scoreBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int depth, double alpha, double beta, bool mySelf, char colour, char opColour, int n);

int main(void)
{
    char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
    int boardSize;
    printf("Enter the board dimension: ");
    scanf("%d", &boardSize);
    boardInitialize(board, boardSize);
    //generateScoreboard(scoreBoard, boardSize); //test
    gameProcess(board, boardSize, computerColour(board, boardSize));
}

void boardInitialize(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n)//initialize stardard starting board configuration
{
    int i, j, k, m;
    for( i = 0; i < MAX_BOARD_SIZE; i++ )
    {
        for( j = 0; j < MAX_BOARD_SIZE; j++ )
            board[i][j] = '\0';
    }
    for( k = 0; k < n; k++ )
    {
        for( m = 0; m < n; m++ )
            board[k][m] = 'U';
    }
    board[( n / 2 ) - 1][( n / 2 - 1 )] = 'W';
    board[( n / 2 ) - 1][n / 2] = 'B';
    board[n / 2][( n / 2 ) - 1] = 'B';
    board[n / 2][n / 2] = 'W';

    //board[( n / 2 ) - 1][( n / 2 - 1 )] = 'B';//only for testing
    //board[( n / 2 ) - 1][n / 2] = 'W';
    //board[n / 2][( n / 2 ) - 1] = 'W';
    //board[n / 2][n / 2] = 'B';
}

void printBoard(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n)//print current board
{
    int i, j, k;
    printf("  ");
    for( i = 0; i < n; i++ )
        printf("%c", 'a' + i);
    printf("\n");
    for( j = 0; j < n; j++ )
    {
        printf("%c ", 'a' + j);
        for( k = 0; k < n; k++ )
            printf("%c", board[j][k]);
        printf("\n");
    }
}

char opColour(char colour)
{
    char opColour;
    if( colour == 'B' )
        opColour = 'W';
    else if( colour == 'W' )
        opColour = 'B';
    return opColour;
}

char computerColour(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n)
{
    char colour;
    printf("Computer plays (B/W) : ");
    scanf(" %c", &colour);
    printBoard(board, n);
    return colour;
}

int legalCases(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], char row, char col, char colour, int n)
{
    int i;
    int result = 0;
    for( i = 0; i < 8; i++ )
    {
        result = result + checkLegalInDirection(board, n, row, col, colour, DELTA[i][0], DELTA[i][1]);
    }
    return result;
}
//may need this function
bool availablePositionornot(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], char row, char col, char colour, int n)
{
    int i;
    bool result = false;
    for( i = 0; i < 8; i++ )
    {
        result = result || checkLegalInDirection(board, n, row, col, colour, DELTA[i][0], DELTA[i][1]);
        if ( result )
            return true;
    }
    return false;
}

bool positionInBounds(int N, char row, char col)//helper func
{
    if(( row >= 'a' ) && ( row <= 'a' + N - 1 ) && ( col >= 'a' ) && ( col <= 'a' + N - 1 ))
        return true;
    else
        return false;
}


int checkLegalInDirection(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int N, char row, char col, char colour, int deltaRow, int deltaCol)
{
    if( board[row - 'a'][col - 'a'] != 'U' )
        return 0;
    else
    {
        int i, counter = 0;
        if( !positionInBounds(N, row + deltaRow, col + deltaCol))
            return 0;
        for( i = 0; positionInBounds(N, row + deltaRow, col + deltaCol); i++ )
        {
            if( board[row - 'a' + deltaRow][col - 'a' + deltaCol] == opColour(colour) )
            {
                counter++;
                row = row + deltaRow;
                col = col + deltaCol;
            }
            else if( board[row - 'a' + deltaRow][col - 'a' + deltaCol] == colour && counter < 1 )
                return 0;
            else if( board[row - 'a' + deltaRow][col - 'a' + deltaCol] == colour && counter >= 1 )
                return counter;
            else if( board[row - 'a' + deltaRow][col - 'a' + deltaCol] == 'U' )
                return 0;
        }
        if( board[row - 'a'][col - 'a'] == opColour(colour) && counter >= 1 )
            return 0;
    }
}

void userMove(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n, char colour)
{
    int i;
    bool caseState = false;
    char userInput[3];
    printf("Make move for colour %c (Row/Col): ", colour);
    for( i = 0; i < 2; i++ )
        scanf(" %c", &userInput[i]);
    if( positionInBounds(n, userInput[0], userInput[1]))
    {
        if( legalCases(board, userInput[0], userInput[1], colour, n) != 0 )
            caseState = true;
        else
            caseState = false;
    }
    else
        caseState = false;
    if( caseState )
        moveFlip(board, n, userInput[0], userInput[1], colour);
    else
    {
        printf("Invalid move.\n");
        printf("%c player wins.\n", opColour(colour));
        exit(0);
    }
}

void moveFlip(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n, char row, char col, char colour)
{
    int i, j, counter = 0;
    char rowTemp;
    char colTemp;
    board[row - 'a'][col - 'a'] = colour;
    for( i = 0; i < 8; i++ )
    {
        rowTemp = row;
        colTemp = col;
        counter = 0;
        while( positionInBounds(n, rowTemp + DELTA[i][0], colTemp + DELTA[i][1]))
        {
            if( board[rowTemp + DELTA[i][0] - 'a'][colTemp + DELTA[i][1] - 'a'] == opColour(colour) )
            {
                counter++;
                rowTemp = rowTemp + DELTA[i][0];
                colTemp = colTemp + DELTA[i][1];
            }
            else if( board[rowTemp + DELTA[i][0] - 'a'][colTemp + DELTA[i][1] - 'a'] == 'U' )
                break;
            else if( board[rowTemp + DELTA[i][0] - 'a'][colTemp + DELTA[i][1] - 'a'] == colour && counter < 1 )
                break;
            else if( board[rowTemp + DELTA[i][0] - 'a'][colTemp + DELTA[i][1] - 'a'] == colour && counter >= 1 )
            {
                for( j = 0; j < counter; j++ )
                    board[rowTemp - j * DELTA[i][0] - 'a'][colTemp - j * DELTA[i][1] - 'a'] = colour;
                break;
            }
        }
    }
}

void flip(char tempBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int movePosition[8][3], int n, char row, char col, char colour)
{
    int i, j, counter = 0;
    char rowTemp;
    char colTemp;
    tempBoard[row - 'a'][col - 'a'] = colour;
    for( i = 0; i < 8; i++ )
    {
        rowTemp = row;
        colTemp = col;
        counter = 0;
        while( positionInBounds(n, rowTemp + DELTA[i][0], colTemp + DELTA[i][1]))
        {
            if( tempBoard[rowTemp + DELTA[i][0] - 'a'][colTemp + DELTA[i][1] - 'a'] == opColour(colour) )
            {
                counter++;
                rowTemp = rowTemp + DELTA[i][0];
                colTemp = colTemp + DELTA[i][1];
            }
            else if( tempBoard[rowTemp + DELTA[i][0] - 'a'][colTemp + DELTA[i][1] - 'a'] == 'U' )
                break;
            else if( tempBoard[rowTemp + DELTA[i][0] - 'a'][colTemp + DELTA[i][1] - 'a'] == colour && counter < 1 )
                break;
            else if( tempBoard[rowTemp + DELTA[i][0] - 'a'][colTemp + DELTA[i][1] - 'a'] == colour && counter >= 1 )
            {
                for( j = 0; j < counter; j++ )
                    tempBoard[rowTemp - j * DELTA[i][0] - 'a'][colTemp - j * DELTA[i][1] - 'a'] = colour;
                break;
            }
        }
        movePosition[i][0] = DELTA[i][0];
        movePosition[i][1] = DELTA[i][1];
        movePosition[i][2] = counter;
    }
}

void unflip(char tempBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int movePosition[8][3], int n, char row, char col, char colour)
{
    int i, j;
    char opColour;
    if( colour == 'B' )
        opColour = 'W';
    else if( colour == 'W' )
        opColour = 'B';
    tempBoard[row - 'a'][col - 'a'] = 'U';
    for( i = 0; i < 8; i++ )
    {
        if( movePosition[i][2] != 0 )
        {
            for( j = 1; j <= movePosition[i][2]; j++ )
            {
                tempBoard[row - 'a' + j * movePosition[i][0]][col - 'a' + j * movePosition[i][1]] = opColour;
            }
        }
    }
}

void gameProcess(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n, char colour)//the process of playing the game
{
    bool gameState = true;
    while( gameState == true )
    {
        if( colour == 'B' )
        {
            if( checkWin(board, n, 'B') == true )//the if no legal move is considered in the checkWin() function
            {
                computerMove(board, n, 'B');
                printBoard(board, n);
            }
            if( checkWin(board, n, 'W') == true )
            {
                userMove(board, n, 'W');
                printBoard(board, n);
            }
        }
        else if( colour == 'W' )
        {
            if( checkWin(board, n, 'B') == true )
            {
                userMove(board, n, 'B');
                printBoard(board, n);
            }
            if( checkWin(board, n, 'W') == true )
            {
                computerMove(board, n, 'W');
                printBoard(board, n);
            }
        }
    }
}

void computerMove(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n, char colour)
{
    int i, j, counter = 0;
    int scoreBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
    double temp[3] = {0};
    int bestMove[3] = {0, 0, -100000000};
    int minCase[3] = {0, 0, 676};
    char tempBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
    generateScoreboard(scoreBoard, n);
    //printf("%lf\n",alphaBeta(2,-1000000, 1000000, true, 'B', 'W', n));
    for( i = 0; i < n; i++ )
    {
        for( j = 0; j < n; j++ )
        {
            if( legalCases(board, i + 'a', j + 'a', 'B', n) > 0 )
            {
                memcpy(tempBoard, board, sizeof( char ) * MAX_BOARD_SIZE * MAX_BOARD_SIZE);
                moveFlip(tempBoard, n, i + 'a', j + 'a', colour);
                temp[0] = i;
                temp[1] = j;
                temp[2] = heuristicScoreevaluation(tempBoard, scoreBoard, n, colour);
                printf("%c%c %lf\n", i + 'a', j + 'a', temp[2]);
                //printf("%d%d\n",i,j);
                if( temp[2] >= bestMove[2] )
                {
                    bestMove[0] = temp[0];
                    bestMove[1] = temp[1];
                    bestMove[2] = temp[2];
                }
            }
        }
    }
    memcpy(tempBoard, board, sizeof( char ) * MAX_BOARD_SIZE * MAX_BOARD_SIZE);
    printf("\n");
    printf("%lf\n", alphaBeta(tempBoard, scoreBoard, 2, -1000000, 1000000, true, 'B', 'W', n));
    moveFlip(board, n, bestMove[0] + 'a', bestMove[1] + 'a', colour);
    printf("Computer places %c at %c%c.\n", colour, bestMove[0] + 'a', bestMove[1] + 'a');
}

void reduceMove(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n, char colour, int* minCase)
{
    int i, j;
    int temp[3];
    char tempBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
    memcpy(tempBoard, board, sizeof( char ) * MAX_BOARD_SIZE * MAX_BOARD_SIZE);

    char opColour;
    if( colour == 'B' )
        opColour = 'W';
    else if( colour == 'W' )
        opColour = 'B';

    for( i = 0; i < n; i++ )
    {
        for( j = 0; j < n; j++ )
        {
            if( legalCases(tempBoard, i + 'a', j + 'a', colour, n) > 0 )
            {
                moveFlip(tempBoard, n, i + 'a', j + 'a', colour);
                temp[2] = availableMoves(tempBoard, n, opColour, NULL, false);
                //printf("%d\n",temp[2]);
                temp[0] = i;
                temp[1] = j;
                memcpy(tempBoard, board, sizeof( char ) * MAX_BOARD_SIZE * MAX_BOARD_SIZE);
                if( temp[2] < minCase[2] )
                {
                    *minCase = temp[0];
                    *( minCase + 1 ) = temp[1];
                    *( minCase + 2 ) = temp[2];
                }
            }
        }
    }
}

bool checkWin(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n, char colour)
{
    int i, j, counterB = 0, counterW = 0, result = 0;
    for( i = 0; i < n; i++ )
    {
        for( j = 0; j < n; j++ )
        {
            result = result + legalCases(board, i + 'a', j + 'a', colour, n);
            if( board[i][j] == 'B' )
                counterB++;
            else if( board[i][j] == 'W' )
                counterW++;
        }
    }
    if( counterB + counterW == n * n )//board full
    {
        if( counterB == counterW )
            printf("Draw!\n");
        else if( counterB > counterW )
            printf("B player wins.\n");
        else if( counterW > counterB )
            printf("W player wins.\n");
        exit(0);
    }
    else if( result == 0 )//no valid move
    {
        printf("%c player has no valid move.\n", colour);
        return false;
    }
    else
        return true;
}

double gameStage(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n)
{
    double maxCount = n * n;
    int i, j, tempCount = 0;
    for( i = 0; i < n; i++ )
    {
        for( j = 0; j < n; j++ )
        {
            if( board[i][j] != 'U' )
                tempCount++;
        }
    }
    return tempCount / maxCount;
}


bool cornerCase(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n, char row, char col, char colour)
{
    //corner [a][a] [a][n-1] [n-1][a] [n-1][n-1]
    if(( row == 'a' && col == 'a' ) || ( row == 'a' && col == 'a' + n - 1 ) || ( row == 'a' + n - 1 && col == 'a' ) || ( row == 'a' + n - 1 && col == 'a' + n - 1 ))
        return true;
    else
        return false;
}

int availableMoves(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n, char colour, int moveList[676][2], bool outputList )
{
    int i, j, k, counter = 0;
    for( i = 0; i < n; i++ )
    {
        for( j = 0; j < n; j++ )
        {
            if( legalCases(board, i + 'a', j + 'a', colour, n) > 0 )
            {
                if( outputList )
                {
                    moveList[k][0] = i;
                    moveList[k][1] = j;
                    k++;
                }
                counter++;
            }
        }
    }
    return counter;
}



void boardCount(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n, char colour, int* boardNum)//boardNum[0] is the colour's number;numberNum[1] is the opcolour
{
    int i, j, colourNum = 0, opcolourNum = 0;
    for( i = 0; i < n; i++ )
    {
        for( j = 0; j < n; j++ )
        {
            if( board[i][j] == colour )
            {
                colourNum++;
            }
            else if( board[i][j] == opColour(colour) )
            {
                opcolourNum++;
            }
        }
    }
    boardNum[0] = colourNum;
    boardNum[1] = opcolourNum;
}

void generateScoreboard(int scoreBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n)
{
    int i, j;
    if( n >= 8 )
    {
        for( i = 0; i < n; i++ )
        {
            for( j = 0; j < n; j++ )
            {
                scoreBoard[i][j] = A_SCORE_DEFAULT * A_SCORE_RATIO * ( n - 7 );
            }
        }
        for( i = 1; i < n - 1; i++ )
        {
            for( j = 1; j < n - 1; j++ )
            {
                scoreBoard[i][j] = E_SCORE_DEFAULT * E_SCORE_RATIO * ( n - 7 );
            }
        }
        scoreBoard[0][0] = CORNER_SCORE_DEFAULT * CORNER_SCORE_RATIO * ( n - 7 );//set score for coners
        scoreBoard[0][n - 1] = CORNER_SCORE_DEFAULT * CORNER_SCORE_RATIO * ( n - 7 );
        scoreBoard[n - 1][0] = CORNER_SCORE_DEFAULT * CORNER_SCORE_RATIO * ( n - 7 );
        scoreBoard[n - 1][n - 1] = CORNER_SCORE_DEFAULT * CORNER_SCORE_RATIO * ( n - 7 );

        scoreBoard[1][1] = X_SCORE_DEFAULT * X_SCORE_RATIO * ( n - 7 );//set score for X squares
        scoreBoard[1][n - 2] = X_SCORE_DEFAULT * X_SCORE_RATIO * ( n - 7 );
        scoreBoard[n - 2][1] = X_SCORE_DEFAULT * X_SCORE_RATIO * ( n - 7 );
        scoreBoard[n - 2][n - 2] = X_SCORE_DEFAULT * X_SCORE_RATIO * ( n - 7 );

        scoreBoard[0][1] = C_SCORE_DEFAULT * C_SCORE_RATIO * ( n - 7 );//set score for C squares
        scoreBoard[1][0] = C_SCORE_DEFAULT * C_SCORE_RATIO * ( n - 7 );
        scoreBoard[0][n - 2] = C_SCORE_DEFAULT * C_SCORE_RATIO * ( n - 7 );
        scoreBoard[1][n - 1] = C_SCORE_DEFAULT * C_SCORE_RATIO * ( n - 7 );
        scoreBoard[n - 2][0] = C_SCORE_DEFAULT * C_SCORE_RATIO * ( n - 7 );
        scoreBoard[n - 1][1] = C_SCORE_DEFAULT * C_SCORE_RATIO * ( n - 7 );
        scoreBoard[n - 2][n - 1] = C_SCORE_DEFAULT * C_SCORE_RATIO * ( n - 7 );
        scoreBoard[n - 1][n - 2] = C_SCORE_DEFAULT * C_SCORE_RATIO * ( n - 7 );

        scoreBoard[0][2] = B_SCORE_DEFAULT * B_SCORE_RATIO * ( n - 7 );//set score for B squares
        scoreBoard[2][0] = B_SCORE_DEFAULT * B_SCORE_RATIO * ( n - 7 );
        scoreBoard[0][n - 3] = B_SCORE_DEFAULT * B_SCORE_RATIO * ( n - 7 );
        scoreBoard[2][n - 1] = B_SCORE_DEFAULT * B_SCORE_RATIO * ( n - 7 );
        scoreBoard[n - 3][0] = B_SCORE_DEFAULT * B_SCORE_RATIO * ( n - 7 );
        scoreBoard[n - 1][2] = B_SCORE_DEFAULT * B_SCORE_RATIO * ( n - 7 );
        scoreBoard[n - 3][n - 1] = B_SCORE_DEFAULT * B_SCORE_RATIO * ( n - 7 );
        scoreBoard[n - 1][n - 3] = B_SCORE_DEFAULT * B_SCORE_RATIO * ( n - 7 );

        scoreBoard[1][2] = D_SCORE_DEFAULT * D_SCORE_RATIO * ( n - 7 );//set score for D squares
        scoreBoard[2][1] = D_SCORE_DEFAULT * D_SCORE_RATIO * ( n - 7 );
        scoreBoard[1][n - 3] = D_SCORE_DEFAULT * D_SCORE_RATIO * ( n - 7 );
        scoreBoard[2][n - 2] = D_SCORE_DEFAULT * D_SCORE_RATIO * ( n - 7 );
        scoreBoard[n - 3][1] = D_SCORE_DEFAULT * D_SCORE_RATIO * ( n - 7 );
        scoreBoard[n - 2][2] = D_SCORE_DEFAULT * D_SCORE_RATIO * ( n - 7 );
        scoreBoard[n - 3][n - 2] = D_SCORE_DEFAULT * D_SCORE_RATIO * ( n - 7 );
        scoreBoard[n - 2][n - 3] = D_SCORE_DEFAULT * D_SCORE_RATIO * ( n - 7 );

        for( i = 2; i < n - 2; i++ )//set score for common
        {
            for( j = 2; j < n - 2; j++ )
            {
                scoreBoard[i][j] = COMMON_SCORE_DEFAULT * COMMON_SCORE_RATIO * ( n - 7 );
            }
        }
        for( i = 3; i < n - 3; i++ )//set score for center
        {
            for( j = 3; j < n - 3; j++ )
            {
                scoreBoard[i][j] = CENTER_SCORE_DEFAULT * CENTER_SCORE_RATIO * ( n - 7 );
            }
        }
    }
    else if( n == 6 )
    {

    }
    else if( n == 4 )
    {

    }
    else
    {
        printf("Error input dimension!");
        exit(0);
    }
    /*
       int ii, jj, kk;
       printf("  ");
       for( ii = 0; ii < n; ii++ )
        printf("%c", 'a' + ii);
       printf("\n");
       for( jj = 0; jj < n; jj++ )
       {
        printf("%c ", 'a' + jj);
        for( kk = 0; kk < n; kk++ )
            printf("%d ", scoreBoard[jj][kk]);
        printf("\n");
       }
     */
}

double heuristicScoreevaluation(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int scoreBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n, char colour)
{
    int myPieces = 0, opPieces = 0, myFrontpieces = 0, opFrontpieces = 0, i, j, k, x, y;
    double p = 0, c = 0, l = 0, m = 0, f = 0, d = 0;

    char opColour;
    if( colour == 'W' )
        opColour = 'B';
    else if( colour == 'B' )
        opColour = 'W';

    //find the score for pieces,pieces position ,and front pieces
    for( i = 0; i < n; i++ )
        for( j = 0; j < n; j++ )
        {
            if( board[i][j] == colour )
            {
                d += scoreBoard[i][j];
                myPieces++;
            }
            else if( board[i][j] == opColour )
            {
                d -= scoreBoard[i][j];
                opPieces++;
            }
            if( board[i][j] != 'U' )
            {
                for( k = 0; k < n; k++ )
                {
                    x = i + DELTA[k][0];
                    y = j + DELTA[k][1];
                    if( x >= 0 && x < n && y >= 0 && y < n && board[x][y] == 'U' )
                    {
                        if( board[i][j] == colour )
                            myFrontpieces++;
                        else
                            opFrontpieces++;
                        break;
                    }
                }
            }
        }

    if( myPieces > opPieces )
        p = ( 100.0 * myPieces ) / ( myPieces + opPieces );
    else if( myPieces < opPieces )
        p = -( 100.0 * opPieces ) / ( myPieces + opPieces );
    else
        p = 0;

    if( myFrontpieces > opFrontpieces )
        f = -( 100.0 * myFrontpieces ) / ( myFrontpieces + opFrontpieces );
    else if( myFrontpieces < opFrontpieces )
        f = ( 100.0 * opFrontpieces ) / ( myFrontpieces + opFrontpieces );
    else
        f = 0;

    //corner score
    myPieces = 0;
    opPieces = 0;
    if( board[0][0] == colour )
        myPieces++;
    else if( board[0][0] == opColour )
        opPieces++;
    if( board[0][n - 1] == colour )
        myPieces++;
    else if( board[0][n - 1] == opColour )
        opPieces++;
    if( board[n - 1][0] == colour )
        myPieces++;
    else if( board[n - 1][0] == opColour )
        opPieces++;
    if( board[n - 1][n - 1] == colour )
        myPieces++;
    else if( board[n - 1][n - 1] == opColour )
        opPieces++;
    c = 25 * ( myPieces - opPieces );

    // Corner closeness
    myPieces = 0;
    opPieces = 0;
    if( board[0][0] == 'U' )
    {
        if( board[0][1] == colour )
            myPieces++;
        else if( board[0][1] == opColour )
            opPieces++;
        if( board[1][1] == colour )
            myPieces++;
        else if( board[1][1] == opColour )
            opPieces++;
        if( board[1][0] == colour )
            myPieces++;
        else if( board[1][0] == opColour )
            opPieces++;
    }
    if( board[0][n - 1] == 'U' )
    {
        if( board[0][n - 2] == colour )
            myPieces++;
        else if( board[0][n - 2] == opColour )
            opPieces++;
        if( board[1][n - 2] == colour )
            myPieces++;
        else if( board[1][n - 2] == opColour )
            opPieces++;
        if( board[1][n - 1] == colour )
            myPieces++;
        else if( board[1][n - 1] == opColour )
            opPieces++;
    }
    if( board[n - 1][0] == 'U' )
    {
        if( board[n - 1][1] == colour )
            myPieces++;
        else if( board[n - 1][1] == opColour )
            opPieces++;
        if( board[n - 2][1] == colour )
            myPieces++;
        else if( board[n - 2][1] == opColour )
            opPieces++;
        if( board[n - 2][0] == colour )
            myPieces++;
        else if( board[n - 2][0] == opColour )
            opPieces++;
    }
    if( board[n - 1][n - 1] == 'U' )
    {
        if( board[n - 2][n - 1] == colour )
            myPieces++;
        else if( board[n - 2][n - 1] == opColour )
            opPieces++;
        if( board[n - 2][n - 2] == colour )
            myPieces++;
        else if( board[n - 2][n - 2] == opColour )
            opPieces++;
        if( board[n - 1][n - 2] == colour )
            myPieces++;
        else if( board[n - 1][n - 2] == opColour )
            opPieces++;
    }
    l = -12.5 * ( myPieces - opPieces );

    // Mobility
    myPieces = availableMoves(board, n, colour, NULL, false);
    opPieces = availableMoves(board, n, colour, NULL, false);
    if( myPieces > opPieces )
        m = ( 100.0 * myPieces ) / ( myPieces + opPieces );
    else if( myPieces < opPieces )
        m = -( 100.0 * opPieces ) / ( myPieces + opPieces );
    else
        m = 0;
    // final weighted score
    double score;
    score = ( 10 * p ) + ( 801.724 * c ) + ( 382.026 * l ) + ( 78.922 * m ) + ( 74.396 * f ) + ( 10 * d );
    return score;
}

double alphaBeta(char tempBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int scoreBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int depth, double alpha, double beta, bool mySelf, char colour, char opColour, int n)
{
    double bestValue;
    if( depth == 0 )
    {
        bestValue = heuristicScoreevaluation(tempBoard, scoreBoard, n, colour);
    }
    else if( mySelf )
    {
        int i, j = 0;
        double childValue;
        bestValue = alpha;
        int movePosition[8][3];
        int moveList[676][2] = {0};
        for( i = 0; i < 676; i++ )
        {
            for( j = 0; j < 2; j++ )
            {
                moveList[i][j] = -1;
            }
        }
        for( i = 0; i < availableMoves(tempBoard, n, colour, moveList, true); i++ )
        {
            if( moveList[i][0] >= 0 && moveList[i][1] >= 0 )
            {
                flip(tempBoard, movePosition, n, moveList[i][0] + 'a', moveList[i][1] + 'a', colour);
                childValue = alphaBeta(tempBoard, scoreBoard, depth - 1, bestValue, beta, false, colour, opColour, n);
                bestValue = fmax(bestValue, childValue);
                unflip(tempBoard, movePosition, n, moveList[i][0] + 'a', moveList[i][1] + 'a', colour);
            }
            if( beta <= bestValue )
            {
                break;
            }
        }

    }
    else
    {
        int i, j = 0;
        double childValue;
        bestValue = beta;
        int movePosition[8][3] = {0};
        int moveList[676][2] = {0};
        for( i = 0; i < 676; i++ )
        {
            for( j = 0; j < 2; j++ )
            {
                moveList[i][j] = -1;
            }
        }
        for( i = 0; i < availableMoves(tempBoard, n, opColour, moveList, true); i++ )
        {
            if( moveList[i][0] >= 0 && moveList[i][1] >= 0 )
            {
                flip(tempBoard, movePosition, n, moveList[i][0] + 'a', moveList[i][1] + 'a', opColour);
                childValue = alphaBeta(tempBoard, scoreBoard, depth - 1, alpha, bestValue, true, colour, opColour, n);
                bestValue = fmin(bestValue, childValue);
                unflip(tempBoard, movePosition, n, moveList[i][0] + 'a', moveList[i][1] + 'a', opColour);
            }
            if( alpha >= bestValue )
            {
                break;
            }
        }
    }
    return bestValue;
}
