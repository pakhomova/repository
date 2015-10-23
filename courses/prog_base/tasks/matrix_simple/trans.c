#include <stdio.h>
#include <stdlib.h>

void fillRand(int mat[4][4]) {
int i, j;
for ( i = 0; i < 4; i++ ) {
    for ( j = 0; j < 4; j++ ) {
      mat[i][j] = (rand()%1999 - 999);
        }
    }
}

void rotateCW180(int mat[4][4]) {
int i, j, mat1[4][4];
for ( i = 0; i < 4; i++ ) {
    for ( j = 0; j < 4; j++ ) {
      mat1[i][j] = mat[i][j];
        }
    }
for ( i = 0; i < 4; i++ ) {
    for ( j = 0; j < 4; j++ ) {
      mat[i][j] = mat1[3-i][3-j];
        }
    }
}

void flipH(int mat[4][4]) {
int i, j, mat1[4][4];
for ( i = 0; i < 4; i++ ) {
    for ( j = 0; j < 4; j++ ) {
      mat1[i][j] = mat[i][j];
        }
    }
for ( i = 0; i < 4; i++ ) {
    for ( j = 0; j < 4; j++ ) {
      mat[i][j] = mat1[i][3-j];
        }
    }
}

void transposSide(int mat[4][4]) {
int i, j, mat1[4][4];
for ( i = 0; i < 4; i++ ) {
    for ( j = 0; j < 4; j++ ) {
      mat1[i][j] = mat[i][j];
        }
    }
for ( i = 0; i < 4; i++ ) {
    for ( j = 0; j < 4; j++ ) {
      mat[i][j] = mat1[3-j][3-i];
        }
    }
}
