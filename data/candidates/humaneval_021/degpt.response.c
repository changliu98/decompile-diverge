void func0(float *numbers,int size)

{
  int i_1;
  int i;
  float max;
  float min;
  int size_local;
  float *numbers_local;
  
  min = *numbers;
  max = *numbers;
  for (i = 1; i < size; i = i + 1) {
    if (numbers[i] < min) {
      min = numbers[i];
    }
    if (max < numbers[i]) {
      max = numbers[i];
    }
  }
  for (i_1 = 0; i_1 < size; i_1 = i_1 + 1) {
    numbers[i_1] = (numbers[i_1] - min) / (max - min);
  }
  return;
}