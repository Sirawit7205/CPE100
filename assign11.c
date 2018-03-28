#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include<ctype.h>

typedef struct score_struct
{	
	long long unsigned int id;
	char name[50],grade[3];
	int mid,final,coll,sum;
	double grade_no;
} score;

int getInt(int min,int max);
int readFile(FILE *fp,score data[]);
void grade(score data[],int count,int criteria[]);
void stat_disp(score data[],int count);
void stat_calc(score data[],int count,int mode,double *min,double *max,double *mean,double *sd);
void grade_count(score data[],int count,int gCount[]);
void findDataRange(score data[],int count,int min,int max,int toPrint[],int *printCount);
void findGrade(score data[],int count,char grShow[],int toPrint[],int *printCount);
void searchName(score data[],int count,char search[],int toPrint[],int *printCount);
void dataDispAll(score data[],int count);
void dataDispSel(score data[],int toPrint[],int printCount);
int cmp_total(const void *a,const void *b);
int cmp_id(const void *a,const void *b);

//main function, flow control, inputs handling
int main()
{
	FILE *fp;
	score data[100]={};
	int i,mode,dataCount=0,gradingRun=0,printCount=0,minRange,maxRange,validGrade;
	int criteria[10]={},toPrint[100]={};
	char filename[100]={},grShow[3]={},search[100]={},gText[8][3]={"A","B+","B","C+","C","D+","D","F"};
	
	do
	{
		//display the menu
		system("cls");
		printf("=====================\n");
		printf("===Grading program===\n");
		printf("=====================\n");
		printf("\nAvailable commands:\n");
		printf("1) Read CSV file\n");
		printf("2) Grading\n");
		printf("3) Show statistics\n");
		printf("4) Show all data\n");
		printf("5) Sort score from most to least\n");
		printf("6) Sort by ID number\n");
		printf("7) Search score range\n");
		printf("8) Show data by grade\n");
		printf("9) Search by name\n");
		printf("0) Exit\n");
		printf("\nEnter command> ");
		
		mode=getInt(0,9);
		system("cls");
		
		if(mode==1)										//mode 1: load data from CSV file
		{
			printf("\n===Load CSV file===\n");
			printf("Enter filename: ");
			do
			{
				scanf("%s",filename);					//get filename
				fp = fopen(filename,"r");				//open file with specified name
				if(fp==NULL)							//file doesn't exist
					printf("Opening file %s failed, please input the filename again: ",filename);
			} while(fp==NULL);							//repeat until success
			dataCount=readFile(fp,data);				//call readFile() to store data, dataCount stores amount of data read
			printf("\n%d lines read.\n",dataCount);		//display results
			printf("Press any key to continue...");
			getch();
		}
		else if(mode==2)								//mode 2: grading
		{
			printf("\n===Grading===\n");
			if(dataCount==0)							//error because of no data
				printf("Please add data first!\n");
			else
			{
				for(i=0;i<7;i++)						//for each grade...
				{
					printf("Please enter criteria for grade %s > ",gText[i]);
					if(i==0)									//for first grade, criteria can be any value from 0-100
						criteria[i]=getInt(0,100);				//read criteria i
					else										//for other grades, criteria can only be 0-last criteria
						criteria[i]=getInt(0,criteria[i-1]);	//read criteria i (for i>0)
				}
			}
			
			grade(data,dataCount,criteria);						//call grade() for grading
			stat_disp(data,dataCount);							//call stat_disp() to display statistics of this dataset
			gradingRun=1;										//marker to tell that grading is already done	
			
			printf("Press any key to continue...");
			getch();
		}
		else
		{
			if(dataCount==0)									//error in case of no data
				printf("Please add data first!\n");
			else if(gradingRun==0)								//error in case of no grading performed
				printf("Please run grading first!\n");
			else
			{
				if(mode==3)										//mode 3: display statistics of this data set
				{
					stat_disp(data,dataCount);					//call stat_disp() to display statistics of this dataset
			
					printf("Press any key to continue...");
					getch();
				}
				else if(mode==4)								//mode 4: display all data
				{
					dataDispAll(data,dataCount);				//call dataDispAll() to display all data stored
					
					printf("Press any key to continue...");
					getch();
				}
				else if(mode==5)									//mode 5: sort data by total score
				{
					qsort(data,dataCount,sizeof(score),cmp_total);	//call qsort, specify sorting by total score with cmp_total compare function
					dataDispAll(data,dataCount);					//call dataDispAll() to display all data stored
					
					printf("Press any key to continue...");
					getch();
				}
				else if(mode==6)									//mode 6: sort data by ID
				{
					qsort(data,dataCount,sizeof(score),cmp_id);		//call qsort, specify sorting by ID number with cmp_id compare function
					dataDispAll(data,dataCount);					//call dataDispAll() to display all data stored
					
					printf("Press any key to continue...");
					getch();					
				}
				else if(mode==7)									//mode 7: find score in range
				{
					printf("\n===Find score in Range===\n");
					printf("Please enter lower range > ");
					minRange=getInt(0,100);							//enter lower range
					printf("Please enter upper range > ");
					maxRange=getInt(minRange,100);					//enter upper range, cannot be lower than lower range
					
					findDataRange(data,dataCount,minRange,maxRange,toPrint,&printCount);	//call findDataRange() to search by score bounds
					dataDispSel(data,toPrint,printCount);			//call dataDispSel() to display only data selected by findDataRange() function
					
					printf("Press any key to continue...");
					getch();
				}
				else if(mode==8)									//mode 8: search data by grade
				{
					printf("\n===Show data by grade===\n");
					printf("Please enter grade to show > ");
					do
					{
						memset(grShow,0,3);							//reset grade input
						validGrade=0;								//reset valid grade marker variable
						
						scanf("%s",grShow);							//enter grade to search			
						for(i=0;i<8;i++)
						{
							if(strcmp(grShow,gText[i])==0)			//if entered grade matches any of the valid grade stored in gText[]...
								validGrade=1;						//set validGrade marker to 1	
						}
						if(validGrade==0)							//if validGrade is still 0 (grShow doesn't match any grade)...
							printf("Error, invalid grade, please try again > ");	//asks user to try again
					} while(validGrade==0);							//loops until valid grade is entered
					
					findGrade(data,dataCount,grShow,toPrint,&printCount);	//call findGrade() to search by grade
					dataDispSel(data,toPrint,printCount);					//call dataDispSel() to display only data selected by findGrade() function
					
					printf("Press any key to continue...");
					getch();
				}
				else if(mode==9)									//mode 9: search data by name
				{
					printf("\n===Search by name===\n");
					printf("Please enter search terms > ");
					scanf("%s",search);								//enter search query
					for(i=0;i<strlen(search);i++)
						search[i]=toupper(search[i]);				//convert the query to uppercase (format of loaded file)	
					
					searchName(data,dataCount,search,toPrint,&printCount);	//call searchName() to search by name
					dataDispSel(data,toPrint,printCount);					//call dataDispSel() to display only data selected by searchName() function	
					
					printf("Press any key to continue...");
					getch();
				}
				
			}
		}
	} while(mode!=0);			//loop until mode is 0
	system("cls");
	printf("End program\n");	//exit program
	return 0;
}

