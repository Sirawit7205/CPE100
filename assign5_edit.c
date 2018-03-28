#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<string.h>

//function prototypes
void initScreen();
int getMenuItem();
int getInt(int min, int max, int errorLine);
void clsRange(int xi, int yi, int xf, int yf);
void gotoXY(int x,int y);
void historyHandling(char history[][100], char appendMsg[], int* head, int* tail, int* size);
double fact(int n);
double fibo(int n, double fiboMemo[]);
double gcd(int x, int y);
double lcm(int x,int y);
double npr(int n, int r);
double ncr(int n, int r);

int main()
{
	int select,n,r,x,y,hIndex=0,tIndex=0,qsize=0;
	double returnVal;
	double fiboMemo[50]={};
	char history[20][100]={}, msgCache[100]={};

	initScreen(); //load UI
	getch();
	clsRange(1,1,52,6); //clear welcome message

	do
	{
		select=getMenuItem();
		clsRange(12,12,60,13); //clear commands view

		if(select == 1) //fact
		{
			gotoXY(7,12);
			printf("Fact");
			gotoXY(12,12);

			printf("Enter n (limit 12): ");
			n=getInt(0,12,0);

			returnVal = fact(n);
			strcpy(msgCache,""); //clear cache
			sprintf(msgCache,"%d! = %.0lf",n,returnVal); //formatting message

			clsRange(12,12,60,13);
			gotoXY(12,12);
			printf("%d! = %.0lf",n,returnVal);
			gotoXY(12,13);
			printf("Press any key to continue...");
			getch();

			historyHandling(history, msgCache, &hIndex, &tIndex, &qsize);
		}
		else if(select == 2) //fibo
		{
			gotoXY(7,12);
			printf("Fibo");
			gotoXY(12,12);

			printf("Enter n (limit 46): ");
			n=getInt(0,46,0);

			returnVal = fibo(n,fiboMemo);
			strcpy(msgCache,""); //clear cache
			sprintf(msgCache,"Fibo(%d) = %.0lf",n,returnVal); //formatting message

			clsRange(12,12,60,13);
			gotoXY(12,12);
			printf("Fibo(%d) = %.0lf",n,returnVal);
			gotoXY(12,13);
			printf("Press any key to continue...");
			getch();

			historyHandling(history, msgCache, &hIndex, &tIndex, &qsize);
		}
		else if(select == 3) //GCD
		{
			gotoXY(7,12);
			printf("GCD");
			gotoXY(12,12);

			printf("Enter x (limit 10000): ");
			x=getInt(0,10000,0);
			gotoXY(12,13);
			printf("Enter y (limit 10000): ");
			y=getInt(0,10000,1);

			returnVal = gcd(x,y);
			strcpy(msgCache,""); //clear cache
			sprintf(msgCache,"GCD(%d,%d) = %.0lf",x,y,returnVal); //formatting message

			clsRange(12,12,60,13);
			gotoXY(12,12);
			printf("GCD(%d,%d) = %.0lf",x,y,returnVal);
			gotoXY(12,13);
			printf("Press any key to continue...");
			getch();

			historyHandling(history, msgCache, &hIndex, &tIndex, &qsize);
		}
		else if(select == 4) //LCM
		{
			gotoXY(7,12);
			printf("LCM");
			gotoXY(12,12);

			printf("Enter x (limit 10000): ");
			x=getInt(0,10000,0);
			gotoXY(12,13);
			printf("Enter y (limit 10000): ");
			y=getInt(0,10000,1);

			returnVal = lcm(x,y);
			strcpy(msgCache,""); //clear cache
			sprintf(msgCache,"LCM(%d,%d) = %.0lf",x,y,returnVal); //formatting message

			clsRange(12,12,60,13);
			gotoXY(12,12);
			printf("LCM(%d,%d) = %.0lf",x,y,returnVal);
			gotoXY(12,13);
			printf("Press any key to continue...");
			getch();

			historyHandling(history, msgCache, &hIndex, &tIndex, &qsize);
		}
		else if(select == 5) //nPr
		{
			gotoXY(7,12);
			printf("nPr");

			do
			{
				gotoXY(12,12);
				printf("Enter n (limit 10): ");
				n=getInt(1,10,0);
				gotoXY(12,13);
				printf("Enter r (limit 10): ");
				r=getInt(1,10,1);

				if(n<r)
				{
					clsRange(12,12,60,13);
					gotoXY(1,13);
					printf("ERR: n<r!");
				}
			} while(n<r);

			returnVal = npr(n,r);
			strcpy(msgCache,""); //clear cache
			sprintf(msgCache,"%dP%d = %.0lf",n,r,returnVal); //formatting message

			clsRange(12,12,60,13);
			clsRange(1,13,9,13); //clear ERR message
			gotoXY(12,12);
			printf("%dP%d = %.0lf",n,r,returnVal);
			gotoXY(12,13);
			printf("Press any key to continue...");
			getch();

			historyHandling(history, msgCache, &hIndex, &tIndex, &qsize);
		}
		else if(select == 6) //nCr
		{
			gotoXY(7,12);
			printf("nCr");

			do
			{
				gotoXY(12,12);
				printf("Enter n (limit 10): ");
				n=getInt(1,10,0);
				gotoXY(12,13);
				printf("Enter r (limit 10): ");
				r=getInt(1,10,1);

				if(n<r)
				{
					clsRange(12,12,60,13);
					gotoXY(1,13);
					printf("ERR: n<r!");
				}
			} while(n<r);

			returnVal = ncr(n,r);
			strcpy(msgCache,""); //clear cache
			sprintf(msgCache,"%dC%d = %.0lf",n,r,returnVal); //formatting message

			clsRange(12,12,60,13);
			clsRange(1,13,9,13); //clear ERR message
			gotoXY(12,12);
			printf("%dC%d = %.0lf",n,r,returnVal);
			gotoXY(12,13);
			printf("Press any key to continue...");
			getch();

			historyHandling(history, msgCache, &hIndex, &tIndex, &qsize);
		}

	} while(select!=0);

	gotoXY(0,16);
	system("cls");
	printf("Program ended.\n");

	return 0;
}

