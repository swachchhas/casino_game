#include <stdio.h>
#include <stdlib.h>

void displayRules();
void playRound();
void saveGame(char playerName[], int balance);
void loadGame(char playerName[], int *balance);

int main()
{
    char playerName[50];
    int initialDeposit;

    printf("Do you want to start a new game or load a previous one?\n");
    printf("1. New Game\n");
    printf("2. Load Game\n");
    int choice;
    scanf("%d", &choice);

    if (choice == 1)
    {
        displayRules();
        printf("\n\n");

        printf("Enter your cool name: ");
        scanf("%s", playerName);

        printf("\n\n");

        printf("Deposit some cool cash to start the game: $");
        scanf("%d", &initialDeposit);

        printf("\n\n");
    }
    else if (choice == 2)
    {
        loadGame(playerName, &initialDeposit);
        printf("\n\n");
    }

    printf("Your current balance is $%d", initialDeposit);

    printf("\n\n");

    int betAmount;
    printf("%s, place a bet: $", playerName);
    scanf("%d", &betAmount);

    printf("\n\n");

    if (betAmount > initialDeposit)
    {
        printf("Oops, you're going overboard. Try again: $");
        scanf("%d", &betAmount);
    }

    printf("\n\n");

    int computerNumber = rand() % 10;

    int userGuess;
    printf("Guess a number between 1 and 10: ");
    scanf("%d", &userGuess);

    printf("\n\n");

    if (userGuess > 10)
    {
        printf("Hold on, that number is too high. Try again: ");
        scanf("%d", &userGuess);
    }

    printf("\n\n");

    if (userGuess == computerNumber)
    {
        printf("Congratulations, you won $%d", betAmount);
        printf("\n\n");

        int totalWinnings = (betAmount == initialDeposit) ? (betAmount * 10) : (betAmount * 10 + initialDeposit);

        printf("You now have $%d in total winnings", totalWinnings);

        saveGame(playerName, totalWinnings);
    }
    else
    {
        printf("Oops, you lost $%d", betAmount);
        printf("\n\n");

        printf("The correct number was: %d", computerNumber);
        printf("\n\n");

        int remainingBalance = initialDeposit - betAmount;

        printf("Now you have $%d left in your cool balance", remainingBalance);

        printf("\n\n");

        if (remainingBalance == 0)
        {
            printf("Sorry, you're broke!\n");
            printf("No more cool money to play with. Have a fantastic day!");
        }
        else
        {
            int continueDecision;
            printf("Press 1 for YES\n");
            printf("Press 2 for NO\n\n");

            printf("Do you want to keep the cool game going (Y/N): ");
            scanf("%d", &continueDecision);
            printf("\n\n");

            if (continueDecision == 1)
            {
                displayRules();

                printf("\n\n");

                printf("Now you have $%d as a super cool balance", remainingBalance);

                printf("\n\n");

                int nextBet;
                printf("%s, place your next cool bet: $", playerName);
                scanf("%d", &nextBet);
                printf("\n\n");

                if (nextBet > remainingBalance)
                {
                    printf("Oops, that's more than you have. Try again: $");
                    scanf("%d", &nextBet);
                }

                int userGuessNext;
                printf("Choose another number between 1 and 10: ");
                scanf("%d", &userGuessNext);
                printf("\n\n");

                int computerNumberNext = 9; // Change this to your preference

                if (userGuessNext > 10)
                {
                    printf("Whoa, that's beyond the limit. Try again: $");
                    scanf("%d", &userGuessNext);
                    printf("\n\n");
                }

                if (userGuessNext == computerNumberNext)
                {
                    printf("Amazing! You won $%d", nextBet);
                    printf("\n\n");

                    int totalWinningsNext = (nextBet == remainingBalance) ? (nextBet * 10) : (nextBet * 10 + remainingBalance);

                    printf("Now your total winnings are $%d", totalWinningsNext);

                    saveGame(playerName, totalWinningsNext);
                }
                else
                {
                    printf("Sorry, you lost $%d", nextBet);
                    printf("\n\n");

                    int remainingBalanceNext = remainingBalance - nextBet;

                    printf("You now have $%d in your super cool balance", remainingBalanceNext);

                    printf("\n\n");

                    if (remainingBalanceNext == 0)
                    {
                        printf("Oops, you're out of cool cash!\n");
                        printf("No more cool money to play with. Have a fantastic day!");
                    }
                }
            }
            else if (continueDecision == 2)
            {
                printf("Alright, have an absolutely awesome day!");
            }
        }
    }

    return 0;
}

void displayRules()
{
    printf("---------------------------------------------------------\n");
    printf("                       SUPER COOL RULES\n");
    printf("---------------------------------------------------------\n");
    printf("1. Choose any number between 1 and 10\n");
    printf("2. Win to get 10 times your cool bet amount\n");
    printf("3. Lose and say goodbye to your betting amount\n");
    printf("---------------------------------------------------------\n");
}

void saveGame(char playerName[], int balance)
{
    FILE *file = fopen("casino_save.txt", "r");

    if (file == NULL)
    {
        printf("Error opening file for saving game data.\n");
        return;
    }

    fprintf(file, "%s\n%d", playerName, balance);

    fclose(file);
}

void loadGame(char playerName[], int *balance)
{
    FILE *file = fopen("casino_save.txt", "r");

    if (file == NULL)
    {
        printf("No saved game found. Starting a new game.\n");
        return;
    }

    fscanf(file, "%s %d", playerName, balance);

    fclose(file);

    printf("Loaded game for %s with a balance of $%d.\n", playerName, *balance);
}