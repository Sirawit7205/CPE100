#include<stdio.h>
#include<conio.h>
#include<windows.h>

//function prototypes
int menu();
int getInt(int min, int max);
double fact(int n);
double fibo(int n, double fiboMemo[]);
double gcd(int x, int y);
double npr(int n, int r);
double ncr(int n, int r);

int main()
{
	int select,n,r,x,y;
	double returnVal;
	double fiboMemo[50]={};
	
	do
	{
		system("cls"); //init screen
		select = menu(); //menu + item select
		
		system("cls");
		if(select == 1) //fact
		{
			printf("Factorial calculation:\n\n");
			printf("Enter n (limit 12): ");
			n=getInt(0,12);
			returnVal = fact(n);
			printf("\n%d! = %.0lf\n\n",n,returnVal);
			printf("Press any key to continue...");
			getch();
		}
		else if(select == 2) //fibo
		{
			printf("Fibonacci calculation:\n\n");
			printf("Enter n (limit 46): ");
			n=getInt(0,46);
			returnVal = fibo(n,fiboMemo);
			printf("\nFibo(%d) = %.0lf\n\n",n,returnVal);
			printf("Press any key to continue...");
			getch();
		}
		else if(select == 3) //GCD
		{
			printf("GCD calculation:\n\n");
			printf("Enter x (limit 10000): ");
			x=getInt(0,10000);
			printf("Enter y (limit 10000): ");
			y=getInt(0,10000);
			returnVal = gcd(x,y);
			printf("\nGCD(%d,%d) = %.0lf\n\n",x,y,returnVal);
			printf("Press any key to continue...");
			getch();
		}
		else if(select == 4) //nPr
		{
			printf("Permutation calculation:\n\n");
			do
			{
				printf("Enter n (limit 10): ");
				n=getInt(1,10);
				printf("Enter r (limit 10): ");
				r=getInt(1,10);
				
				if(n<r)
					printf("Error: n must be greater or equal to r.\n");
			} while(n<r);
			returnVal = npr(n,r);
			printf("\n%dP%d = %.0lf\n\n",n,r,returnVal);
			printf("Press any key to continue...");
			getch();
		}
		else if(select == 5) //nCr
		{
			printf("Combination calculation:\n\n");
			do
			{
				printf("Enter n (limit 10): ");
				n=getInt(1,10);
				printf("Enter r (limit 10): ");
				r=getInt(1,10);
				
				if(n<r)
					printf("Error: n must be greater or equal to r.\n");
			} while(n<r);
			returnVal = ncr(n,r);
			printf("\n%dC%d = %.0lf\n\n",n,r,returnVal);
			printf("Press any key to continue...");
			getch();
		}
		
	} while(select!=0);
	
	printf("Program ended.\n");
	
	return 0;
}

int menu()
{
	int min = 0, max = 5; //menu limit
	printf("===============================\n");
	printf("      Calculation program      \n");
	printf("===============================\n");
	printf("\nAvailable commands:\n\n");
	printf("1) Factorial: 			Fact(n)\n");
	printf("2) Fibonacci: 			Fibo(n)\n");
	printf("3) Greatest Common Divisor: 	GCD(x,y)\n");
	printf("4) Permutation: 		nPr\n");
	printf("5) Combination: 		nCr\n\n");
	printf("0) Exit\n");
	printf("\nPlease enter command: ");
	
	return getInt(min,max); //return menu index
}

int getInt(int min, int max) //TODO: long long int
{
	int input;
	char ch;
	while(scanf("%d%c",&input,&ch)!=2||input<min||input>max||ch!='\n')
	{
		rewind(stdin);
		printf("Invalid input, try again: ");
	}
	return input;
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

double npr(int n, int r) //using n!/(n-r)!
{
	return fact(n)/fact(n-r);
}

double ncr(int n, int r) //using n!/r!(n-r)!
{
	return fact(n)/(fact(r)*fact(n-r));
}