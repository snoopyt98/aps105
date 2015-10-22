#include <stdio.h>
#include <stdlib.h>

void findDNA(char *setDNA, char *patternDNA, int *resultPtr);
int findLength(char *inputArrPtr, int *inputIntPtr);

int main(void)
{
    char DNA[] = {'A', 'G', 'C', 'G', 'G', 'G', 'A', 'C', 'C', 'G', 'T', 'C', 
          'C', 'C', 'G', 'A', 'C', 'A', 'T', 'T', 'G', 'A', 'T', 'G', 
          'A', 'A', 'G', 'G', 'G', 'T', 'C', 'A', 'T', 'A', 'G', 'A', 
          'C', 'C', 'C', 'A', 'A', 'T', 'A', 'C', 'G', 'C', 'C', 'A', 
          'C', 'C', 'A', 'C', 'C', 'C', 'C', 'A', 'A', 'G', 'T', 'T', 
          'T', 'T', 'C', 'C', 'T', 'G', 'T', 'G', 'T', 'C', 'T', 'T', 
          'C', 'C', 'A', 'T', 'T', 'G', 'A', 'G', 'T', 'A', 'G', 'A', 
          'T', 'T', 'G', 'A', 'C', 'A', 'C', 'T', 'C', 'C', 'C', 'A', 
          'G', 'A', 'T', 'G', '\0'};       
    int lengthDNA,i,j;
    int result[100];
    int *resultPtr;
    resultPtr=&result[0];
    for(;;)
    {
        printf("Enter length of DNA sequence to match: ");
        scanf("%d",&lengthDNA);
        if(lengthDNA<=0)
        {
            printf("Goodbye");
            return 0;//exit
        }
        char inputPattern[lengthDNA];
        printf("Enter %d characters (one of AGTC*) as a search sequence: ",lengthDNA);
        for(i=0;i<lengthDNA;i++)
        {
            scanf("%c",&inputPattern[i]);
        }
        inputPattern[i+1]='\0';
        findDNA(&DNA[0],&inputPattern[0],resultPtr);
        for(j=0;j<findLength(0,&result[0]);j++)
        {
            printf("Match of search sequence found at element %d",result[j]);
        }
    }
}

void findDNA(char *setDNAPtr, char *patternDNAPtr, int *resultPtr)
{
    int i=0,j=0,k=0,m=0,n=0;
    int answer[n];
    for(i=0;i<findLength(setDNAPtr,0);i++)
    {
        if(j==findLength(patternDNAPtr,0))
        {   
            n++;
            answer[k]=i-findLength(patternDNAPtr,0);
            k++;
            j=0;
        }
        if(*(patternDNAPtr+j)==*(setDNAPtr+i)||*(patternDNAPtr+j)=='*')
        {
            j++;
        }
        else
        {
            j=0;
        }
    }
    answer[k]='\0';    
    for(m=0;m<findLength(0,&answer[0]);m++)
    {
        *(resultPtr+m)=answer[m];
    }
}

int findLength(char *inputArrPtr, int *inputIntPtr)
{
    if(inputArrPtr!=0&&inputIntPtr==0)
    {
        int i=0;
        while(*(inputArrPtr+i)!='\0')
        {
            i++;
        }
        return i;    
    }
    if(inputArrPtr==0&&inputIntPtr!=0)
    {
        int j=0;
        while(*(inputIntPtr+j)!='\0')
            j++;
    }
}
