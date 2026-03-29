/**
* Description : The machine project for CCPROG2.
* Author/s : Macasaet, Marco 12506532
*            Gaerlan, Marianne 12529133
* Section : S20B
* Last Modified : March 30, 2026
* Acknowledgments : CCPROG2 Course Notes
*/

#include <stdio.h>
#include <stdlib.h>
#define MOVES 20

/* Version History

Version No. 5 by Matteo on March 28, 2026

Just adjusted the functions some more.
Also adjusted the function prototypes.
Incorporated main loop too.

*/

//Declaring R B S and T
//i think we can declare these after we finish our functions

//Adding function prototypes
void removepos(int go, int R[3][3], int B[3][3], int S[3][3], int T[3][3], int ycoord, int xcoord, int M[3][3]);
void replace(int go, int R[3][3], int B[3][3], int S[3][3], int T[3][3], int ycoord, int xcoord, int M[3][3]);
void expand(int go, int R[3][3], int B[3][3], int S[3][3], int T[3][3], int ycoord, int xcoord, int M[3][3]);
void update(int *go, int *good, int R[3][3], int S[3][3], int B[3][3], int T[3][3], int ycoord, int xcoord, int M[3][3]);
void nextplayermove(int *over, int pos, int *good, int *start, 
    int *go, int *val, int R[3][3], int B[3][3], int S[3][3], int T[3][3], int ycoord, int xcoord, int M[3][3]);
void GameOver(int *over, int start, int val, int R[3][3], int B[3][3]);

/**
* randVal produces a random value
* @param max highest possible value
* @param min lowest possible value
* 
* @return random value based on the parameters
* @pre max and min are the limits for the function to guess a value within.
*
*/

int main (){

    int good = 0, //good checks if the move is valid or not
        go = 1, //go determines the player's turn (1 for P1 and 0 for P2)
        start = 1, //start determines if the game is starting
        over = 0, //over determines if the game is over
        found = 0, //found checks if the position is valid or not
        val = 0; //val is the number of turns... I think.... (update: yup that's what it means)
    int M[3][3] =  {{1, 2, 3},
					{4, 5, 6},
					{7, 8, 9}}; //M is the matrix;
	int pos = -1; //is the position the player wants to take
	int fCount = 0; //count variable for F
	int xcoord = 0; //x-coordinate for pos
	int ycoord = 0; //y-coordinate for pos
    int cell = 0; //var for showing cells in the board
    int print = 0;
    int x = 0; //x axis of board
    int y = 0; //y axis of board
    int i, j, k;
	int choice = 0; 
	int counter = 0; //displays the turn number
	int rCount = 0; //count variable for R
	int bCount = 0; //count variable for R
    int R[3][3] =  {{0, 0, 0},
					{0, 0, 0},
					{0, 0, 0}}; //R is player 1's positions/claimed spots
    int B[3][3] =  {{0, 0, 0},
					{0, 0, 0},
					{0, 0, 0}}; //B is player 2's positions/claimed spots
    int S[3][3] =  {{0, 0, 0},
					{0, 0, 0},
					{0, 0, 0}}; //S is the set of all touched? spots on the board
    int F =  9; //F is the set of all free spots on the board
    int T[3][3] =  {{0, 0, 0},
					{0, 0, 0},
					{0, 0, 0}}; //T is the set of all claimed spots that can be expanded from the current move

    
    for(i = 0; i < 3; i++){
    	for(j = 0; j < 3; j++){
    		R[i][j] = 0;
    		B[i][j] = 0;
    		S[i][j] = 0;
    		T[i][j] = 0;
		}
	}

    printf("---CAPTURE GAME---\n");
	printf("   1   2   3 \n");

    for(i=0;i<3;i++){
		printf("%d ", i+1);
        for(j=0;j<3;j++){
            printf("[ ] ");
        }

        printf("\n");

    } //display the start of the game

    while (over == 0){
    	
    	if(go == 1){
    		printf("\nPlayer 1 (R)\n");
		}
		else{
			printf("\nPlayer 2 (B)\n");
		}
		printf("====== TURN %d ======\n\n", counter);

		printf("Pick the x-coordinate of the cell you want to capture: ");
		scanf("%d", &xcoord);
		printf("Pick the y-coordinate of the cell you want to capture: ");
		scanf("%d", &ycoord);
		printf("\n");
		
		xcoord--;
		ycoord--;
		
		if(M[ycoord][xcoord] >= 1 && M[ycoord][xcoord] <= 9){
			printf("You are claming box %d\n", M[ycoord][xcoord]);
			pos = M[ycoord][xcoord];
			nextplayermove(&over, pos, &good, &start, &go, &val, R, B, S, T, ycoord, xcoord, M);			
   		}
   		else{
   			printf("Please input a valid slot!\n");
		   }

		k = 0;

		printf("   1  2  3\n");
		for(i=0;i<3;i++){
			printf("%d", i+1);
			for(j=0;j<3;j++){
				
				if(R[i][j]==1){
					printf("[R] ");
				} else if(B[i][j]==1){
					printf("[B] ");
				} else {
					printf("[ ] ");
				}
				
			}
			printf("\n");
		}

		//Free spots checking
		fCount = F;
		rCount = 0;
		bCount = 0;
		

		for(i=0;i<3;i++){
			for(j=0;j<3;j++){
				if(R[i][j]!=0){
					rCount++;
				}

				if(B[i][j]!=0){
					bCount++;
				}
			}
		}

		fCount = F - (rCount+bCount);

		if(fCount == 3 || val >= MOVES || (start == 0 && ((rCount>0&&bCount==0)||(rCount==0&&bCount>0)))){
			over = 1;
			printf("=== FINAL SCORE ===\n");
			printf("Player 1 (R): %d\n", rCount);
			printf("Player 2 (B): %d\n", bCount);
			GameOver(&over, start, val, R, B);
		}

		counter++;
	}

	system("pause");
    
    return 0;
}