void initScreen()
{
	int i;
	
	system("cls"); //init screen
	
	char ui[20][100] = {
		"_________________________________________________________________",
		"|Welcome to calculation program!                                |",
		"|First, type the command you wish to run,                       |",
		"|then enter required parameters.                                |",
		"|History of last 10 calculations will be shown here.            |",
		"|                                                               |",
		"|Press any key to continue...                                   |",
		"|                                                               |",
		"|                                                               |",
		"|                                                               |",
		"|                                                               |",
		"|_______________________________________________________________|",
		"|Mode>     |Available commands:                                 |",
		"|          |1>n! 2>Fibonacci 3>GCD 4>LCM 5>nPr 6>nCr 0>Exit     |",
		"|__________|____________________________________________________|"
	};

	for(i=0;i<15;i++)
	{
		gotoXY(0,i);
		printf("%10s",ui[i]);
	}
	
	gotoXY(29,6);
}

int getMenuItem()
{
	int min = 0, max = 6; //menu limit

	clsRange(7,12,10,12);
	gotoXY(12,12);
	printf("Available commands:");
	gotoXY(12,13);
	printf("1>n! 2>Fibonacci 3>GCD 4>LCM 5>nPr 6>nCr 0>Exit");
	gotoXY(7,12);

	return getInt(min,max,0);
}

void clsRange(int xi, int yi, int xf, int yf)
{
	int i,j;
	for(i=0;i<=yf-yi;i++)
	{
		gotoXY(xi,yi+i);
		for(j=0;j<=xf-xi;j++)
		{
			printf(" ");
		}
	}
}

void gotoXY(int x,int y)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD currentCoord = {0,0};
	int varX = 0, varY = 0; //global shifting variables

	currentCoord.X = varX + x;
	currentCoord.Y = varY + y;
	SetConsoleCursorPosition(console, currentCoord);
}

int getInt(int min, int max, int errorLine) //TODO: long long int
{
	int input;
	char ch;
	while(scanf("%d%c",&input,&ch)!=2||input<min||input>max||ch!='\n')
	{
		rewind(stdin);
		gotoXY(12,12+errorLine);
		printf("Invalid input, try again: ");
	}
	return input;
}

void historyHandling(char history[][100], char appendMsg[], int* head, int* tail, int* size)
{
	int h,i,j;
	strcpy(history[*tail],appendMsg); //append new history
	(*tail)++;
	
	if((*size)==10) //start using circular queue
		(*head)++;
	
	if((*tail)==10) //circular adj
		(*tail)=0;
	if((*head)==10)
		(*head)=0;

	clsRange(1,1,25,10);
	
	h=(*head);
	j=0;
	for(i=h;i<10;i++) //print from head to right bound
	{
		gotoXY(1,1+j);
		printf("%s",history[i]);
		j++;
	}
	for(i=0;i<h;i++) //print from left bound to before head
	{
		gotoXY(1,1+j);
		printf("%s",history[i]);
		j++;
	}
	
	if((*size)!=10) //check size
		(*size)++;
}

double fact(int n) //using normal recursive
{
	if(n==0||n==1)
		return 1;
	else
		return n*fact(n-1);
}

double fibo(int n, double fiboMemo[]) //using recursive with memoization
{
	double a,b;

	if(n==0)
		return fiboMemo[0]=0;
	else if(n==1)
		return fiboMemo[1]=1;
	else
	{
		if(fiboMemo[n-1]!=0)
			a=fiboMemo[n-1];
		else
			a=fibo(n-1,fiboMemo);

		if(fiboMemo[n-2]!=0)
			b=fiboMemo[n-2];
		else
			b=fibo(n-2,fiboMemo);

		return fiboMemo[n]=a+b;
	}
}

double gcd(int x, int y) //using Euclidian algorithm
{
	int temp;
	if(x<y) //x must be greater than y
	{
		temp=x;
		x=y;
		y=temp;
	}

	while(x%y!=0)
	{
		temp=x%y;
		x=y;
		y=temp;
	}

	return y;
}

double lcm(int x,int y) //using GCD(x,y) * LCM(x,y) = X * Y
{
	return (x*y)/gcd(x,y);
}

double npr(int n, int r) //using n!/(n-r)!
{
	return fact(n)/fact(n-r);
}

double ncr(int n, int r) //using n!/r!(n-r)!
{
	return fact(n)/(fact(r)*fact(n-r));
}
