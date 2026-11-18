float func0(float *l, int size)
{
 int i, j;
 float median;

 for (i = 0; i < size; i++)
  for (j = i + 1; j < size; j++)
   if (l[j] < l[i]) {
    float tmp;
    tmp = l[i];
    l[i] = l[j];
    l[j] = tmp;
   }

 if (size % 2 == 1)
  median = l[size / 2];
 else
  median = (l[size / 2 - 1] + l[size / 2]) * 0.5;

 return median;
}