#include<stdio.h>
#include<string.h>

void strchar_copy(char *src,char *dst,int start,int len);

int main()
{
	char str1[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char str2[100]={};
	
	strchar_copy(str1,str2,3,20);
	printf("%s\n",str2);
}

void strchar_copy(char *src,char *dst,int start,int len)
{
	int i,j;
	
	j=0;
	for(i=start;i<start+len;i++)
	{
		dst[j]=src[i];
		j++;
	}
	dst[j]='\0';
}