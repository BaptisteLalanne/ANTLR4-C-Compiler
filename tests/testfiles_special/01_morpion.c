#include <stdio.h>

char displayPlayer(char coord, int player){
    putchar('P');
    putchar('l');
    putchar('a');
    putchar('y');
    putchar('e');
    putchar('r');
    putchar(' ');
    putchar(player + '0');
    putchar(':');
    putchar(' ');
    putchar('T');
    putchar('y');
    putchar('p');
    putchar('e');
    putchar(' ');
    putchar(coord);
    putchar(' ');
    putchar('c');
    putchar('o');
    putchar('o');
    putchar('r');
    putchar('d');
    putchar(10);
    char c = getchar();
    getchar();
    return c - '0';
}

void displayBoard(int top_left, int top, int top_right, int left, int middle, int right, int bottom_left, int bottom, int bottom_right){
    putchar('B');
    putchar('o');
    putchar('a');
    putchar('r');
    putchar('d');
    putchar(':');
    putchar(10);
    putchar(top_left);
    putchar('|');
    putchar(top);
    putchar('|');
    putchar(top_right);
    putchar(10);
    putchar('-');
    putchar('-');
    putchar('-');
    putchar('-');
    putchar('-');
    putchar(10);
    putchar(left);
    putchar('|');
    putchar(middle);
    putchar('|');
    putchar(right);
    putchar(10);
    putchar('-');
    putchar('-');
    putchar('-');
    putchar('-');
    putchar('-');
    putchar(10);
    putchar(bottom_left);
    putchar('|');
    putchar(bottom);
    putchar('|');
    putchar(bottom_right);
    putchar(10);
    putchar(10);
}

void displayInvalid(){
    putchar('I');
    putchar('n');
    putchar('v');
    putchar('a');
    putchar('l');
    putchar('i');
    putchar('d');
    putchar('!');
    putchar(10);
}

void win(int player){
    putchar('P');
    putchar('l');
    putchar('a');
    putchar('y');
    putchar('e');
    putchar('r');
    putchar(' ');
    putchar(player+'0');
    putchar(' ');
    putchar('w');
    putchar('i');
    putchar('n');
    putchar('s');
    putchar('!');
    putchar(10);
}

int main() {
    
    //board
    char top_left = '_';
    char top = '_';
    char top_right = '_';
    char left = '_';
    char middle = '_';
    char right = '_';
    char bottom_left = '_';
    char bottom = '_';
    char bottom_right = '_';

    int player = 0;

    int turn = 0;

    while(turn < 9){
        
        //get right symbole
        char symbole;
        if(player == 0){
            symbole = 'X';
        } else {
            symbole = 'O';
        }
        
        int valid = 0;
        
        while(!valid){

            displayBoard(top_left,top,top_right,left,middle,right,bottom_left,bottom,bottom_right);

            //choose coords
            int x = displayPlayer('x',player);
            int y = displayPlayer('y',player);
            
            
            if(x<1 || x>3 || y<1 || y>3){
                displayInvalid();
            }

            //apply
            if(x==1 & y==1){
                if(top_left != '_'){
                    displayInvalid();
                } else {
                    top_left = symbole;
                    valid = 1;
                }
            }
            if(x==2 & y==1){
                if(top != '_'){
                    displayInvalid();
                } else {
                    top = symbole;
                    valid = 1;
                }
            }
            if(x==3 & y==1){
                if(top_right != '_'){
                    displayInvalid();
                } else {
                    top_right = symbole;
                    valid = 1;
                }
            }
            if(x==1 & y==2){
                if(left != '_'){
                    displayInvalid();
                } else {
                    left = symbole;
                    valid = 1;
                }
            }
            if(x==2 & y==2){
                if(middle != '_'){
                    displayInvalid();
                } else {
                    middle = symbole;
                    valid = 1;
                }
            }
            if(x==3 & y==2){
                if(right != '_'){
                    displayInvalid();
                } else {
                    right = symbole;
                    valid = 1;
                }
            }
            if(x==1 & y==3){
                if(bottom_left != '_'){
                    displayInvalid();
                } else {
                    bottom_left = symbole;
                    valid = 1;
                }
            }
            if(x==2 & y==3){
                if(bottom != '_'){
                    displayInvalid();
                } else {
                    bottom = symbole;
                    valid = 1;
                }
            }
            if(x==3 & y==3){
                if(bottom_right != '_'){
                    displayInvalid();
                } else {
                    bottom_right = symbole;
                    valid = 1;
                }
            }
            
        }
        
        //win ?
        if(top_left!='_' & top_left==top & top==top_right){
            win(player);
            turn = 10;
        }
        if(left!='_' & left==middle & middle==right){
            win(player);
            turn = 10;
        }
        if(bottom_left!='_' & bottom_left==bottom & bottom==bottom_right){
            win(player);
            turn = 10;
        }
        if(top_left!='_' & top_left==left & left==bottom_left){
            win(player);
            turn = 10;
        }
        if(top!='_' & top==middle & middle==bottom){
            win(player);
            turn = 10;
        }
        if(top_right!='_' & top_right==right & right==bottom_right){
            win(player);
            turn = 10;
        }
        if(top_left!='_' & top_left==middle & middle==bottom_right){
            win(player);
            turn = 10;
        }
        if(top_right!='_' & top_right==middle & middle==bottom_left){
            win(player);
            turn = 10;
        }

        //change player
        player = player+1;
        if(player == 2){
            player = 0;
        }
    }
    
    //end
    putchar('E');
    putchar('n');
    putchar('d');
    putchar('!');
}