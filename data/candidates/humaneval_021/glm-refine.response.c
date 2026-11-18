void __cdecl func0(float *numbers, int size)
{
  if (size <= 0)
    return;

  float min = numbers[0];
  float max = numbers[0];

  // Find the minimum and maximum values in the array
  for (int i = 1; i < size; ++i)
  {
    if (numbers[i] < min)
      min = numbers[i];
    if (numbers[i] > max)
      max = numbers[i];
  }

  // Normalize the array values to a [0.0, 1.0] scale
  float range = max - min;
  for (int i = 0; i < size; ++i)
    numbers[i] = (numbers[i] - min) / range;
}