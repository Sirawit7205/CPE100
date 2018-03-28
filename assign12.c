#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<conio.h>
#include<windows.h>

//struct for storing matrices
typedef struct matrix_struct{
	int row,col;
	double data[50][50];
}matrix;

//function prototypes
void displayHelp();
int openFile(FILE **fp,char filename[],int permission);
matrix readMatrix(FILE *fp);
void writeMatrix(matrix mat,FILE *fp);
void showMatrix(matrix mat,char name[]);
void createMatrix(int row,int col,FILE *fp);
int addMatrix(matrix A,matrix B,FILE *fp);
int subMatrix(matrix A,matrix B,FILE *fp);
int mulMatrix(matrix A,matrix B,FILE *fp);
void mulScaMatrix(matrix A,double mul,FILE *fp);
void transMatrix(matrix A,FILE *fp);
void idenMatrix(int size,FILE *fp);

int main()
{
	char cmd[1000]={},split[5][100]={};
	char *token;
	int cmdSpt=0,i,returnA,returnB,returnTar,returnFunc,row,col,size;
	double mul;
	FILE *fileA=NULL,*fileB=NULL,*fileTar=NULL;
	matrix matA,matB,matTar;
	
	//prints welcome messages
	system("cls");
	printf("\n\n===Matrix manipulation program===\n\n");
	printf("Type <help> for command list and usage\n\n");
	do
	{
		printf("MATRIX> ");					//command prompt
		rewind(stdin);						//rewind everything
		scanf("%[^\n]",cmd);				//get command (with spaces)
		
		cmdSpt=0;							//set sub command count to 0
		token=strtok(cmd," ");				//partition command to subcommand with spaces
		while(token!=NULL&&cmdSpt<=5)
		{
			strcpy(split[cmdSpt],token);	//save subcommands to split[]
			cmdSpt++;						//increase sub command count
			token=strtok(NULL," ");
		}
		
		for(i=0;i<strlen(split[0]);i++)			//set command to lowercase
			split[0][i]=tolower(split[0][i]);	
		
		if(strcmp(split[0],"show")==0&&cmdSpt==2)	//show command
		{
			returnA=openFile(&fileA,split[1],0);	//call openFile() to open file to show
			
			if(returnA==1)							//failed to open
				printf("Error: file %s failed to open.\n\n",split[1]);
			else
			{
				matA=readMatrix(fileA);				//read matrix and save to matA
				showMatrix(matA,split[1]);					//show matrix matA
			}
		}
		else if(strcmp(split[0],"create")==0&&cmdSpt==4)	//create command
		{
			returnTar=openFile(&fileTar,split[3],1);		//call openFile() to create a new file
			{
				if(returnTar==1)							//failed to open
					printf("Error: file %s failed to open.\n\n",split[3]);
				else if(sscanf(split[1],"%d",&row)!=1||sscanf(split[2],"%d",&col)!=1)	//incorrect matrix size entered
					printf("Error: invalid matrix size.\n\n");
				else if(row>50||col>50)						//size too large
					printf("Error: maximum matrix size is 50x50.\n\n");
				else
				{
					createMatrix(row,col,fileTar);			//create a new matrix with specified size
					
					printf("%dx%d matrix was successfully saved to %s.\n\n",row,col,split[3]);
					matTar=readMatrix(fileTar);				//read destination matrix
					printf("===Result matrix===\n");
					showMatrix(matTar,split[3]);			//show result					
				}
			}
		}
		else if(strcmp(split[0],"copy")==0&&cmdSpt==3)		//copy command
		{
			returnA=openFile(&fileA,split[1],0);			//open source and destination files
			returnB=openFile(&fileTar,split[2],1);
			
			if(returnA==1)		//failed to open source
				printf("Error: file %s failed to open.\n\n",split[1]);
			if(returnB==1)		//failed to open destination
				printf("Error: file %s failed to open.\n\n",split[2]);
			
			if(returnA==0&&returnB==0)		//passed
			{
				matA=readMatrix(fileA);		//read source file
				writeMatrix(matA,fileTar);	//write to destination file
				
				printf("Matrix from %s is successfully copied to %s.\n\n",split[1],split[2]);
				matTar=readMatrix(fileTar);				//read destination matrix
				printf("===Source matrix===\n");
				showMatrix(matA,split[1]);				//show source
				printf("===Destination matrix===\n");
				showMatrix(matTar,split[2]);			//show destination				
			}
		}
		else if(strcmp(split[0],"add")==0&&cmdSpt==4)		//add command
		{
			returnA=openFile(&fileA,split[1],0);			//open source and destination files
			returnB=openFile(&fileB,split[2],0);
			returnTar=openFile(&fileTar,split[3],1);
			
			if(returnA==1)		//failed to open source A
				printf("Error: file %s failed to open.\n\n",split[1]);
			if(returnB==1)		//failed to open source B
				printf("Error: file %s failed to open.\n\n",split[2]);
			if(returnTar==1)	//failed to open destination
				printf("Error: file %s failed to open.\n\n",split[3]);
			
			if(returnA==0&&returnB==0&&returnTar==0)		//passed
			{
				matA=readMatrix(fileA);						//read both sources files
				matB=readMatrix(fileB);
				returnFunc=addMatrix(matA,matB,fileTar);	//add matrices and save to destination
				if(returnFunc==0)							//success
				{
					printf("New matrix is successfully saved to %s.\n\n",split[3]);
					matTar=readMatrix(fileTar);				//read destination matrix
					printf("===Base matrix===\n");
					showMatrix(matA,split[1]);				//show base
					printf("===Adder matrix===\n");
					showMatrix(matB,split[2]);				//show adder
					printf("===Result matrix===\n");
					showMatrix(matTar,split[3]);			//show result
				}
				else										//dimensions not matched
					printf("Error: matrix dimensions unmatched.\n\n");
			}
		}
		else if((strcmp(split[0],"subtract")==0||strcmp(split[0],"sub")==0)&&cmdSpt==4)		//subtract command
		{
			returnA=openFile(&fileA,split[1],0);			//open source and destination files
			returnB=openFile(&fileB,split[2],0);
			returnTar=openFile(&fileTar,split[3],1);
			
			if(returnA==1)		//failed to open source A
				printf("Error: file %s failed to open.\n\n",split[1]);
			if(returnB==1)		//failed to open source B
				printf("Error: file %s failed to open.\n\n",split[2]);
			if(returnTar==1)	//failed to open destination	
				printf("Error: file %s failed to open.\n\n",split[3]);
			
			if(returnA==0&&returnB==0&&returnTar==0)		//passed
			{
				matA=readMatrix(fileA);						//read both sources files
				matB=readMatrix(fileB);
				returnFunc=subMatrix(matA,matB,fileTar);	//subtract matrices and save to destination
				if(returnFunc==0)							//success
				{
					printf("New matrix is successfully saved to %s.\n\n",split[3]);
					matTar=readMatrix(fileTar);				//read destination matrix
					printf("===Base matrix===\n");
					showMatrix(matA,split[1]);				//show base
					printf("===Subtractor matrix===\n");
					showMatrix(matB,split[2]);				//show subtractor
					printf("===Result matrix===\n");
					showMatrix(matTar,split[3]);			//show result
				}
				else										//dimensions not matched
					printf("Error: matrix dimensions unmatched.\n\n");
			}			
		}
		else if((strcmp(split[0],"multiply")==0||strcmp(split[0],"mul")==0)&&cmdSpt==4)		//multiply command
		{
			returnA=openFile(&fileA,split[1],0);			//open source and destination files
			returnB=openFile(&fileB,split[2],0);
			returnTar=openFile(&fileTar,split[3],1);
			
			if(returnA==1)		//failed to open source A
				printf("Error: file %s failed to open.\n\n",split[1]);
			if(returnB==1)		//failed to open source B
				printf("Error: file %s failed to open.\n\n",split[2]);
			if(returnTar==1)	//failed to open destination	
				printf("Error: file %s failed to open.\n\n",split[3]);
			
			if(returnA==0&&returnB==0&&returnTar==0)		//passed
			{
				matA=readMatrix(fileA);						//read both sources files
				matB=readMatrix(fileB);
				returnFunc=mulMatrix(matA,matB,fileTar);	//multiply matrices and save to destination
				if(returnFunc==0)							//success
				{
					printf("New matrix is successfully saved to %s.\n\n",split[3]);
					matTar=readMatrix(fileTar);				//read destination matrix
					printf("===Base matrix===\n");
					showMatrix(matA,split[1]);				//show base
					printf("===Multiplier matrix===\n");
					showMatrix(matB,split[2]);				//show multiplier	
					printf("===Result matrix===\n");
					showMatrix(matTar,split[3]);			//show result
				}
				else										//dimensions not matched
					printf("Error: matrix dimensions unmatched.\n\n");
			}			
		}
		else if((strcmp(split[0],"mulscalar")==0||strcmp(split[0],"muls")==0)&&cmdSpt==4)	//multiply scalar command
		{
			returnA=openFile(&fileA,split[2],0);			//open source and destination files
			returnTar=openFile(&fileTar,split[3],1);
			returnFunc=sscanf(split[1],"%lf",&mul);			//convert multiplier to double
			
			if(returnA==1)		//failed to open source A					
				printf("Error: file %s failed to open.\n\n",split[2]);
			if(returnTar==1)	//failed to open destination
				printf("Error: file %s failed to open.\n\n",split[3]);
			if(returnFunc!=1)	//cannot convert multiplier to double (invalid)
				printf("Error: invalid multiplier.\n\n");
			
			if(returnA==0&&returnB==0&&returnFunc==1)		//passed
			{
				matA=readMatrix(fileA);						//read source file
				mulScaMatrix(matA,mul,fileTar);				//multiply with scalar and save to destination
				
				printf("New matrix is successfully saved to %s.\n\n",split[3]);	
				matTar=readMatrix(fileTar);					//read destination matrix
				printf("===Base matrix===\n");
				showMatrix(matA,split[2]);					//show scalar multiplier
				printf("Multiply with %g\n\n",mul);
				printf("===Result matrix===\n");
				showMatrix(matTar,split[3]);				//show result
			}
		}
		else if((strcmp(split[0],"transpose")==0||strcmp(split[0],"trans")==0)&&cmdSpt==3)	//transpose command
		{
			returnA=openFile(&fileA,split[1],0);			//open source and destination files
			returnTar=openFile(&fileTar,split[2],1);	

			if(returnA==1)		//failed to open source A
				printf("Error: file %s failed to open.\n\n",split[1]);
			if(returnTar==1)	//failed to open destination
				printf("Error: file %s failed to open.\n\n",split[2]);	

			if(returnA==0&&returnTar==0)					//passed
			{
				matA=readMatrix(fileA);						//read source file
				transMatrix(matA,fileTar);					//transpose matrix and save to destination
				
				printf("New matrix is successfully saved to %s.\n\n",split[2]);	
				matTar=readMatrix(fileTar);					//read destination matrix
				printf("===Base matrix===\n");
				showMatrix(matA,split[1]);					//show base
				printf("===Result matrix===\n");
				showMatrix(matTar,split[2]);				//show result
			}
		}
		else if((strcmp(split[0],"identity")==0||strcmp(split[0],"iden")==0)&&cmdSpt==3)	//identity matrix command
		{
			returnTar=openFile(&fileTar,split[2],1);		//open destination file
			returnFunc=sscanf(split[1],"%d",&size);			//convert size to integer
			
			if(returnTar==1)			//failed to open destination
				printf("Error: file %s failed to open.\n\n",split[2]);
			else if(returnFunc!=1)		//failed to convert size to integer (invalid)
				printf("Error: invalid matrix size.\n\n");
			else if(size>50)			//size too large
				printf("Error: maximum matrix size is 50x50.\n\n");
			else
			{
				idenMatrix(size,fileTar);		//create identity matrix with specified size and save to destination
				
				printf("Identity matrix of size %d is successfully saved to %s.\n\n",size,split[2]);	
				matTar=readMatrix(fileTar);					//read destination matrix
				printf("===Result matrix===\n");
				showMatrix(matTar,split[2]);				//show result
			}
		}
		else if(strcmp(split[0],"help")==0&&cmdSpt==1)		//help command
		{
			displayHelp();		//display help
		}
		else if((strcmp(split[0],"clear")==0||strcmp(split[0],"cls")==0)&&cmdSpt==1)	//clear screen command
		{
			system("cls");		//clear screen
		}
		else if((strcmp(split[0],"exit")==0||strcmp(split[0],"end")==0)&&cmdSpt==1)		//exit command
		{
			printf("Exit\n");	//display exit message
		}
		else					//invalid command
		{
			printf("Invalid command or incorrect command syntax, type <help> for command list and usage.\n\n");
		}
		
		if(fileA!=NULL)			//close all file pointers after all operations are done
			fclose(fileA);
		if(fileB!=NULL)
			fclose(fileB);
		if(fileTar!=NULL)
			fclose(fileTar);
		
	} while(strcmp(cmd,"exit")!=0&&strcmp(cmd,"end")!=0);	//loop until exit
	return 0;
}

