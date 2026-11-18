static float mean(float *numbers, int size)
{
  float sum = 0.0f;
  int i = 0;
  for (i = 0; i < size; i++)
    sum += numbers[i];
  float msum = 0.0f;
  for (i = 0; i < size; i++)
    msum += (numbers[i] - (sum / size)) * (numbers[i] - (sum / size));
  return msum / size;
}