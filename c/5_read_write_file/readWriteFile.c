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


  array_t arrayRead(const char *fileName){

  array_t a;

  FILE *fp = fopen(fileName, "r");
  if(fp){
    char buffer[BUFSIZ];
    /* skip header line */
    fgets(buffer, BUFSIZ, fp);

    /* read next line */
    int Ndata;
    fgets(buffer, BUFSIZ, fp);
    sscanf(buffer, "%d", &Ndata);

    /* construct array */
    a = arrayConstructor(Ndata);

    /* skip header line */
    fgets(buffer, BUFSIZ, fp);

    /* read array entries */
    int n, m;
    for(n=0;n<a.Ndata;n=n+1){
      fscanf(fp, "%d", &m);
      arraySet(a, n, m); /* a[n] = m */
    }
    fclose(fp);
  }
  else{
    a = arrayConstructor(0);
  }
  return a;
}


void arrayWrite(const char *fileName, array_t a){

  FILE *fp = fopen(fileName, "w");

  if(fp){

    fprintf(fp, "<NUMBER OF ENTRIES IN ARRAY>\n");
    fprintf(fp, "%d\n", a.Ndata);

    fprintf(fp, "<ENTRIES IN ARRAY>\n");
    /* read array entries */
    int n, m;
    for(n=0;n<a.Ndata;n=n+1){
      int m = arrayGet(a, n); /* m = a[n] */
      fprintf(fp, "%d\n", m);
    }
    fclose(fp);
  }
  else{
    fprintf(stderr, "WARNING: failed to open %s to write\n", fileName);
  }
}





  int main(int argc, char **argv){

    // Create array
    int N=10; 
    array_t a = arrayConstructor(N); 
    for(int i=0; i<N; i++){
      arraySet(a, i, i*i*i); 
    }

    // Write array
    const char* filename="arrayData.dat"; 
    arrayWrite(filename, a); 

    array_t b = arrayRead(filename); 

    // Read array from file
    for(int i=0; i<N; i++){
      printf("a[%d] = %d\n", i, b.data[i]);
    }


    // Destruct errors
    arrayDestructor(a); 
    arrayDestructor(b); 
    
    return 0;
  }