//function for displaying help message
void displayHelp()
{
	printf("\nCommand help\n\n");
	printf("<target> is a file you want to save the result to.\n");
	printf("If the file already exists the file will be overwrited.\n\n");

	printf("show\t\t\tShow matrix from file.\n\t\t\t show <file>\n");
	printf("create\t\t\tCreate a new matrix with specified size.\n\t\t\t create <row> <col> <target>\n");
	printf("copy\t\t\tCopy matrix to a new file.\n\t\t\t copy <original> <target>\n");
	printf("add\t\t\tAdd two matrices.\n\t\t\t add <file 1> <file 2> <target>\n");
	printf("subtract OR sub\t\tSubtract two matrices.\n\t\t\t sub <file 1> <file 2> <target>\n");
	printf("muliply OR mul\t\tMultiply two matrices.\n\t\t\t mul <file 1> <file 2> <target>\n");
	printf("mulscalar OR muls\tMultiply a matrix with scalar.\n\t\t\t muls <number> <file> <target>\n");
	printf("transpose OR trans\tTranspose a matrix.\n\t\t\t trans <file> <target>\n");
	printf("identity OR iden\tGenerate identity matrix with specified size.\n\t\t\t iden <number> <target>\n");
	printf("help\t\t\tShow command help.\n");
	printf("clear OR cls\t\tClear the screen.\n");
	printf("exit OR end\t\tExit the program.\n\n");
}

