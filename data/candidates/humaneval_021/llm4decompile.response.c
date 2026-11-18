void func0(float *numbers, int size)
{
 int i;
 float max, min;

 max = numbers[0];
 min = numbers[0];

 for (i = 1; i < size; i++)
 {
  if (numbers[i] > max)
  {
   max = numbers[i];
  }

  if (numbers[i] < min)
  {
   min = numbers[i];
  }
 }

 for (i = 0; i < size; i++)
 {
  numbers[i] = (numbers[i] - min) / (max - min);
 }
}