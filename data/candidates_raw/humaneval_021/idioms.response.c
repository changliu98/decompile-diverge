void normalize(float *numbers, int size)
{
  float min = numbers[0];
  float max = numbers[0];
  int i;
  for (i = 1; i < size; i++)
  {
    if (numbers[i] < min)
      min = numbers[i];
    if (numbers[i] > max)
      max = numbers[i];
  }
  for (i = 0; i < size; i++)
  {
    numbers[i] = (numbers[i] - min)/(max - min);
  }
}