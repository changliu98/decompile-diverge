void find_min_diff(float *numbers, int size, float *out)
{
  float min_diff = 3.40282346638528859811704183484516925e+38F;
  int i; int j; int temp;
  out[0] = numbers[0];
  out[1] = numbers[1];
  for (i = 0; i < size; i++)
  {
    for (j = i + 1; j < size; j++)
    {
      if (min_diff > (float)fabs(numbers[i]-numbers[j]))
      {
        min_diff = (float)fabs(numbers[i]-numbers[j]);
        out[0] = numbers[i];
        out[1] = numbers[j];
      }
    }
  }
  if (out[0] > out[1])
  {
    temp = out[0];
    out[0] = out[1];
    out[1] = temp;
  }
}