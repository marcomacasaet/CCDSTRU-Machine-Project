#include <stdio.h>
#include <stdlib.h>

/* Version History

Version No. 1 by Marco on March 5, 2026

I added translated some of the statements into code.
I think we still need to figure out how to make this code actually work properly though.


*/

//Declaring R B S and T
//i think we can declare these after we finish our functions

//Adding function prototypes
void removepos(int go, int pos);
void replace(int go, int pos, int B);
void expand(int go, int pos);
void update();
void nextplayermove();
void GameOver();



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

    while (start == 1){  //i fixed the condition (used = instead of ==)
    } //main game here
    
    return 0;
}

void removepos(int go, int pos){  //i renamed this function bc C has a remove function apparently

    if(go == 1){  //(used = instead of ==)
        R = R - pos;
    } else if (go == 0){ //(used = instead of ==)
        B = B - pos;
    }
}

void replace(int go, int pos, int B){

    int found = 0;

    if(go == 1 && (pos<=B&&pos>0)){ //(used = instead of ==)

        found = 1;
        
    } else if (go == 1 && (pos<=R&&pos>0)){ //(used = instead of ==)

        found = 1;

    }

}

void expand(int go, int pos){ // worked on expand as well 
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

    //pls check if the logic is correct
}

void update(){
}

void nextplayermove(){
}

void GameOver(){
}
