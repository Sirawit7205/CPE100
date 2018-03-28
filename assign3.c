#include<stdio.h>
#include<time.h>
#include<stdlib.h>

int main()
{
	int input, answer, guess_round, win;
	char name [50]={};
	char aft, cont;
	
	printf("Welcome to number guessing game.\n");
	printf("Please enter your name: ");
	scanf("%s",name);
	printf("Hello %s!\n", name);
	
	do
	{
		srand(time(NULL));
		answer = (rand()%100)+1;
		guess_round = 1;
		win=0;
		
		do
		{
			printf("%s, please enter round %d guess between 1-100: ", name, guess_round);
			while(scanf("%d%c", &input, &aft)!=2||aft!='\n'||input<1||input>100)
			{
				rewind(stdin);
				printf("Invalid input, please try again.\n");
			}
			
			if(input==answer)
				win=1;
			else
			{
				if(input>answer)
					printf("%s, your answer is too high.\n", name);
				else
					printf("%s, your answer is too low.\n", name);
				guess_round++;
			}
		} while(guess_round<=7&&win==0);
		
		if(win==1)
			printf("%s, your answer is correct, you win the game! Total guesses: %d\n", name, guess_round);
		else
			printf("%s, you exceeded your quota and lost the game! Correct answer is %d\n", name, answer);
		
		do
		{
			printf("Do you want to play again? (Y/N): ");
			rewind(stdin);
			scanf("%c",&cont);
		} while(cont!='n'&&cont!='y'&&cont!='N'&&cont!='Y');
		
	} while(cont=='y'||cont=='Y');
	
	printf("Program ended.\n");
	
	return 0;
}