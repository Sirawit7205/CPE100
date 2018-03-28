#include<stdio.h>
#include<windows.h>
#include<conio.h>

//function prototypes
int menu();
int getInt(int min, int max);
void tableHeaderHandling(int func);
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

void tableHeaderHandling(int func)
{
	if(func==1)
	{
		printf("________________________________\n");
		printf("|  i |     fi     |    sum     |\n");
		printf("|----|------------|------------|\n");
	}
	else if(func==2)
	{
		printf("________________________________\n");
		printf("| count |   i   |      fi      |\n");
		printf("|-------|-------|--------------|\n");
	}
	else if(func==3)
	{
		printf("_________________________\n");
		printf("|  i |   fi   |   sum   |\n");
		printf("|----|--------|---------|\n");
	}
	else if(func==4)
	{
		printf("______________________________\n");
		printf("|   no   |    i   |    sum   |\n");
		printf("|--------|--------|----------|\n");
	}
	else if(func==5)
	{
		printf("__________________\n");
		printf("|   no  |  term  |\n");
		printf("|-------|--------|\n");
	}
	
}

void calcSeries1(int n)
{
	int i,num=0,denom=1,lineCount=0;
	double ans=0;
	
	for(i=1;i<=n;i++)
	{
		//printing header
		if(lineCount%20==0)
			tableHeaderHandling(1);
		
		num+=(2*i);
		denom*=i;
		ans+=(double)num/denom;
		
		printf("| %2d |  %.6lf  |  %.6lf  |\n",i,(double)num/denom,ans);
		
		//printing footer
		lineCount++;
		if(lineCount%20==0)
		{
			printf("|____|____________|____________|\n");
			printf("Press any key to continue to next screen...");
			getch();
			printf("\n\n");
		}
	}
	
	//printing last footer and answers
	if(lineCount%20!=0)
		printf("|____|____________|____________|\n");
	printf("ans = %.6lf\n",ans);
}

void calcEvenFibo(int n, int fiboMemo[])
{
	int i,count=0,returnVal,lineCount=0;
	
	for(i=1;count<n;i++)
	{	
		returnVal=fibo(i,fiboMemo);
		if(returnVal%2==0)
		{
			//printing header
			if(lineCount%20==0)
				tableHeaderHandling(2);
			
			count++;
			printf("| %3d   |  %3d  |  %10d  |\n",count,i,returnVal);
			
			//printing footer
			lineCount++;
			if(lineCount%20==0)
			{
				printf("|_______|_______|______________|\n");
				printf("Press any key to continue to next screen...");
				getch();
				printf("\n\n");
			}
		}
	}
	
	if(lineCount%20!=0)
		printf("|_______|_______|______________|\n");
	
}

void calcSeries3(int d)
{
	int i,inc=1,dec=40,sum=0,lineCount=0;
	
	for(i=1;sum<=d;i++)
	{
		//printing header
		if(lineCount%20==0)
			tableHeaderHandling(3);
		
		sum+=(inc*dec);
		
		printf("| %2d |  %4d  |  %5d  |\n",i,inc*dec,sum);
		
		inc+=2;
		dec-=2;
		
		//printing footer
		lineCount++;
		if(lineCount%20==0)
		{
			printf("|____|________|_________|\n");
			printf("Press any key to continue to next screen...");
			getch();
			printf("\n\n");
		}
	}
	
	if(lineCount%20!=0)
		printf("|____|________|_________|\n");
	printf("n = %d, sum = %d\n",i-1,sum);
}

void checkDivisible(int a, int b, int d)
{
	int i,count=0,sum=0,lineCount=0;
	
	for(i=a;i<=b;i++)
	{
		if(i%d==0)
		{
			//printing header
			if(lineCount%20==0)
			tableHeaderHandling(4);
		
			count++;
			sum+=i;
			
			printf("|  %4d  |  %4d  |  %6d  |\n",count,i,sum);
			
			//printing footer
			lineCount++;
			if(lineCount%20==0)
			{
				printf("|________|________|__________|\n");
				printf("Press any key to continue to next screen...");
				getch();
				printf("\n\n");
			}
		}
	}
	
	if(lineCount%20!=0)
		printf("|________|________|__________|\n");
	printf("count = %d, ans = %d\n",count,sum);
}

void checkRepeat(int n)
{
	int i,common=1,lineCount=0;
	int currentA=1,currentB=1,increA=5,increB=3,lcm=15; //customize series
	
	for(i=1;currentA<=n&&currentB<=n;i++)
	{
		//printing header
		if(lineCount%20==0)
		tableHeaderHandling(5);
		
		printf("|  %3d  |  %4d  |\n",i,common);
		
		common+=lcm;
		currentA+=increA;
		currentB+=increB;
		
		//printing footer
		lineCount++;
		if(lineCount%20==0)
		{
			printf("|_______|________|\n");
			printf("Press any key to continue to next screen...");
			getch();
			printf("\n\n");
		}
	}
	
	if(lineCount%20!=0)
		printf("|_______|________|\n");
}
