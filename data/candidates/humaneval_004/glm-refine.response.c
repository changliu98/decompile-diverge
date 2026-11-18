float __cdecl func0(float *numbers, int size)
{
  float sum = 0.0f;
  float msum = 0.0f;

  // Calculate the sum of the array
  for (int i = 0; i < size; ++i)
    sum += numbers[i];

  // Calculate the mean absolute deviation
  for (int i = 0; i < size; ++i)
  {
    float diff = numbers[i] - (sum / (float)size);
    msum += fabsf(diff);
  }

  return msum / (float)size;
}