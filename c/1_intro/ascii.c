#include <stdio.h>
#include <stdlib.h>


// Define ascii printer
void asciiPrint(char *message){
  int n=0;
  while(1){ /* keep iterating the following code */
    printf("char %c => ascii %d\n", message[n], (int)message[n]);
    if(message[n]=='\0'){ break; } /* break if string terminator */
      n=n+1; /* increment counter */
  }
}

// Main function
int main(int argc, char **argv){
  asciiPrint("The quick brown fox Jumped over the lazy dog 5 times!");
  return 0;
}
