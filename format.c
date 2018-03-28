1 	#include<stdio.h>
2 	#include<math.h>
3 	#include<stdlib.h>
4 	int main()
5 	{   double a, b, c;
6 		double x1, x2;
7 		char ch;
8 		do {
9 			a=b=c=0;
10			printf("\nProgram calculate root of Equation ax^2+bx+c=0\n");
11			printf("Enter parameter a:");
12			scanf("%lf",&a);
13			rewind(stdin);
14			printf("Enter parameter b:");
15			scanf("%lf",&b);
16			rewind(stdin);
17			printf("Enter parameter c:");
18			scanf("%lf",&c);
19			x1 = (-b+sqrt(b*b-4*a*c))/(2*a);
20			x2 = (-b-sqrt(b*b-4*a*c))/(2*a);
21			printf("root of %.0lfx^2%+.0lfx%+.0lf = 0 is\n",a,b,c);
22			printf("x1 = %lf\nx2 = %lf\n",x1,x2);
23			do { rewind(stdin);
24				 printf("Enter y to calculate again or n to exit.");
25				 scanf("%c",&ch); //ch = getchar();
26			} while(ch!='y' && ch!='n');
27		} while(ch=='y');
28		printf("\nEnd Program\n");
29		return 0;
30	}
31