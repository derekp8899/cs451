/*
Derek Popowski

derek.a.popowski@und.edu

CSCI 451 Operating systems I

hw



*/

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]){

  system("wget http://undcemcs01.und.edu/~ronald.marsh/CLASS/CS451/hw3-data.txt");
  //FILE* file = fopen("hw3-data.txt","r");
  int charCount = 0;
  char *Count = malloc(256);
  FILE *wc_pipe = popen("wc -c hw3-data.txt", "r");
  //fgets (Count,255,wc_pipe);
  fscanf(wc_pipe,"%d",&charCount);
  pclose(wc_pipe);
       //int i =  system("wc -c hw3-data.txt");
  printf("from counter: %d \n",charCount);
  char *buffer = malloc (charCount);
  int i;
  FILE *data = fopen("hw3-data.txt", "r");
  for (i = 0; i < charCount;i++){
    fscanf(data,"%c",&buffer[i]);
  }
  printf("\n%s\n",buffer);

}
