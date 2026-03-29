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
void removepos(int go, int pos, int R[3][3], int B[3][3], int S[3][3], int T[3][3]);
void replace(int go, int pos, int R[3][3], int B[3][3], int S[3][3], int T[3][3]);
void expand(int go, int pos, int R[3][3], int B[3][3], int S[3][3], int T[3][3]);
void update(int *go, int pos, int good, int R[3][3], int S[3][3], int B[3][3], int T[3][3]);
void nextplayermove(int *over, int pos, int *good, int *start, 
    int *go, int *val, int R[3][3], int B[3][3], int S[3][3], int T[3][3], int ycoord, int xcoord);
void GameOver(int *over, int start, int val, int R[3][3], int B[3][3]);



int main (){

    int good = 0, //good checks if the move is valid or not
        go = 1, //go determines the player's turn (1 for P1 and 0 for P2)
        start = 1, //start determines if the game is starting
        over = 0, //over determines if the game is over
        found = 0, //found checks if the position is valid or not
        val = 0; //val is the number of turns... I think.... (update: yup that's what it means)
    int pos[3][3] = {{1, 2, 3},
					 {4, 5, 6},
					 {7, 8, 9}}; //pos is the position that the player wants to claim
	int xcoord = 0;
	int ycoord = 0;
    int cell = 0; //var for showing cells in the board
    int print = 0;
    int x = 0; //x axis of board
    int y = 0; //y axis of board
    int i, j, k;
	int choice = 0;
	int counter = 1;
	int ro = 0;
	int bo = 0;
	int Fcount = 9; //counts the free spots in F
    int R[3][3]; //R is player 1's positions/claimed spots
    int B[3][3]; //B is player 2's positions/claimed spots
    int S[3][3]; //S is the set of all touched? spots on the board
    int F[3][3]; //F is the set of all free spots on the board
    int T[3][3]; //T is the set of all claimed spots that can be expanded from the current move

    
    for(i = 0; i < 3; i++){
    	for(j = 0; j < 3; j++){
    		R[i][j] = 0;
    		B[i][j] = 0;
    		S[i][j] = 0;
    		T[i][j] = 0;
		}
	}

    printf("---CAPTURE GAME---\n");
	printf("   1 2 3 \n");

    for(i=0;i<3;i++){
		printf("%d ", i+1);
        for(j=0;j<3;j++){
			
            printf("[ ] ");
            F[i][j]=0;
        }

        printf("\n");

    } //display the start of the game

    while (Fcount == 3 || val<20 || start == 0 && ((ro>0&&bo==0)||(ro==0&&bo>0))){
    	
    	if(go == 1){
    		printf("\nPlayer 1 (R)\n");
		}
		else{
			printf("\nPlayer 2 (B)\n");
		}
		printf("Move: %d out of %d\n\n", counter, MOVES);

		printf("Pick the x-coordinate of the cell you want to capture: ");
		scanf("%d", &xcoord);
		printf("Pick the y-coordinate of the cell you want to capture: ");
		scanf("%d", &ycoord);
		printf("\n");
		printf("You are claming box %d", pos[ycoord][xcoord]);
		
		if(pos[ycoord][xcoord] >= 1 && pos[ycoord][xcoord] <= 9){
			printf("You are claming box %d", pos[ycoord][xcoord]);
			nextplayermove(&over, pos[ycoord][xcoord], &good, &start, &go, &val, R, B, S, T, ycoord, xcoord);			
   		}
   		else{
   			printf("Please input a valid slot!\n");
		   }

		k = 0;

		printf("   1  2  3\n");
		for(i=0;i<3;i++){
			printf("%d", i+1);
			for(j=0;j<3;j++){
				
				if(R[i][j]==pos[i][j]){
					printf("[R] ");
				} else if(B[i][j]==pos[i][j]){
					printf("[B] ");
				} else {
					printf("[ ] ");
				}
				
			}
			printf("\n");
		}

		//Free spots checking

		for(i=0;i<3;i++){
			for(j=0;j<3;j++){
				if(F[i][j]==1){
					Fcount++;
				}
				if(F[i][j]==2){
					Fcount++;
				}
			}
		}

		for(i=0;i<3;i++){
			for(j=0;j<3;j++){
				if(R[i][j]!=0){
					ro++;
				}

				if(B[i][j]!=0){
					bo++;
				}
			}
		}
		counter++;
	}

	printf("Final Score: \n\n");
	over = 1;
	GameOver(&over, start, val, R, B);
	system("pause");
    
    return 0;
}