//function for getting integer value between min and max bounds
int getInt(int min,int max)
{
	int dataIn;
	char after;
	rewind(stdin);				//rewind first to clear any unwanted data
	while(scanf("%d%c",&dataIn,&after)!=2||after!='\n'||dataIn<min||dataIn>max)		//if it fails any conditions: scanf completed successfully, ended with enter, integer is between bounds
	{
		rewind(stdin);			//rewind again
		printf("Invalid input, please try again> ");
	}
	return dataIn;				//return dataIn back to caller
}

//function for reading CSV file
int readFile(FILE *fp,score data[])
{
	int i=0;
	while(feof(fp)==0)			//read until EOF
	{
		while(fscanf(fp,"%llu,%[^,],%d,%d,%d",&data[i].id,data[i].name,&data[i].mid,&data[i].final,&data[i].coll)==5)	//read until fscanf doesn't completed successfully, data is saved into array of struct data[i]
		{
			data[i].sum=data[i].mid+data[i].final+data[i].coll;			//find total score
			i++;														//increment to next array index		
		}
	}
	fclose(fp);					//close file
	return i;					//return amount of data saved into array of struct
}

//function for grading
void grade(score data[],int count,int criteria[])
{
	int i;
	for(i=0;i<count;i++)		//for each data in array...
	{
		if(data[i].sum>=criteria[0])		//criteria for grade A
		{
			data[i].grade_no=4.0;			//set grade as number
			strcpy(data[i].grade,"A");		//set grade as letter
		}
		else if(data[i].sum>=criteria[1])	//criteria for grade B+
		{
			data[i].grade_no=3.5;			//set grade as number
			strcpy(data[i].grade,"B+");		//set grade as letter
		}
		else if(data[i].sum>=criteria[2])	//criteria for grade B	
		{
			data[i].grade_no=3;				//set grade as number
			strcpy(data[i].grade,"B");		//set grade as letter
		}
		else if(data[i].sum>=criteria[3])	//criteria for grade C+
		{
			data[i].grade_no=2.5;			//set grade as number
			strcpy(data[i].grade,"C+");		//set grade as letter
		}
		else if(data[i].sum>=criteria[4])	//criteria for grade C
		{
			data[i].grade_no=2;				//set grade as number
			strcpy(data[i].grade,"C");		//set grade as letter
		}
		else if(data[i].sum>=criteria[5])	//criteria for grade D+
		{
			data[i].grade_no=1.5;			//set grade as number
			strcpy(data[i].grade,"D+");		//set grade as letter	
		}
		else if(data[i].sum>=criteria[6])	//criteria for grade D
		{
			data[i].grade_no=1;				//set grade as number
			strcpy(data[i].grade,"D");		//set grade as letter
		}
		else								//otherwise, grade F
		{
			data[i].grade_no=0;				//set grade as number
			strcpy(data[i].grade,"F");		//set grade as letter
		}		
	}
}

