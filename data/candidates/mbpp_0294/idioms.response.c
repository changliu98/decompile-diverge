int func0(int *list, int size){
  int max = -2147483648;
  int i = 0;
  for (i = 0; i < size; i++)
  {
    if (list[i] > max)
    {
      max = list[i];
    }
  }
  return max;
}