#include <stdio.h>
#include <stdlib.h>

/* Version History

Version No. 1 by Marco on March 5, 2026

I added translated some of the statements into code.
I think we still need to figure out how to make this code actually work properly though.

*/

int main (){

    int good = 0, go = 1, start = 1, found = 0, val = 0;
    int i, j;
    int M[3][3];

    printf("---TIC-TAC-TOE---\n");

    for(i=0;i<3;i++){

        for(j=0;j<3;j++){
            printf("[ ] ");
            M[i][j]=2;
        }

        printf("\n");

    } //display the start of the game

    while (start = 1){
    } //main game here
    
    return 0;
}

void remove(int go, int pos){

    if(go=1){
        R = R - pos;
    } else if (go=0){
        B = B - pos;
    }
}

void replace(int go, int pos, int B){

    int found = 0;

    if(go = 1 && (pos<=B&&pos>0)){

        found = 1;
        
    } else if (go = 1 && (pos<=R&&pos>0)){

        found = 1;

    }

}

void expand(){
}

void update(){
}

void nextplayermove(){
}

void GameOver(){
}