//function for opening a file and return file pointer back
int openFile(FILE **fp,char filename[],int permission)
{
	if(permission==0)				//read permission
		(*fp)=fopen(filename,"r+");	//open with mode "r"
	else							//write permission
		(*fp)=fopen(filename,"w+");	//open with mode "w"
	
	if((*fp)!=NULL)					//open success
		return 0;
	else							//open failed
		return 1;
}

//function for reading matrix from file and save to struct
matrix readMatrix(FILE *fp)
{
	int i,j;
	matrix read;
	
	rewind(fp);										//rewind file stream first
	fscanf(fp,"%d %d",&read.row,&read.col);			//get matrix size
	for(i=0;i<read.row;i++)							//for each row...
	{
		for(j=0;j<read.col;j++)						//for each column...	
			fscanf(fp,"%lf",&read.data[i][j]);		//read as double and save to data[][] array in struct
	}
	//fclose(fp);										//close file
	return read;									//return matrix
}

//function for writing matrix to file
void writeMatrix(matrix mat,FILE *fp)
{
	int i,j;
	
	rewind(fp);										//rewind file stream first	
	fprintf(fp,"%d %d\n",mat.row,mat.col);			//save matrix size to file
	for(i=0;i<mat.row;i++)							//for each row...
	{
		for(j=0;j<mat.col;j++)						//for each column...
			fprintf(fp,"%g\t",mat.data[i][j]);		//save each data in array data[][] to file
		fprintf(fp,"\n");							//newline
	}
	
	//fclose(fp);										//close the file
}

