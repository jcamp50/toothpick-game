#define ROUNDS 3
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

void greeting(); //display welcome message to user
int playRound(int round); //play one round
int humanPick(); //retrieve the user's guess
int computerPick(int choice, int leftover); //computer makes its pick
int leftOnTable(int toothpicks, int taken); //calculate number of toothpicks left
void winnerAnnouncment(int user); //overall winner of round announcement

int main()
{
	//insert some code here that will greet the user
	greeting();
	
	for(int x = 0; x < ROUNDS; ++x)
	{
		int result = playRound(x + 1); //call playRound and assign result the value function returns
		
		winnerAnnouncment(result); 
		//Annouce winner based on value stored in result
	}
	
	printf("********************************************************\n");
	printf("Thank you for playing!\n");
	return 0;
}

int playRound(int round)
{
	printf("Welcome to round %d!\n", round);
	printf("You may go first!\n");
	
	int toothpicks = 31; //Initial amount of toothpicks

	
	//loop that keeps track of toothpicks until respective no more toothpicks left. we will learn about conditional loops soon :)
	
	while(toothpicks != 0)
	{
		printf("********************************************************\n");
		printf("There are %d toothpick(s) left on the table.\n", toothpicks);
		int humTaken = humanPick();
		if((humTaken == 1 || humTaken == 2 || humTaken == 3) && humTaken <= toothpicks)
		//User pick must 1, 2, or 3, and <= the current amount of toothpicks
		{			
			printf("You took %d off the table.\n", humTaken);
			toothpicks = leftOnTable(toothpicks, humTaken);
			//assign toothpicks the current amount left of the table
			if(toothpicks == 0)
			{
				return 0;
				//End while loop after user picks if toothpicks == 0
			}
			toothpicks -= computerPick(humTaken, toothpicks); 
			
			printf("********************************************************\n");	
		}
		else //User makes invalid selection
		{	
			printf("Please select 1, 2, or 3 toothpicks.\nDo not try to take more toothpicks than are on the table.\n");
		}
		
	}
	
	return 1;
}

void greeting()
{
	//Print out greeting statement
	printf("********************************************************\n");
	printf("Welcome to Toothpick Game!\n");
	printf("Here are the rules.\n");
	printf("There are currently 31 toothpicks on the table.\n");
	printf("You and I will each get a turn to pick either 1, 2, or 3 toothpicks off the table.\n");
	printf("The player that gets to pick the last toothpicks loses the game!\n");
	printf("Sounds easy right? Well lets see if you can beat me!\n");
	printf("Ready to play?...Here we go!\n");
	printf("********************************************************\n");
}

int leftOnTable(int toothpicks, int taken)
{
	int toothpicksLeft = toothpicks - taken; 
	return toothpicksLeft; //return amount of toothpicks left on the table
}

int humanPick()
{
	int x;
	printf("How many toothpicks do you want to take? ");
	scanf("%d", &x);
	//Store user input at x

	return x;
}

int computerPick(int choice, int leftover)
{
	int y;
	printf("My turn...\n");
	if(leftover > 4)
		y = 4 - choice; //If total toothpics > 4, computer will pick 4 -  previous user choice
	else 
	{ 
		switch(leftover)
		{
			case 4:
				y = 3;
				break;
			case 3:
				y = 2;
				break;
			case 2:
				y = 1;
				break;
			case 1:
				y = 1;

			default:
				break;
		}
	}

	printf("I will take %d toothpick(s) off the table\n", y);

	return y;
}

void winnerAnnouncment(int user)
{
	if(user == 0) //If zero was returned, user wins
		printf("You took the last toothpick, I won! Haha better luck next time!\n");
	else	//Else computer wins
		printf("I took the last toothpick, you won! I'll let you have this one.\n");
}