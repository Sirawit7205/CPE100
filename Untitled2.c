#include<stdio.h>
#include<math.h>
#include<stdlib.h>
int main()
{   int a, b, c;
    double x1, x2;
    char ch;
    do {
        a=b=c=0;
        printf("\nProgram calculate root of Equation ax^2+bx+c=0\n");
        printf("Enter parameter a:");
        scanf("%d",&a);
        printf("Enter parameter b:");
        scanf("%d",&b);
        printf("Enter parameter c:");
        scanf("%d",&c);
        x1 = (-b+sqrt(b*b-4*a*c))/(2*a);
        x2 = (-b-sqrt(b*b-4*a*c))/(2*a);
        printf("root of %dx^2+%dx+%d = 0 is\n",a,b,c);
        printf("x1 = %lf\nx2 = %lf\n",x1,x2);
        do { printf("Enter y to calculate again or n to exit.");
             scanf("%c",&ch); //ch = getchar();
        } while(ch!='y' && ch!='n');
    } while(ch=='y');
    printf("\nEnd Program\n");
    return 0;
    }
}
