double func0(int *numbers,int size)

{
  int i;
  int total;
  int size_local;
  int *numbers_local;
  
  total = 0;
  for (i = 0; i < size; i = i + 1) {
    total = numbers[i] + total;
  }
  return (double)total / (double)size;
}