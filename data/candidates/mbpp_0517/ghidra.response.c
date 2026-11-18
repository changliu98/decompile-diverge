int func0(int *list1,int size)

{
  int i;
  int max;
  int size_local;
  int *list1_local;
  
  max = *list1;
  for (i = 0; i < size; i = i + 1) {
    if (max < list1[i]) {
      max = list1[i];
    }
  }
  return max;
}