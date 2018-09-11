/*
Derek Popowski

derek.a.popowski@und.edu

CSCI 451 Operating systems I

hw



*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int search(char *data,int dataSize,char *search);

int main(int argc, char* argv[]){

  system("wget http://undcemcs01.und.edu/~ronald.marsh/CLASS/CS451/hw3-data.txt");

  int charCount = 0;
  char *Count = malloc(256);
  FILE *wc_pipe = popen("wc -c hw3-data.txt", "r");//pipe to use wc for file size (number of characters)

  fscanf(wc_pipe,"%d",&charCount);//get the int value of number of characters
  pclose(wc_pipe);//close the pipe

  printf("from counter: %d \n",charCount);//verify character count
  char *buffer = malloc (charCount+1);//buffer to store the contents of the file + 1 for ending null terminator
  int i;//loop counter
  FILE *data = fopen("hw3-data.txt", "r");//open the data file for reading
  for (i = 0; i < charCount;i++){
    fscanf(data,"%c",&buffer[i]);//copy the file to the buffer 
  }
  buffer[charCount+1] = '\0';//null terminate the string
  printf("\n%s\n",buffer);//print the buffer the verify the storage is correct
  search(buffer,charCount,"polar");
  search(buffer, charCount,"easy");
  free(buffer);
}

int search(char *data, int dataSize, char *search){
  char *subStr=malloc(100);//sub string buffer
  int i,j = 0;//loop counters
  int wordCount = 0;
  for(i = 0; i < dataSize; i++){
    
    if(data[i] == ' '){
      subStr[j]='\0';//null term the sub string
      //printf("compairing %s with %s \n",search, subStr);
      if(strcmp(subStr,search)==0){

	wordCount++;
      }
      j=0;//reset the substring
      
    
    }
    else{
      subStr[j] = data[i];
      j++;
      
    }


  }
  printf("count of %s in the file : %d\n", search,wordCount);
  return wordCount;

}
