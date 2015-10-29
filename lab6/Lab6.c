#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static const int MAX_BOARD_SIZE=26;

void boardInitialize(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n);
void printBoard(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n);
void boardConfig(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n);
void legalMove(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n);
bool legalCases(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], char i, char j, char bwType, int n);
void makeMove(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n);
bool positionInBounds(int N,char row, char col);
bool checkLegalInDirection(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int N, char row, char col, char colour, int deltaRow, int deltaCol);
int intMax(int a, int b);

int main(void)
{
    char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
    int boardSize;
    printf("Enter the board dimension: ");
    scanf("%d",&boardSize);
    boardInitialize(board,boardSize);    
    boardConfig(board,boardSize);
    legalMove(board,boardSize);
    makeMove(board,boardSize);
    return 0;
}

void boardInitialize(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n)
{
    int i,j,k,m;
    for(i=0;i<MAX_BOARD_SIZE;i++)
    {
        for(j=0;j<MAX_BOARD_SIZE;j++)
            board[i][j]='\0';
    }
    for(k=0;k<n;k++)
    {
        for(m=0;m<n;m++)
            board[k][m]='U';
    }
    board[(n/2)-1][(n/2-1)]='W';
    board[(n/2)-1][n/2]='B';
    board[n/2][(n/2)-1]='B';
    board[n/2][n/2]='W';
    printBoard(board,n);
}

void printBoard(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n)
{
    int i,j,k;
    printf("  ");
    for(i=0;i<n;i++)
        printf("%c", 'a'+i);
    printf("\n");
    for(j=0;j<n;j++)
    {
        printf("%c ",'a'+j);
        for(k=0;k<n;k++)
            printf("%c",board[j][k]);
        printf("\n");
    }
    
}
void boardConfig(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n)
{
    int i,j;
    char inputLine[3]={0};
    bool inputState=true;
    printf("Enter board configuration: \n");
    while(inputState==true)
    {
        for(i=0;i<3;i++)
            scanf(" %c", &inputLine[i]);    
        if((inputLine[0]=='!')&&(inputLine[1]=='!')&&(inputLine[2]=='!'))
            inputState=false;
        else
            board[inputLine[1]-'a'][inputLine[2]-'a']=inputLine[0];
    }   
    printBoard(board,n);
}

void legalMove(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n)
{
    char a,b,c,d;
    printf("Available moves for W: \n");
    for(a='a';a<'a'+n;a++)
    {
        for(b='a';b<'a'+n;b++)
        {
            if(legalCases(board,a,b,'W',n))
                printf("%c%c\n", a,b);
        }
    }    
    printf("Available moves for B: \n");
    for(c='a';c<'a'+n;c++)
    {
        for(d='a';d<'a'+n;d++)
       {
            if(legalCases(board,c,d,'B',n))
                printf("%c%c\n", c,d);
       }
    }    
}

bool legalCases(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], char row, char col , char bwType, int n)
{
    bool a,b,c,d,e,f,g,h;
    a=checkLegalInDirection(board,n,row,col,bwType,-1,-1);
    b=checkLegalInDirection(board,n,row,col,bwType,-1,0);
    c=checkLegalInDirection(board,n,row,col,bwType,-1,1);
    d=checkLegalInDirection(board,n,row,col,bwType,0,-1);
    e=checkLegalInDirection(board,n,row,col,bwType,0,1);
    f=checkLegalInDirection(board,n,row,col,bwType,1,-1);
    g=checkLegalInDirection(board,n,row,col,bwType,1,0);
    h=checkLegalInDirection(board,n,row,col,bwType,1,1);
    if(a||b||c||d||e||f||g||h)//if any case match, the location is legal
        return true;
    else
        return false;
}

bool positionInBounds(int N, char row, char col)
{
    if((row>='a')&&(row<='a'+N-1)&&(col>='a')&&(col<='a'+N-1))
        return true;
    else
        return false;
}


bool checkLegalInDirection(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int N, char row, char col, char colour, int deltaRow, int deltaCol)
{
    int rowNum=row-'a';
    int colNum=col-'a';
    if(board[rowNum][colNum]!='U')
        return false;
    else
    {
        char bwType;
        if(colour=='B')
            bwType='W';
        else if(colour=='W')
            bwType='B';
        int i,maxPiece=0,counter=0;
        if(deltaRow<0 && deltaCol<0)
            maxPiece=intMin(rowNum,colNum);
        else if(deltaRow<0 && deltaCol==0)
            maxPiece=rowNum;
        else if(deltaRow<0 && deltaCol>0)
            maxPiece=intMin(rowNum,N-colNum-1);
        else if(deltaRow==0 && deltaCol<0)
            maxPiece=colNum;
        else if(deltaRow==0 && deltaCol>0)
            maxPiece=N-colNum-1;
        else if(deltaRow>0 && deltaCol<0)
            maxPiece=intMin(N-rowNum-1,colNum);
        else if(deltaRow>0 && deltaCol==0)
            maxPiece=N-rowNum-1;
        else if(deltaRow>0 && deltaCol>0)
            maxPiece=intMin(N-rowNum-1,N-colNum-1);
        if (maxPiece==0)
            return false;
        for(i=0;i<maxPiece;i++)
        {
            if(board[rowNum+deltaRow][colNum+deltaCol]==bwType)
            {
                rowNum=rowNum+deltaRow;
                colNum=colNum+deltaCol;
                counter++;
            }
            else if(board[rowNum+deltaRow][colNum+deltaCol]==colour && counter<1)
                return false;
            else if(board[rowNum+deltaRow][colNum+deltaCol]==colour && counter>=1)
                return true;
            else if(board[rowNum+deltaRow][colNum+deltaCol]=='U')
                return false;
        } 
        if(board[rowNum][colNum]==bwType && counter>=1)
            return false;       
    }    
}

void makeMove(char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n)
{
    int i;
    bool caseState=false;
    char userInput[3];
    printf("Enter a move: \n");
    for(i=0;i<3;i++)
        scanf(" %c", &userInput[i]);
    if(positionInBounds(n, userInput[1], userInput[2]))
    {
        if(legalCases(board, userInput[1], userInput[2], userInput[0], n))
            caseState=true;
        else
            caseState=false;
    }
    else
        caseState=false;
    if(caseState)
    {
        printf("Valid move.\n");
        board[userInput[1]-'a'][userInput[2]-'a']=userInput[0];
    }
    else
        printf("Invalid move.\n");
    printBoard(board, n);
}

int intMin(int a, int b)//takes two int as input and output MIN
{
    if(a>b)
        return b;
    else
        return a;
}
