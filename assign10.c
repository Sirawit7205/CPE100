#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define SIZE 259374 //local

int readTextFile(FILE *fpText,int data1[], int *count1);
int readBinaryFile(FILE *fpBin,int data2[], int *count2);
void compare_scan(int data1[],int data2[],int count1,int count2,int matchCount[], int matches[][100]);
void compare_binarysearch(int data1[],int data2[],int count1,int count2,int matchCount[], int matches[][100]);
void compare_reference(int data1[],int data2[],int count1,int count2,int matchCount[], int matches[][100]);
int cmp(const void *a, const void *b);

int main()
{
	int count1=0,count2=0,return1,return2,i,j;
	int data1[SIZE]={},data2[SIZE]={},matches[5][100]={},matchCount[5]={};
	FILE *fpText,*fpBin;
	clock_t start[5],end[5];

	//method 1, compare all pairs
	fpText=fopen("txt100000.txt","r");						//open text file for read			
	fpBin=fopen("bin100000.bin","rb");						//open binary file for read
	return1=readTextFile(fpText,data1,&count1);				//call function to read text file
	return2=readBinaryFile(fpBin,data2,&count2);			//call function to read binary file
	if(return1==0&&return2==0)								//if there's no file reading error
	{
		printf("Reading successful:\n\t%d integers on text file\n\t%d integers on binary file.\n",count1,count2);	//prints amount of data read
		printf("Running Method 1: Compare all pairs...");
		start[0]=clock();									//capture start time
		compare_scan(data1,data2,count1,count2,matchCount,matches);	//call function to compare all pairs
		end[0]=clock();										//capture end time
		printf("done\n");
	}
	else													//file reading error
		printf("File reading failed.\n");
	
	count1=0;												//reset data1 data count
	count2=0;												//reset data2 data count
	
	//method 2, quicksort and binary search
	fpText=fopen("txt100000.txt","r");						//open text file for read
	fpBin=fopen("bin100000.bin","rb");						//open binary file for read	
	return1=readTextFile(fpText,data1,&count1);				//call function to read text file
	return2=readBinaryFile(fpBin,data2,&count2);			//call function to read binary file
	if(return1==0&&return2==0)								//if there's no file reading error
	{
		printf("Reading successful:\n\t%d integers on text file\n\t%d integers on binary file.\n",count1,count2);	//prints amount of data read
		printf("Running Method 2: Quicksort and binary search...");
		start[1]=clock();												//capture start time
		compare_binarysearch(data1,data2,count1,count2,matchCount,matches);		//call function to compare with quicksort and binary search
		end[1]=clock();													//capture end time
		printf("done\n");
	}
	else													//file reading error
		printf("File reading failed.\n");
	
	count1=0;												//reset data1 data count
	count2=0;												//reset data2 data count
		
	//method 3, sort both arrays
	fpText=fopen("txt100000.txt","r");						//open text file for read
	fpBin=fopen("bin100000.bin","rb");						//open binary file for read	
	return1=readTextFile(fpText,data1,&count1);				//call function to read text file
	return2=readBinaryFile(fpBin,data2,&count2);			//call function to read binary file
	if(return1==0&&return2==0)								//if there's no file reading error
	{
		printf("Reading successful:\n\t%d integers on text file\n\t%d integers on binary file.\n",count1,count2);	//prints amount of data read
		printf("Running Method 3: Sort both arrays...");
		start[2]=clock();											//capture start time
		compare_reference(data1,data2,count1,count2,matchCount,matches);		//call function to compare by sorting both arrays
		end[2]=clock();												//capture end time
		printf("done\n\n");
	}
	else													//file reading error	
		printf("File reading failed.\n");

	for(i=0;i<3;i++)										//print running time of all 3 methods	
		printf("Time used for method %d: %lf seconds.\n",i+1,((double)(end[i]-start[i]))/CLOCKS_PER_SEC);
	
	for(i=0;i<3;i++)										//for each method...
	{
		printf("\nMatching data from method %d:\n",i+1);
		for(j=0;j<matchCount[i];j++)						//for each matches saved...
		{
			printf("Match %d: %d\n",j+1,matches[i][j]);		//print the matches
		}
	}
	
	printf("End program.\n");
	return 0;
}

