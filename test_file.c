#include<stdio.h>

int Read_data_file(char filename[],double data[]);

int main()
{
	double data[10000]={};
	int count;
	count = Read_data_file("DATA.TXT",data);
	
	if(count>0) printf("Read file success, total %d records.\n",count);
	else printf("Read file Error.\n");
}

int Read_data_file(char filename[],double data[])
{
	FILE *fp;
	int count=0;
	
	fp=fopen(filename,"r");
	
	if(fp!=NULL)
	{
		while(feof(fp)==0)
		{
			while(fscanf(fp,"%lf",&data[count])==1)
				count++;
		}
		fclose(fp);
	}
	return count;
}