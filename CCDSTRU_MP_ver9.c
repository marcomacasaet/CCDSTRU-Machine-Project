/**
* Description : The machine project for CCICOMP.
* Author/s : Macasaet, Marco 12506532
*            Covar, Matteo 12504726
* Section : S06
* Last Modified : March 30, 2026
* Acknowledgments : CCPROG2 Course Notes and CCICOMP MP Specs
*/

#include <stdio.h>
#include <stdlib.h>
#define MOVES 20


//Adding function prototypes
void removepos(int go, int R[3][3], int B[3][3], int S[3][3], int T[3][3], int ycoord, int xcoord, int M[3][3]);
void replace(int go, int R[3][3], int B[3][3], int S[3][3], int T[3][3], int ycoord, int xcoord, int M[3][3]);
void expand(int go, int R[3][3], int B[3][3], int S[3][3], int T[3][3], int ycoord, int xcoord, int M[3][3]);
void update(int *go, int *good, int R[3][3], int S[3][3], int B[3][3], int T[3][3], int ycoord, int xcoord, int M[3][3]);
void nextplayermove(int *over, int pos, int *good, int *start, 
    int *go, int *val, int R[3][3], int B[3][3], int S[3][3], int T[3][3], int ycoord, int xcoord, int M[3][3]);
void GameOver(int *over, int start, int val, int R[3][3], int B[3][3]);

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
					{0, 0, 0}}; //S is the set of all touched spots on the board
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

    printf("==================LETTER BOMB===============\n");
	printf("~ Two players: Player 1 (R) and Player  2(B)\n");
	printf("~ Player 1 (R) starts\n");
	printf("~ Each player must alter a spot on the board to capture or expand their territory.\n");
	printf("~ If a player presses on a spot they marked,the letter explodes and causes a chain reaction across the board.\n");
	printf("~ The game ends when 3 spots are left, one player has no spots, or the game runs out of rounds.\n");
	printf("~ Keep in mind that each player cannot alter spots they have already marked in a previous turn\n\n");

	printf("====== ROUND 1 ======\n");
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
    		printf("\nTurn: Player 1 (R)\n");
		}
		else{
			printf("\nTurn: Player 2 (B)\n");
		}
		
		printf("Pick the x-coordinate of the cell you want to change: ");
		scanf("%d", &xcoord);
		printf("Pick the y-coordinate of the cell you want to change: ");
		scanf("%d", &ycoord);
		printf("\n");
		
		xcoord--;
		ycoord--;
		
		if(M[ycoord][xcoord] >= 1 && M[ycoord][xcoord] <= 9){
			pos = M[ycoord][xcoord];
			nextplayermove(&over, pos, &good, &start, &go, &val, R, B, S, T, ycoord, xcoord, M);
			
   		}
   		else{
   			printf("Please input a valid slot!\n");
		   }

		k = 0;
		printf("====== ROUND %d ======\n", counter+2);

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

/** Removes the player's (R or B) piece from that position in S and T.
* @param go indicates player move
* @param R[3][3] stores player 1's cells
* @param B[3][3] stores player 2's cells
* @param S[3][3] stores used cells
* @param T[3][3] stores free cells
* @param ycoord is the row coordinate
* @param xcoord is the col coordinate
* @param M[3][3] is a board for reference
* @pre ycoord and xcoord must be from 0-2
* @pre there must already be a piece in that slot
*/

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

/** Updates the ownership of a position based on the current player. This function can remove the position from the opponent, add it to the current player, and update tracking sets S, T, or expand.
* @param go indicates player move
* @param R[3][3] stores player 1's cells
* @param B[3][3] stores player 2's cells
* @param S[3][3] stores used cells
* @param T[3][3] stores free cells
* @param ycoord is the row coordinate
* @param xcoord is the col coordinate
* @param M[3][3] is a board for reference
* @pre ycoord and xcoord must be from 0-2
* @pre move must happen on a valid cell
*/

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

