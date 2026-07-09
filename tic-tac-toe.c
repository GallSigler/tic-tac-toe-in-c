#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int displayCurrentState(int a[]);
int displayArray(int a[], int k); 
int playerMove(int a[]); 
int opponentMove(int a[]); 
int victoryMoves(int a[], int k, int *OpponentMoveCounter);
int randomPlacement(int a[], int *OpponentMoveCounter);
int assessVictory(int a[], int playerCode, int *done); 
int main(void)
{
    srand(time(NULL)); 
    int tracker[9] = {0}; 

    //STEP 1: start the game
    printf("Do you want to start? Y/N\n"); 

    char startInput[5];
    char startAnswer; 
    fgets(startInput, sizeof(startInput), stdin); //grabs the entire string from the keyboard, emptying the buffer
    sscanf(startInput, "%c", &startAnswer);//extracts the character 

    while(startAnswer!='Y'&&startAnswer!='N'&&startAnswer!='y'&&startAnswer!='x') 
    {
        printf("You typed %c, which is an invalid input.\n", startAnswer); 
        printf("Do you want to start? Y/N\n"); 
        fgets(startInput, sizeof(startInput), stdin); 
        sscanf(startInput, "%c", &startAnswer);
    }

    if (startAnswer=='Y' || startAnswer=='y') {
        printf("Awesome. You will start the game. below is an illustration of the game grid:\n"); 
        for (int i=0; i<3; i++)  
        {
            for (int j=0; j<3; j++) 
            {
                printf("|  %i,%i   ", i+1, j+1); 
            }
            printf("\n"); 
        }

        printf("\n\n"); 
        printf("As you can see, the left number designates the rows and the right number deisgnates the columns.\n\n"); 
        printf("You are X. Where would you like to place your X?\n\n");

        int *board; 
        int gameDoneRaw=0;
        int *gameDone = &gameDoneRaw; 
        int endGame=0; 


        while(1){
            //PLAYER
            playerMove(tracker);
            //displayCurrentState(tracker); 
            //displayArray(tracker,3);
            assessVictory(tracker, 1, gameDone); 

            if (*gameDone==1){
                return 0; 
            }

            endGame++; 
            if(endGame==9){
                displayCurrentState(tracker);
                printf("Stalemate! Try again."); 
                return 0; 
            }

            //OPPONENT
            opponentMove(tracker);  
            displayCurrentState(tracker);  
            //displayArray(tracker,3);
            assessVictory(tracker, 10, gameDone);
            if (*gameDone==1){
                return 0; 
            }

            endGame++; 
            if(endGame==9){
                printf("Stalemate! Try again."); 
                return 0; 
            }
        }
    }

    else 
    {
        printf("Awesome. The computer will start the game. below is an illustration of the game grid:\n"); 
        for (int i=0; i<3; i++)  
        {
            for (int j=0; j<3; j++) 
            {
                printf("|  %i,%i   ", i+1, j+1); 
            }
            printf("\n"); 
        }

        printf("\n\n"); 
        printf("As you can see, the left number designates the rows and the right number deisgnates the columns.\n\n"); 

        int *board; 
        int gameDoneRaw=0;
        int *gameDone = &gameDoneRaw; 
        int endGame=0; 
        endGame++; 

        opponentMove(tracker);  
        displayCurrentState(tracker);  
        printf("The computer played. Where would you like to place your X?\n\n");

        while(1){
            //PLAYER
            playerMove(tracker);
            //displayCurrentState(tracker); 
            //displayArray(tracker,3);
            assessVictory(tracker, 1, gameDone); 

            if (*gameDone==1){
                return 0; 
            }

            endGame++; 
            if(endGame==9){
                displayCurrentState(tracker);
                printf("Stalemate! Try again."); 
                return 0; 
            }

            //OPPONENT
            opponentMove(tracker);  
            displayCurrentState(tracker);  
            //displayArray(tracker,3);
            assessVictory(tracker, 10, gameDone);
            if (*gameDone==1){
                return 0; 
            }

            endGame++; 
            if(endGame==9){
                printf("Stalemate! Try again."); 
                return 0; 
            }
        }
        return 0; 
    }
}


int displayCurrentState(int a[]) 
{
    printf("\n\nHere is the board:\n\n"); 
    
    for (int k=0;k<9;k++)
    {
        if (a[k]==1) {
            printf("|  X   "); 
        } 
        else if (a[k]==10)
        {  
            printf("|  O   "); 
        }
         
        else {
            printf("|      "); 
        }

        //add linebreak
        if ((k+1)%3==0) {
            printf("|\n"); 
        }
    }
    printf("\n"); 
}

int displayArray(int a[], int k) {
    int j=0; 
    for (int i=0; i<k; i++){
        for (; j<k*(i+1); j++) {
            printf("%i, ", a[j]); 
        }
        j=3*(i+1); 
        printf("\n"); 
    }

    printf("\n"); 
}

