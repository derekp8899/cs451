/*
Derek Popowski

derek.a.popowski@und.edu

CSCI 451 - operating systems I

*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char* argv[]){
  int i = 0;
  system("touch output.txt");//create the output file
  system("printf ''>output.txt");//deletes all old data in the output file
  char* command = malloc(50);//create string buffer
  for(i = 1 ; i< argc; i++){//loop through all the commands
    strcpy(command, argv[i]);//grab the next command from arguments
    strcat(command,">>output.txt");//to send to the output file
    system(command); //run each command
    system("printf '\n\n'>>output.txt");//add whitespace between each command in outputfile
  }
  return 0;
}
