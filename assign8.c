#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<windows.h>

void addData(int *count, double data[]);
void deleteData(int *count, double data[]);
void calculate(int count, double data[]);
void displayData(int count, double data[]);
void cleanArray(int count, double data[]);

int main()
{
	int count=0,menu;
	double data[1000]={};
	char ending;
	
	do
	{
		system("cls");
		printf("\n==================\n");
		printf("Statistics program\n");
		printf("==================\n");
		printf("\nAvailable commands:\n\n");
		printf("1) Add new data\n");
		printf("2) Remove data\n");
		printf("3) Calculate statistics\n");
		printf("4) Show current data\n");
		printf("0) Exit\n");
		
		printf("\nEnter command: ");		
		while(scanf("%d%c",&menu,&ending)!=2||ending!='\n'||menu<0||menu>4)
		{
			rewind(stdin);
			printf("Invalid input, please try again: ");
		}
		
		if(menu==1)
		{
			if(count==1000)
			{
				printf("Error: Memory full, delete some data to proceed.\n");
				printf("Press any key to continue...");
				getch();
			}
			else
				addData(&count,data);
		}
		else if(menu==2)
		{
			if(count==0)
			{
				printf("Error: No data to delete, add some data to proceed.\n");
				printf("Press any key to continue...");
				getch();
			}
			else
				deleteData(&count,data);
		}
		else if(menu==3)
		{
			if(count<2)
			{
				printf("Error: At least 2 data required to calculate.\n");
				printf("Press any key to continue...");
				getch();
			}
			else
				calculate(count,data);
		}
		else if(menu==4)
		{
			if(count==0)
			{
				printf("Error: No data to display, add some data to proceed.\n");
				printf("Press any key to continue...");
				getch();
			}
			else
				displayData(count,data);
		}
		
	} while(menu!=0);
	
	system("cls");
	printf("End program.\n");
	return 0;
}

void addData(int *count, double data[])
{
	int tempCount=0,success;
	double tempInput;
	char ending;
	
	system("cls");
	printf("\n\nAdd data:\n\n");
	printf("Enter numbers separated by space, enter anything else to terminate.\n");
	printf("Available memory: %d spaces.\n",1000-(*count));
	printf("Input> ");
	do{
		success=scanf("%lf%c",&tempInput,&ending);
		if(success==2&&tempInput>=0&&(*count)<1000&&(ending==' '||ending=='\n'))
		{
			data[(*count)++]=tempInput;
			tempCount++;
		}
	} while(success==2&&tempInput>=0&&(*count)<1000&&ending==' ');
	rewind(stdin);
	printf("Added %d items, now have %d free memory spaces.\n",tempCount,1000-(*count));
	displayData((*count),data);
}

void deleteData(int *count, double data[])
{
	int i,removeCount=0,success;
	double remove;
	char confirm,ending;
	
	system("cls");
	printf("\n\nDelete data:\n\n");
	printf("Enter a number to delete> ");
	do
	{
		success=scanf("%lf%c",&remove,&ending);
		if(success!=2||remove<0||ending!='\n')
			printf("\nInvalid input, please try again: ");
	} while(success!=2||remove<0||ending!='\n');
	
	for(i=0;i<(*count);i++)
	{
		if(data[i]==remove)
		{
			printf("Do you want to remove %lf at %d? (Y/N): ",remove,i);
			do
			{
				rewind(stdin);
				confirm=getchar();
				if(confirm=='Y'||confirm=='y')
				{
					data[i]=-1;
					removeCount++;
				}
				else if(confirm!='N'&&confirm!='n')
					printf("\nInvalid input, please try again: ");
			} while(confirm!='Y'&&confirm!='y'&&confirm!='N'&&confirm!='n');
			rewind(stdin);
		}
	}
	
	(*count)-=removeCount;
	cleanArray((*count),data);
	printf("%d occurrences of %lf removed, now have %d free memory spaces.\n",removeCount,remove,1000-(*count));
	displayData((*count),data);
}

void calculate(int count, double data[])
{
	double min,max,avg=0,sd,sumX2=0;
	int i;
	
	system("cls");
	
	//init min and max
	min=data[0];
	max=data[0];
	for(i=0;i<count;i++)
	{
		//find min
		if(data[i]<min)
			min=data[i];
		
		//find max
		if(data[i]>max)
			max=data[i];
		
		//find avg sum
		avg+=data[i];
		
		//find x^2 sum
		sumX2+=data[i]*data[i];
	}
	
	avg/=count;
	sd=sqrt((sumX2/count)-(avg*avg));
	
	printf("\n\nStatistics for this data set:\n");
	printf("Min: %lf\nMax: %lf\nAverage: %lf\nSD: %lf\n",min,max,avg,sd);
	printf("\nPress any key to continue...");
	getch();
}

void displayData(int count, double data[])
{
	int i;
	
	printf("\n\nMemory status:\n");
	printf("Currently %d items in memory, %d free spaces.\n",count,1000-count);
	printf("Data list:\n");
	for(i=1;i<=count;i++)
	{
		printf("%g\t",data[i-1]);
		if(i%5==0)
			printf("\n");
	}
	printf("\nPress any key to continue...");
	getch();
}

void cleanArray(int count, double data[])
{
	int target=0,leader=0;
	double temp;

	for(target=0;target<count;target++)
	{
		if(data[target]==-1)
		{
			leader=target+1;
			while(data[leader]==-1)
				leader++;
		}
		
		temp=data[target];
		data[target]=data[leader];
		data[leader]=temp;
		leader++;
	}
}