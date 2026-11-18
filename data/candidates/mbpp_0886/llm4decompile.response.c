double func0(int *numbers, int size)
{
 int total;
 int i;

 total = 0;
 for (i = 0; i < size; i++) {
  total += numbers[i];
 }

 return (double)total / size;
}