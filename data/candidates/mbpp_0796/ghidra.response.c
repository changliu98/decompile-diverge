int func0(int *dict,int size)

{
  int i;
  int sum;
  int size_local;
  int *dict_local;
  
  sum = 0;
  for (i = 0; i < size; i = i + 1) {
    sum = dict[i] + sum;
  }
  return sum;
}