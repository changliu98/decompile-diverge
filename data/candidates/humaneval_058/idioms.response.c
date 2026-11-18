int *func0(int *a, int a_size, int *b, int b_size, int *out_size){
  int *out = (int *)malloc(a_size * sizeof(int));
  int i; int j; int k = 0;
  for(i = 0; i < a_size; i++){
    int exists_in_out = 0;
    for(j = 0; j < k; j++){
      if(out[j] == a[i]){
        exists_in_out = 1;
        break;
      }
    }
    if(!exists_in_out){
      for(j = 0; j < b_size; j++){
        if(a[i] == b[j]){
          out[k++] = a[i];
          break;
        }
      }
    }
  }
  for(i = 0; i < k - 1; i++){
    for(j = 0; j < k - i - 1; j++){
      if(out[j] > out[j + 1]){
        int temp = out[j];
        out[j] = out[j + 1];
        out[j + 1] = temp;
      }
    }
  }
  *out_size = k;
  return out;
}