void removepos(int go, int pos, int R[3][3], int B[3][3], int S[3][3], int T[3][3]){ 
//edited removepos since you can't subtract arrays (forgot abt it whoops)
int i = 0;
int j = 0;

	if (go == 1){ //P1
		for(i = 0; i < 3; i++){
			for(j = 0; j < 3; j++){
				if(R[i][j] == pos){
					R[i][j] = 0;
				}
			}
		}
	}
	else{  //P2
		for(i = 0; i < 3; i++){
			for(j = 0; j < 3; j++){
				if(B[i][j] == pos){
					B[i][j] = 0;
				}
			}
		}
	}
	
	for(i = 0; i < 3; i++){
		for(j = 0; j < 3; j++){
			if(S[i][j] == pos){
				S[i][j] = 0;
			}	
		}
	}
	
	for(i = 0; i < 3; i++){
		for(j = 0; j < 3; j++){
			if(T[i][j] == pos){
				T[i][j] = 0;
			}
		}
	}
	
}

void replace(int go, int pos, int R[3][3], int B[3][3], int S[3][3], int T[3][3]){

    int found = 0;
    int taken = 0;
    int i = 0;
    int j = 0;
    int inputted = 0;
    int containsS = 0;
    int containsT = 0;

	//i changed it so that it searches the whole matrix with the loop.
	
	//P1
	if(go == 1){
		for(i = 0; i < 3; i++){
			for(j = 0; j < 3; j++){
				if(B[i][j] == pos){
					B[i][j] = 0;
					found = 1;
					taken = 1;
				}
			}
		}
		for(i = 0; i < 3; i++){
			for(j = 0; j < 3; j++){
				if(R[i][j] == pos){
					found = 1;
				}
			}
		}
		if(found == 0){
			for(i = 0; i < 3 && inputted == 0; i++){
				for(j = 0; j < 3 && inputted == 0; j++){
					if(R[i][j] == 0){
						R[i][j] = pos;
						inputted = 1;
					}
				}
			}
		}
	}
	//P2
	else{
		for(i = 0; i < 3; i++){
			for(j = 0; j < 3; j++){
				if(R[i][j] == pos){
					R[i][j] = 0;
					found = 1;
					taken = 1;
				}
			}
		}
		for(i = 0; i < 3; i++){
			for(j = 0; j < 3; j++){
				if(B[i][j] == pos){
					found = 1;
				}
			}
		}
		if(found == 0){
			for(i = 0; i < 3 && inputted == 0; i++){
				for(j = 0; j < 3 && inputted == 0; j++){
					if(B[i][j] == 0){
						B[i][j] = pos;
						inputted = 1;
					}
				}
			}
		}
	}
	//for S
	for(i = 0; i < 3; i++){
		for(j = 0; j < 3; j++){
			if(S[i][j] == pos){
				containsS = 1;
			}
		}
	}
	if(taken == 1 && containsS == 0){
		inputted = 0;
		for(i = 0; i < 3 && inputted == 0; i++){
			for(j = 0; j < 3 && inputted == 0; j++){
				if(S[i][j] == 0){
					S[i][j] = pos;
					inputted = 1;
				}
			}
		}
	}
	//for T
	for(i = 0; i < 3; i++){
		for(j = 0; j < 3; j++){
			if(T[i][j] == pos){
				containsT = 1;
			}
		}
	}
	if(taken == 1 && containsS == 1 && containsT == 0){
		inputted = 0;
		for(i = 0; i < 3 && inputted == 0; i++){
			for(j = 0; j < 3 && inputted == 0; j++){
				if(T[i][j] == 0){
					T[i][j] = pos;
					inputted = 1;
				}
			}
		}
		expand(go, pos, R, B, S, T);
	}
	 	
}

