#include<stdio.h>
#include<math.h>

int main()
{
	double g=9.81; //constant
	double tx,ty,tg,sx,sy,sg,ux,uy,u,z,x,rad;
	char cont,ch;
	
	do
	{
		//Data in
		printf("\nFootball shooting calculation program.\n");
		printf("Please enter initial velocity (m/s): ");
		while(scanf("%lf%c",&u,&ch)!=2||ch!='\n')
		{
			rewind(stdin);
			printf("Data error, enter again: ");
		}
		printf("Please enter shooting angle (deg): ");
		while(scanf("%lf%c",&z,&ch)!=2||ch!='\n')
		{
			rewind(stdin);
			printf("Data error, enter again: ");
		}
		printf("Please enter distance (m): ");
		while(scanf("%lf%c",&x,&ch)!=2||ch!='\n')
		{
			rewind(stdin);
			printf("Data error, enter again: ");
		}
		
		//calculation
		rad = (z/180) * M_PI; //deg to rad
		ux = u * cos(rad); //vector x comp
		uy = u * sin(rad); //vector y comp
		ty = uy / g; //time to peak y
		tx = ty * 2; //time x
		sy = pow(uy,2) / (2*g); //max y distance
		sx = ux * tx; //max x distance
		tg = x / ux; //time to goal
		sg = (uy*tg) - 0.5*g*pow(tg,2); //height at goal
		
		//Data out
		printf("\nCalculaton results:\n");
		printf("Football reach highest height of %.2lf m at %.2lf s\n",sy,ty);
		printf("Football reach longest distance of %.2lf m at %.2lf s\n",sx,tx);
		if(sx>=x) //reach the goal
			printf("At goal, football is %.2lf m above ground at %.2lf s\n",sg,tg);
		else //not reach the goal
			printf("Football dropped %.2lf m at %.2lf s before reaching the goal.\n",x-sx,tx);
		
		if(sg>=2.44)
			printf("Result: Missed, football is too high.\n");
		else if(sx<x)
			printf("Result: Missed, football cannot reached the goal.\n");
		else if(tg>0.5)
			printf("Result: Missed, goalkeeper can saved the goal.\n");
		else
			printf("Result: Goal!\n");
		
		//recalc check
		rewind(stdin);
		printf("\nDo you want to calculate again? (y/n): ");
		while(scanf("%c",&cont)!=1||(cont!='y'&&cont!='Y'&&cont!='n'&&cont!='N'))
		{
			rewind(stdin);
			printf("Data error, enter again: ");
		}
		
	} while(cont=='y'||cont=='Y');
	
	printf("Program ended.");
	
	return 0;
}