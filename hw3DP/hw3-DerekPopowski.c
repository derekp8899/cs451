/*
Derek Popowski

derek.a.popowski@und.edu

CSCI 451 Operating systems I

hw - 3 

9-17-18

compile command:
gcc hw3-DerekPopowski.c -o hw3 -lpthread

*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

struct searchArgs{//struct to pass arguements into the function run as threads

  int dataSize;
  char *search;
  char *data;

};

void *search(void *searchArgs);

int main(int argc, char* argv[]){

  system("wget -O hw3-data.txt http://undcemcs01.und.edu/~ronald.marsh/CLASS/CS451/hw3-data.txt");
  //wget the file overwrite if it exists

  int charCount = 0;

  FILE *wc_pipe = popen("wc -c hw3-data.txt", "r");//pipe to use wc for file size (number of characters)

  fscanf(wc_pipe,"%d",&charCount);//get the int value of number of characters
  pclose(wc_pipe);//close the pipe

  printf("from counter: %d \n",charCount);//verify character count
  char *buffer = malloc (charCount+1);//buffer to store the contents of the file + 1 for ending null terminator
  int i;//loop counter
  FILE *data = fopen("hw3-data.txt", "r");//open the data file for reading
  for (i = 0; i < charCount;i++){
    fscanf(data,"%c",&buffer[i]);//copy the file to the buffer 
    if(buffer[i]<91&&buffer[i]>64){//convert all upper case to lower case
      buffer[i] += 32;
    }
  }
  fclose(data);//close the input file
  buffer[charCount+1] = '\0';//null terminate the string
  //printf("\n%s\n",buffer);//debug print call to  print the buffer the verify the storage is correct
  pthread_t thrd1,thrd2;//create the two pthreads

  struct searchArgs search_Args,search_Args2;//create the two search arguments
  search_Args.dataSize = charCount;
  search_Args.data = buffer;
  search_Args.search = "polar";
  pthread_create(&thrd1,NULL, search, (void*)&search_Args);//start first search thread
  search_Args2 = search_Args;
  search_Args2.search = "easy";
  pthread_create(&thrd2,NULL, search, (void*)&search_Args2);//start second search thread
  pthread_join(thrd1,NULL);
  pthread_join(thrd2,NULL);//wait for both threads to finish

  free(buffer);//free the input data buffer
}

void *search(void *searchArgs){//to search the data from the input file for a given string
  struct searchArgs *search_Args = searchArgs;
  int dataSize = search_Args->dataSize;
  char *search = search_Args->search;
  char *data = search_Args->data;
  char *subStr=malloc(100);//sub string buffer
  int i,j = 0;//loop counters
  int wordCount = 0;
  for(i = 0; i < dataSize; i++){//to search the entire data from the file
    if(data[i] == ' '){//when encounter the end of a word
      subStr[j]='\0';//null term the sub string
      //printf("compairing %s with %s \n",search, subStr);//debugging print to check strcomps
      if(strcmp(subStr,search)==0){//compare with the desired search string
	wordCount++;
      }
      j=0;//reset the substring          
    }
    else{
      subStr[j] = data[i];//build the current word
      j++;      
    }
  }
  printf("count of %s in the file : %d\n", search,wordCount);//print the number of occurances found in the file
  free(subStr);//free the substring buffer
  return;
}
