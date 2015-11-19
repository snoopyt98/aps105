#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include <sys/resource.h>

int MAX_DEPTH;//for minimax

static const int END_AHEAD=8;//end 8 moves
static const int MAX_BOARD_SIZE = 26;
static const int DELTA[8][2] = {-1, -1, -1, 0, -1, 1, 0, -1, 0, 1, 1, -1, 1, 0, 1, 1};

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
char Colour(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n);
void gameProcess(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n, char colour);
void Move(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n, char colour);
bool checkWin(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n, char colour);
int gameStage(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n);
int availableMoves(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n, char colour, int moveList[676][2], bool outputList);
void generateScoreboard(int scoreBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n);
double heuristicScoreevaluation(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int scoreBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n, char colour);
double alphaBeta(char tempBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int scoreBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int depth, double alpha, double beta, bool mySelf, char colour, char opColour, int n, char bestMove[2]);
double gameWin(char tempBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n, char colour);
bool gameEnd(char tempBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n, char colour);
double endMove(char tempBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int depth, double alpha, double beta, bool mySelf, char colour, char opColour, int n, char bestMove[2]);
int endEvaluation(char tempBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE],int n,char colour);

int main(void)
{
    char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
    int boardSize;
    printf("Enter the board dimension: ");
    scanf("%d", &boardSize);
    boardInitialize(board, boardSize);
    //generateScoreboard(scoreBoard, boardSize); //test
    gameProcess(board, boardSize, Colour(board, boardSize));
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

char Colour(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n)
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
    //user make move
    int i;
    bool caseState = false;
    char userInput[3];
    printf("Enter move for colour %c (RowCol): ", colour);
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
    //place down move
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
    //flip tempBoard
    char opColour;
    if( colour == 'B' )
        opColour = 'W';
    else if( colour == 'W' )
        opColour = 'B';
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
            if( tempBoard[rowTemp + DELTA[i][0] - 'a'][colTemp + DELTA[i][1] - 'a'] == opColour )
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
    //undo flip
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

void computerMove(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n, char colour)//part1 function
{
    int i, j;
    int temp[3];
    int bestMove[3] = {0};
    for( i = 0; i < n; i++ )
    {
        for( j = 0; j < n; j++ )
        {
            temp[0] = i;
            temp[1] = j;
            temp[2] = legalCases(board, i + 'a', j + 'a', colour, n);
            if( temp[2] > bestMove[2] )
            {
                bestMove[0] = temp[0];
                bestMove[1] = temp[1];
                bestMove[2] = temp[2];
            }
        }
    }
    moveFlip(board, n, bestMove[0] + 'a', bestMove[1] + 'a', colour);
    printf("Part1 places %c at %c%c.\n", colour, bestMove[0] + 'a', bestMove[1] + 'a');
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
                Move(board, n, 'B');
                printBoard(board, n);
            }
            if( checkWin(board, n, 'W') == true )
            {
                //Move(board, n, 'W');
                computerMove(board, n, 'W');
                //userMove(board, n, 'W');
                printBoard(board, n);
            }
        }
        else if( colour == 'W' )
        {
            if( checkWin(board, n, 'B') == true )
            {
                //Move(board, n, 'B');
                computerMove(board, n, 'B');
                //userMove(board, n, 'B');
                printBoard(board, n);
            }
            if( checkWin(board, n, 'W') == true )
            {
                Move(board, n, 'W');
                printBoard(board, n);
            }
        }
    }
}

