int * func0(int *numbers,int size)

{
  int i;
  int max;
  int *out;
  int size_local;
  int *numbers_local;
  int *local_10;
  
  if (size < 1) {
    local_10 = (int *)0x0;
  }
  else {
    local_10 = malloc((long)size << 2);
    if (local_10 == (int *)0x0) {
      local_10 = (int *)0x0;
    }
    else {
      max = *numbers;
      for (i = 0; i < size; i = i + 1) {
        if (max < numbers[i]) {
          max = numbers[i];
        }
        local_10[i] = max;
      }
    }
  }
  return local_10;
}