double func0(int *array, int size){
 int i;
 double temp;
 int n_missing=0;

 for(i=0; i<size; i++){
  if(array[i] == 0)
   n_missing++;
 }

 temp = (double)n_missing / (double)size;
 temp = round(temp * 100) / 100;

 return temp;
}