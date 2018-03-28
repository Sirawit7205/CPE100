#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<conio.h>
#include<windows.h>

void filtering(char rawInput[], char filterInput[]);
int firstFiltering(char rawInput[], char firstFilter[][100]);
int secondFiltering(int count, char firstFilter[][100], char secondFilter[][100]);
int isOperator(char c);

int main()
{
	char rawInput[1005]={},filterInput[1000]={};
	char firstFilter[100][100]={}, secondFilter[100][100]={};
	int firstCount,secondCount;
	
	//user interface + getdata
	system("cls");
	printf("\n\nString filtering program\n\n");
	printf("Enter string to check (max 1000 characters), enter \"end\" or \"exit\" to exit the program.\n");
	printf("Input> ");
	
	fgets(rawInput,1000,stdin);
	filtering(rawInput,filterInput);
	//firstCount=firstFiltering(rawInput,firstFilter);
	//secondCount=secondFiltering(firstCount,firstFilter,secondFilter);
	
	return 0;
}

void filtering(char rawInput[], char filterInput[])
{
	int current=0,i;
	
	for(i=0;i<strlen(rawInput);i++)
	{
		if(isOperator(rawInput[i]))
		{
			filterInput[current]=' ';
			filterInput[current+1]=rawInput[i];
			filterInput[current+2]=' ';
			current+=3;
		}
		else
		{
			filterInput[current]=rawInput[i];
			current++;
		}
	}
	printf("FILTERED: %s\n",filterInput);
}

int firstFiltering(char rawInput[], char firstFilter[][100])
{
	int count=0,i;
	char *token;
	
	//convert all to lowercase
	for(i=0;i<strlen(rawInput);i++)
		rawInput[i]=tolower(rawInput[i]);
	
	//separate with spaces
	token=strtok(rawInput," \n");
	while(token!=NULL)
	{
		if(token!=NULL)
		{
			strcpy(firstFilter[count],token);
			count++;
		}
		token=strtok(NULL," \n");
	}
	
	return count;
}

int secondFiltering(int firstCount, char firstFilter[][100], char secondFilter[][100])
{
	int count=0,countInLine=0,i,j;
	char c;
	
	//for each space separated strings
	for(i=0;i<firstCount;i++)
	{
		countInLine=0;
		
		//for each character
		for(j=0;j<strlen(firstFilter[i]);j++)
		{
			//separate with operators
			c=firstFilter[i][j];
			if(isOperator(c))
			{
				if(j>0&&!isOperator(firstFilter[i][j-1]))
					count++;
				countInLine=0;
				secondFilter[count][countInLine]=c;
				count++;
			}
			else
			{
				secondFilter[count][countInLine]=c;
				countInLine++;
			}
			
			if(!isOperator(c)&&j==strlen(firstFilter[i])-1)
				count++;
			
		}
	}
	
	printf("%d\n",count);
	for(i=0;i<count;i++)
	{
		printf("%s\n",secondFilter[i]);
	}
	
	return count;
}

int isOperator(char c)
{
	if(c=='+'||c=='-'||c=='*'||c=='/'||c=='('||c==')'||c=='^')
		return 1;
	else
		return 0;
}