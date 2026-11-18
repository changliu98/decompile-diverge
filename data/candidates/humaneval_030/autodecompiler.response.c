float* func0(float *data, int size, int *newSize){
 float *cleaned = malloc(size*sizeof(float));
 *newSize = 0;
 int i=0;
 while(1){
  if(i >= size) break;
  if(data[i] > 0){
   cleaned[(*newSize)++] = data[i];
  }
  i++;
 }
 return cleaned;
}