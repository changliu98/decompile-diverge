void merge(int *in, int size, int *out){
  int i;
  int j;
  int temp;
  int low;
  int high;
  int index;
  for(i = 0; i < size - 1; i++){
    for(j = i + 1; j < size; j++){
      if(in[i] > in[j]){
        temp = in[i];
        in[i] = in[j];
        in[j] = temp;
      }
    }
  }
  low = 0;
  high = size - 1;
  index = 0;
  while(low <= high){
    out[index++] = (low == high) ? in[low++] : in[low++];
    out[index++] = in[high--];
  }
}