void removepos(int go, int R[3][3], int B[3][3], int S[3][3], int T[3][3], int ycoord, int xcoord, int M[3][3]){ 

	int i = 0;
	int j = 0;

	if (go == 1){ //P1
		R[ycoord][xcoord] = 0;
	}
	else{  //P2
		B[ycoord][xcoord] = 0;
	}
		S[ycoord][xcoord] = 0;

		T[ycoord][xcoord] = 0;
	
}

void replace(int go, int R[3][3], int B[3][3], int S[3][3], int T[3][3], int ycoord, int xcoord, int M[3][3]){

    int found = 0;

	
	if(go == 1){
		// Player 1 Processing/Checking
	if(B[ycoord][xcoord] == 1){
			B[ycoord][xcoord] = 0;
			found = 1;
		}
	if(R[ycoord][xcoord] == 1){
			found = 1;
		}
	if(R[ycoord][xcoord] == 0){
			R[ycoord][xcoord] = 1;
		}
	} else {
		// Player 2 Processing/Checking
	if(R[ycoord][xcoord] == 1){
			R[ycoord][xcoord] = 0;
			found = 1;
		}

	
	if(B[ycoord][xcoord] == 1){
			found = 1;
		}


	if(B[ycoord][xcoord] == 0){
			B[ycoord][xcoord] = 1;
		}
	}	
	

	//Results of Player Processing/Checking
	if(found == 1 && S[ycoord][xcoord] == 0){
			S[ycoord][xcoord] = 1;
			found = 0;
		} else if(found == 1 && S[ycoord][xcoord] == 1 && T[ycoord][xcoord] == 0){
			T[ycoord][xcoord] = 1;
			expand(go, R, B, S, T, ycoord, xcoord, M);
		}
	
}	 	

/**
* This function is gonna expand the player's territory by replacing empty cells adjacent to the player's current position.
* @param max highest possible value
* @param min lowest possible value
* 
* @return random value based on the parameters
* @pre max and min are the limits for the function to guess a value within.
*
*/

void expand(int go, int R[3][3], int B[3][3], int S[3][3], int T[3][3], int ycoord, int xcoord, int M[3][3]){
    int a = 0; //ycoord
    int b = 0; //xcoord
	int x = 0; //new x coordinate
	int y = 0; //new y coordinate
    int u; //above
    int d; //below
    int k; //left
    int r; //right

    a = ycoord;
    b = xcoord;

	//maybe change y and x to a and b values and alter those ones before calling and passing replace()

	removepos(go, R, B, S, T, ycoord, xcoord, M);

	if(go == 1 && a - 1 >= 0){
		y = a-1;
		x = b;
		u = M[x][y];
   		replace(go, R, B, S, T, y, x, M);
	} else if(go == 0 && a + 1 < 3){
		y = a+1;
		x = b;
		d = M[x][y];
   		replace(go, R, B, S, T, y, x, M);
	}

	if(b - 1 >= 0){
		y = a;
		x = b-1;
		k = M[x][y];
		replace(go, R, B, S, T, y, x, M);
	} else if(b + 1 < 3){
		y = a;
		x = b+1;
		r = M[x][y];
		replace(go, R, B, S, T, y, x, M);
	}

}

