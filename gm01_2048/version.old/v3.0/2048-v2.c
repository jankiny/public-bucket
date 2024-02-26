/* problem: 
 * game logic error. For example, have a line like 2 2 2 0, it will return 2 4 0 0 rather than 4 2 0 0.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cursor.h"

char **cvas;    // Canvas
int mat[4][4];

void init();    // initialization
void cvas_refresh();    // maping, and refresh
void map_mat();    // map matrix to canvas
void mat_to_canvas(int x, int y, int a, int b);
char itoc(int n);
int randN(int m);    // return 4 or 2, 'm' mean probability of '4'
int judge_empty();    //judge empty position
void product_number();    // product number in empty position
void play();    // game main logic
void game_over();    // game over

int main() {
    init();
    cvas_refresh();
    play();
}

// create a canvas, and draw line, product begining number
void init() {
    int i, j;

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

// matrix initialization
    for(i = 0; i < 4; i++)
        for(j = 0; j < 4; j++)
            mat[i][j] = 0;
    product_number();
}

void cvas_refresh() {
    int i, j;

    map_mat();
    refresh();
    if(mode == 2) {
        for(i = 0; i < 4; i++) { 
            for(j = 0; j < 4; j++)
                printf("%d ", mat[i][j]);
            printf(";");
        }
        printf("\n");
    }
}

void map_mat() {
    int i, j;
    int a, b;

    for(a = 0, i = 1; i <= 7; i += 2) {
        for(b = 0, j = 3; j <= 15; j += 4) {
            mat_to_canvas(i, j, a, b);
            b++;
        }
        a++;
    }
}

void mat_to_canvas(int x, int y, int a, int b) {
    int n, t;
    int i;

    i = 0;
    do {
        cursor_move(x, y-i);
        addch(' ');
        i++;
    } while(i < 3);

    if((n=mat[a][b]) == 0) {
        return;
    }
    else {
        i = 0;
        do {
            t = n % 10;
            cursor_move(x, y-i);
            addch(itoc(t));
            i++;
        } while(n /= 10);
    }
}

char itoc(int n) {
    return '0' + n;
}

int randN(int m) {    // m% return 4
    int n;

    srand((unsigned)time(NULL));
    n = rand() % 100;
    if(n <= m) {
        return 4;
    }
    else
        return 2;
}

void product_number() {
    int a, b;

    srand((int)time(NULL));
    do {
        a = rand() % 4;    // n = [0,16]
        b = rand() % 4;
    } while(mat[a][b]);    // if mat[a][b] == 0, out
    mat[a][b] = randN(50);
}

// judge empty pisition
int judge_empty() {
    int i, j;
    int empty;

    empty = 0;
    for(i = 0; i < 4; i++) {
        for(j = 0; j < 4; j++) {
            if(mat[i][j] == 0) {
                empty++;
            }
        }
    }
    return empty;
}

void play() {
    int i, j, m;
    char ch;
    int empty;
    int flag = 0;

    while(1) {
        switch(ch=getch()) {
            case 97: 
            case 65: 
                // left 
                if((empty=judge_empty()) == 0) {
                    game_over();
                }
                for(i = 0; i < 4; i++) {
                    for(j = 3; j > 0; j--) {
                        if(mat[i][j] != 0 && mat[i][j-1] == 0) {
                            m = j;
                            while(m < 4) {
                                if(mat[i][m] == 0)
                                    break;
                                mat[i][m-1] = mat[i][m];
                                mat[i][m] = 0;
                                m++;
                            }
                            flag = 1;
                        }
                        else if(mat[i][j] != 0 && mat[i][j] == mat[i][j-1]) {
                            mat[i][j-1] += mat[i][j];
                            mat[i][j] = 0;
                            flag = 1;
                        }
                        else if(mat[i][j] == 0 || mat[i][j] != mat[i][j-1]) {
                            continue;
                        }
                   }
                }
                if(flag) {
                    product_number();
                    flag = 0;
                }
                cvas_refresh();
                if(mode == 2)
                    printf("left finish \n");
                break;
            case 100: 
            case 68: 
                // right
                if((empty=judge_empty()) == 0) {
                    game_over();
                }
                for(i = 0; i < 4; i++) {
                    for(j = 0; j < 3; j++) {
                        if(mat[i][j] != 0 && mat[i][j+1] == 0) {
                            m = j;
                            while(m >= 0) {
                                if(mat[i][m] == 0)
                                    break;
                                mat[i][m+1] = mat[i][m];
                                mat[i][m] = 0;
                                m--;
                            }
                            flag = 1;
                        }
                        else if(mat[i][j] != 0 && mat[i][j] == mat[i][j+1]) {
                            mat[i][j+1] += mat[i][j];
                            mat[i][j] = 0;
                            flag = 1;
                        }
                        else if(mat[i][j] == 0 || mat[i][j] != mat[i][j+1]) {
                            continue;
                        }
                   }
                }
                if(flag) {
                    product_number();
                    flag = 0;
                }
                cvas_refresh();
                if(mode == 2)
                    printf("right finish \n");
                break;
            case 119: 
            case 87: 
                // up
                if((empty=judge_empty()) == 0) {
                    game_over();
                }
                for(j = 0; j < 4; j++) {
                    for(i = 3; i > 0; i--){
                        if(mat[i][j] != 0 && mat[i-1][j] == 0) {
                            m = i;
                            while(m < 4) {
                                if(mat[m][j] == 0)
                                    break;
                                mat[m-1][j] = mat[m][j];
                                mat[m][j] = 0;
                                m++;
                            }
                            flag = 1;
                        }
                        else if(mat[i][j] != 0 && mat[i][j] == mat[i-1][j]) {
                            mat[i-1][j] += mat[i][j];
                            mat[i][j] = 0;
                            flag = 1;
                        }
                        else if(mat[i][j] == 0 || mat[i][j] != mat[i-1][j]) {
                            continue;
                        }
                   }
                }
                if(flag) {
                    product_number();
                    flag = 0;
                }
                cvas_refresh();
                if(mode == 2)
                    printf("up finish \n");
                break;
            case 115: 
            case 83: 
                // down
                if((empty=judge_empty()) == 0) {
                    game_over();
                }
                for(j = 0; j < 4; j++) {
                    for(i = 0; i < 3; i++){
                        if(mat[i][j] != 0 && mat[i+1][j] == 0) {
                            m = i;
                            while(m >= 0) {
                                if(mat[m][j] == 0)
                                    break;
                                mat[m+1][j] = mat[m][j];
                                mat[m][j] = 0;
                                m--;
                            }
                            flag = 1;
                        }
                        else if(mat[i][j] != 0 && mat[i][j] == mat[i+1][j]) {
                            mat[i+1][j] += mat[i][j];
                            mat[i][j] = 0;
                            flag = 1;
                        }
                        else if(mat[i][j] == 0 || mat[i][j] != mat[i+1][j]) {
                            continue;
                        }
                   }
                }
                if(flag) {
                    product_number();
                    flag = 0;
                }
                cvas_refresh();
                if(mode == 2)
                    printf("down finish \n");
                break;
            default:
                break;
        }
    }
}

void game_over() {
    printf("Game Over! \n");
    exit(0);
}
