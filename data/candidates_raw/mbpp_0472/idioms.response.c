int is_consecutive(int *array, int size){
  int i; int j;
  int *sorted = (int *)malloc(size * sizeof(int));
  for(i = 0; i < size; i++)
    sorted[i] = array[i];
  for(i = 0; i < size; i++)
    for(j = i + 1; j < size; j++)
      if(sorted[i] > sorted[j]){
        int temp = sorted[i];
        sorted[i] = sorted[j];
        sorted[j] = temp;
      }
  int result = 1;
  for(i = 1; i < size; i++)
    if(sorted[i] != sorted[i - 1] + 1){
      result = 0;
      break;
    }
  free(sorted);
  return result;
}