#include <stdio.h>
#include <stdlib.h>

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
void update(int go, int pos, int *good, int R[3][3], int S[3][3], int B[3][3], int T[3][3]);
void nextplayermove(int *over, int pos, int *good, int *start, 
    int *go, int R[3][3], int *val, int B[3][3], int S[3][3], int T[3][3]);
void GameOver(int *over, int start, int val, int R[3][3], int B[3][3]);



int main (){

    int good = 0, //good checks if the move is valid or not
        go = 1, //go determines the player's turn (1 for P1 and 0 for P2)
        start = 1, //start determines if the game is ongoing
        over = 0, //over determines if the game is over
        found = 0, //found checks if the position is valid or not
        val = 0, //val is the number of turns... I think.... (update: yup that's what it means)
        pos = 0; //pos is the position that the player wants to claim
        int cell = 0; //var for showing cells in the board
        int print = 0;
        int x = 0; //x axis of board
        int y = 0; //y axis of board
    int i, j;
    int R[3][3]; //R is player 1's positions/claimed spots
    int B[3][3]; //B is player 2's positions/claimed spots
    int M[3][3]; //M is the matrix of the game board (0 for empty, 1 for player 1, and 2 for player 2)
    int S[3][3]; //S is the set of all unclaimed spots on the board
    int F[3][3]; //F is the set of all claimed spots on the board
    int T[3][3]; //T is the set of all claimed spots that can be expanded from the current move
    
    for(i = 0; i < 3; i++){
    	for(j = 0; j < 3; j++){
    		R[i][j] = 0;
    		B[i][j] = 0;
    		S[i][j] = 0;
    		T[i][j] = 0;
		}
	}

    printf("---GAME NAME---\n");

    for(i=0;i<3;i++){

        for(j=0;j<3;j++){
            printf("[ ] ");
            M[i][j]=2;
        }

        printf("\n");

    } //display the start of the game

    while (over == 0){
    	
    	if(go == 1){
    		printf("\nPlayer 1\n");
		}
		else{
			printf("\nPlayer 2\n");
		}
		printf("Where do you want to place?\n");
		printf("Slot: ");
		scanf("%d", &pos);
		printf("\n");
		
		if(pos >= 1 && pos <= 9){
			good = 0;
			nextplayermove(&over, pos, &good, &start, &go, R, &val, B, S, T);
			GameOver(&over, start, val, R, B);
		
			for(i = 0; i < 3; i++){
				for(j = 0; j < 3; j++){
					cell = i * 3 + j + 1;
					print = 0;
				
					for(x = 0; x < 3; x++){
						for(y = 0; y < 3; y++){
							if(R[x][y] == cell){
								printf("[R] ");
								print = 1;
							}
							if(B[x][y] == cell){
								printf("[B] ");
								print = 1;
							}
						}
					}
					if(print == 0){
						printf("[ ] ");
					}
				}
				printf("\n");
			}			
   		}
   		else{
   			printf("Please input a valid slot!\n");
		   }
	}
    
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

void update(int go, int pos, int *good, int R[3][3], int S[3][3], int B[3][3], int T[3][3]){

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
    int *go, int R[3][3], int *val, int B[3][3], int S[3][3], int T[3][3]){

        int i = 0;
        int j = 0;
        int r = 0;
        int b = 0;
        int rinc = 0;
        int binc = 0;
        int inputted = 0;
        
        for(i = 0; i < 3; i++){
        	for(j = 0; j < 3; j++){
        		if(R[i][j] == pos){
        			r = 1;
				}
				if(B[i][j] == pos){
					b = 1;
				}
			}
		}
		
		if(*over == 0 && *start && *go){
			inputted = 0;
			for(i = 0; i < 3 && inputted == 0; i++){
				for(j = 0; j < 3 && inputted == 0; j++){
					if(R[i][j] == 0){
						R[i][j] = pos;
						inputted = 1;
					}
				}
			}
			
			inputted = 0;
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
		else if(*over == 0 && *start && *go == 0){
			inputted = 0;
			for(i = 0; i < 3 && inputted == 0; i++){
				for(j = 0; j < 3 && inputted == 0; j++){
					if(B[i][j] == 0){
						B[i][j] = pos;
						inputted = 1;
					}
				}
			}
			
			inputted = 0;
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
		
		else if(*over == 0 && *start == 0 && ((*go && r) || (*go == 0 && b))){
			update(*go, pos, good, R, S, B, T);
		}
		
		if(*start == 1){
			rinc = 0;
			binc = 0;
			
			for(i = 0; i < 3; i++){
				for(j = 0; j < 3; j++){
					if(R[i][j] != 0){
						rinc++;
					}
					if(B[i][j] != 0){
						binc++;
					}
				}
			}
			if(rinc == 1 && binc == 1){
				*start = 0;
			}
		}		
		if(*over == 0 && *good){
			*good = !(*good);
			*go = !(*go);
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
