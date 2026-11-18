void getNums(int *numbers)

{
  int i;
  int *numbers_local;
  
  for (i = 0; i < 4; i = i + 1) {
    numbers[i] = i << 1;
  }
  return;
}