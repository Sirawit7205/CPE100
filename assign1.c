#include<stdio.h>
#include<math.h>
#include<stdlib.h>
int main()
{   double a, b, c;
    double x1, x2;
    char ch;
    do {
        a=b=c=0;
        printf("\nProgram calculate root of Equation ax^2+bx+c=0\n");
        printf("Enter parameter a:");
        scanf("%lf",&a);
        rewind(stdin);
        printf("Enter parameter b:");
        scanf("%lf",&b);
        rewind(stdin);
        printf("Enter parameter c:");
        scanf("%lf",&c);
        x1 = (-b+sqrt(b*b-4*a*c))/(2*a);
        x2 = (-b-sqrt(b*b-4*a*c))/(2*a);
        printf("root of %.0lfx^2%+.0lfx%+.0lf = 0 is\n",a,b,c);
        printf("x1 = %lf\nx2 = %lf\n",x1,x2);
        do { rewind(stdin);
             printf("Enter y to calculate again or n to exit.");
             scanf("%c",&ch); //ch = getchar();
        } while(ch!='y' && ch!='n');
    } while(ch=='y');
    printf("\nEnd Program\n");
    return 0;
}
