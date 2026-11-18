void increasingArray(int *array)

{
  int i;
  int *array_local;
  
  for (i = 0; i < 0x10; i = i + 1) {
    array[i] = i;
  }
  return;
}