void Move(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n, char colour)
{
    int scoreBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
    char bestMove[2] = {0};
    char tempBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
    if(n==4)
        MAX_DEPTH=12;
    else if(n==6)
        MAX_DEPTH=6;
    else if(n>=8&&n<=10)
        MAX_DEPTH=4;
    else
        MAX_DEPTH=2;
    generateScoreboard(scoreBoard, n);
    memcpy(tempBoard, board, sizeof( char ) * MAX_BOARD_SIZE * MAX_BOARD_SIZE);
    struct rusage usage; // a structure to hold "resource usage" (including time)
    struct timeval start, end; // will hold the start and end times
    getrusage(RUSAGE_SELF, &usage);
    start = usage.ru_utime;
    double time_start = start.tv_sec + start.tv_usec / 1000000.0; // in seconds
    if(gameStage(board,n)<=END_AHEAD)//if in last 10 steps call endMove
    {
        endMove(tempBoard,MAX_DEPTH, -INFINITY, INFINITY, true, colour, opColour(colour), n, bestMove);
    }
    else
    {
        alphaBeta(tempBoard, scoreBoard, MAX_DEPTH, -INFINITY, INFINITY, true, colour, opColour(colour), n, bestMove);
    }
    getrusage(RUSAGE_SELF, &usage);
    end = usage.ru_utime;
    double time_end = end.tv_sec + end.tv_usec / 1000000.0; // in seconds
    double total_time = time_end - time_start;
// total_time now holds the time (in seconds) it takes to run your code
    moveFlip(board, n, bestMove[0], bestMove[1], colour);
    printf("Computer places %c at %c%c.\n", colour, bestMove[0], bestMove[1]);
}

