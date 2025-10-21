#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int Ndata; 
	int *data; 
} array_t;


array_t arrayConstructor(int Ndata){
	array_t a; 
	a.Ndata = Ndata; 
	a.data = (int *) calloc(Ndata, sizeof(int));

	if(a.data == NULL){
		fprintf(stderr, "WARNING: arrayConstructor calloc failed\n");
	}
	return a;  
}

int arrayGet(array_t a, int n){

#if ARRAY_DEBUG==1
	if(n<0 || n>=a.Ndata){
    fprintf(stderr, "WARNING: arrayGet size %d array bounds error with index %d\n",
            a.Ndata, n);
    return 0;
  }

  if(a.data == NULL){
    fprintf(stderr, "WARNING: arrayGet request to access NULL array\n");
    return 0;
  }
#endif


  return a.data[n];
}

void arraySet(array_t a, int n, int val){

#if ARRAY_DEBUG==1
  if(n<0 || n>=a.Ndata){
    fprintf(stderr, "WARNING: arrayPut size %d array bounds error with index %d\n",
           a.Ndata, n);
    return;
  }

  if(a.data == NULL){
    fprintf(stderr, "WARNING: arrayPut request to access NULL array\n");
    return;
  }
#endif
  a.data[n] = val;
}


array_t arrayDestructor(array_t a){

  if(a.data == NULL){
    fprintf(stderr, "WARNING: arrayDestructor trying to destruct NULL array\n");
  }
  else{
    free(a.data);
  }

  // zero length of array            
  a.Ndata = 0;

  return a;
}

int main(int argc, char **argv){

  int Na = 5;

  /* build array */
  array_t a = arrayConstructor(Na);

  arraySet(a, 3,  1); /* a[3] = 1 */
  arraySet(a, 11, 2); /* a[11] = 2 will get WARNING*/

  int a3 = arrayGet(a, 3); /* set a3 = a[3] */

  /* destroy array */
  a = arrayDestructor(a);

  return 0;
}


