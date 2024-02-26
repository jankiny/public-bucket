#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cursor.h"

char **cvas;    // Canvas
int a[4], b[4];    // save cooedinate
int emp[16];    // use to product number in empty position
int empty = 16;    // use to judge gameover

void init();    // initialization
char randN(int m);    // return 4 or 2, 'm' mean probability of '4'
void judge_empty();    //judge empty position
void product_number();    // product number in empty position
void play();    // game main logic
int line_empty(int r);    // whether empty

int main() {
    init();
    refresh();
    play();
}

// create a canvas, and draw line, product begining number
void init() {
    int i, j;
    int temp;

    // draw frame
    cvas = canvas(7, 15);    //need line x:2 4 6 y:4 8 12
    for(i = 1; i <= 7; i++) {
        for(j = 4; j <= 12; j += 4) {
            cursor_move(i, j);
            addch('|');
        }
    }
    for(i = 2; i <= 6; i += 2) {
        for(j = 1; j <= 15; j++) {
            cursor_move(i, j);
            addch('-');
        }
    }

    // associated digital coordinates
    for(temp = 0, i = 1; i <= 7; i += 2) {
        a[temp++] = i;
    }
    for(temp = 0, j = 3; j <= 15; j += 4) {
        b[temp++] = j;
    }

    judge_empty();
    product_number();
/* problem: if add this function, since of the time is too short,
            so, it would create two same numbers, like double 2 or 4.

    product_number();
*/
}

char randN(int m) {    // m% return 4
    int n;

    srand((unsigned)time(NULL));
    n = rand() % 100;
    if(n <= m) {
        return '4';
    }
    else
        return '2';
}

// judge empty pisition
void judge_empty() {
    int i, j;

    empty = 0;
    for(i = 0; i < 4; i++) {
        for(j = 0; j < 4; j++) {
            if(cvas[*(a+i)][*(b+j)] == ' ') {
                emp[i*4+j] = 0;
                empty++;
            }
        }
    }
}

void product_number() {
    int n;

    srand((int)time(NULL));
    do {
        n = rand() % 16;
    } while(emp[n]);    // if emp(n) is empty, out
/* degub code:  
    show_iarray(emp, 16);
    printf(" N:%d \n", n);   */
    cursor_move(*(a+n/4), *(b+n%4));
    addch(randN(50));    // 50 is probability
    emp[n] = 1;
    empty--;
}

void play() {
    int i, j;
    int m;
    char ch;

    while(1) {
        switch(ch=getch()) {
            case 97: 
            case 65: 
            case 27: 
                // left (testing)
                for(i = 0; i < 4; i++) {
/*  TODO
                    if(line_empty(i))
                        continue;
*/
                    for(j = 3; j > 0; j--) {
                        if(cvas[*(a+i)][*(b+j-1)] == ' ') {
                            m = j;
                            while(m < 4) {
                                cursor_move(*(a+i), *(b+m));
                                char_move(*(a+i), *(b+m-1));
                                m++;
                            }
                        }
                        else if(cvas[*(a+i)][*(b+j-1)] == cvas[*(a+i)][*(b+j)]) {
                            cursor_move(*(a+i), *(b+j));
                            char_move(*(a+i), *(b+j-1));
                            cvas[*(a+i)][*(b+j-1)] *= 2;
                        }
                        else if(cvas[*(a+i)][*(b+j-1)] != cvas[*(a+i)][*(b+j)])
                            continue;
                    }
                }
                judge_empty();
                product_number();
                refresh;
                printf("left finish \n");
                break;
            case 100: 
            case 68: 
            case 26: 
                // right
            case 119: 
            case 87: 
            case 24: 
                // up
            case 115: 
            case 83: 
            case 25: 
                // down
            default:
                break;
        }
    }
}

int line_empty(int r) {
    int i = 0;
    int sum = 0;

    while(4*r+i < 4) {
       sum += emp[r+i];
    }
    if(sum == 0)
        return 1;
    else
        return 0;
}
