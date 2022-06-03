#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include "Resources/err.h"

#define TICK 100 /*milliseconds*/
#define ALIVE "\u2588"

int argCheck(char*);
int** allocMatrix(int, int);
void freeMatrix(int**, int);
int** getSeed(int**, char*, int, int);
int** newGen(int**, int, int);
int check(int**, int, int, int, int);
void print(int**, int, int, int);

int main(int argc, char *argv[]){
  int dimx;
  int dimy;
  int gen;
  int mode;
  int** grid;
  int i, j;

  if(argc<6){
    printerr("Insufficient number of arguments");
    return 1;
  } else {
    dimx = argCheck(argv[1]);
    dimy = argCheck(argv[2]);
    gen = argCheck(argv[4]);
    mode = argCheck(argv[5]);
  }
  
  grid = allocMatrix(dimx, dimy);
  if(grid){
    grid = getSeed(grid, argv[3], dimx, dimy);
    
    for(i=0; i<=gen || gen==0; i++){
      print(grid, i, dimx, dimy);
      if(mode==0)
        usleep(TICK * 1000);
      else
        getc(stdin);
      grid = newGen(grid, dimx, dimy); 
    }
  } else {
    printerr("No memory");
  }
  return 0;
}

int argCheck(char* a){
  int i;

  for(i=0; a[i]!='\0'; i++){
    if(!isdigit(a[i])){
      printerr("Invalid Argument(s)");
      exit(1);
    }
  }
  return atoi(a);

}

int** allocMatrix(int dimx, int dimy){
  int i, j;
  int **mat;

  mat = (int**)malloc(sizeof(int*)*dimy);
  for(i=0; i<dimy; i++){
    mat[i] = (int*)malloc(sizeof(int)*dimx);
  }
  
  return mat;
}

void freeMatrix(int** mat, int dimy){
  int i;

  for(i=0; i<dimy; i++){
    free(mat[i]);
  }
  free(mat);
}

int** getSeed(int** grid, char* filename, int dimx, int dimy){
  int i, j, k;
  FILE *in;
  int flag;

  in = fopen(filename, "r");
  if(in){

    for(i=0, flag=1; i<dimy && flag; i++){
      for(j=0; j<dimx && flag; j++){
        flag = fscanf(in, "%d", &grid[i][j]);
      }
    }
    fclose(in);
  } else {
    printerr("Could not open file");
  }
  
  return grid;
}

int** newGen(int** oldGen, int dimx, int dimy){
  int** mat;
  int i, j;

  mat = allocMatrix(dimx, dimy); 

  for(i=0; i<dimy; i++){
    for(j=0; j<dimx; j++){
      mat[i][j] = check(oldGen, j, i, dimx, dimy);
    }
  }

  freeMatrix(oldGen, dimy);

  return mat;
}

int check(int** oldGen, int x, int y, int dimx, int dimy){
  int i, j;
  int aliveN;
  int isAlive;
  
  /*PADDING*/
  if(x==0 || y==0 || x==dimx-1 || y==dimy-1){
    return 0;
  }

  isAlive=oldGen[y][x];
  
  for(i=-1, aliveN=0; i<=1; i++){
    for(j=-1;  j<=1; j++){
      if(!(i==0 && j==0)){
        if(oldGen[i+y][j+x]==1)
          aliveN++;
      }
    }
  }  

  if(!isAlive){
    if(aliveN==3)
      isAlive=1;
  } else {
    if(aliveN<2 || aliveN>3)
      isAlive=0;
  }

  return isAlive;
}

void print(int** grid, int currentGen, int dimx, int dimy){
  int i, j;

  printf("\e[1;1H\e[2J");
  printf("Current Generation: %d\n", currentGen);
  for(i=1; i<dimy-1; i++){
    for(j=1; j<dimx-1; j++){
      if(grid[i][j]==0){
        printf(" ");
      } else {
        printf("%s", ALIVE);
      }
    }
    printf("\n");
  }

}