//function for reading text file and save to array
int readTextFile(FILE *fpText,int data1[], int *count1)
{
	if(fpText!=NULL)										//if file opens correctly
	{
		while(feof(fpText)==0)								//read text file until EOF
		{
			//read an integer from file and save to array data1, also check for fscanf error (to avoid getting \n)
			while(fscanf(fpText,"%d",&data1[(*count1)])==1)
			{
				(*count1)++;								//increase data1 integer count
			}
		}
		fclose(fpText);										//close file	
		return 0;											//read successful
	}
	else
		return 1;											//read failed
}

//function for reading binary file and save to array
int readBinaryFile(FILE *fpBin,int data2[], int *count2)
{
	if(fpBin!=NULL)											//if file opens correctly
	{
		while(feof(fpBin)==0)								//read binary file until EOF
		{
			//read an integer from file and save to array data2, also check for fread error (to avoid getting \n)
			while(fread(&data2[(*count2)],sizeof(int),1,fpBin)==1)
			{
				(*count2)++;								//increase data2 integer count
			}
		}
		fclose(fpBin);										//close file
		return 0;											//read successful
	}
	else
		return 1;											//read failed
}

//function to compare 2 arrays with all pairs comparison approach, O(n^2)
void compare_scan(int data1[],int data2[],int count1,int count2,int matchCount[], int matches[][100])
{
	int i,j,count=0;
	
	for(i=0;i<count1;i++)								//for each integer in data1...
	{
		for(j=0;j<count2;j++)							//for each integer in data2...
		{
			if(data1[i]==data2[j])						//if the current pair of integer matches
			{
				matches[0][count]=data1[i];				//saves matching data to array
				count++;								//increase match count	
			}
		}
	}
	matchCount[0]=count;								//saves matching counts to array
}

//function to compare 2 arrays by sorting one array, then binary search this array using another array as keys, O(nlogn)
void compare_binarysearch(int data1[],int data2[],int count1,int count2,int matchCount[], int matches[][100])
{
	int i,count=0;
	int *returnval;
	
	qsort(data1,count1,sizeof(int),cmp); 							//sort data1 with quicksort
	
	for(i=0;i<count2;i++)											//for each integer in data2...
	{
		returnval=bsearch(&data2[i],data1,count1,sizeof(int),cmp);	//binary search in data 1 with current integer in data2 as a key
		if(returnval!=NULL)											//if found (not returning NULL pointer)
		{
			matches[1][count]=data2[i];								//saves matching data to array
			count++;												//increase match count
		}
	}
	matchCount[1]=count;											//saves matching counts to array
}

//function to compare 2 arrays by sorting both arrays, then compare from start point of both array and sliding down, O(nlogn)
void compare_reference(int data1[],int data2[],int count1,int count2,int matchCount[], int matches[][100])
{
	int ptr1=0,ptr2=0,count=0;
	
	qsort(data1,count1,sizeof(int),cmp); 			//sort data1
	qsort(data2,count2,sizeof(int),cmp); 			//sort data2
	
	while(ptr1<count1&&ptr2<count2)					//if not reached the end of any array yet
	{
		if(data1[ptr1]==data2[ptr2])				//if integer pair matches
		{
			matches[2][count]=data1[ptr1];			//saves matching data to array
			count++;								//increase match count
			ptr1++;									//set current data1 index to next
			ptr2++;									//set current data2 index to next
		}
		else if(data1[ptr1]<data2[ptr2])			//else if current data1 is less than data2 integer
			ptr1++;									//set current data1 index to next			
		else										//else if current data2 is less than data1 integer
			ptr2++;									//set current data2 index to next
	}
	matchCount[2]=count;							//saves matching counts to array
}

//function for comparing 2 integers, used by qsort
int cmp(const void *a, const void *b)
{
	return (*(int *)a-*(int *)b); //sort from least to most
}
