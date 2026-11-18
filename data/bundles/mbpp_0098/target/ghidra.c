double func0(int *numbers,int size)

{
  int i;
  double total;
  int size_local;
  int *numbers_local;
  
  total = DAT_00102008;
  for (i = 0; i < size; i = i + 1) {
    total = (double)numbers[i] * total;
  }
  return total / (double)size;
}