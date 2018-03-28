#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<conio.h>
#include<windows.h>

void firstFiltering(char rawInput[], char filterInput[]);
int secondFiltering(char filterInput[], char separatedStr[][100], char originalStr[][100]);
int findStrType(char input[]);
void displayResult(int strCount,char originalStr[][100],int strTypeCnt[],int strTypeList[]);
int isOperator(char c);
int isFunction(char input[]);
int isValidIden(char input[]);

int main()
{
	char rawInput[1005]={},filterInput[1000]={},separatedStr[100][100]={},originalStr[100][100]={};
	int i,strType,strCount=0,exitMode=0,strTypeList[100]={},strTypeCnt[5]={};
	
	do
	{
		//user interface + getdata
		system("cls");
		printf("\n\nString filtering program\n\n");
		printf("Enter string to check (max 1000 characters), enter \"end\" or \"exit\" to exit the program.\n");
		printf("Input> ");
		gets(rawInput);
		
		//Add spaces
		firstFiltering(rawInput,filterInput);
		printf("Spaces added: %s\n",filterInput);
		
		//String Token + Count
		strCount=secondFiltering(filterInput,separatedStr,originalStr);
		
		//check for exit keywords
		if(strCount==1&&(strcmp(separatedStr[0],"exit")==0||strcmp(separatedStr[0],"end")==0))
			exitMode=1;
		
		if(exitMode==0)
		{
			//Find type of string
			for(i=0;i<strCount;i++)
			{
				strType=findStrType(separatedStr[i]);
				strTypeCnt[strType]++;
				strTypeList[i]=strType;
			}
			
			//Print output
			displayResult(strCount,originalStr,strTypeCnt,strTypeList);
		}
		
		//clear memory
		memset(rawInput,0,sizeof rawInput);
		memset(filterInput,0,sizeof filterInput);
		memset(separatedStr,0,sizeof separatedStr);
		memset(originalStr,0,sizeof originalStr);
		memset(strTypeCnt,0,sizeof strTypeCnt);
		memset(strTypeList,0,sizeof strTypeList);
		
	} while(exitMode==0);
	
	system("cls");
	printf("End program.");
	return 0;
}

void firstFiltering(char rawInput[], char filterInput[])
{
	int current=0,i;

	//separate operators with spaces
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
}

int secondFiltering(char filterInput[], char separatedStr[][100], char originalStr[][100])
{
	int i,count=0;
	char *token;
	
	//separate with spaces
	token=strtok(filterInput," ");
	while(token!=NULL)
	{
		if(token!=NULL)
		{
			strcpy(separatedStr[count],token); //for checking
			strcpy(originalStr[count],token);  //for displaying
			
			//convert separatedStr to lowercase
			for(i=0;i<strlen(separatedStr[count]);i++)
				separatedStr[count][i]=tolower(separatedStr[count][i]);
			
			count++;
		}
		token=strtok(NULL," ");
	}
	
	return count;
}

int findStrType(char input[])
{
	char *err;
	
	strtod(input,&err); //check for valid number
	
	if(isOperator(input[0])==1)	//operator
		return 0;
	else if(*err==0) //number
		return 1;
	else if(isFunction(input)==1) //function name
		return 2;
	else if(isValidIden(input)==1) //identifier
		return 3;
	else	//error
		return 4;
}

void displayResult(int strCount,char originalStr[][100],int strTypeCnt[],int strTypeList[])
{
	int i,j;
	char display[5][15]={"operators","numbers","functions","identifiers","errors"};
	
	printf("\nString count: %d\n",strCount);
	
	for(i=0;i<5;i++)
	{
		printf("Found %d %s: ",strTypeCnt[i],display[i]);
		for(j=0;j<strCount;j++)
			if(strTypeList[j]==i)
				printf("%s ",originalStr[j]);
		printf("\n");
	}
	
	printf("\nPress any key to continue...");
	getch();
}

int isOperator(char c)
{
	if(c=='+'||c=='-'||c=='*'||c=='/'||c=='('||c==')'||c=='^')
		return 1;
	else
		return 0;
}

int isFunction(char input[])
{
	char validNames[10][5]={"sin","cos","tan","asin","acos","atan","sqrt","log","exp","pow"};
	int i,returnVal=0;
	
	for(i=0;i<10;i++)
		if(strcmp(input,validNames[i])==0)
			returnVal=1;
	
	return returnVal;
}

int isValidIden(char input[])
{
	int i,returnVal=1;
	
	if(!isalpha(input[0])&&input[0]!='_')
		returnVal=0;

	for(i=1;i<strlen(input);i++)
	{
		if(!isalnum(input[i])&&input[i]!='_')
			returnVal=0;
	}
	return returnVal;
}