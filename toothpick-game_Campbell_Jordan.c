#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define STRIKES 6
#define SIZE 20

void rules(void); //display rules of the game
void maskWord (char starword[], int size); //mask the word with stars to display
int playRound(char starword[], char answer[]); //play a round of hangman
int occurancesInWord(char userguess, char answer[]); //number of times letter occurs in word
void updateStarWord(char starword[], char answer[], char userguess); //replace respective *
void playAgain(int *play); //ask user if to play again. 1 is yes 2 is no


int main()
{
    char answer[SIZE] = "";
    
    //File pointer to read from word file
    FILE *fptr = fopen("words.txt", "r"); 

    int play = 1;
    int *playptr = &play;
    int result;
    
    //call rules
    rules();

    while(play == 1) //Repeat while user selects play again (play = 1)
    {
        int scanresult = fscanf(fptr, "%s", answer); //Read a new word from file, will go down a line for repeated calls

        if(scanresult != 1) //if file wasn't successfully read
        {
            printf("End of solution file reached.\n");
            printf("Thank you for playing today!.\n");
            fclose(fptr);
            
            return 0;
        }
        
        char starword[SIZE] = "";
        maskWord(starword, strlen(answer)); //create a masked word the size of answer
        result = playRound(starword, answer);
        //Store the return value of playround in result

        if(result == 1) //if user wins
        {
            printf("\nCongratulations! You won! The word was %s.\n", answer);
        }
        else //if user loses
        {
            printf("************************************************************************\n");
            printf("Sorry you did not win the round. The word was %s.\n", answer);
        }
        playAgain(playptr); //Ask to play again
    }

    printf("Thank you for playing today!\n"); //Print when user does not play again
    fclose(fptr); //close file

    
    return 0;
}

void rules(void)
{
    //Display rules
    printf("Welcome to the Hangman Game!\n");
    printf("************************************************************************\n");
    printf("Here are the rules.\n");
    printf("I will provide you a set of * characters for each round.\n");
    printf("Each * represents a letter in the English Alphabet.\n");
    printf("You must figure out each letter of the missing word.\n");
    printf("For every correct letter guessed, I will reveal its place in the word.\n");
    printf("Each mistake will result in a strike.\n");
    printf("6 strikes will result in a loss that round.\n");
    printf("Are you ready? Here we go!\n");
    printf("************************************************************************\n");
    

}

void maskWord(char starword[], int size)
{
    for(int i = 0; i < size; ++i) 
    {
        starword[i] = '*'; //set startword[i] to * for the until reaching size (len of answer)
    }
}

int playRound(char starword[], char answer[])
{   
    //Declare and assign variables
    char waste[SIZE]; //string for extra input
    char userguess = ' ';
    char xtra;
    char guessStr[SIZE] = "";
    int size = strlen(answer);
    int x = 0; //strike counter

    //Display welcome and word size
    printf("Welcome to the Round!\n");
    printf("The size of the word is %d letters.\n\n", size);
    

    while(x < STRIKES) //while there are strikes remaining
    {
        do{
            printf("You currently have %d strike(s).\n", x);
            printf("Letter(s) you have guessed: %s\n\n", guessStr);

            printf("%s\n", starword);

            printf("\nEnter your guess: ");
            scanf(" %c%c", &userguess, &xtra); //scan for user guess and char after it

            //if input is invalid or more than on char inputted
            if(isdigit(userguess) || ispunct(userguess) || xtra != '\n') 
            {
                printf("\nPlease enter a single letter from the alphabet.\n\n");
                if(xtra != '\n')//if char after userguess is not blank (\n)
                {
                    fgets(waste, SIZE, stdin); //Clear buffer by storing extra input in useless string
                }
            }
            
        }while(userguess == ' ' || isdigit(userguess) || ispunct(userguess) || xtra != '\n');   
        //Repeat until input is valid 

        //change userguess to be lowercase
        userguess = tolower(userguess);

        //update starword with guesses
        updateStarWord(starword, answer, userguess);


        if(strcmp(starword, answer) == 0) //if starword is equal to answer
        {
            return 1;
        }

        //if occurancesInWord returns a pos value, userguess occurs at least once in answer
        if(occurancesInWord(userguess, answer) > 0)  
        {
            printf("\nThe letter %c is in the word.\n\n", userguess);
            strncat(guessStr, &userguess, 1); //add the userguess to the total guesses string
        }
        else //userguess does not exist in answer
        {
            printf("\nThe letter %c is NOT in the word.\n\n", userguess);
            strncat(guessStr, &userguess, 1); //add the userguess to the total guesses string
            x++; //add to strike counter
        }

        
    }

    return 0;

}

int occurancesInWord(char userguess, char answer[])
{
    int occ = 0; //occurances counter

    for(int i = 0; i < strlen(answer); ++i) //for every char in answer
        {
            if(answer[i] == userguess) //if the char at [i] == userguess
            {
                occ++; //increment occurance counter
            }
        }

    return occ; //return total occurances
}

void updateStarWord(char starword[], char answer[], char userguess)
{

    for(int i = 0; i < strlen(answer); ++i) //for every char in answer
    {
        if(answer[i] == userguess) //if the char at [i] == userguess
        {   
            starword[i] = userguess; //set startword[i] = userguess
        }
    }

}

void playAgain(int *play)
{   
    char trash[SIZE]; //string for extra input
    int choice = 0;

    do{
        //display choice options
        printf("************************************************************************\n");
        printf("Would you like to play another round?\n");
        printf("1: Yes\n");
        printf("2: No\n");
        printf("Choice: ");
        if(scanf("%d", &choice) != 1) //if scanf did not properly read int
        {
            fgets(trash, SIZE, stdin); //store input in trash string
        }
        printf("************************************************************************\n");

        if(choice != 1 && choice != 2) //if answer is not 1 or 2
        {
            printf("Please select 1 or 2.\n");
        }
    }while(choice != 1 && choice != 2);//repeat while input is invalid

    *play = choice; //set the value at the dereferenced address of play to = choice
}