#include<stdio.h>
#include<math.h>

#ifdef _WIN32
#include<windows.h>
#include<conio.h>
#endif

void dataOutput(double sx, double sy, double sg, double tx, double ty, double tg, double x, double u, double z);
void dataOutputWindows(double sx, double sy, double sg, double tx, double ty, double tg, double x, double u, double z);

int main()
{
	double tx,ty,tg,sx,sy,sg,ux,uy,u,z,x,rad,g=9.81;
	char cont,ch;
	
	do
	{
		//init clear screen
		#ifdef _WIN32
		system("cls");
		#endif
		
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
		
		#ifdef _WIN32
		dataOutputWindows(sx,sy,sg,tx,ty,tg,x,u,z);
		#endif
		
		#ifndef _WIN32
		dataOutput(sx,sy,sg,tx,ty,tg,x,u,z);
		#endif
		
		//recalc check
		rewind(stdin);
		printf("\nDo you want to calculate again? (y/n): ");
		while(scanf("%c",&cont)!=1||(cont!='y'&&cont!='Y'&&cont!='n'&&cont!='N'))
		{
			rewind(stdin);
			printf("Data error, enter again: ");
		}
		
	} while(cont=='y'||cont=='Y');
	
	return 0;
}

//not Windows
#ifndef _WIN32
void dataOutput(double sx, double sy, double sg, double tx, double ty, double tg, double x, double u, double z)
{
	//Data out
	printf("\nInput parameters:\n");
	printf("Initial velocity (m/s): %.2lf\n",u);
	printf("Shooting angle (deg): %.2lf\n",z);
	printf("Goal distance (m): %.2lf\n",x);
	printf("\nCalculation results:\n");
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
	
	printf("Animation is not available in this OS.\n");
}
#endif

//Windows only
#ifdef _WIN32
void dataOutputWindows(double sx, double sy, double sg, double tx, double ty, double tg, double x, double u, double z)
{	
	int i;
	char scene[10][100]={"							..",
						"							||\\",
						"   O_/						\\O	|| \\",
						" _/|						\\|	||  \\",
						" __)\\						/|	||   \\",
						"`    \\o				  	       |  \\	||____\\",}; //art from ascii-art.de
	
	//Windows API declarations
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	CONSOLE_CURSOR_INFO cursorInfo;
	DWORD consoleSize, writtenLen;
	WORD original_attrib;
	WORD green = FOREGROUND_GREEN;
	WORD red = FOREGROUND_RED | FOREGROUND_INTENSITY;
	COORD startCoord = {0,0}, finalCoord = {0,10}, currentCoord = {0,0}, varCoord = {0,11};
	COORD coordListOver[13]={{6,8},{13,5},{15,4},{20,3},{25,2},{30,1},{35,0},{40,0},{45,0},{50,1},{55,2},{60,3},{65,4}};
	COORD coordListGoal[12]={{6,8},{10,6},{15,5},{20,4},{25,3},{30,2},{35,2},{40,2},{45,3},{50,4},{55,5},{59,6}};
	COORD coordListSave[12]={{6,8},{10,7},{13,6},{16,5},{20,4},{23,3},{25,2},{28,2},{31,2},{37,3},{43,4},{47,5}};
	COORD coordListNear[9]={{6,8},{10,7},{13,6},{18,5},{21,4},{24,5},{29,6},{32,7},{38,8}};
	
	GetConsoleScreenBufferInfo(console, &consoleInfo);
	original_attrib = consoleInfo.wAttributes; //save original console attributes to revert to later
	
	cursorInfo.dwSize = 100; //for cursor hiding
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(console, &cursorInfo);
	
	//Clear screen
	system("cls");
	
	//Data out
	printf("\nInput parameters:\n");
	printf("Initial velocity (m/s): %.2lf\n",u);
	printf("Shooting angle (deg): %.2lf\n",z);
	printf("Goal distance (m): %.2lf\n",x);
	printf("\nCalculation results:\n");
	printf("Football reach highest height of %.2lf m at %.2lf s\n",sy,ty);
	printf("Football reach longest distance of %.2lf m at %.2lf s\n",sx,tx);
	if(sx>=x) //reach the goal
		printf("At goal, football is %.2lf m above ground at %.2lf s\n",sg,tg);
	else //not reach the goal
		printf("Football dropped %.2lf m at %.2lf s before reaching the goal.\n",x-sx,tx);
	
	SetConsoleTextAttribute(console, red);
	if(sg>=2.44)
		printf("Result: Missed, football is too high.\n");
	else if(sx<x)
		printf("Result: Missed, football cannot reached the goal.\n");
	else if(tg>0.5)
		printf("Result: Missed, goalkeeper can saved the goal.\n");
	else
	{
		SetConsoleTextAttribute(console, green);
		printf("Result: Goal!\n");
	}
	
	SetConsoleTextAttribute(console, original_attrib);
	
	//printing scene
	printf("\n\n\n");
	for(i=0;i<6;i++)
		printf("%s\n",scene[i]);
	
	//football animation
	if(sg>=2.44)
	{
		for(i=0;i<12;i++)
		{
			Sleep(100);
			currentCoord.X = coordListOver[i].X + varCoord.X;
			currentCoord.Y = coordListOver[i].Y + varCoord.Y;
			SetConsoleCursorPosition(console, currentCoord);
			printf(" ");
			currentCoord.X = coordListOver[i+1].X + varCoord.X;
			currentCoord.Y = coordListOver[i+1].Y + varCoord.Y;
			SetConsoleCursorPosition(console, currentCoord);
			printf("o");
		}
	}
	else if(sx<x)
	{
		for(i=0;i<8;i++)
		{
			Sleep(100);
			currentCoord.X = coordListNear[i].X + varCoord.X;
			currentCoord.Y = coordListNear[i].Y + varCoord.Y;
			SetConsoleCursorPosition(console, currentCoord);
			printf(" ");
			currentCoord.X = coordListNear[i+1].X + varCoord.X;
			currentCoord.Y = coordListNear[i+1].Y + varCoord.Y;
			SetConsoleCursorPosition(console, currentCoord);
			printf("o");
		}
	}
	else if(tg>0.5)
	{
		for(i=0;i<11;i++)
		{
			Sleep(100);
			currentCoord.X = coordListSave[i].X + varCoord.X;
			currentCoord.Y = coordListSave[i].Y + varCoord.Y;
			SetConsoleCursorPosition(console, currentCoord);
			printf(" ");
			currentCoord.X = coordListSave[i+1].X + varCoord.X;
			currentCoord.Y = coordListSave[i+1].Y + varCoord.Y;
			SetConsoleCursorPosition(console, currentCoord);
			printf("o");
		}
	}
	else
	{
		for(i=0;i<11;i++)
		{
			Sleep(100);
			currentCoord.X = coordListGoal[i].X + varCoord.X;
			currentCoord.Y = coordListGoal[i].Y + varCoord.Y;
			SetConsoleCursorPosition(console, currentCoord);
			printf(" ");
			currentCoord.X = coordListGoal[i+1].X + varCoord.X;
			currentCoord.Y = coordListGoal[i+1].Y + varCoord.Y;
			SetConsoleCursorPosition(console, currentCoord);
			printf("o");
		}
	}
	
	//back to bottom
	currentCoord.X = finalCoord.X + varCoord.X;
	currentCoord.Y = finalCoord.Y + varCoord.Y;
	SetConsoleCursorPosition(console,currentCoord);
	
	//show cursor
	cursorInfo.dwSize = 10;
	cursorInfo.bVisible = TRUE;
	SetConsoleCursorInfo(console, &cursorInfo);
}
#endif