//function for showing matrix to screen
void showMatrix(matrix mat,char name[])
{
	int i,j;
	
	printf("\nShowing matrix %s\n",name);
	printf("Matrix size: %d rows | %d columns\n\n",mat.row,mat.col);	//show matrix size
	for(i=0;i<mat.row;i++)							//for each row...
	{
		for(j=0;j<mat.col;j++)						//for each column...
			printf("%g\t",mat.data[i][j]);			//print the data to screen
		printf("\n");
	}
	printf("\n");
}

//function for creating matrix from user input
void createMatrix(int row,int col,FILE *fp)
{
	int i,j;
	char after;
	matrix input;
	
	input.row=row;		//set row and column in struct
	input.col=col;
	
	printf("Creating [%dx%d] matrix:\n",row,col);
	for(i=0;i<row;i++)			//for each row...
	{
		for(j=0;j<col;j++)		//for each column...
		{
			printf("Enter data for position [%d,%d] > ",i+1,j+1);
			while(scanf("%lf%c",&input.data[i][j],&after)!=2||after!='\n')		//scan the input from keyboard to array data[][] + error checking
			{
				rewind(stdin);	//rewind in case of invalid input			
				printf("Error: invalid input, try again> ");
			}
		}
	}
	
	writeMatrix(input,fp);		//call writeMatrix() to save the struct to file
}

