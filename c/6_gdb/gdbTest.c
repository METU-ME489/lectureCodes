#include <stdlib.h>
#include <stdio.h>

float otherFunction(float a){
  float b = 3.2*a;
  return b;
}

float someFunction(float a){
  int b = 2*otherFunction(a);
  return b;
}

int main(int argc, char **argv){
  float a = 1.2;
  float b = someFunction(a);

  printf("a=%f, b=%f\n", a, b);
  return 0;
}
