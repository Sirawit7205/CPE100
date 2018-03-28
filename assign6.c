#include<stdio.h>
#include<windows.h>
#include<conio.h>

//function prototypes
int menu();
int getInt(int min, int max);
int fibo(int n, int fiboMemo[]);
void calcSeries1(int n);
void calcEvenFibo(int n, int fiboMemo[]);
void calcSeries3(int d);
void checkDivisible(int a, int b, int d);
void checkRepeat(int n);

int main()
{
	int select,n,a,b,d;
	int memo[1000]={};
	
	do
	{
		system("cls");
		select = menu(); //get menu
		system("cls");
		
		if(select==1)
		{
			printf("                                2   2+4   2+4+6      \n");
			printf("1) Find sum of first N terms of - + --- + ----- + ...\n");
			printf("                                1   1*2   1*2*3      \n\n");
			
			printf("Please enter N (limit 12): ");
			n=getInt(1,12);
			
			calcSeries1(n);
			printf("Press any key to continue...");
			getch();
		}
		else if(select==2)
		{
			printf("2) Find first N even terms of Fibonacci sequence\n");
			
			printf("Please enter N (limit 15): ");
			n=getInt(1,15);
			
			calcEvenFibo(n,memo);
			printf("Press any key to continue...");
			getch();
		}
		else if(select==3)
		{
			printf("3) Find minimal terms of (1x40)+(3x38)+...+(39x2) with a minimal sum exceeding D\n");
			
			printf("Please enter D (limit 5000): ");
			d=getInt(1,5000);
			
			calcSeries3(d);
			printf("Press any key to continue...");
			getch();
		}
		else if(select==4)
		{
			printf("4) Find sum and terms count of integers between A and B that are divisible by D\n");
			
			do
			{
				printf("Please enter A (limit 1000): ");
				a=getInt(1,1000);
				printf("Please enter B (limit 1000): ");
				b=getInt(1,1000);
				
				if(a>=b)
					printf("A must be less than B\n");
			} while(a>=b);
			printf("Please enter D (limit 1000): ");
			d=getInt(1,1000);
			
			checkDivisible(a,b,d);
			printf("Press any key to continue...");
			getch();
		}
		else if(select==5)
		{
			printf("5) Find repeated terms and terms count in first Nth terms between 1,4,7,10,... and 1,6,11,16,...\n");
			
			printf("Please enter N (limit 1000): ");
			n=getInt(1,1000);
			
			checkRepeat(n);
			printf("Press any key to continue...");
			getch();
		}
		
		
		
	} while(select!=0);
		
	printf("End program.\n");
	return 0;
}

int menu()
{
	int min = 0, max = 5; //valid menus
	
	printf("=============================\n");
	printf("     Calculation Program     \n");
	printf("=============================\n\n");
	printf("Available commands: \n\n");
	printf("                                2   2+4   2+4+6      \n");
	printf("1) Find sum of first N terms of - + --- + ----- + ...\n");
	printf("                                1   1*2   1*2*3      \n");
	printf("2) Find first N even terms of Fibonacci sequence\n");
	printf("3) Find minimal terms of (1x40)+(3x38)+...+(39x2) with a minimal sum exceeding D\n");
	printf("4) Find sum and terms count of integers between A and B that are divisible by D\n");
	printf("5) Find repeated terms and terms count in first Nth terms between 1,4,7,10,... and 1,6,11,16,...\n");
	printf("0) Exit\n\n");
	printf("Please enter command: ");
	
	return getInt(min,max);
}

int getInt(int min, int max)
{
	int input;
	char ch;
	while(scanf("%d%c",&input,&ch)!=2||ch!='\n'||input<min||input>max)
	{
		rewind(stdin);
		printf("Invalid input, please try again: ");
	}
	return input;
}

int fibo(int n, int fiboMemo[]) //using recursive with memoization
{
	int a,b;
	
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

void calcSeries1(int n)
{
	int i,num=0,denom=1;
	double ans=0;
	
	printf("********************************\n");
	printf("*  i *     fi     *    sum     *\n");
	printf("********************************\n");
	
	for(i=1;i<=n;i++)
	{
		num+=(2*i);
		denom*=i;
		ans+=(double)num/denom;
		
		printf("* %2d *  %.6lf  *  %.6lf  *\n",i,(double)num/denom,ans);
	}
	
	printf("********************************\n");
	printf("ans = %.6lf\n",ans);
}

void calcEvenFibo(int n, int fiboMemo[])
{
	int i,count=0,returnVal;
	
	printf("********************************\n");
	printf("* count *   i   *      fi      *\n");
	printf("********************************\n");
	
	for(i=1;count<n;i++)
	{
		returnVal=fibo(i,fiboMemo);
		if(returnVal%2==0)
		{
			count++;
			printf("* %3d   *  %3d  *  %10d  *\n",count,i,returnVal);
		}
	}
	
	printf("********************************\n");
}

void calcSeries3(int d)
{
	int i,inc=1,dec=40,sum=0;
	
	printf("*************************\n");
	printf("*  i *   fi   *   sum   *\n");
	printf("*************************\n");
	
	for(i=1;sum<=d;i++)
	{
		sum+=(inc*dec);
		
		printf("* %2d *  %4d  *  %5d  *\n",i,inc*dec,sum);
		
		inc+=2;
		dec-=2;
	}
	
	printf("*************************\n");
	printf("n = %d, sum = %d\n",i-1,sum);
}

void checkDivisible(int a, int b, int d)
{
	int i,count=0,sum=0;
	
	printf("******************************\n");
	printf("*   no   *    i   *    sum   *\n");
	printf("******************************\n");
	
	for(i=a;i<=b;i++)
	{
		if(i%d==0)
		{
			count++;
			sum+=i;
			
			printf("*  %4d  *  %4d  *  %6d  *\n",count,i,sum);
		}
	}
	
	printf("******************************\n");
	printf("count = %d, ans = %d\n",count,sum);
}

void checkRepeat(int n)
{
	int i,common=1;
	int currentA=1,currentB=1,increA=5,increB=3,lcm=15; //customize series
	
	printf("******************\n");
	printf("*   no  *  term  *\n");
	printf("******************\n");
	
	for(i=1;currentA<=n&&currentB<=n;i++)
	{
		printf("*  %3d  *  %4d  *\n",i,common);
		
		common+=lcm;
		currentA+=increA;
		currentB+=increB;
	}
	
	printf("******************\n");
}