int playerMove(int a[])
{

int processedCol; 
int processedRow; 
do
{
    printf("Column:"); 
    char col[5]; 
    fgets(col, sizeof(col), stdin); 
    sscanf(col, "%i", &processedCol);
    printf("Row:"); 
    char row[5]; 
    fgets(row, sizeof(row), stdin); 
    sscanf(row, "%i", &processedRow); 
    if (processedRow!=1 && processedRow!=2 && processedRow!=3) {
        printf("You provided an invalid index. Try again.\n");
    }
    if (a[(processedCol-1)+(3*(processedRow-1))]!=0) {
        printf("You tried to cheat! Shame on you. Try again.\n");
    }
} while ((processedRow!=1 && processedRow!=2 && processedRow!=3)||(processedCol!=1&&processedCol!=2&&processedCol!=3)||(a[(processedCol-1)+(3*(processedRow-1))]!=0));

    a[(processedCol-1)+(3*(processedRow-1))]=1;
}

int opponentMove(int a[]) 
{
        int counter = 0; 
        printf("\nComputer making move...\n"); 
        victoryMoves(a, 20, &counter); //first check victory possibility
        if (counter!=0)
        {
            printf("Opponent identified winning move...\n\n"); 
            return 0; //break out of the function if move was made
        } 
        victoryMoves(a, 2, &counter); //second prevent opponent victory possibility
        if (counter!=0)
        {
            printf("Opponent prevented you from winning...\n\n"); 
            return 0; //break out of the function if move was made
        }

        randomPlacement(a, &counter); 
        if (counter!=0)
        {
            return 0; //break out of the function if move was made
        }
}

int victoryMoves(int a[], int k, int *OpponentMoveCounter)//k is 2 for player victory, 20 for opponent

{
    for(int p=0;p<7;p=p+3)
        {
            if (a[p]+a[p+1]+a[p+2]==k)//meaning that the opponent has two out of three
            {
                for(p; p<p+3;p++)
                {
                    if (a[p]==0) {
                        a[p]=10; //make the move
                        *OpponentMoveCounter=1; //account for the fact that we did a move
                        break;
                    } 
                }
            }
            if (*OpponentMoveCounter == 1) 
            {
                break; 
            }
        }

        if (*OpponentMoveCounter == 1) 
            {
                return 0; 
            }

        for (int h=0;h<3;h++)
        {
            if (a[h]+a[h+3]+a[h+6]==k)//meaning that the opponent has two out of three
            {
                for(h; h<h+7;h=h+3)
                {
                    if (a[h]==0) {
                        a[h]=10; //make the move
                        *OpponentMoveCounter=1; 
                        break;
                    } 
                }
            }
            if (*OpponentMoveCounter == 1) 
                {
                    break; 
                }
        }
        
        if (*OpponentMoveCounter == 1) 
            {
                return 0; 
            }
        if(a[0]+a[4]+a[8]==k){
            for(int m=0;m<9;m=m+4)
            {
                if (a[m]==0) {
                    a[m]=10; //make the move
                    *OpponentMoveCounter=1; 
                    break;
                } 
            }
        }
        if (*OpponentMoveCounter == 1) 
        {
            return 0; 
        }
        if(a[2]+a[4]+a[6]==k){
            for(int m=2;m<7;m=m+2)
            {
                if (a[m]==0) {
                    a[m]=10; //make the move
                    *OpponentMoveCounter=1; 
                    break;
                } 
            }
        }
        if (*OpponentMoveCounter == 1) 
        {
            return 0; 
        }
}

int randomPlacement(int a[], int *OpponentMoveCounter)
{
    int emptySlotsCount=0; 

    //extract number of empty slots
    for(int i=0;i<9; i++){
        if(a[i]==0) {
            emptySlotsCount=emptySlotsCount+1; 
        }
    }
    int random = rand(); 
    printf("Random number: %i\n", random);
    
    int chosenIndex = random%emptySlotsCount; 
    printf("Chosen index: %i\n", chosenIndex);

    int iterSlotsCount=0; //initialize a variable to count through loops in the array

    for (int iter=0;iter<9;iter++)//iterating over the slots, assessing if they are empty and placing a 'O' in the generated index
    {
        if(a[iter]==0) {
            iterSlotsCount=iterSlotsCount+1; 
            if(iterSlotsCount==chosenIndex) 
            {
                a[iter]=10; 
                *OpponentMoveCounter = 1; 
                return 0; 
            }
        }

    }
    if (*OpponentMoveCounter!=1)
    {
        printf("Opponent did not make a move. Program error."); 
        exit(1); 
    }
}

int assessVictory(int a[], int playerCode, int *done) {

    char *gameOverText; 
    //customizing text
    if(playerCode==1) {
        gameOverText = "Congratulations! You won."; 
    } else {
        gameOverText = "The computer won, unfortunately. Try again!"; 
    }

    int check=0; 
    for(;check<7;check=check+3){
        if(a[check]+a[check+1]+a[check+2]==(3*playerCode)) {
            displayCurrentState(a); 
            printf("%s", gameOverText); 
            (*done)=1; 
            return 0;
        }
    }
    check = 0; //reset check
    for(;check<3;check++){
        if(a[check]+a[check+3]+a[check+6]==(3*playerCode)) {
            displayCurrentState(a); 
            printf("%s", gameOverText); 
            (*done)=1; 
            return 0;
        }
    }
    //check diagonals 
    if(a[0]+a[4]+a[8]==(3*playerCode)){
        displayCurrentState(a); 
        printf("%s", gameOverText); 
        (*done)=1; 
        return 0;
    }
    if(a[2]+a[4]+a[6]==(3*playerCode)){
        displayCurrentState(a); 
        printf("%s", gameOverText); 
        (*done)=1; 
        return 0;
    }
}