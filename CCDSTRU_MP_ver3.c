#include <stdio.h>
#include <stdlib.h>

/* Version History

Version No. 3 by Marco on March 18, 2026

Added more variables and descriptions to keep us informed on what we're doing.
Added the last 3 functions.
Edited some functions to include more parameters and fixed array variables.
Please also give your opinion on the variable "val" because I'm not sure what it is really.
However, I think all the functions should be complete. It's really just testing now.
I also added some parameters to the functions. Can you check the functions you call?


*/

//Declaring R B S and T
//i think we can declare these after we finish our functions

//Adding function prototypes
void removepos(int go, int pos, int R[3][3], int B[3][3]);
void replace(int go, int pos, int B[3][3], int R[3][3]);
void expand(int go, int pos);
void update(int pos, int good, int S[3][3], int T[3][3]);
void nextplayermove(int over, int pos, int good, int start, 
    int go, int R[3][3], int val, int B[3][3], int S[3][3]);
void GameOver(int over, int R[3][3], int B[3][3]);



int main (){

    int good = 0, //good checks if the move is valid or not
        go = 1, //go determines the player's turn (1 for P1 and 0 for P2)
        start = 1, //start determines if the game is ongoing
        over = 0, //over determines if the game is over
        found = 0, //found checks if the position is valid or not
        val = 0, //val is the number of turns... I think....
        pos = 0; //pos is the position that the player wants to claim
    int i, j;
    int R[3][3]; //R is player 1's positions/claimed spots
    int B[3][3]; //B is player 2's positions/claimed spots
    int M[3][3]; //M is the matrix of the game board (0 for empty, 1 for player 1, and 2 for player 2)
    int S[3][3]; //S is the set of all unclaimed spots on the board
    int F[3][3]; //F is the set of all claimed spots on the board
    int T[3][3]; //T is the set of all claimed spots that can be expanded from the current move

    printf("---GAME NAME---\n");

    for(i=0;i<3;i++){

        for(j=0;j<3;j++){
            printf("[ ] ");
            M[i][j]=2;
        }

        printf("\n");

    } //display the start of the game

    while (start == 1){
    } //main game here
    
    return 0;
}

void removepos(int go, int pos, int R[3][3], int B[3][3]){ 

    if(go == 1){ 
        R = R - pos;
    } else if (go == 0){ 
        B = B - pos;
    }
}

void replace(int go, int pos, int B[3][3], int R[3][3]){

    int found = 0;

    if(go == 1 && (pos<=B&&pos>0)){ 

        found = 1;
        
    } else if (go == 1 && (pos<=R&&pos>0)){ 

        found = 1;

    }

}

void expand(int go, int pos){
    int a;
    int b;
    int u;
    int d;
    int k;
    int r;

    a = (pos - 1) / 3;
    b = (pos - 1) % 3;
    u = (a - 1) * 3 + b + 1;
    d = (a + 1) * 3 + b + 1;
    k = a * 3 + (b - 1) + 1;
    r = a * 3 + (b + 1) + 1;

    removepos(go, pos);

    if(go >= 1){
        replace(go, u, 9);
    }
    else{
        replace(go, d, 9);
    }

    replace(go, k, 9);
    replace(go, r, 9);

    //I think you need to change go because go is a checker for the player's turn.
}

void update(int pos, int good, int S[3][3], int T[3][3]){

    good = 0;
    int found = 0;
    int i, j;
    int xpos, ypos;

    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            if(S[i][j] == pos){
                S[i][j] = 1;
                found = 1;
                xpos = i;
                ypos = j;
            }
        }
    }

    if (found != 1){
        S[xpos][ypos] = 1;
        good = 1;
    }

    if (good == 1 && found == 1){
  
        for(i=0;i<3;i++){
            for(j=0;j<3;j++){
                if(T[i][j] == pos){
                    T[i][j] = pos;
                }
            }
        }
        
        Expand(pos);
    }
}

void nextplayermove(int over, int pos, int good, int start, 
    int go, int R[3][3], int val, int B[3][3], int S[3][3]){

        int i, j;

        if (over == 0 && start == 1 && go == 1)
        {

           for(i=0;i<3;i++){
                for(j=0;j<3;j++){
                    if(R[i][j] == pos){
                        R[i][j] = 1;
                    }
                }
            }

        } else if (over == 0 && start == 1 && go == 0)
        {

           for(i=0;i<3;i++){
                for(j=0;j<3;j++){
                    if(B[i][j] == pos){
                        B[i][j] = 1;
                    }
                }
            }

        } else if (over == 0 && start == 1 && (go && pos )){

            update(pos, good, S);
            good = 1;

        } else if (start == 1 && R == 1 && B == 1)
        {
            start = 0;
            over = 1;

        } 
        
        if (over == 0 && good == 1)
        {
            good = 1;
            go = 1 - go; //switch player turn
            val++;
        } 
        
}

void GameOver(int over, int R[3][3], int B[3][3]){

    int i, j;
    int countR = 0;
    int countB = 0;
    over = 1;

    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            if(R[i][j] == 1){
                countR++;
            }
            if(B[i][j] == 1){
                countB++;
            }
        }
    }

    if(countR > countB){
        printf("Player 1 (R) wins!");
    } else if(countB > countR){
        printf("Player 2 (B) wins!");
    } else if(countR == countB){
        printf("It's a draw!");
    }
}