void update(int *go, int *good, int R[3][3], int S[3][3], int B[3][3], int T[3][3], int ycoord, int xcoord, int M[3][3]){

    int i, j;
    int sFound = 0;
    int tFound = 0;

	(*good) = 0;

	if(S[ycoord][xcoord] == 1){
			sFound = 1;
		}

	if(T[ycoord][xcoord] == 1){
		 tFound = 1;
		}

	if(sFound == 0){
		S[ycoord][xcoord] = 1;
		(*good)=!(*good);
	} else if((*good) == 0 && sFound == 1 && tFound == 0){
		T[ycoord][xcoord] = 1;
		expand(*go, R, B, S, T, ycoord, xcoord, M);
	}
}

void nextplayermove(int *over, int pos, int *good, int *start, 
    int *go, int *val, int R[3][3], int B[3][3], int S[3][3], int T[3][3], int ycoord, int xcoord, int M[3][3]){

    int i = 0;
    int j = 0;
    int rFound = 0;
    int bFound = 0;
	int rCount = 0;
	int bCount = 0;


	if((*over) == 0 && (*start) == 1 && (*go) == 1){
		R[ycoord][xcoord] = 1;
		S[ycoord][xcoord] = 1;
		(*good) = 1;
	}
	else if((*over) == 0 && (*start) == 1 && (*go) == 0){
		B[ycoord][xcoord] = 1;
		S[ycoord][xcoord] = 1;
		(*good) = 1;
	}

	if(R[ycoord][xcoord] == 1){
		rFound = 1;
		}
	if(B[ycoord][xcoord] == 1){
		bFound = 1;
		}

	if((*over) == 0 && (*start) == 0){
	
    	if(rFound == 0 && bFound == 0){
        	if(*go == 1){
            	R[ycoord][xcoord] = 1;
        	}
        	else{
           	 B[ycoord][xcoord] = 1;
        	}

        	S[ycoord][xcoord] = 1;
        	(*good) = 1;
    	}
    	else if((rFound == 1 && (*go) == 1) || (bFound == 1 && (*go) == 0)){
       	 update(go, good, R, S, B, T, ycoord, xcoord, M);
    	}

	}		

	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if(R[i][j] != 0){
				rCount++;
			}
			if(B[i][j] != 0){
				bCount++;
			}
		}
	}

	if((*start) == 1 && rCount == 1 && bCount == 1){
		(*start) = 0;
	}

	if((*over) == 0 && (*good) == 1){
		(*good) = !(*good);
		if(*go == 1){
			(*go) = 0;
		}
		else if(*go == 0){
			(*go) = 1;
		}
		(*val)++;
	}
}


void GameOver(int *over, int start, int val, int R[3][3], int B[3][3]){

    int i, j;
    int countR = 0;
    int countB = 0;
	int Final = 0;
//just tweaked gameover so that it doesn't force game to end and checks is over is 1. also put the printf inside the if statement.

		for(i = 0; i < 3; i++){
			for(j = 0; j < 3; j++){
				if(R[i][j] != 0){
					countR++;
				}
			}
		}
		
		for(i = 0; i < 3; i++){
			for(j = 0; j < 3; j++){
				if(B[i][j] != 0){
					countB++;
				}
			}
		}
		
		Final = 9 - (countR + countB);

		if(Final == 3 || val >= 20 || (!start && ((countR > 0 && countB == 0) || (countR == 0 && countB > 0)))){
			*over = 1;
				}
	if(*over == 1){
    	if(countR > countB){
        	printf("Player 1 (R) wins!\n");
  	  } else if(countB > countR){
        printf("Player 2 (B) wins!\n");
  	  } else if(countR == countB){
  	      printf("It's a draw!\n");
  	  }			
	}


}

/**
* This is to certify that this project is my/our own work, based on my/our personal
* efforts in studying and applying the concepts learned. I/We have constructed the
* functions and their respective algorithms and corresponding code by myself/ourselves.
* The program was run, tested, and debugged by my/our own efforts. I/We further certify
* that I/we have not copied in part or whole or otherwise plagiarized the work of
* other students and/or persons.
*
* Macasaet, Marco 12506532
* Gaerlan, Marianne 12529133
*/