#include<stdio.h>

void Insert_data(int data[],int *count,int x);

int main()
{
	int i,data[11]={1,5,10,14,15,17,18,20,25,30,0},count=10,x;
	
	//for(i=0;i<count;i++)
	//	scanf("%d",&data[i]);
	
	printf("Insert: ");
	scanf("%d",&x);
	
	Insert_data(data,&count,x);
	
	for(i=0;i<count;i++)
		printf("%d ",data[i]);
	
	return 0;
}

void Insert_data(int data[],int *count,int x)
{
	int pos=(*count);
	while(data[pos-1]>x&&pos>0)
	{
		data[pos]=data[pos-1];
		pos--;
	}
	data[pos]=x;
	(*count)++;
}