//function for adding matrices
int addMatrix(matrix A,matrix B,FILE *fp)
{
	int i,j;
	matrix output;
	
	if(A.row!=B.row||A.col!=B.col)					//size checking	
		return 1;									//return error	
	
	output.row=A.row;								//set output matrix size
	output.col=A.col;
	
	for(i=0;i<A.row;i++)							//for each row...
	{
		for(j=0;j<A.col;j++)						//for each column...
			output.data[i][j]=A.data[i][j]+B.data[i][j];	//add current data from A and B then save to output
	}
	
	writeMatrix(output,fp);		//call writeMatrix() to save the struct to file
	return 0;					//return success
}

//function for subtracting matrices
int subMatrix(matrix A,matrix B,FILE *fp)
{
	int i,j;
	matrix output;
	
	if(A.row!=B.row||A.col!=B.col)					//size checking	
		return 1;									//return error
	
	output.row=A.row;								//set output matrix size
	output.col=A.col;
	
	for(i=0;i<A.row;i++)							//for each row...
	{
		for(j=0;j<A.col;j++)						//for each column...
			output.data[i][j]=A.data[i][j]-B.data[i][j];	//subtract current data from A and B then save to output
	}
	
	writeMatrix(output,fp);		//call writeMatrix() to save the struct to file	
	return 0;					//return success
}

//function for multipling two matrices
int mulMatrix(matrix A,matrix B,FILE *fp)
{
	int i,j,k;
	double temp;
	matrix output;
	
	if(A.col!=B.row)				//first matrix's column must be equal to second matrix's row
		return 1;					//return error	
	
	output.row=A.row;				//result matrix will have row count of first matrix...
	output.col=B.col;				//and column count of second matrix
	
	for(i=0;i<A.row;i++)			//for each row...
	{
		for(j=0;j<B.col;j++)		//for each column...
		{
			temp=0;					//set temporary sum to 0
			for(k=0;k<A.col;k++)	//for each data to be sum this round...
			{
				temp+=(A.data[i][k]*B.data[k][j]);	//add sum to temp
			}
			output.data[i][j]=temp;	//save temp to data[][]
		}
	}
	
	writeMatrix(output,fp);			//call writeMatrix() to save the struct to file
	return 0;						//return success
}	

//function for multiplying matrix with scalar
void mulScaMatrix(matrix A,double mul,FILE *fp)
{
	int i,j;
	matrix output;
	
	output.row=A.row;				//set output matrix size
	output.col=A.col;
	
	for(i=0;i<A.row;i++)			//for each row...
	{	
		for(j=0;j<A.col;j++)		//for each column...
			output.data[i][j]=A.data[i][j]*mul;		//multiply current data with mul and save to data[][]
	}
	
	writeMatrix(output,fp);			//call writeMatrix() to save the struct to file
}

//function to transpose the matrix
void transMatrix(matrix A,FILE *fp)
{
	int i,j;
	matrix output;
	
	output.row=A.col;				//set output matrix size (inverse of original)
	output.col=A.row;
	
	for(i=0;i<A.row;i++)			//for each row...
	{
		for(j=0;j<A.col;j++)		//for each column...
			output.data[j][i]=A.data[i][j];		//set output data (inverse of original)
	}
	
	writeMatrix(output,fp);			//call writeMatrix() to save the struct to file
}

//function for generating identity matrix
void idenMatrix(int size,FILE *fp)
{
	int i,j;
	matrix output;
	
	output.row=size;				//set output matrix size
	output.col=size;
	
	for(i=0;i<size;i++)				//for each row...
	{
		for(j=0;j<size;j++)			//for each column...
		{
			if(i==j)					//if currently at the main diagonal...
				output.data[i][j]=1;	//set this cell to 1	
			else
				output.data[i][j]=0;	//set this cell to 0	
		}
	}
	
	writeMatrix(output,fp);			//call writeMatrix() to save the struct to file
}