/** "Explodes" the piece (up, down, left, and right) depending on the position. This function removes the current position if it is occupied and applies Replace to the other positions.
* @param go indicates player move
* @param R[3][3] stores player 1's cells
* @param B[3][3] stores player 2's cells
* @param S[3][3] stores used cells
* @param T[3][3] stores free cells
* @param ycoord is the row coordinate
* @param xcoord is the col coordinate
* @param M[3][3] is a board for reference
* @pre selected pos must be already marked
* @pre ycoord and xcoord must be from 0-2
*/

void expand(int go, int R[3][3], int B[3][3], int S[3][3], int T[3][3], int ycoord, int xcoord, int M[3][3]){
    int a = 0; //ycoord
    int b = 0; //xcoord
	int x = 0; //new x coordinate
	int y = 0; //new y coordinate

    a = ycoord;
    b = xcoord;

	removepos(go, R, B, S, T, ycoord, xcoord, M);

	//u, d, k, r in the specs were implemented through these if, else statements
	if(go == 1 && a - 1 >= 0){
		y = a-1;
		x = b;
   		replace(go, R, B, S, T, y, x, M);
	} else if(go == 0 && a + 1 < 3){
		y = a+1;
		x = b;
   		replace(go, R, B, S, T, y, x, M);
	}
	
	if(b - 1 >= 0){
		y = a;
		x = b-1;
		replace(go, R, B, S, T, y, x, M);
	} else if(b + 1 < 3){
		y = a;
		x = b+1;
		replace(go, R, B, S, T, y, x, M);
	}

}

/** Updates tracking sets by adding the position to S if it is not already included, and possibly adding it to T and triggering an explosion if certain conditions are met.
* @param go indicates player move
* param good indicates if move is valid
* @param R[3][3] stores player 1's cells
* @param B[3][3] stores player 2's cells
* @param S[3][3] stores used cells
* @param T[3][3] stores free cells
* @param ycoord is the row coordinate
* @param xcoord is the col coordinate
* @param M[3][3] is a board for reference
* @pre ycoord and xcoord must be from 0-2
* @pre only called when a player selects an occupied cell
*/

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

/** Processes the player's move. This function deals with  placement, playing, switching turns, and incrementing the move counter.
* @param go indicates player move
* @param pos is the selected cell number
* @param good indicates if the move is valid	
* @param start indicates if game is starting
* @param val is turn counter
* @param R[3][3] stores player 1's cells
* @param B[3][3] stores player 2's cells
* @param S[3][3] stores used cells
* @param T[3][3] stores free cells
* @param ycoord is the row coordinate
* @param xcoord is the col coordinate
* @param M[3][3] is a board for reference
* @pre game must not be over
* @pre ycoord and xcoord must be from 0-2
* @pre pos must be from 1-9
*/

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
		printf("You captured Coordinate (%d,%d).\n\n", xcoord+1,ycoord+1);
	}
	else if((*over) == 0 && (*start) == 1 && (*go) == 0){
		B[ycoord][xcoord] = 1;
		S[ycoord][xcoord] = 1;
		(*good) = 1;
		printf("You captured Coordinate (%d,%d).\n\n", xcoord+1,ycoord+1);
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

			printf("You captured Coordinate (%d,%d).\n\n", xcoord+1,ycoord+1);
    	}
    	else if((rFound == 1 && (*go) == 1) || (bFound == 1 && (*go) == 0)){
			printf("Expanding from Coordinate (%d, %d).\n\n", xcoord+1,ycoord+1);
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

/** Determines the result of the game when it ends by comparing the sizes of sets R and B, or if the game reaches 20 turns.
* @param over indicates if the game is over
* @param start indicates if game is starting
* @param val is turn counter
* @param R[3][3] stores player 1's cells
* @param B[3][3] stores player 2's cells
* @pre val must be 20 
* @pre game conditions must be met
*/

void GameOver(int *over, int start, int val, int R[3][3], int B[3][3]){

    int i, j;
    int countR = 0;
    int countB = 0;
	int Final = 0;

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
* This is to certify that this project is our own work, based on our personal
* efforts in studying and applying the concepts learned. We have constructed the
* functions and their respective algorithms and corresponding code by ourselves.
* The program was run, tested, and debugged by our own efforts. We further certify
* that we have not copied in part or whole or otherwise plagiarized the work of
* other students or persons.
*
* Macasaet, Marco 12506532
* Covar, Matteo 12504726
*/