void expand(int go, int pos, int R[3][3], int B[3][3], int S[3][3], int T[3][3]){
    int a = 0;
    int b = 0;
    int u = 0;
    int d = 0;
    int k = 0;
    int r = 0;

    a = (pos - 1) / 3;
    b = (pos - 1) % 3;
    
    //i moved initialization of u, d, k, and r so that it doesn't update if the values aren't within the boundary.

    removepos(go, pos, R, B, S, T);

	//changed the inputs of replace to fit the parameters of the function
	//also added checkers in case the input is above the boundary
    if(go == 1){ 
    	if(a - 1 >= 0){
    		u = (a - 1) * 3 + b + 1;
        	replace(go, u, R, B, S, T);
    	}
    }
    else{
    	if(a + 1 < 3){
    		d = (a + 1) * 3 + b + 1;
        	replace(go, d, R, B, S, T);
    	}
    }

	if(b - 1 >= 0){
		k = a * 3 + (b - 1) + 1;
		replace(go, k, R, B, S, T);
	}
	
	if(b + 1 < 3){
		r = a * 3 + (b + 1) + 1;
		replace(go, r, R, B, S, T);
	}

    //I think you need to change go because go is a checker for the player's turn.
    // go changes in the nextplayer function so i kept it the same in expand
}

void update(int *go, int pos, int good, int R[3][3], int S[3][3], int B[3][3], int T[3][3]){

    *good = 0;
    int i, j;
    int s = 0;
    int t = 0;
    int inputted = 0;

	//for S
	for(i = 0; i < 3; i++){
		for(j = 0; j < 3; j++){
			if(S[i][j] == pos){
				s = 1;
			}
		}
	}
	
	if(s == 0){
		for(i = 0; i < 3 && inputted == 0; i++){
			for(j = 0; j < 3 && inputted == 0; j++){
				if(S[i][j] == 0){
					S[i][j] = pos;
					inputted = 1;
				}
			}
		}
		*good = 1;
	}
	
	//for T
	for(i = 0; i < 3; i++){
		for(j = 0; j < 3; j++){
			if(T[i][j] == pos){
				t = 1;
			}
		}
	}
	
	if(t == 0 && *good == 0 && s == 1){
		inputted = 0;
		for(i = 0; i < 3 && inputted == 0; i++){
			for(j = 0; j < 3 && inputted == 0; j++){
				if(T[i][j] == 0){
					T[i][j] = pos;
					inputted = 1;
				}
			}
		}
		expand(go, pos, R, B, S, T);
	}
	
}

void nextplayermove(int *over, int pos, int *good, int *start, 
    int *go, int *val, int R[3][3], int B[3][3], int S[3][3], int T[3][3], int ycoord, int xcoord){

        int i = 0;
        int j = 0;
        int r = 0;
        int b = 0;
		int ro = 0;
		int bo = 0;

		printf("%d", pos);

		if((*over) == 1 && (*start) == 1 && (*go) == 1){
			R[ycoord][xcoord]=pos;
			S[ycoord][xcoord]=1;
			(*good) = 1;
		} else if((*over) == 1 && (*start) == 1 && (*go) == 0){
			B[ycoord][xcoord]=pos;
			S[ycoord][xcoord]=1;
			(*good) = 1;
		}

		//Is it in R or B?
		for(i=0;i<3;i++){
			for(j=0;j<3;j++){
				if(R[ycoord][xcoord]==pos){
					r++;
				}

				if(B[ycoord][xcoord]==pos){
					b++;
				}
			}
		}

		if((*over) == 0 && (*start) == 0 &&((r==1&&(*go)==1)||(b==1&&(*go)==0))){
			update((*go), pos, (*good), R, S, B, T);
		}

		//Is the game ongoing?
		for(i=0;i<3;i++){
			for(j=0;j<3;j++){
				if(R[i][j]!=0){
					ro++;
				}

				if(B[i][j]!=0){
					bo++;
				}
			}
		}

		if((*start) == 1 && ro == 1 && bo == 1){
			(*start) = 0;
		}

		if((*over) == 0 && (*good) == 0){
			(*good) = 1;
			if(*go == 1){
				(*go) = 0;
			} else if (*go == 0){
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
        	printf("Player 1 (R) wins!");
  	  } else if(countB > countR){
        printf("Player 2 (B) wins!");
  	  } else if(countR == countB){
  	      printf("It's a draw!");
  	  }			
	}


}