//function for calculating statistics data
void stat_calc(score data[],int count,int mode,double *min,double *max,double *mean,double *sd)
{
	int i;
	double cMin,cMax,cSum=0,sumSqr=0,current;
	
	for(i=0;i<count;i++)
	{
		//select current data from struct array
		if(mode==0)					//check mode from caller to see which dataset to calculate
			current=data[i].mid;	//mode 0: midterm
		else if(mode==1)
			current=data[i].final;	//mode 1: final
		else if(mode==2)
			current=data[i].coll;	//mode 2: collect
		else
			current=data[i].sum;	//mode 3: total
		
		if(i==0)
		{
			cMin=current;			//initialize min checker
			cMax=current;			//initialize max checker	
		}
		else if(current<cMin)		//current value is less than min
			cMin=current;			//min = current value
		else if(current>cMax)		//current value is more than max
			cMax=current;			//max = current value
		
		cSum+=current;				//sum of all data
		sumSqr+=(current*current);	//square sum of all data
		
	}
	
	(*min)=cMin;					//return min to caller
	(*max)=cMax;					//return max to caller
	(*mean)=cSum/count;				//return mean to caller
	(*sd)=sqrt((sumSqr/count)-((*mean)*(*mean)));	//return SD to caller
}

//function to count each grade
void grade_count(score data[],int count,int gCount[])
{
	int i;
	for(i=0;i<count;i++)
	{
		if(data[i].grade_no==4.0)			//count 4.0
			gCount[0]++;
		else if(data[i].grade_no==3.5)		//count 3.5
			gCount[1]++;
		else if(data[i].grade_no==3.0)		//count 3.0	
			gCount[2]++;
		else if(data[i].grade_no==2.5)		//count 2.5
			gCount[3]++;
		else if(data[i].grade_no==2.0)		//count 2.0
			gCount[4]++;
		else if(data[i].grade_no==1.5)		//count 1.5
			gCount[5]++;
		else if(data[i].grade_no==1.0)		//count 1.0
			gCount[6]++;
		else if(data[i].grade_no==0)		//count 0.0
			gCount[7]++;
	}
}

//function to find data in score range
void findDataRange(score data[],int count,int min,int max,int toPrint[],int *printCount)
{
	int i;
	
	(*printCount)=0;							//set print pointer to 0
	for(i=0;i<count;i++)						//for each data in array...
	{
		if(data[i].sum>=min&&data[i].sum<=max)	//if total score is in min and max bounds...
		{
			toPrint[(*printCount)]=i;			//mark this data to be print
			(*printCount)++;					//increase print pointer
		}
	}
}

//function to find data by grade
void findGrade(score data[],int count,char grShow[],int toPrint[],int *printCount)
{
	int i;
	
	(*printCount)=0;							//set print pointer to 0
	for(i=0;i<count;i++)						//for each data in array...
	{
		if(strcmp(data[i].grade,grShow)==0)		//if grade matches grShow...
		{
			toPrint[(*printCount)]=i;			//mark this data to be print
			(*printCount)++;					//increase print pointer
		}
	}
}

