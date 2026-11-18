float func0(float *numbers, int size)
{
 int i;
 float sum = 0;
 for (i = 0; i < size; i++)
  sum += numbers[i];
 float avg = sum / size;
 float msum = 0;
 for (i = 0; i < size; i++)
  msum += numbers[i] - avg;
 return msum / size;
}