bool checkWin(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n, char colour)// check for win and pass
{
    int i, j, counterB = 0, counterW = 0, resultC = 0, resultO = 0;
    for( i = 0; i < n; i++ )
    {
        for( j = 0; j < n; j++ )
        {
            resultC = resultC + legalCases(board, i + 'a', j + 'a', colour, n);
            resultO = resultO + legalCases(board, i + 'a', j + 'a', opColour(colour), n);
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
    else if( resultC == 0 && resultO == 0 )
    {
        if( counterB == counterW )
            printf("Draw!\n");
        else if( counterB > counterW )
            printf("B player wins.\n");
        else if( counterW > counterB )
            printf("W player wins.\n");
        exit(0);
    }
    else if( resultC == 0 )//no valid move
    {
        printf("%c player has no valid move.\n", colour);
        return false;
    }
    else
        return true;
}

int gameStage(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n)//check game stage
{
    int maxCount = n * n;
    int i, j, tempCount = 0;
    for( i = 0; i < n; i++ )
    {
        for( j = 0; j < n; j++ )
        {
            if( board[i][j] != 'U' )
                tempCount++;
        }
    }
    return maxCount-tempCount;
}

int availableMoves(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n, char colour, int moveList[676][2], bool outputList )
{
    //generate moveList if outputList=true
    int i, j, k = 0, counter = 0;
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

void generateScoreboard(int scoreBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n)//generate score board for n>=8
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
        p = ( 40.0 * myPieces ) / ( myPieces + opPieces );
    else if( myPieces < opPieces )
        p = -( 40.0 * opPieces ) / ( myPieces + opPieces );
    else
        p = 0;

    if( n == 4 )
    {
        return myPieces;
    }

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
    opPieces = availableMoves(board, n, opColour, NULL, false);
    if( myPieces > opPieces )
        m = ( 100.0 * myPieces ) / ( myPieces + opPieces );
    else if( myPieces < opPieces )
        m = -( 100.0 * opPieces ) / ( myPieces + opPieces );
    else
        m = 0;
    // final weighted score
    double score;
    if(n==6)
    {
        score = ( 40 * p ) + ( 801.724 * c) + ( 382.026 * l ) + ( 78.922 * m) + ( 74.396 * f) + ( 10 * d);
        return score;
    }
    score = ( 30 * p *(n-7)) + ( 801.724 * c *(n-7)) + ( 382.026 * l *(n-7)) + (78.922 * m) + ( 74.396 * f/(n-7) ) + ( 10 * d/((n-7)));
    return score;
}

double alphaBeta(char tempBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int scoreBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int depth, double alpha, double beta, bool mySelf, char colour, char opColour, int n, char bestMove[2])
{
    double bestValue;
    if ( gameEnd(tempBoard, n, colour) )//game over conditions
    {
        bestValue = gameWin(tempBoard, n, colour);
    }
    else if( depth == 0 )//reach end node
    {
        bestValue = heuristicScoreevaluation(tempBoard, scoreBoard, n, colour);//find score
    }
    else if( mySelf )
    {
        int i, j = 0;
        double bestScore = -INFINITY;
        double childValue;
        bestValue = alpha;
        int movePosition[8][3] = {0};
        int moveList[676][2] = {0};
        j = availableMoves(tempBoard, n, colour, moveList, true);
        if( j == 0 )
        {
            childValue = alphaBeta(tempBoard, scoreBoard, depth - 1, bestValue, beta, false, colour, opColour, n, bestMove);
            bestValue = fmax(bestValue, childValue);
        }
        else
        {

            for( i = 0; i < j; i++ )
            {
                flip(tempBoard, movePosition, n, moveList[i][0] + 'a', moveList[i][1] + 'a', colour);
                childValue = alphaBeta(tempBoard, scoreBoard, depth - 1, bestValue, beta, false, colour, opColour, n, bestMove);
                bestValue = fmax(bestValue, childValue);
                unflip(tempBoard, movePosition, n, moveList[i][0] + 'a', moveList[i][1] + 'a', colour);
                if( depth == MAX_DEPTH )//first generation nodes
                {
                    //printf("availableMoves update: %c%c %lf\n", moveList[i][0] + 'a', moveList[i][1] + 'a', bestValue);
                    if( bestValue > bestScore )//save best move
                    {
                        bestScore = bestValue;
                        bestMove[0] = moveList[i][0] + 'a';
                        bestMove[1] = moveList[i][1] + 'a';
                        //printf("Best move update: %c%c %lf\n", bestMove[0], bestMove[1], bestScore);
                    }
                    if(bestScore==-INFINITY)//make the first possible move if lost
                    {
                        bestMove[0]=moveList[0][0] + 'a';
                        bestMove[1]=moveList[0][1] + 'a';
                    }
                }
                if( beta <= bestValue )//pruning
                {
                    break;
                }
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
        j = availableMoves(tempBoard, n, opColour, moveList, true);
        if( j == 0 )
        {
            childValue = alphaBeta(tempBoard, scoreBoard, depth - 1, alpha, bestValue, true, colour, opColour, n, bestMove);
            bestValue = fmin(bestValue, childValue);
        }
        else
        {
            for( i = 0; i < j; i++ )
            {
                flip(tempBoard, movePosition, n, moveList[i][0] + 'a', moveList[i][1] + 'a', opColour);
                childValue = alphaBeta(tempBoard, scoreBoard, depth - 1, alpha, bestValue, true, colour, opColour, n, bestMove);
                bestValue = fmin(bestValue, childValue);
                unflip(tempBoard, movePosition, n, moveList[i][0] + 'a', moveList[i][1] + 'a', opColour);
                if( alpha >= bestValue )//pruning
                {
                    break;
                }
            }
        }
    }
    return bestValue;
}

double gameWin(char tempBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n, char colour)//report win or loss
{
    char opColour;
    if( colour == 'W' )
        opColour = 'B';
    else if( colour == 'B' )
        opColour = 'W';
    int i, j, counterB = 0, counterW = 0, resultC = 0, resultO = 0;
    for( i = 0; i < n; i++ )
    {
        for( j = 0; j < n; j++ )
        {
            resultC = resultC + legalCases(tempBoard, i + 'a', j + 'a', colour, n);
            resultO = resultO + legalCases(tempBoard, i + 'a', j + 'a', opColour, n);
            if( tempBoard[i][j] == 'B' )
                counterB++;
            else if( tempBoard[i][j] == 'W' )
                counterW++;
        }
    }
    if( counterB + counterW == n * n )//board full
    {
        if( counterB == counterW )
            return -INFINITY;
        else if( counterB > counterW )
        {
            if( colour == 'B' )
                return INFINITY;
        }
        else if( counterW > counterB )
        {
            if( colour == 'W' )
                return INFINITY;
        }
        return -INFINITY;
    }
    else if( resultC == 0 && resultO == 0 )
    {
        if( counterB == counterW )
            return -INFINITY;
        else if( counterB > counterW )
        {
            if( colour == 'B' )
                return INFINITY;
        }
        else if( counterW > counterB )
        {
            if( colour == 'W' )
                return INFINITY;
        }
        printf("-INFINITY");
        return -INFINITY;
    }
}

bool gameEnd(char tempBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n, char colour)//find end game node
{
    char opColour;
    if( colour == 'W' )
        opColour = 'B';
    else if( colour == 'B' )
        opColour = 'W';
    int i, j, counterB = 0, counterW = 0, resultC = 0, resultO = 0;
    for( i = 0; i < n; i++ )
    {
        for( j = 0; j < n; j++ )
        {
            resultC = resultC + legalCases(tempBoard, i + 'a', j + 'a', colour, n);
            resultO = resultO + legalCases(tempBoard, i + 'a', j + 'a', opColour, n);
            if( tempBoard[i][j] == 'B' )
                counterB++;
            else if( tempBoard[i][j] == 'W' )
                counterW++;
        }
    }
    if( counterB + counterW == n * n )//board full
        return true;
    else if( resultC == 0 && resultO == 0 )
        return true;
    else
        return false;
}

double endMove(char tempBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE],int depth, double alpha, double beta, bool mySelf, char colour, char opColour, int n, char bestMove[2])
{
    double bestValue;
    if ( gameEnd(tempBoard, n, colour) )
    {
        bestValue = endEvaluation(tempBoard,n,colour);
    }
    else if( mySelf )
    {
        int i, j = 0;
        double bestScore = -INFINITY;
        double childValue;
        bestValue = alpha;
        int movePosition[8][3] = {0};
        int moveList[676][2] = {0};
        j = availableMoves(tempBoard, n, colour, moveList, true);//generate moveList
        if( j == 0 )//if pass move
        {
            childValue = endMove(tempBoard,depth - 1, bestValue, beta, false, colour, opColour, n, bestMove);
            bestValue = fmax(bestValue, childValue);
        }
        else
        {

            for( i = 0; i < j; i++ )//go through the moveList
            {
                flip(tempBoard, movePosition, n, moveList[i][0] + 'a', moveList[i][1] + 'a', colour);
                childValue = endMove(tempBoard, depth - 1, bestValue, beta, false, colour, opColour, n, bestMove);
                bestValue = fmax(bestValue, childValue);
                unflip(tempBoard, movePosition, n, moveList[i][0] + 'a', moveList[i][1] + 'a', colour);
                if( depth == MAX_DEPTH )
                {
                    //printf("availableMoves update: %c%c %lf\n", moveList[i][0] + 'a', moveList[i][1] + 'a', bestValue);
                    if( bestValue > bestScore )
                    {
                        bestScore = bestValue;
                        bestMove[0] = moveList[i][0] + 'a';
                        bestMove[1] = moveList[i][1] + 'a';
                        //printf("Best move update: %c%c %lf\n", bestMove[0], bestMove[1], bestScore);
                    }
                    if(bestScore==-INFINITY)
                    {
                        bestMove[0]=moveList[0][0] + 'a';
                        bestMove[1]=moveList[0][1] + 'a';
                    }
                }
                if( beta <= bestValue )
                {
                    break;
                }
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
        j = availableMoves(tempBoard, n, opColour, moveList, true);
        if( j == 0 )
        {
            childValue = endMove(tempBoard,depth - 1, alpha, bestValue, true, colour, opColour, n, bestMove);
            bestValue = fmin(bestValue, childValue);
        }
        else
        {
            for( i = 0; i < j; i++ )
            {
                flip(tempBoard, movePosition, n, moveList[i][0] + 'a', moveList[i][1] + 'a', opColour);
                childValue = endMove(tempBoard,depth - 1, alpha, bestValue, true, colour, opColour, n, bestMove);
                bestValue = fmin(bestValue, childValue);
                unflip(tempBoard, movePosition, n, moveList[i][0] + 'a', moveList[i][1] + 'a', opColour);
                if( alpha >= bestValue )
                {
                    break;
                }
            }
        }
    }
    return bestValue;
}

int endEvaluation(char tempBoard[MAX_BOARD_SIZE][MAX_BOARD_SIZE],int n,char colour)//game evaluation
{
    int i,j,myPieces=0,opPieces=0;
    int score;
    char opColour;
    if( colour == 'W' )
        opColour = 'B';
    else if( colour == 'B' )
        opColour = 'W';
    for( i = 0; i < n; i++ )
        for( j = 0; j < n; j++ )
        {
            if( tempBoard[i][j] == colour )
            {
                myPieces++;
            }
            else if( tempBoard[i][j] == opColour )
            {
                opPieces++;
            }
        }
    if( myPieces > opPieces )
        score = ( 100.0 * myPieces ) / ( myPieces + opPieces );
    else if( myPieces < opPieces )
        score = -( 100.0 * opPieces ) / ( myPieces + opPieces );
    else
        score = 0;
    return score;
}