//function to search data by name
void searchName(score data[],int count,char search[],int toPrint[],int *printCount)
{
	int i;
	
	(*printCount)=0;							//set print pointer to 0
	for(i=0;i<count;i++)						//for each data in array...
	{
		if(strstr(data[i].name,search)!=NULL)	//if search query is found in this name...
		{
			toPrint[(*printCount)]=i;			//mark this data to be print
			(*printCount)++;					//increase print pointer
		}			
	}
}

//function to display statistics data
void stat_disp(score data[],int count)
{
	int i,gCount[8]={};
	double mean,sd,min,max,save[5][5]={},weight[8]={4,3.5,3,2.5,2,1.5,1,0},weightSum=0;
	char table[4][100]={"Min","Max","Mean","SD"};
	
	//prints table header
	printf("\n===Statistics===\n");
	printf("Student count = %d\n",count);
	printf("-----------------------------------------\n");
	printf("| Score |  Mid  | Final | Atten | Total |\n");
	printf("|-------|-------|-------|-------|-------|\n");
	
	for(i=0;i<4;i++)
	{
		stat_calc(data,count,i,&min,&max,&mean,&sd);	//call stat_calc() to calculate statistics of type 0-3 (mid/final/coll/total)
		save[0][i]=min;		//save min to save array
		save[1][i]=max;		//save max to save array
		save[2][i]=mean;	//save mean to save array	
		save[3][i]=sd;		//save SD to save array
	}
	for(i=0;i<4;i++)
		printf("|%-7s|%7.2lf|%7.2lf|%7.2lf|%7.2lf|\n",table[i],save[i][0],save[i][1],save[i][2],save[i][3]);	//prints all statistics data from save array
	printf("-----------------------------------------\n");
	
	grade_count(data,count,gCount);		//call grade_count() to count each grade
	
	//prints table header
	printf("\nGrade count:\n\n");
	printf("---------------------------------------------------------\n");
	printf("| Grade |  A  |  B+ |  B  |  C+ |  C  |  D+ |  D  |  F  |\n");
	printf("|-------|-----|-----|-----|-----|-----|-----|-----|-----|\n");
	printf("| Count |");
	for(i=0;i<8;i++)
	{
		weightSum+=(double)gCount[i]*weight[i];		//sum of weighted sum of each grade
		printf("%-5d|",gCount[i]);					//prints count of each grade
	}
	printf("\n---------------------------------------------------------\n");
	printf("\nGPA = %.2lf\n",weightSum/count);		//prints GPA
}

//function to display all data in struct array
void dataDispAll(score data[],int count)
{
	int i;
	
	//prints table header
	printf("\n===Show all data===\n");
	printf("No.\tID no.\t\tStudent name\t\t\t\tMid\tFinal\tAtten\tTotal\tGrade\tPoint\n");
	
	for(i=0;i<count;i++)
	{
		//prints each data in struct array
		printf("%d\t%llu\t%-30s\t\t%d\t%d\t%d\t%d\t%s\t%.1lf\n",i+1,data[i].id,data[i].name,data[i].mid,data[i].final,
		data[i].coll,data[i].sum,data[i].grade,data[i].grade_no);
	}
}

//function to display data in struct array specified by toPrint array
void dataDispSel(score data[],int toPrint[],int printCount)
{
	int i,p;
	
	//prints table header
	printf("No.\tID no.\t\tStudent name\t\t\t\tMid\tFinal\tAtten\tTotal\tGrade\tPoint\n");
	
	for(i=0;i<printCount;i++)
	{
		p=toPrint[i];		//select data to print from toPrint array
		
		//prints data selected by p
		printf("%d\t%llu\t%-30s\t\t%d\t%d\t%d\t%d\t%s\t%.1lf\n",i+1,data[p].id,data[p].name,data[p].mid,data[p].final,
		data[p].coll,data[p].sum,data[p].grade,data[p].grade_no);
	}
}

//compare function for qsort by total score
int cmp_total(const void *a,const void *b)
{
	score *A=(score *)a;
	score *B=(score *)b;
	return (B->sum - A->sum);	//sort by score from most to least
}

//compare function for qsort by ID number
int cmp_id(const void *a,const void *b)
{
	score *A=(score *)a;
	score *B=(score *)b;
	return (A->id - B->id);		//sort by ID number from least to most
}
