#include<stdio.h>
#include<math.h>
#include<windows.h>

int newton_raph(double a,double b,double c,double *x,int *iterCnt);
double different(double a,double b,double c,double x);
int doubleComp(double a,double b);
double dataIn();

int main()
{
	double a,b,c,xa,xb;
	double chkA,chkB;
	int iterCntA=0,iterCntB=0;
	char ch;
	
	do
	{
		system("cls");
		printf("Newton-Raphson calculator\n");
		
		printf("\nPlease enter a,b,c value of equation ax^2+bx+c=0\n");
		do
		{
			printf("Enter a: ");
			a=dataIn();
			printf("Enter b: ");
			b=dataIn();
			printf("Enter c: ");
			c=dataIn();
			
			if(doubleComp(a,0)&&doubleComp(b,0))
				printf("A and B cannot be both zero. Please try again: \n");
		} while(doubleComp(a,0)&&doubleComp(b,0));
		
		printf("\nPlease enter left and right initial testing point.\n");
		printf("Enter x Left: ");
		do{
			xa=dataIn();
			if(doubleComp((2*a*xa)+b,0)) //denom cannot be 0
				printf("Testing point caused divide by zero, please try again: ");
		} while(doubleComp((2*a*xa)+b,0));
		
		printf("Enter x Right: ");
			do{
			xb=dataIn();
			if(doubleComp((2*a*xb)+b,0)) //denom cannot be 0
				printf("Testing point caused divide by zero, please try again: ");
		} while(doubleComp((2*a*xb)+b,0));
		
		iterCntA=0;
		iterCntB=0;
		
		chkA = newton_raph(a,b,c,&xa,&iterCntA);
		chkB = newton_raph(a,b,c,&xb,&iterCntB);
		
		if(chkA==-1||chkB==-1) //no answer
			printf("\nAnswer of %.2lfx^2 %+.2lfx %+.2lf = 0 is not available.\nCalculation timed out.\n\n",a,b,c);
		
		else if(fabs(xa-xb)<0.000001) //1 answer
			printf("\nAnswer of %.2lfx^2 %+.2lfx %+.2lf = 0 is %lf\nCalculated using %d iterations.\n\n",a,b,c,xa,iterCntA+iterCntB);
			
		else //2 answers
			printf("\nAnswer of %.2lfx^2 %+.2lfx %+.2lf = 0 are %lf and %lf\nCalculated using %d iterations.\n\n",a,b,c,xa,xb,iterCntA+iterCntB);
			
		do
		{
			rewind(stdin);
			printf("Do you want to calculate again? (Y/N): ");
			scanf("%c",&ch);
		} while(ch!='Y'&&ch!='y'&&ch!='N'&&ch!='n');
		
	} while(ch=='Y'||ch=='y');
	printf("\nEnd program.\n");
	return 0;
}

int newton_raph(double a,double b,double c,double *x,int *iterCnt)
{
	double delta=0.000001; //adjustment in case of divide by zero
	double cur,diff;
	do
	{
		cur=(*x);
		while(doubleComp((2*a*cur)+b,0)) //check divide by zero
			cur+=delta;
		diff=different(a,b,c,cur);
		cur-=diff;
		(*x)=cur;
		(*iterCnt)++;
	} while(!doubleComp(diff,0)&&(*iterCnt)<1000);
	
	if((*iterCnt)<1000)
		return 0;
	else
		return -1;
}

double different(double a,double b,double c,double x)
{
	return ((a*x*x)+(b*x)+c)/((2*a*x)+b); //f(x)/f'(x)
}

int doubleComp(double a,double b)
{
	double delta=0.0000001; //very small number
	return (fabs(a-b)<delta); //close "enough"
}

double dataIn()
{
	double data;
	char ch;
	
	while(scanf("%lf%c",&data,&ch)!=2||ch!='\n')
	{
		rewind(stdin);
		printf("Invalid input, please try again: ");
	}
	
	return data;
}
