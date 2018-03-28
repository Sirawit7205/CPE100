#include<stdio.h>
#include<math.h>

struct stat_info
{
	double min,max,mean,sd;
};

int Read_data_file(char filename[],double data[]);
void Calculate_Stat(double data[],int count,struct stat_info *stat);

int main()
{
	struct stat_info stat;
	double data[10000]={};
	int count;
	count = Read_data_file("DATA.TXT",data);
	
	if(count>0) printf("Read file success, total %d records.\n",count);
	else printf("Read file Error.\n");
	
	if(count>1)
	{
		Calculate_Stat(data,count,&stat);
		printf("%lf %lf %lf %lf\n",stat.min,stat.max,stat.mean,stat.sd);
	}
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

void Calculate_Stat(double data[],int count,struct stat_info *stat)
{
	int i;
	double min,max,sum=0,sum_sq=0;
	
	min=data[0];
	max=data[0];
	
	for(i=0;i<count;i++)
	{
		if(data[i]<min)	min=data[i];
		if(data[i]>max) max=data[i];
		sum+=data[i];
		sum_sq+=pow(data[i],2);
	}
	(*stat).mean=(sum/count);
	(*stat).sd=sqrt( (sum_sq/count) - pow((*stat).mean,2) );
	(*stat).min=min;
	(*stat).max=max;
}