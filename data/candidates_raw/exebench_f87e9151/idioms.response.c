void minarray(int *minindex, float *array, float value, int arlength)
{
  int i;
  float min; float min2;
  min = (array[*minindex] - value)*(array[*minindex] - value);
  *minindex = 0;
  for (i = 1; i < arlength; i++)
  {
    min2 = (array[i] - value)*(array[i] - value);
    if (min2 < min)
    {
      min = min2;
      *minindex = i;
    }
  }
}